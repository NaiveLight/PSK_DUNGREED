#include "stdafx.h"
#include "TownScene.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "SceneManager.h"
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

	if (ObjectManager->GetPlayer() == nullptr)
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::CreateObj();
		ObjectManager->AddObject(OBJ_PLAYER, pPlayer);
		ObjectManager->SetPlayer(pPlayer);
	}

	ObjectManager->AddObject(OBJ_BACKGROUND, CAbstractFactory<CBackGround>::CreateBackGround(L"Town"));
	ObjectManager->AddObject(OBJ_LAYER, CAbstractFactory<CLayer>::CreateLayer(L"Town", 0.05f, &D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f + 50.f, 0.f), &FRAME(0.f, 0.f, 0.f)));
	ObjectManager->AddObject(OBJ_LAYER, CAbstractFactory<CLayer>::CreateLayer(L"Town", 0.2f, &D3DXVECTOR3(WINCX * 0.5f + 100.f, WINCY * 0.5f + 400.f, 0.f), &FRAME(1.f, 1.f, 1.f)));
	ObjectManager->AddObject(OBJ_TILEMAP, CAbstractFactory<CTileMap>::CreateTileMap(L"Town_TILE.dat"));
	ObjectManager->AddObject(OBJ_MAPOBJ, CAbstractFactory<CMapObj>::CreateMapObj(L"Town_OBJ.dat"));
	ObjectManager->GetObjectList(OBJ_CURSOR)->front()->SetFrame(&FRAME(1.f, 0.f, 0.f));

	ObjectManager->GetPlayer()->SetPos(
		&dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTile(2004)->vPos);
	
	ObjectManager->AddObject(OBJ_MONSTER, 
		CAbstractFactory<CMonster_Skell>::CreateObj(&D3DXVECTOR3(ObjectManager->GetPlayer()->GetInfo()->vPos.x + 500.f, ObjectManager->GetPlayer()->GetInfo()->vPos.y - 300.f, 0.f)));
	return S_OK;
}

void CTownScene::LateInit()
{
	ObjectManager->SetSceneChange(false);
	
	dynamic_cast<CPlayer*>(ObjectManager->GetObjectList(OBJ_PLAYER)->front())->SetMinMaxPos(
		16.f, dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileX() * TILECX - 16.f
	);

	ScrollManager->SetMaxScroll(TILECX * 95, TILECY * 17);
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
	ObjectManager->ReleaseObject(OBJ_MAPOBJ);
	ObjectManager->ReleaseObject(OBJ_TILEMAP);
	ObjectManager->ReleaseObject(OBJ_LAYER);
	ObjectManager->ReleaseObject(OBJ_BACKGROUND);
}
