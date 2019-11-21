#include "defines.h"
#include "cKeyManager.h"

cKeyManager::cKeyManager(void)
{
	memset(m_byKeyUp, 0, sizeof(bool) * 256);
	memset(m_byKeyDown, 0, sizeof(bool) * 256);
	memset(m_byDoubleClick, 0, sizeof(bool) * 256);
	memset(m_fDoubleTime, 0, sizeof(float) * 256);
}

cKeyManager::~cKeyManager(void)
{
	
}

cKeyManager& cKeyManager::GetSingleton()
{
	static cKeyManager		cInst;
	return cInst;
}

bool cKeyManager::KeyDown( BYTE byKey)
{
	if( GetKeyState(byKey) & 0x8000)
	{
		return true;
	}

	return false;
}

bool cKeyManager::KeyUp(BYTE byKey)
{
	if( GetKeyState(byKey) & 0x8000)
	{
		m_byKeyUp[ byKey ] = true;
	}
	else if( m_byKeyUp[ byKey ] == true)
	{
		m_byKeyUp[ byKey ] = false;

		/*if( m_byDoubleClick[ byKey ] == false )
		{
			m_fDoubleTime[byKey] = TIMER->GetTime();
		}*/
		return true;
	}

	return false;
}

bool cKeyManager::OnceKeyDown( BYTE byKey)
{
	if( GetKeyState(byKey) & 0x8000)
	{
		if(m_byKeyDown[ byKey ] == false )
		{
			m_byKeyDown[ byKey ] = true;
			return true;
		}
	}
	else if( m_byKeyDown[ byKey ] == true)
	{
		m_byKeyDown[ byKey ] = false;
	}

	return false;
}

bool cKeyManager::KeyDoubleClick(BYTE byKey )
{
	/*const int nDelayTime = 0.2f;

	KeyUp(byKey);

	if( GetKeyState(byKey) & 0x8000 )
	{
		if( m_byDoubleClick[byKey] == false )
		{
			if( TIMER->GetTime() < m_fDoubleTime[byKey] + nDelayTime)
			{
				m_byDoubleClick[byKey] = true;
				return true;
			}
		}
	}
	else if (m_byDoubleClick[byKey] )
	{
		m_byDoubleClick[byKey] = false;
		m_byDoubleClick[byKey] = 0;
	}*/

	return false;
}