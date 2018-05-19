#pragma once
#include "Weapon.h"
class CWeapon_Sword :
	public CWeapon
{
public:
	CWeapon_Sword();
	virtual ~CWeapon_Sword();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void UpdateMatrix() override;
	virtual void Attack() override;

private:
	float m_fAngleOffset = 0.f;
	float m_fOffsetX = 0.f;
	float m_fOffsetY = 0.f;
};

