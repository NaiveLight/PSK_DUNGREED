#include "stdafx.h"
#include "Belial_Hand.h"

#include "Device.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"

CBelial_Hand::CBelial_Hand()
{
}

CBelial_Hand::~CBelial_Hand()
{
	Release();
}

HRESULT CBelial_Hand::Initialize()
{
	m_fTime = TimeManager->GetDeltaTime();
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Belial Hand Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Belial Hand Get Sprite Failed");
		return E_FAIL;
	}

	m_wstrObjKey = L"BOSS_HAND";
	m_wstrStateKey = L"Idle";
	m_eCurState = IDLE;
	m_tFrame = FRAME(0.f, 20.f, 10.f);
	m_tInfo.vLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_fAlpha = 0.f;
	m_tData.iMinAtt = 12;

	return S_OK;
}

int CBelial_Hand::Update()
{
	if (m_bAttack)
	{
		if (!m_bFixed)
		{
			if (m_vPlayerPos.y > m_tInfo.vPos.y)
				m_tInfo.vDir = D3DXVECTOR3(0.f, 1.f, 0.f);
			else
				m_tInfo.vDir = D3DXVECTOR3(0.f, -1.f, 0.f);

			m_tInfo.vPos += m_tInfo.vDir * 800.f * m_fTime;

			if (abs(m_vPlayerPos.y - m_tInfo.vPos.y) <= 10.f)
			{
				m_eCurState = ATTACK;
				m_bFixed = true;
			}
		}

		UpdateMatrix();
		FrameChange();
		FrameMove();

		return 0;
	}

	UpdateMatrix();
	FrameChange();
	FrameMove();
	return 0;
}

void CBelial_Hand::Render()
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

void CBelial_Hand::Release()
{
}

void CBelial_Hand::Attack()
{
	m_bAttack = true;
	m_vPlayerPos = ObjectManager->GetPlayer()->GetInfo()->vPos;
}

void CBelial_Hand::UpdateMatrix()
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

void CBelial_Hand::FrameChange()
{
	if (m_ePrevState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_wstrStateKey = L"Idle";
			m_tFrame = FRAME(0.f, 20.f, 10.f);
			break;
		case ATTACK:
			m_wstrStateKey = L"Attack";
			m_tFrame = FRAME(0.f, 36.f, 18.f);
			break;
		}
		m_ePrevState = m_eCurState;
	}
}

void CBelial_Hand::FrameMove()
{
	m_tFrame.fFrame += m_tFrame.fCount * m_fTime;

	if (m_eCurState == ATTACK)
	{
		if ((int)m_tFrame.fFrame == 9 && !m_bHitCreated)
		{
			SoundManager->PlaySound(L"BossLaser.wav", CSoundManager::MONSTER);
			m_bHitCreated = true;
			// CreateHitBox
			CObj* pEffect = CAbstractFactory<CEffect_Extinction>::CreateEffect(
				L"BossHand"
				, m_bIsLeft
				, &D3DXVECTOR3(m_tInfo.vPos.x + (m_bIsLeft ? -64.f : 64.f), m_tInfo.vPos.y, 0.f)
				, &FRAME(0.f, 14.f, 7.f)
				, &D3DXVECTOR3(0.f, -1.f, 0.f));
			ObjectManager->AddObject(OBJ_EFFECT, pEffect);

			pEffect = CAbstractFactory<CEffect_Extinction>::CreateEffect(
				L"BossLaser"
				, m_bIsLeft
				, &D3DXVECTOR3(m_tInfo.vPos.x + (m_bIsLeft ? - 64.f - 512.f : 64.f + 512.f), m_tInfo.vPos.y, 0.f)
				, &FRAME(0.f, 14.f, 7.f)
				, &D3DXVECTOR3(0.f, -1.f, 0.f));
			ObjectManager->AddObject(OBJ_EFFECT, pEffect);
			ObjectManager->AddObject(OBJ_MATTACK, CAbstractFactory<CHitBox>::CreateHitBox(
				m_tData.iMinAtt
				, true
				, false
				, &HITBOX(m_tInfo.vPos.x + (m_bIsLeft ? -508.f : 508.f), m_tInfo.vPos.y, float(WINCX), 200.f)
				, &D3DXVECTOR3(m_tInfo.vPos.x + (m_bIsLeft ? -508.f : 508.f), m_tInfo.vPos.y, 0.f)
			));
		}
	}

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		switch (m_eCurState)
		{
		case ATTACK:
			m_eCurState = IDLE;
			m_bFixed = false;
			m_bHitCreated = false;
			m_bAttack = false;
			m_tFrame.fFrame = 0.f;
			break;
		case IDLE: case MOVE:
			m_tFrame.fFrame = 0.f;
			break;
		}
	}
}
