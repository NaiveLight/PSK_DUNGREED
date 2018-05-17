#pragma once
#include "Bridge.h"
class CWeaponBridge :
	public CBridge
{
public:
	CWeaponBridge();
	virtual ~CWeaponBridge();

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update(INFO & rInfo) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	LPD3DXSPRITE m_pSprite = nullptr;

protected:
	float m_fRevolveAngle = 0.f;
	float m_fRotateAngle = 0.f;
};

