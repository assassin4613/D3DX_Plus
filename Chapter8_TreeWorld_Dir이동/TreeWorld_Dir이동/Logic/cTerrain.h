#pragma once
#include "cInstance.h"

class cTerrain : public cInstance
{
	struct SVertex
	{
		D3DXVECTOR3	vPos;
		DWORD		color;
		const static DWORD CUSTOM_FVF =  D3DFVF_XYZ  |D3DFVF_DIFFUSE;
	};



public:
	void Make();
	void Render();
public:

	cTerrain( LPDIRECT3DDEVICE9 pDevice);
	//cTerrain(void);
	~cTerrain(void);
};
