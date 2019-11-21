#pragma once
#include "Util\cAxis.h"
#include "Util\cGrid.h"

class cMainGame
{
protected:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pDevice;

	cAxis				m_cAxis;
	cGrid				m_cGrid;

	D3DXVECTOR3					m_vEye;
	D3DXVECTOR3					m_vLook;

	D3DPRESENT_PARAMETERS		m_sBackupD3dpp;
	bool						m_bWindowMode;
	int							m_nResoultionX;
	int							m_nResoultionY;

protected:
	void RestoreDevice();
	void SetRenderState();
	void ResetWindow();
	bool ResetDevice( int width, int height );
	void Render();
	void InitCamera();
	void UpdateCamera();

public:
	bool Init();
	void Release();
	void Update();
public:

	cMainGame(void);
	~cMainGame(void);


};
