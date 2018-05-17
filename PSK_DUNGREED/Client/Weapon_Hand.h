#pragma once
#include "WeaponBridge.h"

class CWeapon_Hand :
	public CWeaponBridge
{
public:
	CWeapon_Hand();
	virtual ~CWeapon_Hand();

public:
	virtual HRESULT Initialize() override;
	virtual int Update(INFO & rInfo) override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void UpdateMatrix(INFO& rInfo);
};

