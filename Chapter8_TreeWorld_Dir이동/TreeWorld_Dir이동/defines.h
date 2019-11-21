#pragma once

#include <windows.h>

#include "d3dx9.h"
#include "d3d9.h"
#include "vector"

using namespace std;

#define WINSIZE_X	800
#define WINSIZE_Y	600

#define START_X		100
#define START_Y		100

extern HWND g_hWnd;

struct SVertex
{
	D3DXVECTOR3	vPos;
	DWORD		color;
	const static DWORD CUSTOM_FVF = D3DFVF_DIFFUSE | D3DFVF_XYZ;
};

#include "cMainGame.h"
#include "cKeyManager.h"