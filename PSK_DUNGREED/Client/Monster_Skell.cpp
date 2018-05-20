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
	m_wstrStateKey = L"Idle";
	m_tFrame = FRAME(0.f, 0.f, 0.f);
	m_ePrevState = m_eCurState = IDLE;

	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);

	m_tData.fMoveSpeed = 250.f;
	m_tData.fAttSpeed = 3.f;

	m_tData.iCurHp = 100;
	m_tData.iMaxHp = 100;

	m_fGravity = 300.f * m_fTime;
	m_fAlpha = 255.f;
	m_bIsLeft = false;
	m_bIsDead = false;
	m_bAttack = false;

	m_bGround = true;

	m_fMinPosX = 0.f;
	m_fMaxPosX = 5000.f;
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
		if (m_tFrame.fFrame == 7.f)
		{

		}
	
		m_fAttackTime -= m_fTime;

		if (m_fAttackTime < 0.f)
		{
			m_fAttackTime = 0.f;
			m_bAttack = false;
		}

		FrameChange();
		FrameMove();

		UpdateMatrix();
		UpdateHitBox();

		return 0;
	}
		

	CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();

	if (pPlayer == nullptr)
		return 0;

	m_tInfo.vDir = pPlayer->GetInfo()->vPos - m_tInfo.vPos;
	m_bIsLeft = m_tInfo.vDir.x < 0 ? true : false;
	float fDist = D3DXVec3Length(&m_tInfo.vDir);

	if (fDist <= 30.f && m_fAttackTime <= 0.f)
	{
		m_bAttack = true;
		m_eCurState = ATTACK;
		m_fVelocityX = 0.f;
		m_fAttackTime = m_tData.fAttSpeed;
	}
	else if (fDist <= 500.f)
	{
		m_eCurState = MOVE;
		m_fVelocityX = m_bIsLeft ? -m_tData.fMoveSpeed * m_fTime : m_tData.fMoveSpeed * m_fTime;
	}
	else if (fDist > 600.f)
	{
		m_eCurState = IDLE;
		m_fVelocityX = 0.f;
	}

	m_bGround = CCollisionManager::MonsterToTile(this, dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front()));

	m_tInfo.vPos.x += m_bGround ? m_fVelocityX : 0.f;
	m_tInfo.vPos.y += m_fVelocityY + (m_bGround ? 0 : m_fGravity);

	if (m_tInfo.vPos.x <= m_fMinPosX)
		m_tInfo.vPos.x = m_fMinPosX;
	if (m_tInfo.vPos.x >= m_fMaxPosX)
		m_tInfo.vPos.x = m_fMaxPosX;

	FrameChange();
	FrameMove();

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
	m_tHitBox.fCX = 32.f;
	m_tHitBox.fCY = 64.f;
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
			m_tFrame = FRAME(0.f, 2.f, 1.f);
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
		if ((int)m_tFrame.fFrame == 7 && !m_bHitCreated)
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
			m_bHitCreated = false;
			m_tFrame.fFrame = 0.f;
			break;
		case IDLE: case MOVE:
			m_tFrame.fFrame = 0.f;
			break;
		}
	}
}
