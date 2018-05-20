#include "stdafx.h"
#include "HpEffect.h"

#include "Device.h"
#include "TextureManager.h"
#include "TimeManager.h"

CHpEffect::CHpEffect()
{
}

CHpEffect::~CHpEffect()
{
	Release();
}

HRESULT CHpEffect::Initialize()
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

	m_fTime = TimeManager->GetDeltaTime();
	m_wstrObjKey = L"EFFECT";
	m_wstrStateKey = L"HpWave";
	m_tFrame = FRAME(0.f, 14.f, 7.f);
}

int CHpEffect::Update()
{
	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x 
		, m_tInfo.vPos.y 
		, 0.f);

	m_tFrame.fFrame += m_tFrame.fCount * m_fTime;

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;

	return 0;
}

void CHpEffect::Render()
{
	const TEXINFO*		pTexInfo = TextureManager->GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
		return;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CHpEffect::Release()
{
}
