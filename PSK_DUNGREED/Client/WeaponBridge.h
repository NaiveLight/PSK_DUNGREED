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
};

