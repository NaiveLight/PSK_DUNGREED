#pragma once
#include "Weapon.h"
class CWeapon_Hand :
	public CWeapon
{
public:
	CWeapon_Hand();
	virtual ~CWeapon_Hand();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
	
public:
	virtual void UpdateMatrix() override;
	virtual void Attack() override;

private:
	void UpdateHitBox();
};

