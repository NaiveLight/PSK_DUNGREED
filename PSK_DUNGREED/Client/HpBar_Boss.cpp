#include "stdafx.h"
#include "HpBar_Boss.h"
#include "Device.h"
#include "PlayerObserver.h"
#include "DataSubject.h"
#include "TextureManager.h"

#include "Obj.h"

CHpBar_Boss::CHpBar_Boss()
{
}


CHpBar_Boss::~CHpBar_Boss()
{
	Release();
}

HRESULT CHpBar_Boss::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"HPBar Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"HPBar Get Sprite Failed");
		return E_FAIL;
	}

	m_tInfo.vPos = D3DXVECTOR3(WINCX * 0.5f, WINCY - 64.f, 0.f);

	m_wstrObjKey = L"UI_BOSS";

	m_pObserver = new CPlayerObserver;
	CDataSubject::GetInstance()->Subscribe(m_pObserver);
	CDataSubject::GetInstance()->Notify(BOSS_DATA);
	return S_OK;
}

int CHpBar_Boss::Update()
{
	m_iCurHp = static_cast<CPlayerObserver*>(m_pObserver)->GetBossData()->iCurHp;
	m_iMaxHp = static_cast<CPlayerObserver*>(m_pObserver)->GetBossData()->iMaxHp;
	m_fHpRatio = (float)m_iCurHp / (float)m_iMaxHp;

	m_tRect = {
		LONG(0)
		, LONG(0)
		,  LONG(400.f * m_fHpRatio)
		,  LONG(40)
	};

	return 0;
}

void CHpBar_Boss::Render()
{
	/*
	UI_BOSS|BossHp|1|..\Texture\UI\UI_BOSS\BossHp\BossHp0%d.png
	UI_BOSS|BossHpBack|1|..\Texture\UI\UI_BOSS\BossHpBack\BossHpBack0%d.png
	UI_BOSS|BossHpBase|1|..\Texture\UI\UI_BOSS\BossHpBase\BossHpBase0%d.png
	UI_BOSS|BossIcon|1|..\Texture\UI\UI_BOSS\BossIcon\BossIcon0%d.png
	*/

	const TEXINFO* pTexInfo = TextureManager->GetTexture(m_wstrObjKey, L"BossHpBack", 0);

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	
	pTexInfo = TextureManager->GetTexture(m_wstrObjKey, L"BossHp", 0);

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x - 161.f, m_tInfo.vPos.y - 20.f, 0.f);

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, &m_tRect
		, nullptr
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = TextureManager->GetTexture(m_wstrObjKey, L"BossIcon", 0);

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x - 205.f, m_tInfo.vPos.y, 0.f);

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	pTexInfo = TextureManager->GetTexture(m_wstrObjKey, L"BossHpBase", 0);

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CHpBar_Boss::Release()
{
	Safe_Delete(m_pObserver);
}
