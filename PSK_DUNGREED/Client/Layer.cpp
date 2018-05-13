#include "stdafx.h"
#include "Layer.h"

#include "Device.h"
#include "TextureManager.h"
#include "ScrollManager.h"

CLayer::CLayer()
{
}


CLayer::~CLayer()
{
	Release();
}

HRESULT CLayer::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Layer Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Layer Get Sprite Failed");
		return E_FAIL;
	}

	m_tInfo.vPos = D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f, 0.f);
	m_tInfo.vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);

	return S_OK;
}

int CLayer::Update()
{
	UpdateMatrix();

	return 0;
}

void CLayer::Render()
{
	const TEXINFO* pTexInfo = TextureManager->GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
	{
		MSG_BOX(L"Get TexInfo failed in Layer");
		return;
	}

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CLayer::Release()
{
}

void CLayer::UpdateMatrix()
{
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x - (ScrollManager->GetScroll().x * m_fScrollRatio)
		, m_tInfo.vPos.y - (ScrollManager->GetScroll().y * m_fScrollRatio)
		, 0.f);
}
