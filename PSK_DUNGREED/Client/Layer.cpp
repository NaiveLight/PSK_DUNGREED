#include "stdafx.h"
#include "Layer.h"

#include "Device.h"
#include "TextureManager.h"

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
	return 0;
}

void CLayer::Render()
{
}

void CLayer::Release()
{
}
