#include "stdafx.h"
#include "Belial.h"

#include "Device.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "Belial_Hand.h"

CBelial::CBelial()
{
}

CBelial::~CBelial()
{
	Release();
}

void CBelial::InitAttributes()
{
	m_fTime = TimeManager->GetDeltaTime();
	m_wstrObjKey = L"BOSS_HEAD";
	m_wstrStateKey = L"Idle";
	m_tFrame = FRAME(0.f, 15.f, 10.f);
	m_ePrevState = m_eCurState = IDLE;

	m_tInfo.vLook = D3DXVECTOR3(0.f, -1.f, 0.f);

	m_tData.fAttSpeed = 3.f;

	m_tData.iMinAtt = 10;
	m_tData.iCurHp = 100;
	m_tData.iMaxHp = 500;

	m_tData.iGold = (rand() % 3000);

	m_fAlpha = 0.f;
	m_fAttTime = 8.f;
	m_fBulletTime = 0.2f;
	m_fFadeTime = 5.f;
	m_bIsLeft = false;
	m_bIsDead = false;
	m_bAttack = false;
}

HRESULT CBelial::Initialize()
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

int CBelial::Update()
{
	if (m_bIsOver)
	{
		return 1;
	}

	if (!m_bInit)
	{
		LateInit();
		m_bInit = true;
	}

	if (m_bDigEffect)
	{
		m_fEffectTime -= m_fTime;

		if (m_fEffectTime <= 0.f)
		{
			for (int i = 0; i < 6; ++i)
			{
				float fAngle = 60.f * i;
				D3DXVECTOR3 vDir = D3DXVECTOR3(sinf(D3DXToRadian(fAngle)), cosf(D3DXToRadian(fAngle)), 0.f);
				CObj* pObj = CAbstractFactory<CEffect_Extinction>::CreateEffect(L"Die",
					false, &D3DXVECTOR3(m_tHitBox.fX + 32.f + vDir.x * m_fCurDist, m_tHitBox.fY + 128.f + vDir.y * m_fCurDist, 0.f), &FRAME{ 0.f, 22.f, 11.f }, &D3DXVECTOR3(0.f, -1.f, 0.f));
				ObjectManager->AddObject(OBJ_EFFECT, pObj);
				SoundManager->PlaySound(L"Die.wav", CSoundManager::MONSTER);
			}

			if (m_fCurDist >= m_fMaxDist)
			{
				m_bDigEffect = false;
				m_bIsOver = true;
			}

			m_fCurDist += 50.f;
			m_fEffectTime = 0.1f;
		}

		FrameChange();
		UpdateMatrix();
		UpdateHitBox();

		m_pParticle->Update();
		m_pLeftHand->Update();
		m_pRightHand->Update();
	}

	if (m_bCircleEffect)
	{
		m_fEffectTime -= m_fTime;

		if (m_fEffectTime <= 0.f)
		{
			D3DXVECTOR3 vDir = D3DXVECTOR3(sinf(D3DXToRadian(m_fAngle)), cosf(D3DXToRadian(m_fAngle)), 0.f);
			CObj* pObj = CAbstractFactory<CEffect_Extinction>::CreateEffect(L"Die",
				false, &D3DXVECTOR3(m_tHitBox.fX + 32.f + vDir.x * 400.f, m_tHitBox.fY + 128.f + vDir.y * 400.f, 0.f), &FRAME{ 0.f, 22.f, 11.f }, &D3DXVECTOR3(0.f, -1.f, 0.f));
			ObjectManager->AddObject(OBJ_EFFECT, pObj);
			SoundManager->PlaySound(L"Die.wav", CSoundManager::MONSTER);

			if (m_fAngle >= 360.f)
			{
				m_bCircleEffect = false;
				m_bDigEffect = true;
			}

			m_fAngle += 10.f;
			m_fEffectTime = 0.1f;
		}

		FrameChange();
		UpdateMatrix();
		UpdateHitBox();

		m_pParticle->Update();
		m_pLeftHand->Update();
		m_pRightHand->Update();
		return 0;
	}
		

	if (m_bIsDead)
	{
		m_fAngle = 0.f;
		m_eCurState = ATTACK;
		m_tFrame.fFrame = 9.f;
		SoundManager->StopSound(CSoundManager::BGM);

		FrameChange();
		UpdateMatrix();
		UpdateHitBox();

		m_pParticle->Update();
		m_pLeftHand->Update();
		m_pRightHand->Update();

		m_bCircleEffect = true;

		return 0;
	}

	if (!m_bActive)
	{
		CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();

		m_tInfo.vDir = pPlayer->GetInfo()->vPos - m_tInfo.vPos;
		float fDist = D3DXVec3Length(&m_tInfo.vDir);

		if (fDist <= 500.f)
		{
			SoundManager->StopAll();
			SoundManager->PlaySound(L"BossIntro.wav", CSoundManager::MONSTER);
			m_bActive = true;
			m_bIsFade = true;
			D3DXVECTOR3 vPos = D3DXVECTOR3(m_tInfo.vPos.x - WINCX * 0.5f, m_tInfo.vPos.y - WINCY* 0.5f, 0.f);
			ScrollManager->FocusingStart(vPos, 7.f);
		}
			
		return 0;
	}

	if (m_bIsFade)
	{
		m_fAlpha += 100.f * m_fTime;
		m_pParticle->SetAlpha(m_fAlpha);
		m_pLeftHand->SetAlpha(m_fAlpha);
		m_pRightHand->SetAlpha(m_fAlpha);

		m_fFadeTime -= m_fTime;

		if (m_fAlpha >= 250.f)
		{
			m_fAlpha = 255.f;
			m_bIsFade = false;
			SoundManager->PlayBGM(L"BG_BOSS.wav");
		}
	}
	else
	{	
		if (m_bAttack)
		{
			if (m_iAttackPattern % 3 == 0)
			{
				m_fAngle += 0.5f;
				if (m_fAngle >= 360.f)
					m_fAngle -= 360.f;

				Attack();
				//Head
				m_fAttTime -= m_fTime;

				if (m_fAttTime <= 0.f)
				{
					m_bAttack = false;
					m_eCurState = IDLE;
					m_fAttTime = 5.f;
				}
			}
			else if (m_iAttackPattern % 3 == 1)
			{
				// Left
				m_bAttack = dynamic_cast<CBelial_Hand*>(m_pLeftHand)->GetIsAttack();

				if (!m_bAttack)
				{
					m_eCurState = IDLE;
					m_fAttTime = 3.f;
				}
			}
			else if (m_iAttackPattern % 3 == 2)
			{
				// Right
				m_bAttack = dynamic_cast<CBelial_Hand*>(m_pRightHand)->GetIsAttack();

				if (!m_bAttack)
				{
					m_eCurState = IDLE;
					m_fAttTime = 3.f;
				}
			}

		}
		else
		{
			m_fAttTime -= m_fTime;

			if (m_fAttTime <= 0.f)
			{
				m_iAttackPattern = rand() % 10;

				if (m_iAttackPattern % 3 == 0)
				{
					// Head
					m_eCurState = ATTACK;
					m_fAttTime = 3.f;
					m_bAttack = true;
				}
				else if (m_iAttackPattern % 3 == 1)
				{
					// Left
					m_eCurState = ATTACK_LEFT;
					m_bAttack = true;
					dynamic_cast<CBelial_Hand*>(m_pLeftHand)->Attack();
				}
				else if (m_iAttackPattern % 3 == 2)
				{
					// Right
					m_eCurState = ATTACK_RIGHT;
					m_bAttack = true;
					dynamic_cast<CBelial_Hand*>(m_pRightHand)->Attack();
				}
			}
		}
	}

	FrameChange();
	FrameMove();

	UpdateMatrix();
	UpdateHitBox();

	m_pLeftHand->Update();
	m_pRightHand->Update();
	m_pParticle->Update();

	return 0;
}

