#include "stdafx.h"
#include "TownScene.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"

CTownScene::CTownScene()
{
}

CTownScene::~CTownScene()
{
	Release();
}

HRESULT CTownScene::Initialize()
{
	Device->SetBuffColor(D3DCOLOR_ARGB(255, 0, 0, 0));
	ObjectManager->AddObject(OBJ_BACKGROUND, CAbstractFactory<CBackGround>::CreateBackGround(L"Town"));

	return S_OK;
}

int CTownScene::Update()
{
	return 0;
}

void CTownScene::Render()
{
}

void CTownScene::Release()
{
}
