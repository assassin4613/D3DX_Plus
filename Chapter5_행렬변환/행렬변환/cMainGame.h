#pragma once
#include "cGrid.h"
#include "cAxis.h"
class cMainGame
{
protected:
	LPDIRECT3D9					m_pD3D;
	LPDIRECT3DDEVICE9			m_pDevice;

	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	cGrid						m_cGrid;
	cAxis						m_cAxis;

	D3DXVECTOR3					m_vEye;
	D3DXVECTOR3					m_vLook;


	D3DPRESENT_PARAMETERS		m_sBackupD3dpp;
	bool						m_bWindowMode;
	int							m_nResoultionX;
	int							m_nResoultionY;


protected:
	void RestoreDevice();
	bool ResetDevice( int width, int height );
	void ResetWindow();
	void MakeVB();
	void Input();
	void InitCamera();
	void UpdateCamera();

public:
	void SetRenderState();
	bool Init();
	void Release();
	void Update();


public:

	cMainGame(void);
	~cMainGame(void);


};
