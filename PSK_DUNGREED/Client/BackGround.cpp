#include "stdafx.h"
#include "BackGround.h"

#include "Device.h"
#include "TextureManager.h"

CBackGround::CBackGround()
{
}


CBackGround::~CBackGround()
{
	Release();
}

HRESULT CBackGround::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"BackGround Get Device Failed");
		return E_FAIL;
	}

	m_pSprite= Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"BackGround Get Sprite Failed");
		return E_FAIL;
	}

	InitBackGroundAttributes();

	return S_OK;
}

int CBackGround::Update()
{
	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x
		, m_tInfo.vPos.y
		, 0.f);

	return 0;
}

void CBackGround::Render()
{
	const TEXINFO* pTexInfo = TextureManager->GetTexture(m_wstrObjKey, m_wstrStateKey);
	if (pTexInfo == nullptr)
	{
		MSG_BOX(L"Get TexInfo failed in BackGround ");
		return;
	}

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CBackGround::Release()
{
}

void CBackGround::InitBackGroundAttributes()
{
	m_tInfo.vPos = D3DXVECTOR3(WINCX * 0.5f, WINCY * 0.5f, 0.f);
	m_tInfo.vLook = m_tInfo.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	D3DXMatrixIdentity(&m_tInfo.matWorld);

	m_wstrObjKey = L"BACKGROUND";
}
