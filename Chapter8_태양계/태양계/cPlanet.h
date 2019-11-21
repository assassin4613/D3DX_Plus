#pragma once

class cPlanet
{
protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	cPlanet*					m_pParent;
	LPDIRECT3DDEVICE9			m_pDevice;
	D3DXVECTOR3					m_vPosition;
	D3DXVECTOR3					m_vRotation;
	D3DXVECTOR3					m_vRevolution;
	D3DXVECTOR3					m_vScale;

	D3DXMATRIX					m_mWorld;
	D3DXMATRIX					m_mTemp;
	float						m_fRotSpeed;
	float						m_fRevoSpeed;

protected:
	void MakeVB();

	

public:
	void Init(LPDIRECT3DDEVICE9 device, 
				cPlanet* pParent );
	void Render();
	void Update();
	void Release();
	void SetPos( D3DXVECTOR3 position ) { m_vPosition = position; }
	void SetScale( D3DXVECTOR3 scale ) { m_vScale = scale; }
	void SetRotSpeed( float speed ) { m_fRotSpeed = speed; }
	void SetRevoSpeed( float speed ) { m_fRevoSpeed = speed; }

public:
	cPlanet(void);
	~cPlanet(void);
};
