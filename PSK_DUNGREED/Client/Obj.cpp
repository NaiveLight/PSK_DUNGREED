#include "stdafx.h"
#include "Obj.h"

CObj::CObj()
{
}


CObj::~CObj()
{
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
