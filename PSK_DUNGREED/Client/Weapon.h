#pragma once
#include "Obj.h"

class CWeapon :
	public CObj
{
public:
	CWeapon();
	virtual ~CWeapon();

public:
	const bool& GetIsRectHit() { return m_bRectHit; }
	const float& GetAttackTime() { return m_fAttTime; }
	const bool& GetRenderFirst() { return m_bRender; }
	const int& GetAtt() { return m_iAtt; }

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	virtual void Attack() PURE;

protected:
	virtual void CreateHitBox();

protected:
	D3DXVECTOR3 m_vOrigin = D3DXVECTOR3(0.f, 0.f, 0.f);
	int m_iAtt = 0.f;
	float m_fAttTime = 0.f;
	float m_fRotateAngle = 0.f;
	float m_fRevolveAngle = 0.f;
	float m_bTempLeft = false;
	bool m_bRectHit = false;
	bool m_bAttack = false;
	bool m_bRender = false;
};

