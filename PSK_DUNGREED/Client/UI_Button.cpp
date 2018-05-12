#include "stdafx.h"
#include "UI_Button.h"

#include "Include.h"
#include "Device.h"
#include "TextureManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

CUI_Button::CUI_Button()
{
}

CUI_Button::~CUI_Button()
{
}

HRESULT CUI_Button::Initialize()
{
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Button Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Button Get Sprite Failed");
		return E_FAIL;
	}

	return S_OK;
}

int CUI_Button::Update()
{
	POINT pt = {};
	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	if (PtInRect(&m_tHitRect, pt))
		m_tFrame.fFrame = 1.f;
	else
		m_tFrame.fFrame = 0.f;

	UpdateRect();
	CObj::UpdateMatrix();
	CheckInput();

	return 0;
}

void CUI_Button::Render()
{
	const TEXINFO* pTexInfo = TextureManager->GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
	{
		MSG_BOX(L"Get TexInfo failed in Button");
		return;
	}

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CUI_Button::Release()
{
}

void CUI_Button::UpdateRect()
{
	const TEXINFO* pTexInfo = TextureManager->GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);
	m_tHitRect = {
			(LONG)(m_tInfo.vPos.x - (pTexInfo->tImgInfo.Width * 0.5f))
		,	(LONG)(m_tInfo.vPos.y - (pTexInfo->tImgInfo.Height * 0.5f))
		,	(LONG)(m_tInfo.vPos.x + (pTexInfo->tImgInfo.Width * 0.5f))
		,	(LONG)(m_tInfo.vPos.y + (pTexInfo->tImgInfo.Height * 0.5f))
	};
}

void CUI_Button::CheckInput()
{
	if (KeyManager->KeyDown(VK_LBUTTON) && m_tFrame.fFrame == 1.0f)
	{
		switch (m_eBtID)
		{
		case BT_TSTART:
			SceneManager->ChangeScene(SCENE_TOWN);
			break;
		case BT_TOPTION:
			break;
		case BT_TEXIT:
			break;
		case BT_GOPTION:
			break;
		case BT_GEXIT:
			break;
		case BT_UEXIT:
			break;
		default:
			break;
		}
	}
}
