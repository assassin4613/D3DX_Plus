#pragma once

class cAxis
{
	struct SVertex
	{
		D3DXVECTOR3	vPos;
		DWORD		color;

		static const DWORD	CUSTOM_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};
protected:
	LPDIRECT3DDEVICE9			m_pDevice;
	cAxis::SVertex				m_sVertex[6];
public:
	void Init( LPDIRECT3DDEVICE9 pDevice);
	void Render();
	void Release();
public:
	cAxis(void);
	~cAxis(void);
};
