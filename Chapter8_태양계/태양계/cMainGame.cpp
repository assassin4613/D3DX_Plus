#include "defines.h"
#include "cMainGame.h"

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


	m_cAxis.Init(m_pDevice );
	m_cGrid.Init(m_pDevice, 50, 50,  1, 0xff808080 );

	m_cTimer.Init();

	return true;
}

void cMainGame::InitCamera()
{
	m_vEye	= D3DXVECTOR3( 0, 20, -20);
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
	InitLight();
	InitPlanet();
	return true;
}

void cMainGame::SetRenderState()
{
	//m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
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


// v0---v1
// |   / |
// |  /  |
// | /   |
// |/    |
// v2----v3


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

void cMainGame::InitLight()
{
	//포인트 라이트 // 다이렉셔널 라이트 // 스포트라이트

	D3DLIGHT9 light;
	memset( &light, 0, sizeof(D3DLIGHT9) );

	light.Type = D3DLIGHT_DIRECTIONAL;

	light.Direction = D3DXVECTOR3( 0, -1, 1 );
	light.Diffuse	= D3DXCOLOR(1,1,1,1);
	light.Ambient	= D3DXCOLOR(1,1,1,1);	

	m_pDevice->SetLight( 0, &light );
	m_pDevice->LightEnable( 0, TRUE );

}

void cMainGame::Update()
{
	m_cTimer.Update(0);

	UpdateCamera();

	for( int i = 0 ; i < PLANET_MAX ; i++)
	{
		m_cPlanet[i].Update();
	}

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
	const float	fRot = 0.5f * m_cTimer.GetFrameTime();

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

	for( int i = 0 ; i < PLANET_MAX ; i++)
	{
		m_cPlanet[i].Render();
	}
}


void cMainGame::InitPlanet()
{
	m_cPlanet[PLANET_SUN].Init( m_pDevice, 0);

	m_cPlanet[PLANET_MERCURY].Init( m_pDevice, &m_cPlanet[PLANET_SUN]);
	m_cPlanet[PLANET_MERCURY].SetPos(D3DXVECTOR3(3, 0, 0) );
	m_cPlanet[PLANET_MERCURY].SetScale(D3DXVECTOR3(0.3f,0.3f,0.3f ));
	m_cPlanet[PLANET_MERCURY].SetRotSpeed( 0.01f);
	m_cPlanet[PLANET_MERCURY].SetRevoSpeed( 0.1f );

	m_cPlanet[PLANET_VENUS].Init( m_pDevice, &m_cPlanet[PLANET_SUN]);
	m_cPlanet[PLANET_VENUS].SetPos(D3DXVECTOR3(5, 0, 0) );
	m_cPlanet[PLANET_VENUS].SetScale(D3DXVECTOR3(0.5f,0.5f,0.5f ));
	m_cPlanet[PLANET_VENUS].SetRotSpeed( 0.02f);
	m_cPlanet[PLANET_VENUS].SetRevoSpeed( 0.03f );

	m_cPlanet[PLANET_EARTH].Init( m_pDevice, &m_cPlanet[PLANET_SUN]);
	m_cPlanet[PLANET_EARTH].SetPos(D3DXVECTOR3(8, 0, 0) );
	m_cPlanet[PLANET_EARTH].SetScale(D3DXVECTOR3(0.7f,0.7f,0.7f ));
	m_cPlanet[PLANET_EARTH].SetRotSpeed( 0.03f);
	m_cPlanet[PLANET_EARTH].SetRevoSpeed( 0.01f );

	m_cPlanet[PLANET_MARS].Init( m_pDevice, &m_cPlanet[PLANET_SUN]);
	m_cPlanet[PLANET_MARS].SetPos(D3DXVECTOR3(10, 0, 0) );
	m_cPlanet[PLANET_MARS].SetScale(D3DXVECTOR3(0.6f,0.6f,0.6f ));
	m_cPlanet[PLANET_MARS].SetRotSpeed( 0.001f);
	m_cPlanet[ PLANET_MARS ].SetRevoSpeed( 0.002f );

	m_cPlanet[ PLANET_MOON ].Init( m_pDevice, 
								&m_cPlanet[PLANET_EARTH] );
	m_cPlanet[ PLANET_MOON ].SetPos(D3DXVECTOR3(0,0,2));
	m_cPlanet[ PLANET_MOON ].SetScale( D3DXVECTOR3(0.2f,0.2f,0.2f));
	//m_cPlanet[ PLANET_MOON ].SetRotSpeed( 0.1f);
	//m_cPlanet[ PLANET_MOON ].SetRevoSpeed( 0.1f );
}


void cMainGame::Release()
{

	for( int i = 0 ; i < PLANET_MAX ; i++)
	{
		m_cPlanet[i].Release();
	}

	SAFE_RELEASE( m_pDevice );
	SAFE_RELEASE( m_pD3D );
}
