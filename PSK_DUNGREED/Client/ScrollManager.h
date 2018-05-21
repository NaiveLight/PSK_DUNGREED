#pragma once

#include "Include.h"

class CScrollManager :
	public CSingleton<CScrollManager>
{
public:
	CScrollManager();
	virtual ~CScrollManager();

public:
	const bool& GetShaking() { return m_bIsShaking; }
	const bool& GetFocus() { return m_bIsFocusing; }

public:
	void Update();

public:
	void SetCurScroll(float fX, float fY);
	void SetMinScroll(float fX, float fY);
	void SetMaxScroll(float fX, float fY);
	void AddScroll(float fX, float fY);

	void ShakingStart(float fPower, float fTime);
	void ShakingEnd();

	void FocusingStart(const D3DXVECTOR3& vPos, float fTime);
	void FocusingEnd();

public:
	const D3DXVECTOR3& GetScroll() const;
	const D3DXVECTOR3& GetMaxScroll() const;

private:
	D3DXVECTOR3 m_vScroll = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3 m_vMinScroll = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3 m_vMaxScroll = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3 m_vFocusScroll = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3 m_vPrevScroll = D3DXVECTOR3(0.f, 0.f, 0.f);

private:
	float m_fShakePower = 0.f;
	float m_fShakeTime = 0.f;
	float m_fFocusTime = 0.f;
	bool m_bIsShaking = false;
	bool m_bIsFocusing = false;
};

