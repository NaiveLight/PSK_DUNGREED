#include "stdafx.h"
#include "Weapon.h"
#include "Bridge.h"

CWeapon::CWeapon()
{
}

CWeapon::~CWeapon()
{
	Release();
}

HRESULT CWeapon::Initialize()
{
	if (m_pBridge)
		m_pBridge->SetObj(this);

	return S_OK;
}

int CWeapon::Update()
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

void CWeapon::Render()
{
	if (m_pBridge)
		m_pBridge->Render();
}

void CWeapon::Release()
{
	Safe_Delete(m_pBridge);
}
