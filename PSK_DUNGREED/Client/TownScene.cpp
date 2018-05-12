#include "stdafx.h"
#include "TownScene.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "ScrollManager.h"
#include "KeyManager.h"

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
	ObjectManager->AddObject(OBJ_TILEMAP, CAbstractFactory<CTileMap>::CreateTileMap(L"Town_TILE.dat"));
	return S_OK;
}

void CTownScene::LateInit()
{
	ObjectManager->SetSceneChange(false);
}

int CTownScene::Update()
{
	CScene::LateInit();

	if (KeyManager->KeyPressing('W'))
		ScrollManager->SetScroll(D3DXVECTOR3(0.f, -5.f, 0.f));
	if (KeyManager->KeyPressing('A'))
		ScrollManager->SetScroll(D3DXVECTOR3(-5.f, 0.f, 0.f));
	if (KeyManager->KeyPressing('S'))
		ScrollManager->SetScroll(D3DXVECTOR3(0.f, 5.f, 0.f));
	if (KeyManager->KeyPressing('D'))
		ScrollManager->SetScroll(D3DXVECTOR3(5.f, 0.f, 0.f));

	std::cout << ScrollManager->GetScroll().x << " / "  << ScrollManager->GetScroll().y<< std::endl;


	ObjectManager->Update();
	return 0;
}

void CTownScene::Render()
{
	ObjectManager->Render();
}

void CTownScene::Release()
{
	ObjectManager->ReleaseObject(OBJ_BACKGROUND);
	ObjectManager->ReleaseObject(OBJ_TILEMAP);
}
