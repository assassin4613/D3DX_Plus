#pragma once
#include "cInstance.h"

class cHero : public cInstance
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
	void Update();
public:
	cHero( LPDIRECT3DDEVICE9 pDevice);
	~cHero(void);
};
