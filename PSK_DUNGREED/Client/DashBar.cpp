#include "stdafx.h"
#include "DashBar.h"
#include "Device.h"
#include "PlayerObserver.h"
#include "DataSubject.h"
#include "TextureManager.h"

CDashBar::CDashBar()
{
}

CDashBar::~CDashBar()
{
	Release();
}

HRESULT CDashBar::Initialize()
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

	m_tInfo.vPos = D3DXVECTOR3(48.f, 84.f, 0.f);
	m_wstrObjKey = L"UI_DASH";

	m_pObserver = new CPlayerObserver;
	CDataSubject::GetInstance()->Subscribe(m_pObserver);
	CDataSubject::GetInstance()->Notify(PLAYER_PDATA);
}

int CDashBar::Update()
{
	m_iCurDash = static_cast<CPlayerObserver*>(m_pObserver)->GetPlayerData()->iDashCnt;

	m_tRect = {
		LONG(0)
		, LONG(0)
		,  LONG(38.f * m_iCurDash)
		,  LONG(16)
	};
	return 0;
}

void CDashBar::Render()
{
	const TEXINFO* pTexInfo = TextureManager->GetTexture(m_wstrObjKey, L"DashCountBase", 0);

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));

	pTexInfo = TextureManager->GetTexture(m_wstrObjKey, L"DashCount", 0);

	D3DXMatrixTranslation(&m_tInfo.matWorld, m_tInfo.vPos.x - 38.f, m_tInfo.vPos.y - 8.f, 0.f);
	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, &m_tRect
		, nullptr
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CDashBar::Release()
{
}
