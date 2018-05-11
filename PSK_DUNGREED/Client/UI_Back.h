#pragma once
#include "UIBridge.h"
class CUI_Back :
	public CUIBridge
{
public:
	CUI_Back();
	virtual ~CUI_Back();

public:
	virtual HRESULT Initialize(void) override;
	virtual int Update(INFO & rInfo) override;
	virtual void Render(void) override;
	virtual void Release(void) override;


};

