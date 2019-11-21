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


	InitCamera();
	SetRenderState();
	m_cTerrain = new cTerrain( m_pDevice );
	m_cTerrain->Make();

	for( int i = 0 ; i < 50 ; i ++)
	{

		cTree* pTree = new cTree(m_pDevice );
		
		/*string ttt = "cTree"
		cTree* ccc = new ttt;*/


		pTree->Make();

		pTree->SetPos( 
			D3DXVECTOR3( rand() % 20 - 10,
						 0,
						 rand() % 20 - 10 ) ); 

		m_svTree.push_back(pTree);
	}

	m_cHero = new cHero(m_pDevice );
	m_cHero->Make();
		
		
	//m_cTree.Init(m_pDevice);

	return true;
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


void cMainGame::SetRenderState()
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, false);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE );
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
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	m_pD3D->CreateDevice( 
					D3DADAPTER_DEFAULT,		//0번 ( 기본 ) 그래픽 카드를 사용하겠다
					D3DDEVTYPE_HAL,		//하드웨어 가속을 사용하겠다
					g_hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &m_pDevice);


	

	return true;
}


void cMainGame::InitCamera()
{
	m_vEye	= D3DXVECTOR3( 0, 10, -10);
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
		WINSIZE_X / WINSIZE_Y,	//화면 비율
		0.1f, //근평면 거리
		1000.f ); // 원평면

	// 디바이스에 전달
	m_pDevice->SetTransform( D3DTS_PROJECTION, &mProj );

}

void cMainGame::Update()
{
	m_cHero->Update();
	//UpdateCamera();
	m_pDevice->Clear( 0, 0,	// 무조건 0
					D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,//실제 눈에 보이는걸 지워라
					D3DXCOLOR(0.00f, 0.125f, 0.35f, 1),
					1.f,	//zbuffer를1 로 지워라
					0.f); // 스텐실 버퍼를 0으로 지워라

	if( SUCCEEDED( m_pDevice->BeginScene() ))
	{
		//여기서 그린다!!!
		
		for( int i = 0 ; i  < m_svTree.size() ; i++)
		{
			m_svTree[i]->Render();
		}
		/*for( int i = 0 ; i < 50 ; i ++)
			m_cTree[i].Render();*/

		m_cTerrain->Render();

		m_cHero->Render();

//		m_cTree.Render();
		m_pDevice->EndScene();
	}

	m_pDevice->Present(0,0,0,0);
						
}

void cMainGame::Release()
{

}
