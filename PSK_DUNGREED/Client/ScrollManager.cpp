#include "stdafx.h"
#include "ScrollManager.h"


CScrollManager::CScrollManager()
{
}

CScrollManager::~CScrollManager()
{
}

void CScrollManager::SetScroll(float fX, float fY)
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

const D3DXVECTOR3 & CScrollManager::GetScroll() const
{
	return m_vScroll;
}
