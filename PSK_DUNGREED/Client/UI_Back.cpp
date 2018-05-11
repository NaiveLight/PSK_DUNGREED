#include "stdafx.h"
#include "UI_Back.h"

#include "Device.h"

CUI_Back::CUI_Back()
{
}

CUI_Back::~CUI_Back()
{
	Release();
}

HRESULT CUI_Back::Initialize(void)
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"UI_Back Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"UI_Back Get Sprite Failed");
		return E_FAIL;
	}

	return E_NOTIMPL;
}

int CUI_Back::Update(INFO & rInfo)
{
	return 0;
}

void CUI_Back::Render(void)
{
	CUIBridge::Render();
}

void CUI_Back::Release(void)
{
}
