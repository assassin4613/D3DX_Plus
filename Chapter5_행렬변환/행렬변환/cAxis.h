#pragma once

class cAxis
{
protected:
	LPDIRECT3DDEVICE9			m_pDevice;
	SVertex						m_sVertex[6];
public:
	void Init( LPDIRECT3DDEVICE9 pDevice);
	void Render();
	void Release();
public:
	cAxis(void);
	~cAxis(void);
};
