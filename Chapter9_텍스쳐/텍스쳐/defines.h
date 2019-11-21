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

struct SVertex
{
	D3DXVECTOR3	pos;
	D3DXVECTOR3	nor;
	float u, v;

	static const DWORD CUSTOM_FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1;
};

extern HWND g_hWnd;


#include "cMainGame.h"