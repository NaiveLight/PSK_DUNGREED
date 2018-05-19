#include "stdafx.h"
#include "MainGame.h"

#include "Device.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "ScrollManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "TimeManager.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize()
{
	//ShowCursor(FALSE);
	//TextureManager->InsertTexture(L"BACKGROUND", L"")

	D3DXMatrixIdentity(&m_matIdentity);

	if (FAILED(Device->Initialize()))
	{
		MSG_BOX(L"Device Initialize Failed in MainGame");
		return E_FAIL;
	}

	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
		return E_FAIL;

	m_pSprite = Device->GetSprite();
	if (m_pSprite == nullptr)
		return E_FAIL;

	D3DXFONT_DESC		tFontInfo;
	tFontInfo.Width = 10;
	tFontInfo.Height = 15;
	tFontInfo.Italic = FALSE;
	tFontInfo.Weight = FW_BOLD;
	tFontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"메이플스토리");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		MSG_BOX(L"Create Font Failed in MainGame");
		return E_FAIL;
	}

	SceneManager->ChangeScene(SCENE_LOGO);
	TimeManager->InitTime();

	return S_OK;
}

void CMainGame::Update()
{
	if (KeyManager->KeyDown(VK_F1))
		m_bIsDebug = !m_bIsDebug;
	if (KeyManager->KeyDown(VK_F5))
		SceneManager->ChangeScene(SCENE_TOWN);
	if (KeyManager->KeyDown(VK_F6))
		SceneManager->ChangeScene(SCENE_ROOM1);
	if (KeyManager->KeyDown(VK_F7))
		SceneManager->ChangeScene(SCENE_ROOM2);
	//if (KeyManager->KeyDown(VK_F5))
	//	SceneManager->ChangeScene(SCENE_TOWN);

	TimeManager->SetTime();
	SceneManager->Update();
	KeyManager->Update();
}

void CMainGame::Render()
{
	CalcFPS();

	Device->BeginDraw();

	SceneManager->Render();

	if (m_bIsDebug)
	{
		m_pSprite->SetTransform(&m_matIdentity);
		m_pFont->DrawTextW(m_pSprite, m_szFps, lstrlen(m_szFps), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	}

	Device->EndDraw(g_hWnd);
}

void CMainGame::Release()
{
	KeyManager->DestroyInstance();
	TimeManager->DestroyInstance();
	SceneManager->DestroyInstance();
	ScrollManager->DestroyInstance();
	TextureManager->DestroyInstance();
	ObjectManager->DestroyInstance();
	Device->DestroyInstance();
}

void CMainGame::CalcFPS()
{
	//std::cout << TimeManager->GetDeltaTime() << std::endl;
	m_fTime += TimeManager->GetDeltaTime();
	++m_dwCount;

	if (m_fTime > 1.f)
	{
		m_fTime = 0.f;
		wsprintf(m_szFps, L"FPS : %d", m_dwCount);
		m_dwCount = 0;
	}
}
