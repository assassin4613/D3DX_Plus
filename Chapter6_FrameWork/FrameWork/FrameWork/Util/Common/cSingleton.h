#pragma once

#include "vector"
using namespace std;

class cSingletonNode 
{
public:
	virtual void Init() {}
	virtual void Loop() {}
	virtual void Quit() {}

	virtual ~cSingletonNode(){}
};


template<typename T>
class cSingleton : public cSingletonNode
{
protected:
	static T*	mInstance;
public:
	static T*	GetSingleton() 
	{
		if( mInstance == 0)
		{
			mInstance = new T;
			mInstance->Init();
			cSingletonMgr::Add( (cSingletonNode*)mInstance );
		}
		
		return mInstance;
	}

	virtual void Quit() {} 
	virtual ~cSingleton() {}
	
};

template<typename T>	T*	cSingleton<T>::mInstance = 0;

class cSingletonMgr
{
	friend class cSingletonNode;
private:
	static vector<cSingletonNode*>		m_svSingletons;
public:

	static void Add( cSingletonNode* instance )
	{
		m_svSingletons.push_back(instance);
	}

	static void Update()
	{
		for( int i = 0 ;  i < cSingletonMgr::m_svSingletons.size() ; i ++)
		{
			cSingletonMgr::m_svSingletons[i]->Loop();
		}
	}

	static void Release()
	{
		for( unsigned int i = 0 ;  i < m_svSingletons.size() ; i ++)
		{
			m_svSingletons[i]->Quit();
			SAFE_DELETE( m_svSingletons[i] );
		}

		m_svSingletons.clear();
	}
};

//vector<cSingletonNode*>		cSingletonMgr::m_svSingletons;
//	
//
//	static void Update()
//	{
//		for( int i = 0 ;  i < m_svSingletons.size() ; i ++)
//		{
//			m_svSingletons[i]->Update();
//		}
//	}
//
//	static void Release()
//	{
//		for( int i = 0 ;  i < m_svSingletons.size() ; i ++)
//		{
//			m_svSingletons[i]->Quit();
//		}
//	}
//}