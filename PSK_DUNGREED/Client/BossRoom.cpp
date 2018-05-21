#include "stdafx.h"
#include "BossRoom.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "SceneManager.h"
#include "ScrollManager.h"
#include "KeyManager.h"
#include "SoundManager.h"

CBossRoom::CBossRoom()
{
}


CBossRoom::~CBossRoom()
{
	Release();
}

HRESULT CBossRoom::Initialize()
{
	Device->SetBuffColor(D3DCOLOR_ARGB(255, 44, 46, 59));

	if (ObjectManager->GetPlayer() == nullptr)
	{
		CObj* pPlayer = CAbstractFactory<CPlayer>::CreateObj();
		ObjectManager->AddObject(OBJ_PLAYER, pPlayer);
		ObjectManager->SetPlayer(pPlayer);
	}

	ObjectManager->AddObject(OBJ_TILEMAP, CAbstractFactory<CTileMap>::CreateTileMap(L"Boss_TILE.dat"));
	ObjectManager->AddObject(OBJ_MAPOBJ, CAbstractFactory<CMapObj>::CreateMapObj(L"Boss_OBJ.dat"));
	ObjectManager->GetObjectList(OBJ_CURSOR)->front()->SetFrame(&FRAME(1.f, 0.f, 0.f));

	ObjectManager->GetPlayer()->SetPos(
		&dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTile(1052)->vPos);

	//704 º¸½º
	D3DXVECTOR3 vPos = dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTile(704)->vPos;
	//vPos.x += 32.f;
	//vPos.y += 32.f;
	ObjectManager->AddObject(OBJ_MONSTER,
		CAbstractFactory<CBelial>::CreateObj(&vPos));

	return S_OK;
}

void CBossRoom::LateInit()
{
	ObjectManager->SetSceneChange(false);

	dynamic_cast<CPlayer*>(ObjectManager->GetObjectList(OBJ_PLAYER)->front())->SetMinMaxPos(
		16.f, dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileX() * TILECX - 16.f
	);

	ScrollManager->SetMaxScroll(
		float(TILECX *  (dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileX() - 20))
		, float(TILECY *  (dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front())->GetTileY() - 13))
	);

	SoundManager->PlayBGM(L"BG_BOSSROOM.wav");
}

int CBossRoom::Update()
{
	CScene::LateInit();

	ObjectManager->Update();
	return 0;
}

void CBossRoom::Render()
{
	ObjectManager->Render();
}

void CBossRoom::Release()
{
	SoundManager->StopAll();
	ObjectManager->ReleaseObject(OBJ_MONSTER);
	ObjectManager->ReleaseObject(OBJ_MAPOBJ);
	ObjectManager->ReleaseObject(OBJ_TILEMAP);
}
