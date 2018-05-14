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
	ObjectManager->AddObject(OBJ_PLAYER, CAbstractFactory<CPlayer>::CreateObj());
	ObjectManager->AddObject(OBJ_BACKGROUND, CAbstractFactory<CBackGround>::CreateBackGround(L"Town"));
	ObjectManager->AddObject(OBJ_LAYER, CAbstractFactory<CLayer>::CreateLayer(L"Town", 0.05f, &D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f + 50.f, 0.f), &FRAME(0.f, 0.f, 0.f)));
	ObjectManager->AddObject(OBJ_LAYER, CAbstractFactory<CLayer>::CreateLayer(L"Town", 0.2f, &D3DXVECTOR3(WINCX * 0.5f + 100.f, WINCY * 0.5f + 400.f, 0.f), &FRAME(1.f, 1.f, 1.f)));
	ObjectManager->AddObject(OBJ_TILEMAP, CAbstractFactory<CTileMap>::CreateTileMap(L"Town_TILE.dat"));
	ObjectManager->AddObject(OBJ_MAPOBJ, CAbstractFactory<CMapObj>::CreateMapObj(L"Town_OBJ.dat"));
	return S_OK;
}

void CTownScene::LateInit()
{
	ObjectManager->SetSceneChange(false);
	ScrollManager->SetMaxScroll(TILECX * 95, TILECY * 17);
}

int CTownScene::Update()
{
	CScene::LateInit();

	//if (KeyManager->KeyPressing('W'))
	//	ScrollManager->SetScroll(D3DXVECTOR3(0.f, -10.f, 0.f));
	//if (KeyManager->KeyPressing('A'))
	//	ScrollManager->SetScroll(D3DXVECTOR3(-10.f, 0.f, 0.f));
	//if (KeyManager->KeyPressing('S'))
	//	ScrollManager->SetScroll(D3DXVECTOR3(0.f, 10.f, 0.f));
	//if (KeyManager->KeyPressing('D'))
		//ScrollManager->SetScroll(D3DXVECTOR3(10.f, 0.f, 0.f));

	//std::cout << ScrollManager->GetScroll().x << " / "  << ScrollManager->GetScroll().y<< std::endl;


	ObjectManager->Update();
	return 0;
}

void CTownScene::Render()
{
	ObjectManager->Render();
}

void CTownScene::Release()
{
	ObjectManager->ReleaseObject(OBJ_MAPOBJ);
	ObjectManager->ReleaseObject(OBJ_TILEMAP);
	ObjectManager->ReleaseObject(OBJ_LAYER);
	ObjectManager->ReleaseObject(OBJ_BACKGROUND);
}
