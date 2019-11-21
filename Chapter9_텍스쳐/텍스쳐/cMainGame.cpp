#include "defines.h"
#include "cMainGame.h"

cMainGame::cMainGame(void)
{
	m_pDevice = 0;
	m_pD3D = 0;

	D3DXMatrixIdentity(&m_mTexTM);
}

cMainGame::~cMainGame(void)
{

}

bool cMainGame::Init()
{
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION );

	if( !ResetDevice(WINSIZE_X, WINSIZE_Y) )
		return false;


	m_cAxis.Init(m_pDevice );
	m_cGrid.Init(m_pDevice, 50, 50,  1, 0xff808080 );

	return true;
}

void cMainGame::InitCamera()
{
	m_vEye	= D3DXVECTOR3( 0, 0, -10);
	m_vLook	= D3DXVECTOR3( 0, 0, 0);
	D3DXVECTOR3 vUp		= D3DXVECTOR3( 0, 1, 0);	

	D3DXMATRIX	mCam;

	D3DXMatrixLookAtLH( &mCam, &m_vEye, &m_vLook, &vUp );

	// 디바이스에다가 특정 오브젝트의 행렬을 셋팅한다
	// 카메라 행렬을 디바이스에 전달한다
	m_pDevice->SetTransform( D3DTS_VIEW, &mCam );

	D3DXMATRIX mProj;

	D3DXMatrixPerspectiveFovLH( &mProj, 
								D3DXToRadian(53.8f),//시야각(FOV)
								m_nResoultionX / m_nResoultionY,	//화면 비율
								0.1f, //근평면 거리
								1000.f ); // 원평면

	// 디바이스에 전달
	m_pDevice->SetTransform( D3DTS_PROJECTION, &mProj );
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
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.EnableAutoDepthStencil = true;

	if( m_pDevice == 0)
	{
		m_pD3D->CreateDevice( 
					D3DADAPTER_DEFAULT,		//0번 ( 기본 ) 그래픽 카드를 사용하겠다
					D3DDEVTYPE_HAL,		//하드웨어 가속을 사용하겠다
					g_hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &m_pDevice);
	}
	else
	{
		m_pDevice->Reset(&d3dpp);
	}


	m_nResoultionX = width;
	m_nResoultionY = height;
	m_sBackupD3dpp = d3dpp;

	ResetWindow();
	SetRenderState();
	InitCamera();
	InitVB();
	LoadTexture();
	return true;
}

void cMainGame::LoadTexture()
{
	//D3DXCreateTexture(
	//D3DXCreateTexture
	D3DXCreateTextureFromFile( m_pDevice, "./Data/nayeon.jpg", &m_pTexture );
	//D3DXCreateTextureFromFileInMemory

}

void cMainGame::InitVB()
{
	SVertex	sVertex[6] = 
	{
		{D3DXVECTOR3(-1, 2, 0), D3DXVECTOR3(0,0,-1), 0, 0 },	//LT
		{D3DXVECTOR3( 1, 2, 0), D3DXVECTOR3(0,0,-1), 1, 0 },	//RT
		{D3DXVECTOR3(-1, 0, 0), D3DXVECTOR3(0,0,-1), 0, 1 },	//LB

		{D3DXVECTOR3(-1, 0, 0), D3DXVECTOR3(0,0,-1), 0, 1 },	//LB
		{D3DXVECTOR3( 1, 2, 0), D3DXVECTOR3(0,0,-1), 1, 0 },	//RT
		{D3DXVECTOR3( 1, 0, 0), D3DXVECTOR3(0,0,-1), 1, 1 },	//RB
	};

	m_pDevice->CreateVertexBuffer( sizeof( SVertex) * 6,
		0, SVertex::CUSTOM_FVF, D3DPOOL_MANAGED, &m_pVB, 0);


	void* pData = NULL;

	m_pVB->Lock(0, sizeof(SVertex) * 6, &pData, 0);

	memcpy( pData, sVertex, sizeof(SVertex)* 6 );

	m_pVB->Unlock();
}

void cMainGame::SetRenderState()
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE );
}


