#include "stdafx.h"
#include "Player.h"

#include "Device.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
	Release();
}

HRESULT CPlayer::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Player Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Player Get Sprite Failed");
		return E_FAIL;
	}

	InitPlayerAttributes();

	ScrollManager->SetCurScroll(m_tInfo.vPos.x - WINCX * 0.5f, m_tInfo.vPos.y + WINCY * 0.5f);
	
	return S_OK;
}

int CPlayer::Update()
{
	m_fTime = TimeManager->GetDeltaTime();

	UpdateMatrix();
	UpdateHitRect();

	CheckMousePos();
	CheckInput();

	if (m_bJump || m_bDash)
		m_eCurState = JUMP;

	m_bGround = CCollisionManager::PlayerToTile(this, dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front()));

	m_tInfo.vPos.x += m_fVelocityX;
	m_tInfo.vPos.y += m_fVelocityY + (m_bGround ? 0 : m_fGravity);

	if (m_tInfo.vPos.x <= m_fMinPosX)
		m_tInfo.vPos.x = m_fMinPosX;
	if (m_tInfo.vPos.x >= m_fMaxPosX)
		m_tInfo.vPos.x = m_fMaxPosX;

	FrameChange();
	FrameMove();

	ScrollManager->SetCurScroll(m_tInfo.vPos.x - WINCX * 0.5f, m_tInfo.vPos.y - WINCY * 0.5f + m_fAddScrollY);

	return 0;
}

void CPlayer::Render()
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

	//const TEXINFO*		pColInfo = TextureManager->GetTexture(m_wstrObjKey, L"PCollider", 0);
	//if (pColInfo == nullptr)
	//	return;

	//D3DXMATRIX matScale, matTrans;

	//D3DXMatrixIdentity(&matScale);

	//if (m_bIsLeft)
	//{
	//	D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
	//}

	//D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	//D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	//D3DXMatrixTranslation(&m_tInfo.matWorld
	//	, m_tInfo.vPos.x - ScrollManager->GetScroll().x
	//	, m_tInfo.vPos.y + 32.f - ScrollManager->GetScroll().y
	//	, 0.f);

	//m_tInfo.matWorld = matScale * m_tInfo.matWorld;

	//m_pSprite->SetTransform(&m_tInfo.matWorld);
	//m_pSprite->Draw(pColInfo->pTexture
	//	, nullptr
	//	, &D3DXVECTOR3(pColInfo->tImgInfo.Width * 0.5f, pColInfo->tImgInfo.Height * 0.5f, 0.f)
	//	, nullptr
	//	, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CPlayer::Release()
{
}

void CPlayer::UpdateMatrix()
{
	D3DXMATRIX matScale, matTrans;
	
	D3DXMatrixIdentity(&matScale);

	if (m_bIsLeft)
	{
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);
	}

	D3DXVec3TransformNormal(&m_tInfo.vDir, &m_tInfo.vLook, &m_tInfo.matWorld);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x - ScrollManager->GetScroll().x
		, m_tInfo.vPos.y - ScrollManager->GetScroll().y
		, 0.f);

	m_tInfo.matWorld = matScale * m_tInfo.matWorld;
}

void CPlayer::UpdateHitRect()
{
	m_tHitRect.left = LONG(m_tInfo.vPos.x - 16.f);
	m_tHitRect.top = LONG(m_tInfo.vPos.y);
	m_tHitRect.right = LONG(m_tInfo.vPos.x + 16.f);
	m_tHitRect.bottom = LONG(m_tInfo.vPos.y + 64.f);
}

void CPlayer::InitPlayerAttributes()
{
	m_fTime = TimeManager->GetDeltaTime();

	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 64.f;

	m_wstrObjKey = L"PLAYER";
	m_wstrStateKey = L"Idle";

	m_tFrame = FRAME(0, 10, 5);

	m_tData.fMoveSpeed = 450.f;
	m_tData.fAttSpeed = 1.f;

	m_tData.iCurHp = 80;
	m_tData.iMaxHp = 80;
	
	m_tPData.iLevel = 1;
	m_tPData.iCurExp = 0;
	m_tPData.iMaxExp= 100;
	m_tPData.iDashCnt = 2;
	m_tPData.iMaxDashCnt = 2;

	m_tPData.iCurFood = 0;
	m_tPData.iMaxFood = 100;

	m_tPData.iStr = 0;
	m_tPData.iDex = 0;
	m_tPData.iDef = 0;
	m_tPData.iInt = 0;
	m_tPData.iDeg = 0;

	m_tPData.fDashSpeed = 500.f;
	m_tPData.fDashTime = 0.5f;
	m_tPData.fDashChargeTime = 2.f;

	m_fGravity = 16.f * m_fTime;
	m_fAlpha = 255.f;

	m_fDustTime = 0.2f;
}

void CPlayer::CheckMousePos()
{
	m_tInfo.vDir = (GetMousePos() + ScrollManager->GetScroll()) - m_tInfo.vPos;
	if (m_tInfo.vDir.x < 0.f)
		m_bIsLeft = true;
	else
		m_bIsLeft = false;
}

void CPlayer::CheckInput()
{
	if (KeyManager->KeyPressing('S'))
		m_bDown = true;
		
	if (!KeyManager->KeyPressing('S'))
		m_bDown = false;

	Move();
	Jump();
	Dash();

	if (m_bDown)
		m_fAddScrollY += 5.f;
	else
		m_fAddScrollY -= 5.f;

	if (m_fAddScrollY > 300.f)
		m_fAddScrollY = 300.f;
	if (m_fAddScrollY < 0.f)
		m_fAddScrollY = 0.f;
}

