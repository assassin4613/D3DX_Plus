#pragma once

#include "defines.h"

class cMainGame
{
protected:
	LPDIRECT3D9					m_pD3D;
	LPDIRECT3DDEVICE9			m_pDevice;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;


protected:
	bool ResetDevice( int width, int height );
	void MakeVB();

public:
	void SetRenderState();
	bool Init();
	void Release();
	void Update();


public:

	cMainGame(void);
	~cMainGame(void);


};
