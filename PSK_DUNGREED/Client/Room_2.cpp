#include "stdafx.h"
#include "Room_2.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "SceneManager.h"
#include "ScrollManager.h"
#include "KeyManager.h"

CRoom_2::CRoom_2()
{
}


CRoom_2::~CRoom_2()
{
	Release();
}

HRESULT CRoom_2::Initialize()
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
		&dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTile(305)->vPos);

	ObjectManager->AddObject(OBJ_MONSTER,
		CAbstractFactory<CMonster_Skell>::CreateObj(&D3DXVECTOR3(ObjectManager->GetPlayer()->GetInfo()->vPos.x + 500.f, ObjectManager->GetPlayer()->GetInfo()->vPos.y - 300.f, 0.f)));

	return S_OK;
}

void CRoom_2::LateInit()
{
	ObjectManager->SetSceneChange(false);

	dynamic_cast<CPlayer*>(ObjectManager->GetObjectList(OBJ_PLAYER)->front())->SetMinMaxPos(
		16.f, dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileX() * TILECX - 16.f
	);

	ScrollManager->SetMaxScroll(
		float(TILECX *  (dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileX() - 20))
		, float(TILECY *  (dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileY() - 13))
	);
}

int CRoom_2::Update()
{
	CScene::LateInit();

	ObjectManager->Update();
	return 0;
}

void CRoom_2::Render()
{
	ObjectManager->Render();
}

void CRoom_2::Release()
{
	ObjectManager->ReleaseObject(OBJ_MAPOBJ);
	ObjectManager->ReleaseObject(OBJ_TILEMAP);
	ObjectManager->ReleaseObject(OBJ_LAYER);
	ObjectManager->ReleaseObject(OBJ_BACKGROUND);
}
