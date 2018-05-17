#include "stdafx.h"
#include "UI_Logo.h"

#include "Device.h"
#include "TextureManager.h"
#include "TimeManager.h"

CUI_Logo::CUI_Logo()
{
}

CUI_Logo::~CUI_Logo()
{
	Release();
}

void CUI_Logo::SetAlphaBlend(const bool bAlpha)
{
	m_bAlpha = bAlpha;
}

HRESULT CUI_Logo::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Logo Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Logo Get Sprite Failed");
		return E_FAIL;
	}

	D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vPos = m_tInfo.vDir = m_tInfo.vLook = D3DXVECTOR3(0.f, 0.f, 0.f);

	return S_OK;
}

int CUI_Logo::Update()
{
	if (m_bAlpha)
	{
		m_fAlpha += m_fAlphaVal * TimeManager->GetDeltaTime();

		if (m_fAlpha < 0.f)
			return 1;

		if (m_fAlpha >= 255.f)
		{
			m_fAlphaVal *= -1;
			m_fAlpha = 255.f;
		}
	}

	CObj::UpdateMatrix();

	return 0;
}

void CUI_Logo::Render()
{
	const TEXINFO* pTexInfo =TextureManager->GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
	{
		MSG_BOX(L"Get TexInfo failed in Logo");
		return;
	}

	if (m_bAlpha)
	{
		m_pSprite->SetTransform(&m_tInfo.matWorld);
		m_pSprite->Draw(pTexInfo->pTexture
			, nullptr
			, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
			, nullptr
			, D3DCOLOR_ARGB(BYTE(m_fAlpha), 255, 255, 255));
	}
	else
	{
		m_pSprite->SetTransform(&m_tInfo.matWorld);
		m_pSprite->Draw(pTexInfo->pTexture
			, nullptr
			, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CUI_Logo::Release()
{
}
