#include "stdafx.h"
#include "Monster_Banshee.h"

#include "Device.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "TimeManager.h"
#include "SoundManager.h"

CMonster_Banshee::CMonster_Banshee()
{
}

CMonster_Banshee::~CMonster_Banshee()
{
	Release();
}

HRESULT CMonster_Banshee::Initialize()
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

void CMonster_Banshee::InitAttributes()
{
	m_fTime = TimeManager->GetDeltaTime();
	m_wstrObjKey = L"BANSHEE";
	m_wstrStateKey = L"Idle";
	m_tFrame = FRAME(0.f, 12.f, 6.f);
	m_ePrevState = m_eCurState = IDLE;

	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);

	m_tData.fMoveSpeed = 0.f;
	m_tData.fAttSpeed = 5.f;

	m_tData.iMinAtt = 8;
	m_tData.iCurHp = 100;
	m_tData.iMaxHp = 100;

	m_tData.iGold = (rand() % 200);

	m_fAlpha = 255.f;

	m_bIsLeft = false;
	m_bIsDead = false;
	m_bAttack = false;
}

void CMonster_Banshee::UpdateMatrix()
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

void CMonster_Banshee::UpdateHitBox()
{
	m_tHitBox.fX = m_tInfo.vPos.x;
	m_tHitBox.fY = m_tInfo.vPos.y;
	m_tHitBox.fCX = 80.f;
	m_tHitBox.fCY = 88.f;
}

void CMonster_Banshee::FrameChange()
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
			m_tFrame = FRAME(0.f, 12.f, 6.f);
			break;
		case ATTACK:
			m_wstrStateKey = L"Attack";
			m_tFrame = FRAME(0.f, 12.f, 6.f);
			break;
		}

		m_ePrevState = m_eCurState;
	}
}

void CMonster_Banshee::FrameMove()
{
	m_tFrame.fFrame += m_tFrame.fCount * m_fTime;

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		switch (m_eCurState)
		{
		case ATTACK:
			m_eCurState = IDLE;
			m_tFrame.fFrame = 0.f;
			break;
		case IDLE:
			m_tFrame.fFrame = 0.f;
			break;
		}
	}
}


int CMonster_Banshee::Update()
{
	if (m_bIsDead)
	{
		//SoundManager 죽는 소리 출력
		//EFFECT 추가
		CObj* pObj = CAbstractFactory<CEffect_Extinction>::CreateEffect(L"Die",
			false, &D3DXVECTOR3(m_tHitBox.fX, m_tHitBox.fY, 0.f), &FRAME{ 0.f, 22.f, 11.f }, &D3DXVECTOR3(0.f, -1.f, 0.f));
		ObjectManager->AddObject(OBJ_EFFECT, pObj);
		SoundManager->PlaySound(L"Die.wav", CSoundManager::MONSTER);
		return 1;
	}

	if (m_bAttack)
	{
		m_fAttackTime -= m_fTime;

		if (m_fAttackTime < 0.f)
		{
			m_fAttackTime = 3.f;
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

	m_fAttackTime -= m_fTime;

	if (m_fAttackTime <= 0.f)
	{
		m_bAttack = true;
		m_eCurState = ATTACK;
		m_fAttackTime = 3.f;

		for (int i = 0; i < 9; i++)
		{
			//Create Bullet
			SoundManager->PlaySound(L"BansheeAttack.wav", CSoundManager::MONSTER);
			float fAngle = m_fAngle + 40.f * i;
			D3DXVECTOR3 vDir = D3DXVECTOR3(sinf(D3DXToRadian(fAngle)), cosf(D3DXToRadian(fAngle)), 0.f);
			CObj* pBullet = CAbstractFactory<CBullet>::CreateBullet(BULLET_BANSHEE, L"Banshee", m_tData.iMinAtt, &FRAME(0.f, 4.f, 4.f), &HITBOX(0.f, 0.f, 52.f, 64.f), &m_tInfo.vPos, &vDir);
			ObjectManager->AddObject(OBJ_BULLET, pBullet);
		}
	}

	m_fAngle += 5.f * m_fTime;
	if (m_fAngle >= 360.f)
		m_fAngle -= 360.f;

	FrameChange();
	FrameMove();

	UpdateMatrix();
	UpdateHitBox();

	return 0;
}

void CMonster_Banshee::Render()
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

void CMonster_Banshee::Release()
{
}

