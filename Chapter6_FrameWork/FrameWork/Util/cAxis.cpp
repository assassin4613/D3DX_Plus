#include "defines.h"
#include "cAxis.h"

cAxis::cAxis(void)
{
}

cAxis::~cAxis(void)
{
}

void cAxis::Init( LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;

	cAxis::SVertex		sVertex [6] = 
	{
		{ D3DXVECTOR3(0, 0, 0 ), D3DCOLOR_XRGB(255,0,0) },
		{ D3DXVECTOR3(3, 0, 0 ), D3DCOLOR_XRGB(255,0,0) },

		{ D3DXVECTOR3(0, 0, 0 ), D3DCOLOR_XRGB(0,255,0) },
		{ D3DXVECTOR3(0, 3, 0 ), D3DCOLOR_XRGB(0,255,0) },

		{ D3DXVECTOR3(0, 0, 0 ), D3DCOLOR_XRGB(0,0,255) },
		{ D3DXVECTOR3(0, 0, 3 ), D3DCOLOR_XRGB(0,0,255) },
	};

	memcpy( m_sVertex, sVertex, sizeof(cAxis::SVertex) * 6 );
}

void cAxis::Render()
{
	D3DXMATRIX		mWorld;
	D3DXMatrixIdentity( &mWorld );
	m_pDevice->SetTransform( D3DTS_WORLD, &mWorld);


	m_pDevice->SetRenderState( D3DRS_ZENABLE, false );

	m_pDevice->SetFVF( cAxis::SVertex::CUSTOM_FVF );
	m_pDevice->DrawPrimitiveUP( D3DPT_LINELIST,
								3, &m_sVertex,
								sizeof(SVertex ));

	m_pDevice->SetRenderState( D3DRS_ZENABLE, true );
}

void cAxis::Release()
{

}