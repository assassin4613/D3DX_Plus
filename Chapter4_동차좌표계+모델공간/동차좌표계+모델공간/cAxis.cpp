#include "defines.h"

cAxis::cAxis(void)
{
}

cAxis::~cAxis(void)
{
}

void cAxis::Init( LPDIRECT3DDEVICE9 pDevice)
{
	m_pDevice = pDevice;

	SVertex		sVertex [6] = 
	{
		{ D3DXVECTOR3(0, 0, 0 ), D3DCOLOR_XRGB(255,0,0) },
		{ D3DXVECTOR3(3, 0, 0 ), D3DCOLOR_XRGB(255,0,0) },

		{ D3DXVECTOR3(0, 0, 0 ), D3DCOLOR_XRGB(0,255,0) },
		{ D3DXVECTOR3(0, 3, 0 ), D3DCOLOR_XRGB(0,255,0) },

		{ D3DXVECTOR3(0, 0, 0 ), D3DCOLOR_XRGB(0,0,255) },
		{ D3DXVECTOR3(0, 0, 3 ), D3DCOLOR_XRGB(0,0,255) },
	};

	memcpy( m_sVertex, sVertex, sizeof(SVertex) * 6 );
}

void cAxis::Render()
{
	m_pDevice->SetFVF( SVertex::CUSTOM_FVF );
	m_pDevice->DrawPrimitiveUP( D3DPT_LINELIST,
								3, &m_sVertex,
								sizeof(SVertex ));
}

void cAxis::Release()
{

}
