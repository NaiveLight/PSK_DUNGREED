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

const FRAME * CObj::GetFrame()
{
	return &m_tFrame;
}

void CObj::SetBridge(CBridge * pBridge)
{
	m_pBridge = pBridge;
}

void CObj::SetPos(const D3DXVECTOR3 * pPos)
{
	m_tInfo.vPos = *pPos;
}

void CObj::SetFrame(const FRAME * pFrame)
{
	m_tFrame = *pFrame;
}

void CObj::SetObjKey(const std::wstring & wstrObjKey)
{
	m_wstrObjKey = wstrObjKey;
}

void CObj::SetStateKey(const std::wstring & wstrStateKey)
{
	m_wstrStateKey = wstrStateKey;
}

void CObj::UpdateMatrix()
{
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x
		, m_tInfo.vPos.y
		, 0.f);
}
