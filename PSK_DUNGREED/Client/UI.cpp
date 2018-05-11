#include "stdafx.h"
#include "UI.h"

#include "Bridge.h"

CUI::CUI()
{
}

CUI::~CUI()
{
	Release();
}

HRESULT CUI::Initialize()
{
	if (m_pBridge)
		m_pBridge->SetObj(this);

	return S_OK;
}

int CUI::Update()
{
	int iResult = 0;
	if (m_pBridge)
		iResult = m_pBridge->Update(m_tInfo);

	if (iResult == 1)
	{
		delete this;
		return 1;
	}

	return 0;
}

void CUI::Render()
{
	if (m_pBridge)
	{
		m_pBridge->Render();
	}
}

void CUI::Release()
{
	Safe_Delete(m_pBridge);
}
