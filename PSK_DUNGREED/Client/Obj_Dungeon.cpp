#include "stdafx.h"
#include "Obj_Dungeon.h"

#include "Device.h"
#include "Player.h"
#include "ObjectManager.h"
#include "ScrollManager.h"
#include "TimeManager.h"
#include "TextureManager.h"
#include "SceneManager.h"

CObj_Dungeon::CObj_Dungeon()
{
}

CObj_Dungeon::~CObj_Dungeon()
{
	Release();
}

HRESULT CObj_Dungeon::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Obj_Dungeon Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Obj_Dungeon Get Sprite Failed");
		return E_FAIL;
	}

	m_wstrObjKey = L"OBJECT";
	m_wstrStateKey = L"DungeonEat";
	m_tInfo.vDir = m_tInfo.vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tFrame = FRAME(0.f, 27.f, 27.f);

	return S_OK;


}

int CObj_Dungeon::Update()
{
	if ((int)m_tFrame.fFrame > 8.f)
		dynamic_cast<CPlayer*>(ObjectManager->GetPlayer())->SetDungeonEnter(true);

	m_tFrame.fFrame += m_tFrame.fCount * TimeManager->GetDeltaTime();
	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		SceneManager->ChangeScene(SCENE_ROOM1);
		return 1;
	}
		
	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x - ScrollManager->GetScroll().x
		, m_tInfo.vPos.y - 106.f - ScrollManager->GetScroll().y
		, 0.f);

	return 0;
}

void CObj_Dungeon::Render()
{
	const TEXINFO*		pTexInfo = TextureManager->GetTexture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
		return;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CObj_Dungeon::Release()
{
}
