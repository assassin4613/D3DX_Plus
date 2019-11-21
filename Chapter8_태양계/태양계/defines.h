#pragma once

#include <windows.h>

#include "d3dx9.h"
#include "d3d9.h"

#define WINSIZE_X	800
#define WINSIZE_Y	600

#define START_X		100
#define START_Y		100


#define SAFE_RELEASE(t)	{if(t != 0){t->Release(); t = 0;} }
#define SAFE_DELETE(t)	{if(t != 0){delete t; t = 0;} }


enum PLANET
{
	PLANET_SUN,
	PLANET_MERCURY,
	PLANET_VENUS,
	PLANET_EARTH,
	PLANET_MARS,
	PLANET_MOON,
	PLANET_MAX,
};

extern HWND g_hWnd;

//struct SVertex
//{
//	D3DXVECTOR3 vPos;
//	DWORD		dwColor;
//	static const DWORD CUSTOM_FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;
//};


struct SVertex
{
	float	x, y, z;
	D3DXVECTOR3 normal;
	//DWORD	dwColor;
	static const DWORD CUSTOM_FVF = D3DFVF_XYZ | D3DFVF_NORMAL;
};

#include "cMainGame.h"