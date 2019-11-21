#pragma once
#include "defines.h"

class cGrid
{
	struct SVertex
	{
		D3DXVECTOR3	vPos;
		DWORD		color;

		static const DWORD	CUSTOM_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
	};
protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DDEVICE9			m_pDevice;
	int							m_LineCount;
public:
	void Init( LPDIRECT3DDEVICE9 pDevice,  int width, int height, 
			   float scale, DWORD color );
	void Render();

	void Release();
public:
	cGrid(void);
	~cGrid(void);
};
