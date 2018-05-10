#include "stdafx.h"
#include "TimeManager.h"


CTimeManager::CTimeManager()
{
}

CTimeManager::~CTimeManager()
{
}

const float & CTimeManager::GetTime() const
{
	return m_fTime;
}

void CTimeManager::InitTime()
{
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);

	QueryPerformanceFrequency(&m_CpuTick);
}

void CTimeManager::SetTime()
{
	QueryPerformanceCounter(&m_FrameTime);

	if (m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;
	m_FixTime = m_FrameTime;
}
