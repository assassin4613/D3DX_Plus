#pragma once
#include "cInstance.h"

class cTree : public cInstance
{
	struct SVertex
	{
		D3DXVECTOR3	vPos;
		DWORD		color;
		const static DWORD CUSTOM_FVF =  D3DFVF_XYZ  |D3DFVF_DIFFUSE;
	};
	
public:
	virtual void Make();
	void Render();
public:
	cTree( LPDIRECT3DDEVICE9 pDevice);
	~cTree(void);
};
