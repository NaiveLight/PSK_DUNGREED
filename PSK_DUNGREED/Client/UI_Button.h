#pragma once
#include "UI.h"
class CUI_Button :
	public CUI
{
public:
	CUI_Button();
	virtual ~CUI_Button();

public:
	void SetButtonID(BUTTONID eBtID) { m_eBtID = eBtID; }

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void UpdateRect();
	int CheckInput();

private:
	BUTTONID m_eBtID = BT_END;
	RECT			m_tHitRect = {};
};

