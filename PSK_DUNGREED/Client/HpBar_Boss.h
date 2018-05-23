#pragma once
#include "UI.h"
class CHpBar_Boss :
	public CUI
{
public:
	CHpBar_Boss();
	virtual ~CHpBar_Boss();

	// CUI을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	RECT m_tRect = {};
	int m_iCurHp = 0;
	int m_iMaxHp = 0;
	float m_fHpRatio = 0;
};

