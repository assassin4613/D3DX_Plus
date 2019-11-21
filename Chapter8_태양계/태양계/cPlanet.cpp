#include "defines.h"
#include "cPlanet.h"

cPlanet::cPlanet(void) :
m_vPosition(0,0,0),
m_vRotation (0,0,0),
m_vRevolution(0,0,0),
m_vScale(1,1,1),
m_pParent(0),
m_pVB(0),
m_pDevice(0),
m_fRotSpeed(0),
m_fRevoSpeed(0)
{
}

cPlanet::~cPlanet(void)
{
}


void cPlanet::MakeVB()
{

	SVertex		sVertex[36] =
	{
		// 정면	face0
		{ -1,  1, -1, D3DXVECTOR3(0,0,-1) },	// v0
		{  1,  1, -1, D3DXVECTOR3(0,0,-1) }, // v1
		{ -1, -1, -1, D3DXVECTOR3(0,0,-1) }, // v2
		// face1
		{ -1, -1, -1, D3DXVECTOR3(0,0,-1) }, // v2
		{  1,  1, -1, D3DXVECTOR3(0,0,-1) }, // v1
		{  1, -1, -1, D3DXVECTOR3(0,0,-1) },  // v3

		// 뒷면 face 0 
		{ -1,  1, 1, D3DXVECTOR3(0,0,1) }, // v0
		{  1,  1, 1, D3DXVECTOR3(0,0,1) }, // v1
		{ -1, -1, 1, D3DXVECTOR3(0,0,1) }, // v2
		// face1
		{ -1, -1, 1, D3DXVECTOR3(0,0,1) }, // v2
		{  1,  1, 1, D3DXVECTOR3(0,0,1) }, // v1
		{  1, -1, 1, D3DXVECTOR3(0,0,1) },  // v3

		// 우측면 face 0 
		{  1,  1, -1, D3DXVECTOR3(1,0,0) }, // v0
		{  1,  1,  1, D3DXVECTOR3(1,0,0) }, // v1
		{  1, -1, -1, D3DXVECTOR3(1,0,0) }, // v2
		// face1
		{  1, -1, -1, D3DXVECTOR3(1,0,0) }, // v2
		{  1,  1,  1, D3DXVECTOR3(1,0,0) }, // v1
		{  1, -1, 1, D3DXVECTOR3(1,0,0) },  // v3

		// 좌측면 face 0 
		{  -1,  1, -1, D3DXVECTOR3(-1,0,0)}, // v0
		{  -1,  1,  1, D3DXVECTOR3(-1,0,0)}, // v1
		{  -1, -1, -1, D3DXVECTOR3(-1,0,0)}, // v2
		// face1
		{  -1, -1, -1, D3DXVECTOR3(-1,0,0)}, // v2
		{  -1,  1,  1, D3DXVECTOR3(-1,0,0)}, // v1
		{  -1, -1,  1, D3DXVECTOR3(-1,0,0)},  // v3

		// 상단 face 0
		{ -1, 1 , 1, D3DXVECTOR3(0,1,0) }, // v0
		{  1, 1 , 1, D3DXVECTOR3(0,1,0) }, // v1
		{ -1, 1 ,-1, D3DXVECTOR3(0,1,0) }, // v2

		// face 1
		{ -1, 1 ,-1, D3DXVECTOR3(0,1,0) }, // v2
		{  1, 1 , 1, D3DXVECTOR3(0,1,0) }, // v1
		{  1, 1 ,-1, D3DXVECTOR3(0,1,0) }, // v3


		// 하단 face 0
		{ -1, -1 , 1, D3DXVECTOR3(0,-1,0) }, // v0
		{  1, -1 , 1, D3DXVECTOR3(0,-1,0) }, // v1
		{ -1, -1 ,-1, D3DXVECTOR3(0,-1,0) }, // v2

		// face 1
		{ -1, -1 ,-1, D3DXVECTOR3(0,-1,0) }, // v2
		{  1, -1 , 1, D3DXVECTOR3(0,-1,0) }, // v1
		{  1, -1 ,-1, D3DXVECTOR3(0,-1,0) }, // v3
	};

	m_pDevice->CreateVertexBuffer( 
		sizeof( SVertex ) * 36 , 0, 
		SVertex::CUSTOM_FVF, 
		D3DPOOL_MANAGED,
		&m_pVB, 0);

	void* pData = 0 ;
	m_pVB->Lock( 0, sizeof(SVertex)* 36, &pData, 0 );
	memcpy( pData, sVertex, sizeof( SVertex ) * 36 );
	m_pVB->Unlock();
}

void cPlanet::Release()
{
	SAFE_RELEASE(m_pVB);
}


void cPlanet::Update()
{
	m_vRotation.y += m_fRotSpeed;
	m_vRevolution.y += m_fRevoSpeed;
}

void cPlanet::Render()
{
	D3DXMATRIX	mTrans;
	D3DXMATRIX	mRot;
	D3DXMATRIX	mRotX;
	D3DXMATRIX	mRotY;
	D3DXMATRIX	mRotZ;
	D3DXMATRIX	mScale;
	D3DXMATRIX	mRevo;
	D3DXMATRIX	mRevoX;
	D3DXMATRIX	mRevoY;
	D3DXMATRIX	mRevoZ;

	D3DXMatrixTranslation(&mTrans, m_vPosition.x,
									m_vPosition.y,
									m_vPosition.z );

	//D3DXMatrixRotationAxis(
	//D3DXMatrixRotationYawPitchRoll
	//쿼터니언


	D3DXMatrixRotationX(&mRotX, m_vRotation.x );
	D3DXMatrixRotationY(&mRotY, m_vRotation.y );
	D3DXMatrixRotationZ(&mRotZ, m_vRotation.z );

	mRot = mRotX * mRotY * mRotZ;

	D3DXMatrixScaling( &mScale,  m_vScale.x, m_vScale.y, m_vScale.z );

	D3DXMatrixRotationX(&mRevoX, m_vRevolution.x );
	D3DXMatrixRotationY(&mRevoY, m_vRevolution.y );
	D3DXMatrixRotationZ(&mRevoZ, m_vRevolution.z );

	mRevo = mRevoX * mRevoY * mRevoZ;

	m_mTemp = mTrans * mRevo;

	if( m_pParent != 0 )
	{
		m_mWorld = mScale * 
					mRot * 
					mTrans *
					mRevo *
					m_pParent->m_mTemp;

		
	}
	else
	{
		m_mWorld = mScale * 
			mRot * 
			mTrans *
			mRevo;
	}


	m_pDevice->SetTransform( D3DTS_WORLD, &m_mWorld );

	D3DMATERIAL9	mtrl;
	memset(&mtrl, 0, sizeof(D3DMATERIAL9 ) );
	mtrl.Diffuse = D3DXCOLOR(1.f,0,0,1);
	mtrl.Ambient = D3DXCOLOR(0.2f,0,0,1);
	m_pDevice->SetMaterial( &mtrl );

	m_pDevice->SetStreamSource( 0, m_pVB,  0, sizeof(SVertex) );
	m_pDevice->SetFVF( SVertex::CUSTOM_FVF );
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 12 );
}

void cPlanet::Init(LPDIRECT3DDEVICE9 device, 
				   cPlanet* pParent )
{
	m_pDevice = device;
	m_pParent = pParent;

	MakeVB();
}