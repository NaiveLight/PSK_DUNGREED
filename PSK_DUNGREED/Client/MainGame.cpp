#include "stdafx.h"
#include "MainGame.h"

#include "Device.h"
#include "TextureManager.h"
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

	if (FAILED(TextureManager->ReadImagePath(L"../Data/ImgPath.txt")))
	{
		MSG_BOX(L"TextureManager ReadImage Failed in MainGame");
		return E_FAIL;
	}

	SceneManager->ChangeScene(SCENE_LOGO);
	TimeManager->InitTime();

	return S_OK;
}

void CMainGame::Update()
{
	TimeManager->SetTime();
	SceneManager->Update();
	KeyManager->Update();
}

void CMainGame::Render()
{
	Device->BeginDraw();
	SceneManager->Render();
	Device->EndDraw(g_hWnd);
}

void CMainGame::Release()
{
	KeyManager->DestroyInstance();
	TimeManager->DestroyInstance();
	SceneManager->DestroyInstance();
	TextureManager->DestroyInstance();
	Device->DestroyInstance();
}
