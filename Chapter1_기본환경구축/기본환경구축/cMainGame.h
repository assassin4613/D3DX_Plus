#pragma once
#include "define.h"

class cMainGame
{
protected:
	LPDIRECT3D9			m_pD3D = NULL;
	LPDIRECT3DDEVICE9	m_pDevice = NULL;

protected:
	bool ResetDevice( int width, int height );

public:
	bool Init();
	void Release();
	void Update();


public:

	cMainGame(void);
	~cMainGame(void);


};
