#include "stdafx.h"
#include "LogoScene.h"

#include "Device.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "TimeManager.h"

#include "AbstractObjFactory.h"
#include <process.h>

CLogoScene::CLogoScene()
{
}

CLogoScene::~CLogoScene()
{
	Release();
}

HRESULT CLogoScene::Initialize()
{
	Device->SetBuffColor(D3DCOLOR_ARGB(255, 0, 0, 0));
	
	if (FAILED(TextureManager->InsertTexture(L"../Texture/UI/UI_LOGO/TeamLogo/TeamLogo0%d.png", L"UI_LOGO", TEX_MULTI, L"TeamLogo", 3)))
	{
		MSG_BOX(L"Insert TeamLogo Texture Failed in LogoScene");
		return E_FAIL;
	}

	m_hThread = (HANDLE)_beginthreadex(nullptr, 0, ThreadFunc, this, 0, nullptr);

	return S_OK;
}

void CLogoScene::LateInit()
{
	ObjectManager->AddObject(OBJ_UI, CAbstractFactory<CUI_Logo>::CreateLogo(L"TeamLogo", &D3DXVECTOR3{ WINCX * 0.5f, WINCY * 0.5f, 0.f }, &FRAME{ 0.f, 0.f, 0.f }));
	ObjectManager->AddObject(OBJ_UI, CAbstractFactory<CUI_Logo>::CreateLogo(L"TeamLogo", &D3DXVECTOR3{ WINCX * 0.5f, WINCY * 0.5f, 0.f }, &FRAME{ 1.f, 0.f, 0.f }, true));

}

int CLogoScene::Update()
{
	CScene::LateInit();

	ObjectManager->Update();

	if (!m_bLogo && ObjectManager->GetObjectList(OBJ_UI)->size() == 1)
	{
		ObjectManager->AddObject(OBJ_UI, CAbstractFactory<CUI_Logo>::CreateLogo(L"TeamLogo", &D3DXVECTOR3{ WINCX * 0.5f, WINCY * 0.5f, 0.f }, &FRAME{ 2.f, 0.f, 0.f }, true));
		m_bLogo = true;
	}

	if (m_bComplete && m_bLogo && ObjectManager->GetObjectList(OBJ_UI)->size() == 1)
	{
		SceneManager->ChangeScene(SCENE_TITLE);
	}
		
	return 0;
}

void CLogoScene::Render()
{
	ObjectManager->Render();

	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	matIdentity._41 = WINCX * 0.5f - (lstrlen(TextureManager->GetLoadingMessage())) * 7.f;
	matIdentity._42 = WINCY - 30.f;

	Device->GetSprite()->SetTransform(&matIdentity);
	Device->GetFont()->DrawTextW(Device->GetSprite()
		, TextureManager->GetLoadingMessage()
		, lstrlen(TextureManager->GetLoadingMessage())
		, nullptr
		, 0
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLogoScene::Release()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
	ObjectManager->ReleaseObject(OBJ_UI);
}

unsigned int _stdcall CLogoScene::ThreadFunc(void * pArg)
{
	CLogoScene*	pLogoScene = (CLogoScene*)pArg;

	if (TextureManager->ReadImagePath(L"../Data/ImgPath.txt"))
		return 0;

	pLogoScene->m_bComplete = true;

	return 0;
}
