#include "stdafx.h"
#include "Effect.h"
#include "Bridge.h"

CEffect::CEffect()
{
}


CEffect::~CEffect()
{
	Release();
}

HRESULT CEffect::Initialize()
{
	if (m_pBridge)
		m_pBridge->SetObj(this);

	m_wstrObjKey = L"EFFECT";

	return S_OK;
}

int CEffect::Update()
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

void CEffect::Render()
{
	if (m_pBridge)
		m_pBridge->Render();
}

void CEffect::Release()
{
	Safe_Delete(m_pBridge);
}
