#pragma once
#include "Obj.h"

class CWeapon :
	public CObj
{
public:
	CWeapon();
	virtual ~CWeapon();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

