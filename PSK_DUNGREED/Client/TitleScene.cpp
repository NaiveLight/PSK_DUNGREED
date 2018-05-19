#include "stdafx.h"
#include "TitleScene.h"

#include "Include.h"
#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"

CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
	Release();
}

HRESULT CTitleScene::Initialize()
{
	Device->SetBuffColor(D3DCOLOR_ARGB(255, 121, 185, 255));
	ObjectManager->SetSceneChange(false);

	ObjectManager->AddObject(OBJ_BACKGROUND, CAbstractFactory<CBackGround>::CreateBackGround(L"BackCloud"));
	ObjectManager->AddObject(OBJ_BACKGROUND, CAbstractFactory<CBackGround>::CreateBackGround(L"FrontCloud"));
	ObjectManager->AddObject(OBJ_UI, CAbstractFactory<CUI_Logo>::CreateLogo(L"MainLogo", &D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f - 130.f, 0.f), &FRAME{ 0.f, 0.f, 0.f }));
	ObjectManager->AddObject(OBJ_UI, CAbstractFactory<CUI_Logo>::CreateLogo(L"Copyright", &D3DXVECTOR3(WINCX * 0.5f, WINCY - 35.f, 0.f), &FRAME{ 0.f, 0.f, 0.f }));
	ObjectManager->AddObject(OBJ_UI, CAbstractFactory<CUI_Button>::CreateButton(L"Play", &D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f + 96.f, 0.f), BUTTONID::BT_TSTART));
	ObjectManager->AddObject(OBJ_UI, CAbstractFactory<CUI_Button>::CreateButton(L"Option", &D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f + 96 + 48.f, 0.f), BUTTONID::BT_TSTART));
	ObjectManager->AddObject(OBJ_UI, CAbstractFactory<CUI_Button>::CreateButton(L"Exit", &D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f + 96.f + 96.f, 0.f), BUTTONID::BT_TSTART));
	ObjectManager->AddObject(OBJ_CURSOR, CAbstractFactory<CUI_Cursor>::CreateCursor(&FRAME(0.f, 0.f, 0.f)));

	return S_OK;
}

void CTitleScene::LateInit()
{
}

int CTitleScene::Update()
{
	CScene::LateInit();
	ObjectManager->Update();

	return 0;
}

void CTitleScene::Render()
{
	ObjectManager->Render();
}

void CTitleScene::Release()
{
	ObjectManager->ReleaseObject(OBJ_BACKGROUND);
	ObjectManager->ReleaseObject(OBJ_UI);
}
