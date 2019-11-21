#include "defines.h"

cMainGame::cMainGame(void)
{
	m_pDevice = 0;
	m_pD3D = 0;
	m_bWindowMode = true;
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

	

	return true;
}

bool cMainGame::ResetDevice( int width, int height )
{
	if( m_pD3D == 0 )
		return false;

	D3DPRESENT_PARAMETERS	d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));

	d3dpp.Windowed = m_bWindowMode;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;

	if( m_pDevice == 0)
	{
		m_pD3D->CreateDevice( 
					D3DADAPTER_DEFAULT,		//0번 ( 기본 ) 그래픽 카드를 사용하겠다
					D3DDEVTYPE_REF,		//하드웨어 가속을 사용하겠다
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

	return true;
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

void cMainGame::SetRenderState()
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update()
{
	Input();

	m_pDevice->Clear( 0, 0,	// 무조건 0
					D3DCLEAR_TARGET,//실제 눈에 보이는걸 지워라
					D3DCOLOR_XRGB(2, 95, 209),
					1.f,	//zbuffer를1 로 지워라
					0.f); // 스텐실 버퍼를 0으로 지워라

	if( SUCCEEDED( m_pDevice->BeginScene() ))
	{
		//여기서 그린다!!!

		m_pDevice->SetStreamSource( 0, m_pVB, 0, 
			sizeof(SVertex)//버텍스 버퍼 한개에 대한 크기
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

	if( m_pDevice->Present(0,0,0,0) == D3DERR_DEVICELOST )
	{
		RestoreDevice();
	}
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

void cMainGame::Input()
{
	if( cKeyManager::GetSingleton().OnceKeyDown(VK_F1))
	{
		m_bWindowMode = true;
		ResetDevice(1024, 768);
	}

	if( cKeyManager::GetSingleton().OnceKeyDown(VK_F2))
	{
		m_bWindowMode = true;
		ResetDevice(800, 600);
	}

	if( cKeyManager::GetSingleton().OnceKeyDown(VK_F3))
	{
		//FullScreen
		m_bWindowMode = false;
		ResetDevice(1920, 1080);
	}
}


void cMainGame::MakeVB()
{
	//LPDIRECT3DVERTEXBUFFER9	
	SVertex	sVertex[3] = 
	{
		{ 1.f, -1.f, 0.f, 0xffff0000 },
		{-1.f, -1.f, 0.f, 0xff00ff00 },
		{ 0.f,  1.f, 0.f, 0xff0000ff },
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
				sizeof(SVertex) * 3,	//전체 버텍스 버퍼의 크기
				0,
				D3DFVF_CUSTOMVERTEX,
				D3DPOOL_MANAGED,

				/*
				D3DPOOL_DEFAULT                 = 0,
				D3DPOOL_MANAGED                 = 1,
				D3DPOOL_SYSTEMMEM               = 2,
				*/

				&m_pVB, 0);
	void* pData = NULL;
	m_pVB->Lock(
		0,	// 어디에서부터 락을걸꺼냐
		sizeof(SVertex) * 3,	//어디까지 락을걸거냐
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
