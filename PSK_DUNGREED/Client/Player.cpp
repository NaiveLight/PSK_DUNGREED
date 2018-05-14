#include "stdafx.h"
#include "Player.h"

#include "Device.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "TimeManager.h"

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
	//std::cout << m_tInfo.vPos.x << " , " << m_tInfo.vPos.y << "\n";

	CheckMousePos();

	//std::cout << m_tInfo.vDir.x << " , " << m_tInfo.vDir.y << "\n";

	m_tFrame.fFrame += m_tFrame.fCount * TimeManager->GetTime();
	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;

	CheckInput();
	UpdateMatrix();

	m_tInfo.vPos.x += m_fVelocityX;
	m_tInfo.vPos.y += m_fVelocityY + m_fAccelY;

	ScrollManager->SetCurScroll(m_tInfo.vPos.x - WINCX * 0.5f, m_tInfo.vPos.y - WINCY * 0.5f);

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
		, m_tInfo.vPos.y - ScrollManager->GetScroll().y
		, 0.f);

	m_tInfo.matWorld = matScale * m_tInfo.matWorld;
}

void CPlayer::InitPlayerAttributes()
{
	m_tInfo.vPos = D3DXVECTOR3(WINCX * 0.5f, WINCY  + 360.f, 0.f);
	m_tInfo.vLook = D3DXVECTOR3(1.f, 0.f, 0.f);

	m_wstrObjKey = L"PLAYER";
	m_wstrStateKey = L"Idle";

	m_tFrame = FRAME(0, 10, 5);

	m_tData.fMoveSpeed = 500.f;
	m_tData.fAttSpeed = 3.f;

	m_tData.iCurHp = 80;
	m_tData.iMaxHp = 80;
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

}


