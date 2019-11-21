#include "defines.h"

cMainGame::cMainGame(void)
{
	m_pDevice = 0;
	m_pD3D = 0;
}

cMainGame::~cMainGame(void)
{
	
}

bool cMainGame::Init()
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION );

	if( !ResetDevice(WINSIZE_X, WINSIZE_Y) )
		return false;

	MakeVB();

	SetRenderState();

	return true;
}

bool cMainGame::ResetDevice( int width, int height )
{
	if( m_pD3D == 0 )
		return false;

	D3DPRESENT_PARAMETERS	d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));

	d3dpp.Windowed = true;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	m_pD3D->CreateDevice( 
					D3DADAPTER_DEFAULT,		//0�� ( �⺻ ) �׷��� ī�带 ����ϰڴ�
					D3DDEVTYPE_HAL,		//�ϵ���� ������ ����ϰڴ�
					g_hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &m_pDevice);



	return true;
}
void cMainGame::SetRenderState()
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);

}

void cMainGame::Update()
{
	m_pDevice->Clear( 0, 0,	// ������ 0
					D3DCLEAR_TARGET,//���� ���� ���̴°� ������
					D3DCOLOR_XRGB(2, 95, 209),
					1.f,	//zbuffer��1 �� ������
					0.f); // ���ٽ� ���۸� 0���� ������

	if( SUCCEEDED( m_pDevice->BeginScene() ))
	{
		//���⼭ �׸���!!!

		m_pDevice->SetStreamSource( 0, m_pVB, 0, 
			sizeof(SVertex)//���ؽ� ���� �Ѱ��� ���� ũ��
			);
		m_pDevice->SetFVF(D3DFVF_CUSTOMVERTEX);

		/*
		D3DPT_POINTLIST             = 1,
		D3DPT_LINELIST              = 2,
		D3DPT_LINESTRIP             = 3,
		D3DPT_TRIANGLELIST          = 4,
		D3DPT_TRIANGLESTRIP         = 5,
		D3DPT_TRIANGLEFAN           = 6,
		*/
		m_pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1);

		m_pDevice->EndScene();
	}

	m_pDevice->Present(0,0,0,0);
						
}


void cMainGame::MakeVB()
{
	//LPDIRECT3DVERTEXBUFFER9	
	SVertex	sVertex[3] = 
	{
		{ 1.f, -1.f, 0.f, 0xffff0000 },
		{-1.f, -1.f, 0.f, 0xffff0000 },
		{ 0.f,  1.f, 0.f, 0xffff0000 },
	};

	/*
	struct SVertex
	{
	float	x,y,z;
	DWORD	color;
	};

	#define D3DFVF_CUSTOMVERTEX			D3DFVF_XYZ | D3DFVF_DIFFUSE
	*/
	m_pDevice->CreateVertexBuffer(
				sizeof(SVertex) * 3,	//��ü ���ؽ� ������ ũ��
				0,
				D3DFVF_CUSTOMVERTEX,
				D3DPOOL_MANAGED,
				&m_pVB, 0);
	void* pData = NULL;
	m_pVB->Lock(
		0,	// ��𿡼����� �����ɲ���
		sizeof(SVertex) * 3,	//������ �����ɰų�
		&pData,
		0 );

	memcpy(pData, sVertex, sizeof(SVertex) * 3 );
	m_pVB->Unlock();
}

void cMainGame::Release()
{
	SAFE_RELEASE(m_pDevice)
	SAFE_RELEASE(m_pD3D)
}
