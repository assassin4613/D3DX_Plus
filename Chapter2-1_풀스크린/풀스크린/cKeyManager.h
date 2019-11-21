#pragma once

#include "defines.h"

class cKeyManager 
{
protected:
	bool	m_byKeyUp[256];
	bool	m_byKeyDown[256];
	float	m_fDoubleTime[256];
	bool	m_byDoubleClick[256];

public:
	static cKeyManager& GetSingleton();
	cKeyManager(void);
	~cKeyManager(void);

	bool KeyDoubleClick(BYTE byKey );
	bool KeyDown( BYTE byKey);
	bool KeyUp(BYTE byKey);
	bool OnceKeyDown( BYTE byKey);
};
