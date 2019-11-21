#include "defines.h"
#include "cTimer.h"
#include "stdio.h"

int cTimer::fps = 0; 
float cTimer::deltaTime = 0;
float cTimer::time = 0;
float cTimer::timeScale = 1;

cTimer::cTimer(void)
{
}

cTimer::~cTimer(void)
{
}

void cTimer::Init()
{
	if( QueryPerformanceFrequency( &m_sPredFrequncy ) != 0 )
	{
		m_bHardwareEnable = true;
		LARGE_INTEGER		sCurTime;
		QueryPerformanceCounter( &sCurTime );

		m_nCurTime = sCurTime.QuadPart;
		m_nLastTime = sCurTime.QuadPart;
		cTimer::timeScale = 1.f / m_sPredFrequncy.QuadPart;

	}
	else
	{
		m_bHardwareEnable = false;
		cTimer::timeScale = 1 / 1000.f;
		m_nCurTime = GetTickCount();
		m_nLastTime = GetTickCount();
	}


	m_nFPSCheckCount = 0;
	m_fFPSCheckTime = 0.f;
	m_fWorldTime = 0.f;
}

void cTimer::Loop()
{
	const int nLockFPS = 60;
	if( m_bHardwareEnable )
	{
		LARGE_INTEGER		sCurTime;
		QueryPerformanceCounter( &sCurTime );
		m_nCurTime = sCurTime.QuadPart;
	}
	else
	{
		m_nCurTime = GetTickCount();
	}

	cTimer::deltaTime = (m_nCurTime - m_nLastTime) * cTimer::timeScale;
	
	if( nLockFPS > 0 )
	{
		while( cTimer::deltaTime < 1.f / nLockFPS )
		{
			if( m_bHardwareEnable )
			{
				LARGE_INTEGER		sCurTime;
				QueryPerformanceCounter( &sCurTime );
				m_nCurTime = sCurTime.QuadPart;
			}
			else
			{
				m_nCurTime = GetTickCount();
			}


			cTimer::deltaTime = (m_nCurTime - m_nLastTime) * cTimer::timeScale;
		}
	}


	m_nLastTime = m_nCurTime;
	m_fFPSCheckTime += cTimer::deltaTime;
	m_nFPSCheckCount++;

	m_fWorldTime += cTimer::deltaTime;

	if( m_fFPSCheckTime >= 1.f )
	{
		m_fFPSCheckTime = 0;
		cTimer::fps = m_nFPSCheckCount;
		m_nFPSCheckCount = 0;
	}
}

//void cTimer::Output(HDC hdc)
//{
//	char	szFPS[128] = { 0, };
//	sprintf(szFPS, "FPS : %d", cTimer::fps );
//	TextOut( hdc, 10, 10, szFPS, strlen( szFPS ) );
//
//
//	char	szEllipseTime[128] = { 0, };
//	sprintf(szEllipseTime, "deltaTime : %0.4f", cTimer::deltaTime );
//	TextOut( hdc, 10, 50, szEllipseTime, strlen( szEllipseTime ) );
//}