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

const float & CTimeManager::GetDeltaTime() const
{
	return m_fDeltaTime;
}

void CTimeManager::InitTime()
{
	QueryPerformanceCounter(&m_FrameTime);
	QueryPerformanceCounter(&m_FixTime);
	QueryPerformanceCounter(&m_LastTime);

	QueryPerformanceFrequency(&m_CpuTick);

	m_iFrame = 70;

	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;
	m_fPerFrame = float(m_CpuTick.QuadPart / m_iFrame);
}

void CTimeManager::SetTime()
{
	while (true)
	{
		QueryPerformanceCounter(&m_FrameTime);
		m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart);

		if (m_fPerFrame < m_fTime)
		{
			m_fDeltaTime = float(m_fTime / m_CpuTick.QuadPart);
			m_FixTime = m_FrameTime;
			break;
		}
	}

	if (m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		QueryPerformanceFrequency(&m_CpuTick);
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	//m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;
	//m_FixTime = m_FrameTime;
}