void CBelial::Render()
{
	m_pLeftHand->Render();
	m_pRightHand->Render();
	m_pParticle->Render();

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

void CBelial::Release()
{
	Safe_Delete(m_pLeftHand);
	Safe_Delete(m_pRightHand);
	Safe_Delete(m_pParticle);
}

void CBelial::LateInit()
{
	if (m_pLeftHand == nullptr)
		m_pLeftHand = CAbstractFactory<CBelial_Hand>::CreateObj(false, &D3DXVECTOR3(m_tInfo.vPos.x + 32.f - 508.f , m_tInfo.vPos.y  + 128.f, 0.f));
	if (m_pRightHand == nullptr)
		m_pRightHand = CAbstractFactory<CBelial_Hand>::CreateObj(true, &D3DXVECTOR3(m_tInfo.vPos.x + 32.f + 508.f, m_tInfo.vPos.y - 128.f, 0.f));
	if (m_pParticle == nullptr)
		m_pParticle = CAbstractFactory<CBelial_CenterParticle>::CreateObj(&D3DXVECTOR3(m_tInfo.vPos.x + 32.f, m_tInfo.vPos.y + 128.f, 0.f));
}

void CBelial::UpdateMatrix()
{
	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x - ScrollManager->GetScroll().x
		, m_tInfo.vPos.y - ScrollManager->GetScroll().y
		, 0.f);
}

