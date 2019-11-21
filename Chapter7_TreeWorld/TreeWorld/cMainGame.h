#pragma once
#include "Logic/cTerrain.h"
#include "Logic/cTree.h"

class cMainGame
{
protected:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pDevice;

	cTerrain*			m_cTerrain;
	vector<cTree*>		m_svTree;
	//cTree*				m_pTree;

	D3DXVECTOR3					m_vEye;
	D3DXVECTOR3					m_vLook;

protected:
	void UpdateCamera();
	bool ResetDevice( int width, int height );
	
public:
	bool Init();
	void Release();
	void Update();
	void InitCamera();
	void SetRenderState();

public:

	cMainGame(void);
	~cMainGame(void);


};
