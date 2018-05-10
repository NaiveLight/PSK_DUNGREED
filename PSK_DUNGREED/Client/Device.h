#pragma once

#include "Include.h"

class CDevice :
	public CSingleton<CDevice>
{
public:
	CDevice();
	virtual ~CDevice();

public:
	void SetBuffColor(const D3DXCOLOR& buffColor);

public:
	const LPDIRECT3DDEVICE9 GetDevice();
	const LPD3DXSPRITE	GetSprite();
	const LPD3DXFONT		GetFont();

public:
	HRESULT Initialize();

public:
	void BeginDraw();
	void EndDraw(HWND hWnd);

private:
	void SetParameters(D3DPRESENT_PARAMETERS& d3dpp);
	void Release();

private:
	LPDIRECT3D9	m_p3D = nullptr;
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT	m_pFont = nullptr;

private:
	D3DXCOLOR	m_backBuffColor = D3DCOLOR_ARGB(255, 0, 0, 255);
};