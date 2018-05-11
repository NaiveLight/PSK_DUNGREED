#pragma once
#include "UI.h"
class CUI_Cursor :
	public CUI
{
public:
	CUI_Cursor();
	virtual ~CUI_Cursor();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

