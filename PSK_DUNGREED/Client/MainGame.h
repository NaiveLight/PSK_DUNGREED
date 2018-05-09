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
	LPDIRECT3DDEVICE9	m_pDevice = nullptr;
	LPD3DXSPRITE				m_pSprite = nullptr;

private:
	D3DXMATRIX	m_matIdentity;
};

