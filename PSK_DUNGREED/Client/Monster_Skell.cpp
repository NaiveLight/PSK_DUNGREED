#include "stdafx.h"
#include "Monster_Skell.h"

#include "Device.h"

CMonster_Skell::CMonster_Skell()
{
}

CMonster_Skell::~CMonster_Skell()
{
	Release();
}

HRESULT CMonster_Skell::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Monster Skell Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Monster Skell Get Sprite Failed");
		return E_FAIL;
	}
	
	return S_OK;
}

int CMonster_Skell::Update()
{
	return 0;
}

void CMonster_Skell::Render()
{
}

void CMonster_Skell::Release()
{
}
