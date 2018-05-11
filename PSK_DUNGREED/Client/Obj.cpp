#include "stdafx.h"
#include "Obj.h"

CObj::CObj()
{
}


CObj::~CObj()
{
}

const std::wstring & CObj::GetObjKey()
{
	return m_wstrObjKey;
}

const std::wstring & CObj::GetStateKey()
{
	return m_wstrStateKey;
}

const INFO * CObj::GetInfo()
{
	return &m_tInfo;
}

void CObj::SetBridge(CBridge * pBridge)
{
	m_pBridge = pBridge;
}

void CObj::SetPos(const D3DXVECTOR3 * pPos)
{
	m_tInfo.vPos = *pPos;
}

void CObj::SetObjKey(const std::wstring & wstrObjKey)
{
	m_wstrObjKey = wstrObjKey;
}

void CObj::SetStateKey(const std::wstring & wstrStateKey)
{
	m_wstrStateKey = wstrStateKey;
}
