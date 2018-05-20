#pragma once
#include "UI.h"
class CDashBar :
	public CUI
{
public:
	CDashBar();
	virtual ~CDashBar();

	// CUI��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	RECT m_tRect = {};
	int m_iCurDash = 0;
	int m_iMaxDash = 2;
};

