#pragma once

class cTimer  : public cSingleton<cTimer>
{
protected:
	__int64				m_nLastTime;
	__int64				m_nCurTime;

	LARGE_INTEGER		m_sPredFrequncy;
	bool				m_bHardwareEnable;

	int					m_nFPSCheckCount;
	float				m_fFPSCheckTime;
	float				m_fWorldTime;

public:
	static float		deltaTime;
	static float		timeScale;
	static int			fps;
	static float		time;
public:
	virtual void Init();
	virtual void Loop();

public:
	cTimer(void);
	virtual ~cTimer(void);
};
