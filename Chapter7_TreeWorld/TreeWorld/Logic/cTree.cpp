#include "defines.h"
#include "cTree.h"

cTree::cTree( LPDIRECT3DDEVICE9 pDevice ) : 
cInstance(pDevice)
{

}
//{
//	m_vScale = D3DXVECTOR3(1,1,1);
//}

cTree::~cTree(void)
{
}

void cTree::Make()
{
	//cTree::SVertex sVertex[6]  =
	//{
	//	{D3DXVECTOR3(0, 1.0f, 0), 0xff006600 },
	//	{D3DXVECTOR3(-0.5f, 0, 0), 0xff006600 },
	//	{D3DXVECTOR3( 0.5f, 0.0f, 0), 0xff006600 },

	//	{D3DXVECTOR3(0, 2.0f, 0), 0xff006600 },
	//	{D3DXVECTOR3(-0.5f, 0.5f, 0), 0xff006600 },
	//	{D3DXVECTOR3( 0.5f, 0.5f, 0), 0xff006600 },
	//};

	//m_pDevice->CreateVertexBuffer( sizeof(cTree::SVertex) * 6,
	//								0, 
	//								cTree::SVertex::CUSTOM_FVF,
	//								D3DPOOL_MANAGED,
	//								&m_pVB, 0);


	//cTree::SVertex* pData = NULL;
	////void* pData = NULL;

	//
	//m_pVB->Lock(0, sizeof(cTree::SVertex) * 6,
	//			(void**)&pData, 0 );

	////memcpy(pData, sVertex, sizeof(cTree::SVertex) * 6 );

	//for( int i = 0 ; i < 6 ; i++)
	//{
	//	memcpy(pData, &sVertex[i], sizeof(cTree::SVertex) );
	//	pData += 1;
	//}

	//m_pVB->Unlock();

}


void cTree::Render()
{
	if( m_pDevice == 0)
		return;

	D3DXMATRIX	mWorld;

	D3DXMATRIX mScale;
	D3DXMatrixScaling(&mScale, m_vScale.x,m_vScale.y,m_vScale.z);

	D3DXMATRIX mTran;
	D3DXMatrixTranslation(&mTran, m_vPos.x, m_vPos.y, m_vPos.z );

	mWorld = mScale * mTran;

	m_pDevice->SetTransform( D3DTS_WORLD, &mWorld);

	m_pDevice->SetStreamSource( 0, m_pVB, 0,
								sizeof(cTree::SVertex) );
	m_pDevice->SetFVF( cTree::SVertex::CUSTOM_FVF );
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

}