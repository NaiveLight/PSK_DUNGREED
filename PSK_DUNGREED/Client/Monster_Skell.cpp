#include "stdafx.h"
#include "Monster_Skell.h"

#include "Device.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"

CMonster_Skell::CMonster_Skell()
{
}

CMonster_Skell::~CMonster_Skell()
{
	Release();
}

void CMonster_Skell::InitAttributes()
{
	m_fTime = TimeManager->GetDeltaTime();
	m_wstrObjKey = L"SKELL";
	m_wstrStateKey = L"SPAWN";
	m_ePrevState = m_eCurState = SPAWN;

	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);

	m_tData.fMoveSpeed = 450.f;
	m_tData.fAttSpeed = 3.f;

	m_tData.iCurHp = 100;
	m_tData.iMaxHp = 100;

	m_fGravity = 16.f * m_fTime;
	m_fAlpha = 255.f;
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

	InitAttributes();
	
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

void CMonster_Skell::UpdateMatrix()
{
}

void CMonster_Skell::UpdateHitBox()
{
}

void CMonster_Skell::FrameChange()
{
	if (m_ePrevState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case SPAWN:
			break;
		case IDLE:
			m_wstrStateKey = L"Idle";
			m_tFrame = FRAME(0.f, 10.f, 5.f);
			break;
		case MOVE:
			m_wstrStateKey = L"Run";
			m_tFrame = FRAME(0.f, 14.f, 7.f);
			break;
		case ATTACK:
			m_wstrStateKey = L"Jump";
			m_tFrame = FRAME(0.f, 0.f, 0.f);
			break;
		}

		m_ePrevState = m_eCurState;
	}
}

void CMonster_Skell::FrameMove()
{
}
