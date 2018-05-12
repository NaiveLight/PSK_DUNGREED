#include "stdafx.h"
#include "ScrollManager.h"


CScrollManager::CScrollManager()
{
}

CScrollManager::~CScrollManager()
{
}

void CScrollManager::SetCurScroll(float fX, float fY)
{
	m_vScroll.x = fX;
	m_vScroll.y = fY;
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

void CScrollManager::SetScroll(const D3DXVECTOR3 & vScroll)
{
	m_vScroll.x += vScroll.x;
	m_vScroll.y += vScroll.y;

	if (m_vScroll.x > m_vMaxScroll.x)
		m_vScroll.x = m_vMaxScroll.x;

	if (m_vScroll.x < m_vMinScroll.x)
		m_vScroll.x = m_vMinScroll.x;

	if (m_vScroll.y > m_vMaxScroll.y)
		m_vScroll.y = m_vMaxScroll.y;

	if (m_vScroll.y  < m_vMinScroll.y)
		m_vScroll.y = m_vMinScroll.y;
}

const D3DXVECTOR3 & CScrollManager::GetScroll() const
{
	return m_vScroll;
}
