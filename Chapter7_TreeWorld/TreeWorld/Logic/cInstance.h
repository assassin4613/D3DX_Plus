#pragma once

class cInstance
{
protected:
	LPDIRECT3DDEVICE9			m_pDevice;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	D3DXVECTOR3					m_vPos;
	D3DXVECTOR3					m_vScale;

public:
	virtual void Make() = 0;
	void SetPos( D3DXVECTOR3 pos )		{ m_vPos = pos; }
	void SetScale( D3DXVECTOR3 scale )	{ m_vScale = scale; }
	void SetVB( LPDIRECT3DVERTEXBUFFER9 vb){ m_pVB = vb; }

public:
	cInstance(LPDIRECT3DDEVICE9 pDevice);
	virtual ~cInstance(void);
};
