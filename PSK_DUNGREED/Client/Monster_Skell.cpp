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
	if (m_bIsDead)
	{
		//SoundManager 죽는 소리 출력
		//EFFECT 추가
		return 1;
	}

	if (m_bAttack)
	{
		if(m_tFrame.fFrame == 7.f)
		return 0;
	}
		

	CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();

	m_tInfo.vDir = pPlayer->GetInfo()->vPos - m_tInfo.vPos;
	float fDist = D3DXVec3Length(&m_tInfo.vDir);

	if (fDist < 500.f);
	{
		m_eCurState = MOVE;
	}

	m_tInfo.vPos.x += m_fVelocityX;
	m_tInfo.vPos.y += m_fVelocityY + (m_bGround ? 0 : m_fGravity);

	if (m_tInfo.vPos.x <= m_fMinPosX)
		m_tInfo.vPos.x = m_fMinPosX;
	if (m_tInfo.vPos.x >= m_fMaxPosX)
		m_tInfo.vPos.x = m_fMaxPosX;

	UpdateMatrix();
	UpdateHitBox();
	return 0;
}

void CMonster_Skell::Render()
{
	const TEXINFO*		pTexInfo = TextureManager->GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
		return;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(BYTE(m_fAlpha), 255, 255, 255));
}

void CMonster_Skell::Release()
{
}

void CMonster_Skell::UpdateMatrix()
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixIdentity(&matScale);

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	D3DXMatrixScaling(&matScale, (m_bIsLeft ? -1.f : 1.f), 1.f, 0.f);
	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x - ScrollManager->GetScroll().x
		, m_tInfo.vPos.y - ScrollManager->GetScroll().y
		, 0.f);

	m_tInfo.matWorld = matScale * m_tInfo.matWorld;
}

void CMonster_Skell::UpdateHitBox()
{
	m_tHitBox.fX = m_tInfo.vPos.x + (m_bIsLeft? 4.f : - 4.f);
	m_tHitBox.fY = m_tInfo.vPos.y + 32.f;
	m_tHitBox.fCX = 0.f;
}

void CMonster_Skell::FrameChange()
{
	if (m_ePrevState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case SPAWN:
			m_fAlpha = 0.f;
			break;
		case IDLE:
			m_wstrStateKey = L"Idle";
			m_tFrame = FRAME(0.f, 0.f, 1.f);
			break;
		case MOVE:
			m_wstrStateKey = L"Walk";
			m_tFrame = FRAME(0.f, 12.f, 6.f);
			break;
		case ATTACK:
			m_wstrStateKey = L"Attack";
			m_tFrame = FRAME(0.f, 22.f, 11.f);
			break;
		}

		m_ePrevState = m_eCurState;
	}
}

void CMonster_Skell::FrameMove()
{
	m_tFrame.fFrame += m_tFrame.fCount * m_fTime;

	if (m_eCurState == ATTACK)
	{
		if ((int)m_tFrame.fFrame == 7)
		{
			m_bHitCreated = true;
			// CreateHitBox
		}
			
	}

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		switch (m_eCurState)
		{
		case SPAWN: case ATTACK:
			m_eCurState = IDLE;
			m_bAttack = false;
			m_bHitCreated = false;
			break;
		case IDLE: case MOVE:
			m_tFrame.fFrame = 0.f;
			break;
		}
	}
		m_tFrame.fFrame = 0.f;
}
