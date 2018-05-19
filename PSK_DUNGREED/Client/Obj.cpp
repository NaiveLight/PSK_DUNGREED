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

const HITBOX * CObj::GetHitBox()
{
	return &m_tHitBox;
}

const bool & CObj::GetIsLeft()
{
	return m_bIsLeft;
}

void CObj::SetBridge(CBridge * pBridge)
{
	m_pBridge = pBridge;
}

void CObj::SetPos(const D3DXVECTOR3 * pPos)
{
	m_tInfo.vPos = *pPos;
}

void CObj::SetHitBox(const HITBOX * pHitBox)
{
	m_tHitBox = *pHitBox;
}

void CObj::SetDir(const D3DXVECTOR3 * pDir)
{
	m_tInfo.vDir = *pDir;
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

void CObj::SetIsLeft(const bool & bIsLeft)
{
	m_bIsLeft = bIsLeft;
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
