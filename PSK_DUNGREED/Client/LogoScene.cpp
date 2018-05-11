#include "stdafx.h"
#include "LogoScene.h"

#include "Device.h"
#include "ObjectManager.h"
#include "TextureManager.h"

#include "AbstractObjFactory.h"

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
	
	if (FAILED(TextureManager->InsertTexture(L"../Texture/UI/TeamLogo0%d.png", L"UI", TEX_MULTI, L"TeamLogo", 3)))
	{
		MSG_BOX(L"Insert TeamLogo Texture Failed in LogoScene");
		return E_FAIL;
	}



	return S_OK;
}

int CLogoScene::Update()
{
	ObjectManager->Update();
	return 0;
}

void CLogoScene::Render()
{
	ObjectManager->Render();
}

void CLogoScene::Release()
{
}
