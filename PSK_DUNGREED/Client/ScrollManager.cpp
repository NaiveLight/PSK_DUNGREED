#include "stdafx.h"
#include "ScrollManager.h"

#include "TimeManager.h"

CScrollManager::CScrollManager()
{
}

CScrollManager::~CScrollManager()
{
}

void CScrollManager::Update()
{
	if (m_bIsShaking)
	{
		m_fShakeTime -= TimeManager->GetDeltaTime();
		m_fShakePower *= -1.f;
		m_vScroll.y += m_fShakePower;

		if (m_fShakeTime <= 0.f)
			ShakingEnd();
	}
}

void CScrollManager::SetCurScroll(float fX, float fY)
{
	m_vScroll.x = fX;
	m_vScroll.y = fY;

	if (m_vScroll.x > m_vMaxScroll.x)
		m_vScroll.x = m_vMaxScroll.x;

	if (m_vScroll.x < m_vMinScroll.x)
		m_vScroll.x = m_vMinScroll.x;

	if (m_vScroll.y > m_vMaxScroll.y)
		m_vScroll.y = m_vMaxScroll.y;

	if (m_vScroll.y  < m_vMinScroll.y)
		m_vScroll.y = m_vMinScroll.y;
}

void CScrollManager::SetMinScroll(float fX, float fY)
{
	m_vMinScroll.x = fX;
	m_vMinScroll.y = fY;
}

void CScrollManager::SetMaxScroll(float fX, float fY)
{
	m_vMaxScroll.x = fX;
	m_vMaxScroll.y = fY;
}

void CScrollManager::AddScroll(float fX, float fY)
{
	m_vScroll.x += fX;
	m_vScroll.y += fY;

	if (m_vScroll.x > m_vMaxScroll.x)
		m_vScroll.x = m_vMaxScroll.x;

	if (m_vScroll.x < m_vMinScroll.x)
		m_vScroll.x = m_vMinScroll.x;

	if (m_vScroll.y > m_vMaxScroll.y)
		m_vScroll.y = m_vMaxScroll.y;

	if (m_vScroll.y  < m_vMinScroll.y)
		m_vScroll.y = m_vMinScroll.y;
}

void CScrollManager::ShakingStart(float fPower, float fTime)
{
	if (!m_bIsShaking)
	{
		m_bIsShaking = true;
		m_fShakePower = fPower;
		m_fShakeTime = fTime;
	}
}

void CScrollManager::ShakingEnd()
{
	m_bIsShaking = false;
	m_fShakePower = 0.f;
}

const D3DXVECTOR3 & CScrollManager::GetScroll() const
{
	return m_vScroll;
}

const D3DXVECTOR3 & CScrollManager::GetMaxScroll() const
{
	return m_vMaxScroll;
}
