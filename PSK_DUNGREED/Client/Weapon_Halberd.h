#pragma once
#include "Weapon.h"
class CWeapon_Halberd :
	public CWeapon
{
public:
	CWeapon_Halberd();
	virtual ~CWeapon_Halberd();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void UpdateMatrix() override;
	virtual void Attack() override;
};