#include "stdafx.h"
#include "Obj_Door.h"

#include "Device.h"
#include "Player.h"
#include "ObjectManager.h"
#include "ScrollManager.h"
#include "TimeManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "SoundManager.h"

CObj_Door::CObj_Door()
{
}

CObj_Door::~CObj_Door()
{
	Release();
}

HRESULT CObj_Door::Initialize()
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
	m_wstrStateKey = L"Door";
	m_tInfo.vDir = m_tInfo.vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tFrame = FRAME(0.f, 5.f, 10.f);

	SoundManager->PlaySound(L"Door.wav", CSoundManager::MAPOBJ);

	return S_OK;
}

int CObj_Door::Update()
{
	m_tFrame.fFrame += m_tFrame.fCount * TimeManager->GetDeltaTime();
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = m_tFrame.fMax - 1;

	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x + 114.f - ScrollManager->GetScroll().x
		, m_tInfo.vPos.y - 98.f - ScrollManager->GetScroll().y
		, 0.f);

	return 0;
}

void CObj_Door::Render()
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

void CObj_Door::Release()
{
}
