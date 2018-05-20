#pragma once
#include "UI.h"

class CEffect;
class CHpBar_Player :
	public CUI
{
public:
	CHpBar_Player();
	virtual ~CHpBar_Player();

	// CUI을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	LPD3DXFONT m_pFont = nullptr;
	CObj* m_pHpEffect = nullptr;
	RECT m_tRect = {};
	int m_iLev = 0;
	int m_iCurHp = 0;
	int m_iMaxHp = 0;
	float m_fHpRatio = 0.f;
	TCHAR m_szLev[128]= L"";
	TCHAR m_szHp[128] = L"";
};

