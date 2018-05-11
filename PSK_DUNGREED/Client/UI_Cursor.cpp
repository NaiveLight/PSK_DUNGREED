#include "stdafx.h"
#include "UI_Cursor.h"

#include "Include.h"
#include "Device.h"
#include "TextureManager.h"

CUI_Cursor::CUI_Cursor()
{
}


CUI_Cursor::~CUI_Cursor()
{
	Release();
}

HRESULT CUI_Cursor::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Cursor Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Cursor Get Sprite Failed");
		return E_FAIL;
	}

	m_tInfo.vPos = m_tInfo.vLook = m_tInfo.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	return S_OK;
}

int CUI_Cursor::Update()
{
	m_tInfo.vPos = GetMousePos();

	CObj::UpdateMatrix();

	return 0;
}

void CUI_Cursor::Render()
{
	const TEXINFO* pTexInfo = TextureManager->GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
	{
		MSG_BOX(L"Get TexInfo failed in Cursor");
		return;
	}

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUI_Cursor::Release()
{
}
