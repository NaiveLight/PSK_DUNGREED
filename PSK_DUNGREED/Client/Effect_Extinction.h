#pragma once
#include "EffectBridge.h"
class CEffect_Extinction :
	public CEffectBridge
{
public:
	CEffect_Extinction();
	virtual ~CEffect_Extinction();

public:
	virtual HRESULT Initialize() override;
	virtual int Update(INFO & rInfo) override;
	virtual void Render() override;
	virtual void Release() override;
};

