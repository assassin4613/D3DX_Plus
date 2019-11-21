#include "defines.h"
#include "cTerrain.h"


cTerrain::cTerrain( LPDIRECT3DDEVICE9 pDevice):
cInstance(pDevice)
{

}
cTerrain::~cTerrain(void)
{
}

void cTerrain::Make()
{
	cTerrain::SVertex sVertex[6]  =
	{
		{ D3DXVECTOR3(-1, 0, 1), 0xff00ff00 },	//LT
		{ D3DXVECTOR3( 1, 0, 1), 0xff00ff00 },  //RT
		{ D3DXVECTOR3(-1, 0, -1), 0xff00ff00 },  //LB

		{ D3DXVECTOR3(-1, 0, -1), 0xff00ff00 },  //LB
		{ D3DXVECTOR3( 1, 0, 1), 0xff00ff00 },  //RT
		{ D3DXVECTOR3( 1, 0, -1), 0xff00ff00 },  //RB
	};

	m_pDevice->CreateVertexBuffer( sizeof(cTerrain::SVertex) * 6,
									0, 
									cTerrain::SVertex::CUSTOM_FVF,
									D3DPOOL_MANAGED,
									&m_pVB, 0);


	cTerrain::SVertex* pData = NULL;
	
	m_pVB->Lock(0, sizeof(cTerrain::SVertex) * 6,
				(void**)&pData, 0 );

	//memcpy(pData, sVertex, sizeof(cTerrain::SVertex) * 6 );

	for( int i = 0 ; i < 6 ; i++)
	{
		memcpy(pData, &sVertex[i], sizeof(cTerrain::SVertex) );
		pData += 1;
	}

	m_pVB->Unlock();

}


void cTerrain::Render()
{
	if( m_pDevice == 0)
		return;

	D3DXMATRIX	mWorld;
	D3DXMatrixScaling(&mWorld, 10,10,10);
	
	m_pDevice->SetTransform( D3DTS_WORLD, &mWorld);

	m_pDevice->SetStreamSource( 0, m_pVB, 0,
								sizeof(cTerrain::SVertex) );
	m_pDevice->SetFVF( cTerrain::SVertex::CUSTOM_FVF );
	m_pDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

}