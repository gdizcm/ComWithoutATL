#pragma once
#include <Windows.h>

class AutoLock
{
public:
	AutoLock()
	{
		InitializeCriticalSection(&m_cSection);
		EnterCriticalSection(&m_cSection);
	}
	~AutoLock()
	{
		LeaveCriticalSection(&m_cSection);
		DeleteCriticalSection(&m_cSection);
	}
private:
	CRITICAL_SECTION m_cSection;
};