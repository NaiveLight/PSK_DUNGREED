#include "stdafx.h"
#include "Room_3.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "SceneManager.h"
#include "ScrollManager.h"
#include "KeyManager.h"

CRoom_3::CRoom_3()
{
}

CRoom_3::~CRoom_3()
{
	Release();
}

HRESULT CRoom_3::Initialize()
{
	Device->SetBuffColor(D3DCOLOR_ARGB(255, 44, 46, 59));

	if (ObjectManager->GetPlayer() == nullptr)
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::CreateObj();
		ObjectManager->AddObject(OBJ_PLAYER, pPlayer);
		ObjectManager->SetPlayer(pPlayer);
	}

	ObjectManager->AddObject(OBJ_LAYER, CAbstractFactory<CLayer>::CreateLayer(L"Dungeon", 0.05f, &D3DXVECTOR3(WINCX * 0.5f - 100.f, WINCY * 0.5f + 150.f, 0.f), &FRAME(0.f, 0.f, 0.f)));
	ObjectManager->AddObject(OBJ_TILEMAP, CAbstractFactory<CTileMap>::CreateTileMap(L"Room3_TILE.dat"));
	ObjectManager->AddObject(OBJ_MAPOBJ, CAbstractFactory<CMapObj>::CreateMapObj(L"Room3_OBJ.dat"));
	ObjectManager->GetObjectList(OBJ_CURSOR)->front()->SetFrame(&FRAME(1.f, 0.f, 0.f));

	ObjectManager->GetPlayer()->SetPos(
		&dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTile(287)->vPos);

	ObjectManager->AddObject(OBJ_MONSTER,
		CAbstractFactory<CMonster_Banshee>::CreateObj(&dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTile(164)->vPos));
	ObjectManager->AddObject(OBJ_MONSTER,
		CAbstractFactory<CMonster_Skell>::CreateObj(&dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTile(293)->vPos));
	ObjectManager->AddObject(OBJ_MONSTER,
		CAbstractFactory<CMonster_Skell>::CreateObj(&dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTile(300)->vPos));


	return S_OK;
}

void CRoom_3::LateInit()
{
	ObjectManager->SetSceneChange(false);

	dynamic_cast<CPlayer*>(ObjectManager->GetObjectList(OBJ_PLAYER)->front())->SetMinMaxPos(
		16.f, dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileX() * TILECX - 16.f
	);

	ScrollManager->SetMaxScroll(
		float(TILECX *  (dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileX() - 20))
		, float(TILECY *  (dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileY() - 10))
	);
}

int CRoom_3::Update()
{
	CScene::LateInit();

	ObjectManager->Update();
	return 0;
}

void CRoom_3::Render()
{
	ObjectManager->Render();
}

void CRoom_3::Release()
{
	ObjectManager->ReleaseObject(OBJ_MONSTER);
	ObjectManager->ReleaseObject(OBJ_MAPOBJ);
	ObjectManager->ReleaseObject(OBJ_TILEMAP);
	ObjectManager->ReleaseObject(OBJ_LAYER);
}