void cMainGame::ResetWindow()
{
	DWORD	dwStyle		= GetWindowLong( g_hWnd, GWL_STYLE);
	DWORD	dwExStyle	= GetWindowLong( g_hWnd, GWL_EXSTYLE);	 

	RECT rc;
	GetWindowRect(g_hWnd, &rc);

	
	RECT rcNew;
	SetRect(&rcNew, 0,0, m_nResoultionX, m_nResoultionY );

	AdjustWindowRectEx(&rcNew, dwStyle, false, dwExStyle );

	int newWidth  = rcNew.right - rcNew.left;
	int newHeight = rcNew.bottom - rcNew.top;

	/*SetWindowPos(g_hWnd, HWND_NOTOPMOST, 
				rc.left, rc.top, newWidth, newHeight, SWP_SHOWWINDOW);*/

	MoveWindow(g_hWnd, rc.left, rc.top, newWidth, newHeight, true);

}


void cMainGame::RestoreDevice()
{
	HRESULT res = D3DERR_DEVICELOST;

	while ( res ==  D3DERR_DEVICELOST)
	{
		while(res != D3DERR_DEVICENOTRESET )
		{
			MSG			Message;
			PeekMessage( &Message, NULL, 0U, 0U, PM_REMOVE );
			TranslateMessage( &Message );
			DispatchMessage( &Message );

			res = m_pDevice->TestCooperativeLevel();
		}

		res = m_pDevice->Reset(&m_sBackupD3dpp);
	}

	SetRenderState();
}

void cMainGame::UpdateUVAnim()
{
	//SVertex* pData = NULL;

	//m_pVB->Lock(0, sizeof(SVertex) * 6, (void**)&pData, 0);

	//for( int i = 0 ; i < 6 ; i ++)
	//{
	//	pData->u += 0.01f;
	//	pData += 1;
	//}
	////memcpy( pData, sVertex, sizeof(SVertex)* 6 );

	//m_pVB->Unlock();

//	m_mTexTM._31 += 0.01f;

	static float rot = 0.f;
	rot += 0.01f;
	D3DXMatrixRotationX( &m_mTexTM, rot );
	
}

void cMainGame::Update()
{

	UpdateUVAnim();

	m_pDevice->Clear( 0, 0,	// 무조건 0
					D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,//실제 눈에 보이는걸 지워라
					D3DXCOLOR(0.00f, 0.125f, 0.35f, 1),
					1.f,	//zbuffer를1 로 지워라
					0.f); // 스텐실 버퍼를 0으로 지워라

	if( SUCCEEDED( m_pDevice->BeginScene() ))
	{
		//여기서 그린다!!!
		Render();

		m_pDevice->EndScene();
	}

	if( m_pDevice->Present(0,0,0,0) == D3DERR_DEVICELOST )
	{
		RestoreDevice();
	}
						
}


void cMainGame::UpdateCamera()
{
	D3DXVECTOR3	vNewEye = D3DXVECTOR3(0,0,0);
	const float	fRot = 0.01f;

	D3DXMATRIX mRot;

	D3DXMatrixRotationY( &mRot, fRot );

	D3DXVec3TransformCoord(&vNewEye, &m_vEye, &mRot );

	m_vEye = vNewEye;

	D3DXVECTOR3 vUp		= D3DXVECTOR3( 0, 1, 0);	

	D3DXMATRIX	mCam;

	D3DXMatrixLookAtLH( &mCam, &m_vEye, &m_vLook, &vUp );

	// 디바이스에다가 특정 오브젝트의 행렬을 셋팅한다
	// 카메라 행렬을 디바이스에 전달한다
	m_pDevice->SetTransform( D3DTS_VIEW, &mCam );
}

void cMainGame::Render()
{
	m_cGrid.Render();
	m_cAxis.Render();

	
	//m_pDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2 );
	//// 2차원 텍스쳐의 좌표를 조작하겠다

	//m_pDevice->SetTransform( D3DTS_TEXTURE0, &m_mTexTM );
	m_pDevice->SetTexture( 0, m_pTexture );


	m_pDevice->SetTransform( D3DTS_WORLD, &m_mTexTM );

	m_pDevice->SetStreamSource( 0, m_pVB, 0, sizeof(SVertex));
	m_pDevice->SetFVF( SVertex::CUSTOM_FVF );
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );
	
	m_pDevice->SetTextureStageState( 0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE );

}



void cMainGame::Release()
{
	SAFE_RELEASE( m_pDevice );
	SAFE_RELEASE( m_pD3D );
}
