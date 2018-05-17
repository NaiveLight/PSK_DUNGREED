#pragma once
#include "UI.h"
class CUI_Logo :
	public CUI
{
public:
	CUI_Logo();
	virtual ~CUI_Logo();

public:
	void SetAlphaBlend(const bool bAlpha);

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	bool m_bAlpha = false;
	float m_fAlphaVal = 150.f;
};

