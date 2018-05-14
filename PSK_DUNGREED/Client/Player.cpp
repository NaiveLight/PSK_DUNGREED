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
	CheckMousePos();

	m_tFrame.fFrame += m_tFrame.fCount * TimeManager->GetTime();
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;

	CheckInput();

	m_bGround = CCollisionManager::PlayerToTile(this, dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front()));

	//if (m_bGround)
	//{
	//	std::cout << "Ground\n";
	//}

	m_tInfo.vPos.x += m_fVelocityX;
	m_tInfo.vPos.y += (m_bGround ? 0.f : 98.1f * TimeManager->GetTime()) + m_fVelocityY;

	ScrollManager->SetCurScroll(m_tInfo.vPos.x - WINCX * 0.5f, m_tInfo.vPos.y - WINCY * 0.5f);

	UpdateMatrix();
	UpdateHitRect();

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

	const TEXINFO*		pColInfo = TextureManager->GetTexture(m_wstrObjKey, L"PCollider", 0);
	if (pColInfo == nullptr)
		return;

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
		, m_tInfo.vPos.y + 32.f - ScrollManager->GetScroll().y
		, 0.f);

	m_tInfo.matWorld = matScale * m_tInfo.matWorld;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pColInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pColInfo->tImgInfo.Width * 0.5f, pColInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
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
		, m_tInfo.vPos.y /*- 32.f*/ - ScrollManager->GetScroll().y
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
	m_tInfo.vPos = D3DXVECTOR3(WINCX * 0.5f + 500.f, WINCY  + 360.f, 0.f);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);
	m_tInfo.fCX = 32.f;
	m_tInfo.fCY = 64.f;

	m_wstrObjKey = L"PLAYER";
	m_wstrStateKey = L"Idle";

	m_tFrame = FRAME(0, 10, 5);

	m_tData.fMoveSpeed = 500.f;
	m_tData.fAttSpeed = 1.f;

	m_tData.iCurHp = 80;
	m_tData.iMaxHp = 80;

	m_fMaxY = m_tData.fMoveSpeed * 2.f * TimeManager->GetTime();
	m_fAlpha = 155.f;
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
	Move();
	Jump();
}

void CPlayer::Move()
{
	m_fVelocityX = 0.f;

	if (KeyManager->KeyPressing('A'))
	{
		m_fVelocityX = -m_tData.fMoveSpeed * TimeManager->GetTime();
	}
	if (KeyManager->KeyPressing('D'))
	{
		m_fVelocityX = m_tData.fMoveSpeed * TimeManager->GetTime();
	}
}

void CPlayer::Jump()
{
	if (!m_bJump)
	{
		if (KeyManager->KeyPressing('W'))
		{
			m_bJump = true;
			m_bGround = false;
			m_fVelocityY = -m_tData.fMoveSpeed * TimeManager->GetTime();
		}
	}
	else
	{	
		// 점프 중일 때
		if (m_bGround)
		{
			m_bJump = false;
			m_fVelocityY = 0.f;
		}
		else
			m_fVelocityY += m_tData.fMoveSpeed  * 0.05f * TimeManager->GetTime();

		if (KeyManager->KeyUp('W') && m_fVelocityY < 0)
			m_fVelocityY = 0.f;

	}
}


