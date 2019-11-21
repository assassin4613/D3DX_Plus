#pragma once

class cInstance
{
protected:
	LPDIRECT3DDEVICE9			m_pDevice;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	D3DXVECTOR3					m_vPos;
	D3DXVECTOR3					m_vScale;
	D3DXVECTOR3					m_vRot;

public:
	virtual void Make() = 0;
	void SetPos( D3DXVECTOR3 pos )		{ m_vPos = pos; }
	void SetScale( D3DXVECTOR3 scale )	{ m_vScale = scale; }
	void SetRot( D3DXVECTOR3 rot )		{ m_vRot = rot; }
	void SetVB( LPDIRECT3DVERTEXBUFFER9 vb){ m_pVB = vb; }

public:

public:
	cInstance(LPDIRECT3DDEVICE9 pDevice);
	virtual ~cInstance(void);
};