void CPlayer::AddEffect(PLAYEREFFECT pEffect)
{
	CObj* pObj = nullptr;

	switch (pEffect)
	{
	case EFFECT_JUMP:
		pObj = CAbstractFactory<CEffect_Extinction>::CreateEffect(L"Jump", &D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 60.f, 0.f), &FRAME{ 0.f, 10.f, 5.f });
		ObjectManager->AddObject(OBJ_EFFECT, pObj);
		break;
	case EFFECT_DUST:
		m_fDustTime -= m_fTime;
		if (m_fDustTime < 0.f)
		{
			m_fDustTime = 0.2f;
			pObj = CAbstractFactory<CEffect_Extinction>::CreateEffect(L"Dust", &D3DXVECTOR3(m_tInfo.vPos.x, m_tInfo.vPos.y + 32.f, 0.f), &FRAME{ 0.f, 10.f, 5.f });
			ObjectManager->AddObject(OBJ_EFFECT, pObj);
		}
		break;
	}
}

void CPlayer::FrameChange()
{
	if (m_ePrevState != m_eCurState)
	{
		switch (m_eCurState)
		{
		case IDLE:
			m_wstrStateKey = L"Idle";
			m_tFrame = FRAME(0.f, 10.f, 5.f);
			break;
		case MOVE:
			m_wstrStateKey = L"Run";
			m_tFrame = FRAME(0.f, 14.f, 7.f);
			break;
		case JUMP:
			m_wstrStateKey = L"Jump";
			m_tFrame = FRAME(0.f, 0.f, 0.f);
			break;
		case DIE:
			m_wstrStateKey = L"Die";
			m_tFrame = FRAME(0.f, 0.f, 0.f);
			break;
		}

		m_ePrevState = m_eCurState;
	}
}

void CPlayer::FrameMove()
{
	m_tFrame.fFrame += m_tFrame.fCount * m_fTime;

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;
}

void CPlayer::Move()
{
	if (!m_bDash)
	{
		m_eCurState = IDLE;
		m_fVelocityX = 0.f;

		if (KeyManager->KeyDown('A') || KeyManager->KeyDown('D'))
		{
			m_fDustTime = 0.f;
			if(!m_bJump)
				AddEffect(EFFECT_DUST);
		}

		if (KeyManager->KeyPressing('A'))
		{
			m_fVelocityX = -m_tData.fMoveSpeed * m_fTime;
			m_eCurState = MOVE;

			if (!m_bJump)
				AddEffect(EFFECT_DUST);
		}
		if (KeyManager->KeyPressing('D'))
		{
			m_fVelocityX = m_tData.fMoveSpeed * m_fTime;
			m_eCurState = MOVE;

			if (!m_bJump)
				AddEffect(EFFECT_DUST);
		}
	}
}

void CPlayer::Jump()
{
	if (!m_bJump)
	{
		if (KeyManager->KeyDown('W'))
		{
			AddEffect(EFFECT_JUMP);
		}

		if (KeyManager->KeyPressing('W'))
		{
			m_bJump = true;
			m_bGround = false;
			m_fVelocityY = -m_tData.fMoveSpeed * 2.f * m_fTime;
		}

		if (m_bDown && KeyManager->KeyPressing(VK_SPACE))
		{
			m_bJump = true;
			m_bGround = false;
			m_fVelocityY += m_tData.fMoveSpeed * 0.5f * m_fTime;
		}
	}
	else
	{
		// 점프 중일 때
		m_fVelocityY += m_tData.fMoveSpeed  * 0.05f * /*0.010f*/m_fTime;

		if (m_bGround)
		{
			m_bJump = false;
			m_bDash = false;
			m_bDown = false;
		}

		if (!(KeyManager->KeyPressing('W')) && m_fVelocityY < 0)
			m_fVelocityY = 0.f;
	}
}

void CPlayer::Dash()
{
	//대시 카운트가 0 이상일 때 대시 가능
	if (m_tPData.iDashCnt > 0)
	{
		//마우스 우측 클릭 시 대시
		if (KeyManager->KeyDown(VK_RBUTTON))
		{
			std::cout << "DASH START\n";
			m_bDash = true;
			m_tPData.fDashTime = 0.5f;
			m_tPData.iDashCnt--;
			// 현재 마우스 방향 가져옴
			// 이전에 CheckMousePos에서 m_tInfo.vDir에 이미 계산되어 있음
			D3DXVec3Normalize(&m_vDashDir, &m_tInfo.vDir);

			// X속도와 Y속도 초기화 후 대시 속도 만큼 증가시킨다.
			m_vDashDir.x = m_vDashDir.x * m_tPData.fDashSpeed * m_fTime;
			m_vDashDir.y = m_vDashDir.y * m_tPData.fDashSpeed * m_fTime;
			m_fVelocityX = m_vDashDir.x;
			m_fVelocityY = m_vDashDir.y;
		}
	}

	if (m_bDash)
	{
		m_tPData.fDashTime -= m_fTime;

		if (m_tPData.fDashTime < 0.f)
		{
			m_bDash = false;
		}
		m_fVelocityX += m_vDashDir.x;
		m_fVelocityY += m_vDashDir.y;
	}

	//대시 카운트는 일정 시간 마다 충전되어야 한다.
	if (m_tPData.iMaxDashCnt > m_tPData.iDashCnt)
	{
		m_tPData.fDashChargeTime -= m_fTime;
		if (m_tPData.fDashChargeTime < 0.f)
		{
			m_tPData.iDashCnt++;
			m_tPData.fDashChargeTime = 2.f;
		}
	}
}