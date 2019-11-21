#include "defines.h"
#include "cTimer.h"
#include "stdio.h"
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
		m_fTimeScale = 1.f / m_sPredFrequncy.QuadPart;

	}
	else
	{
		m_bHardwareEnable = false;
		m_fTimeScale = 1 / 1000.f;
		m_nCurTime = GetTickCount();
		m_nLastTime = GetTickCount();
	}



	m_fEllipseTime = 0.f;
	m_nFPSCheckCount = 0;
	m_fFPSCheckTime = 0.f;
	m_fWorldTime = 0.f;
	m_nFPS = 0;
}

void cTimer::Update(int nLockFPS)
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


	m_fEllipseTime = (m_nCurTime - m_nLastTime) * m_fTimeScale;

	
	if( nLockFPS > 0 )
	{
		while( m_fEllipseTime < 1.f / nLockFPS )
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


			m_fEllipseTime = (m_nCurTime - m_nLastTime) * m_fTimeScale;
		}
	}


	m_nLastTime = m_nCurTime;
	m_fFPSCheckTime += m_fEllipseTime;
	m_nFPSCheckCount++;

	m_fWorldTime += m_fEllipseTime;

	if( m_fFPSCheckTime >= 1.f )
	{
		m_fFPSCheckTime = 0;
		m_nFPS = m_nFPSCheckCount;
		m_nFPSCheckCount = 0;
	}
}

void cTimer::Output(HDC hdc)
{
	char	szFPS[128] = { 0, };
	sprintf(szFPS, "FPS : %d", m_nFPS );
	TextOut( hdc, 10, 10, szFPS, strlen( szFPS ) );


	char	szEllipseTime[128] = { 0, };
	sprintf(szEllipseTime, "EllipseTime : %0.4f", m_fEllipseTime );
	TextOut( hdc, 10, 50, szEllipseTime, strlen( szEllipseTime ) );
}