#include "stdafx.h"
#include "Room_1.h"

#include "Device.h"
#include "Player.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "SceneManager.h"
#include "ScrollManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

CRoom_1::CRoom_1()
{
}

CRoom_1::~CRoom_1()
{
	Release();
}

HRESULT CRoom_1::Initialize()
{
	Device->SetBuffColor(D3DCOLOR_ARGB(255, 44, 46, 59));

	if (ObjectManager->GetPlayer() == nullptr)
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::CreateObj();
		ObjectManager->AddObject(OBJ_PLAYER, pPlayer);
		ObjectManager->SetPlayer(pPlayer);
	}

	dynamic_cast<CPlayer*>(ObjectManager->GetPlayer())->SetInpuActive(true);
	dynamic_cast<CPlayer*>(ObjectManager->GetPlayer())->SetDungeonEnter(false);
	ObjectManager->AddObject(OBJ_TILEMAP, CAbstractFactory<CTileMap>::CreateTileMap(L"Room1_TILE.dat"));
	ObjectManager->AddObject(OBJ_MAPOBJ, CAbstractFactory<CMapObj>::CreateMapObj(L"Room1_OBJ.dat"));
	ObjectManager->GetObjectList(OBJ_CURSOR)->front()->SetFrame(&FRAME(1.f, 0.f, 0.f));

	ObjectManager->GetPlayer()->SetPos(
		&dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTile(338)->vPos);

	return S_OK;
}

void CRoom_1::LateInit()
{
	ObjectManager->SetSceneChange(false);

	dynamic_cast<CPlayer*>(ObjectManager->GetObjectList(OBJ_PLAYER)->front())->SetMinMaxPos(
		16.f, dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileX() * TILECX - 16.f
	);

	ScrollManager->SetMaxScroll(
		float(TILECX *  (dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileX() - 20))
		, float(TILECY *  (dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileY() - 13))
	);

	SoundManager->PlayBGM(L"BG_FIELD.wav");
}

int CRoom_1::Update()
{
	CScene::LateInit();

	ObjectManager->Update();

	return 0;
}

void CRoom_1::Render()
{
	ObjectManager->Render();
}

void CRoom_1::Release()
{
	ObjectManager->ReleaseObject(OBJ_MAPOBJ);
	ObjectManager->ReleaseObject(OBJ_TILEMAP);
	ObjectManager->ReleaseObject(OBJ_LAYER);
	ObjectManager->ReleaseObject(OBJ_MONSTER);
	ObjectManager->ReleaseObject(OBJ_BACKGROUND);
}
