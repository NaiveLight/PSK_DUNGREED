#include "stdafx.h"
#include "HpBar_Player.h"
#include "Device.h"
#include "PlayerObserver.h"
#include "DataSubject.h"
#include "TextureManager.h"

#include "Obj.h"
#include "HpEffect.h"

CHpBar_Player::CHpBar_Player()
{
}

CHpBar_Player::~CHpBar_Player()
{
	Release();
}

HRESULT CHpBar_Player::Initialize()
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

	m_pFont = Device->GetFont();

	m_tInfo.vPos = D3DXVECTOR3(150.f, 34.f, 0.f);

	m_pHpEffect = new CHpEffect;
	m_pHpEffect->Initialize();

	m_wstrObjKey = L"UI_HPBAR";

	m_pObserver = new CPlayerObserver;
	CDataSubject::GetInstance()->Subscribe(m_pObserver);
	CDataSubject::GetInstance()->Notify(PLAYER_DATA);
	CDataSubject::GetInstance()->Notify(PLAYER_PDATA);
	return S_OK;
}

int CHpBar_Player::Update()
{
	m_iLev = static_cast<CPlayerObserver*>(m_pObserver)->GetPlayerData()->iLevel;
	m_iCurHp = static_cast<CPlayerObserver*>(m_pObserver)->GetData()->iCurHp;
	m_iMaxHp = static_cast<CPlayerObserver*>(m_pObserver)->GetData()->iMaxHp;
	m_fHpRatio = (float)m_iCurHp / (float)m_iMaxHp;

	wsprintf(m_szLev, L"%d", m_iLev);
	wsprintf(m_szHp, L"%d  /  %d", m_iCurHp, m_iMaxHp);

	m_tRect = {
		LONG(0)
		, LONG(0)
		,  LONG(192.f * m_fHpRatio)
		,  LONG(40)
	};

	m_pHpEffect->SetPos(&D3DXVECTOR3(m_tInfo.vPos.x - 49.f + 192.f * m_fHpRatio, m_tInfo.vPos.y, 0.f));
	m_pHpEffect->Update();

	return 0;
}

void CHpBar_Player::Render()
{
	//UI_HPBAR | PlayerBack | 1 |..\Texture\UI\UI_HPBAR\PlayerBack\PlyaerBack0%d.png
	//UI_HPBAR | PlayerBase | 1 | ..\Texture\UI\UI_HPBAR\PlayerBase\PlayerBase0%d.png
	//UI_HPBAR | PlayerHp | 1 | ..\Texture\UI\UI_HPBAR\PlayerHp\PlayerHp0%d.png
	const TEXINFO* pTexInfo = TextureManager->GetTexture(m_wstrObjKey, L"PlayerBack", 0);
	
	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));


	pTexInfo = TextureManager->GetTexture(m_wstrObjKey, L"PlayerHp", 0);

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x - 60.f, m_tInfo.vPos.y - 20.f, 0.f);

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, &m_tRect
		, nullptr
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	m_pHpEffect->Render();

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x - 20.f, m_tInfo.vPos.y - 15.f, 0.f);
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pFont->DrawTextW(m_pSprite
		, m_szHp
		, lstrlen(m_szHp)
		, nullptr
		, 0
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x - 110.f, m_tInfo.vPos.y - 15.f, 0.f);
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pFont->DrawTextW(m_pSprite
		, m_szLev
		, lstrlen(m_szLev)
		, nullptr
		, 0
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = TextureManager->GetTexture(m_wstrObjKey, L"PlayerBase", 0);

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));

}

void CHpBar_Player::Release()
{
	Safe_Delete(m_pObserver);
	Safe_Delete(m_pHpEffect);
}
