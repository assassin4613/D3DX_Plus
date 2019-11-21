#pragma once

class cTimer
{
protected:
	__int64				m_nLastTime;
	__int64				m_nCurTime;

	LARGE_INTEGER		m_sPredFrequncy;
	bool				m_bHardwareEnable;


	float				m_fEllipseTime;
	float				m_fTimeScale;
	int					m_nFPSCheckCount;
	float				m_fFPSCheckTime;
	int					m_nFPS;
	float				m_fWorldTime;

public:
	void	Init();
	void	Update(int nLockFPS = 60);
	void	Output(HDC hdc);
	float	GetFrameTime() { return m_fEllipseTime; }
	float	GetTime() { return m_fWorldTime; }

public:
	cTimer(void);
	~cTimer(void);
};
