#pragma once

#include "Include.h"

class CScrollManager :
	public CSingleton<CScrollManager>
{
public:
	CScrollManager();
	virtual ~CScrollManager();

public:
	void SetCurScroll(float fX, float fY);
	void SetMinScroll(float fX, float fY);
	void SetMaxScroll(float fX, float fY);
	void AddScroll(float fX, float fY);

public:
	const D3DXVECTOR3& GetScroll() const;
	const D3DXVECTOR3& GetMaxScroll() const;

private:
	D3DXVECTOR3 m_vScroll = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3 m_vMinScroll = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXVECTOR3 m_vMaxScroll = D3DXVECTOR3(0.f, 0.f, 0.f);
};

