#include "stdafx.h"
#include "TownScene.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "ScrollManager.h"

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

void CTownScene::LateInit()
{
	//ScrollManager->SetMinScroll(0.f, 0.f);
	//ScrollManager->SetMaxScroll(0.f, 0.f);
	//ScrollManager->SetScroll(0.f, 0.f);

	ObjectManager->SetSceneChange(false);
}

int CTownScene::Update()
{
	CScene::LateInit();
	ObjectManager->Update();
	return 0;
}

void CTownScene::Render()
{
	ObjectManager->Render();
}

void CTownScene::Release()
{

}
