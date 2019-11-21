#include "defines.h"
#include "cHero.h"

cHero::cHero( LPDIRECT3DDEVICE9 pDevice ) : 
cInstance(pDevice)
{

}
//{
//	m_vScale = D3DXVECTOR3(1,1,1);
//}

cHero::~cHero(void)
{
}

void cHero::Make()
{
	cHero::SVertex sVertex[3]  =
	{
		{D3DXVECTOR3(-0.5f, 2.0f, 0), 0xff0000ff },
		{D3DXVECTOR3( 0.5f, 2.0f, 0), 0xff0000ff },
		{D3DXVECTOR3( 0.f, 0.0f, 0),  0xff000011 },
	};

	m_pDevice->CreateVertexBuffer( sizeof(cHero::SVertex) * 3,
									0, 
									cHero::SVertex::CUSTOM_FVF,
									D3DPOOL_MANAGED,
									&m_pVB, 0);


	cHero::SVertex* pData = NULL;
	//void* pData = NULL;

	
	m_pVB->Lock(0, sizeof(cHero::SVertex) * 3,
				(void**)&pData, 0 );

	memcpy(pData, sVertex, sizeof(cHero::SVertex) * 3 );

	

	m_pVB->Unlock();

}

void cHero::Update()
{
	if( cKeyManager::GetSingleton().KeyDown( VK_UP ) )
	{
		m_vPos += D3DXVECTOR3(0,0, 0.1f);
	}

	m_vRot.y += 0.02f;
}

void cHero::Render()
{
	if( m_pDevice == 0)
		return;

	D3DXMATRIX	mWorld;

	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, m_vScale.x,m_vScale.y,m_vScale.z);

	D3DXMATRIX mTran;
	D3DXMatrixTranslation(&mTran, m_vPos.x, m_vPos.y, m_vPos.z );

	D3DXMATRIX mRot;
	D3DXMATRIX mRotX;
	D3DXMATRIX mRotY;
	D3DXMATRIX mRotZ;

	D3DXMatrixRotationX( &mRotX, m_vRot.x );
	D3DXMatrixRotationY( &mRotY, m_vRot.y );
	D3DXMatrixRotationZ( &mRotZ, m_vRot.z );

	mRot = mRotX * mRotY * mRotZ;
	mWorld = mScale * mRot* mTran;

	m_pDevice->SetTransform( D3DTS_WORLD, &mWorld);

	m_pDevice->SetStreamSource( 0, m_pVB, 0,
								sizeof(cHero::SVertex) );
	m_pDevice->SetFVF( cHero::SVertex::CUSTOM_FVF );
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );

}