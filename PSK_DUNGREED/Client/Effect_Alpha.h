#pragma once
#include "EffectBridge.h"
class CEffect_Alpha :
	public CEffectBridge
{
public:
	CEffect_Alpha();
	virtual ~CEffect_Alpha();

public:
	virtual HRESULT Initialize() override;
	virtual int Update(INFO & rInfo) override;
	virtual void Render() override;
	virtual void Release() override;

private:
	bool m_bIsLeft = 0.f;
	float m_fAlpha = 0.f;
};