void CBelial::UpdateHitBox()
{
	m_tHitBox.fX = m_tInfo.vPos.x;
	m_tHitBox.fY = m_tInfo.vPos.y;
	m_tHitBox.fCX = 280.f;
	m_tHitBox.fCY = 400.f;
}

void CBelial::FrameChange()
{
	if (m_ePrevState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE: case ATTACK_LEFT: case ATTACK_RIGHT:
			m_wstrStateKey = L"Idle";
			m_tFrame = FRAME(0.f, 15.f, 10.f);
			break;
		case ATTACK:
			m_wstrStateKey = L"Attack";
			m_tFrame = FRAME(0.f, 20.f, 10.f);
			break;
		}

		m_ePrevState = m_eCurState;
	}
}

void CBelial::FrameMove()
{
	m_tFrame.fFrame += m_tFrame.fCount * m_fTime;

	if (m_tFrame.fFrame > m_tFrame.fMax)
	{
		switch (m_eCurState)
		{
		case ATTACK: 
			m_tFrame.fFrame = m_tFrame.fMax - 1.f;
			break;
		case IDLE: case ATTACK_LEFT: case ATTACK_RIGHT:
			m_tFrame.fFrame = 0.f;
			break;
		}
	}
}

void CBelial::Attack()
{
	// 4방향 탄막 생성

	m_fBulletTime -= m_fTime;

	if (m_fBulletTime <= 0.f)
	{
		for (int i = 0; i < 4; i++)
		{
			//Create Bullet
			SoundManager->PlaySound(L"BossAttack.wav", CSoundManager::MONSTER);
			float fAngle = m_fAngle + 90.f * i;
			if (fAngle > 360.f)
				fAngle -= 360.f;
			D3DXVECTOR3 vDir = D3DXVECTOR3(sinf(D3DXToRadian(fAngle)), cosf(D3DXToRadian(fAngle)), 0.f);
			CObj* pBullet = CAbstractFactory<CBullet>::CreateBullet(BULLET_BELIAL_HEAD, L"BossHead", m_tData.iMinAtt, &FRAME(0.f, 2.f, 2.f), &HITBOX(0.f, 0.f, 52.f, 52.f), &D3DXVECTOR3(m_tInfo.vPos.x +32.f, m_tInfo.vPos.y + 128.f, 0.f), &vDir);
			ObjectManager->AddObject(OBJ_BULLET, pBullet);
		}
		m_fBulletTime = 0.2f;
	}
}
