#include "define.h"

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
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if( !ResetDevice(WINSIZE_X, WINSIZE_Y) )
		return false;

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

		m_pDevice->EndScene();
	}

	m_pDevice->Present(0,0,0,0);
						
}

void cMainGame::Release()
{

}
