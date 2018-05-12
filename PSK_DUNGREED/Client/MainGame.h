#pragma once

#include "Include.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	HRESULT Initialize();
	void Update();
	void Render();

private:
	void Release();

private:
	void CalcFPS();

private:
	LPDIRECT3DDEVICE9	m_pDevice = nullptr;
	LPD3DXSPRITE				m_pSprite = nullptr;
	LPD3DXFONT				m_pFont = nullptr;

private:
	float m_fTime = 0.f;
	DWORD m_dwCount = 0;
	TCHAR m_szFps[128] = L"";
	D3DXMATRIX	m_matIdentity;

	bool m_bIsDebug = false;
};

