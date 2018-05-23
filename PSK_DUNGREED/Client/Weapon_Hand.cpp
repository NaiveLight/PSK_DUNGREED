#include "stdafx.h"
#include "Weapon_Hand.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "ScrollManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "SoundManager.h"

CWeapon_Hand::CWeapon_Hand()
{
}

CWeapon_Hand::~CWeapon_Hand()
{
	Release();
}

HRESULT CWeapon_Hand::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Weapon_Hand Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Weapon_Hand Get Sprite Failed");
		return E_FAIL;
	}

	m_wstrObjKey = L"WEAPON";
	m_wstrStateKey = L"Hand";
	m_tFrame = FRAME(0.f, 0.f, 0.f);

	m_tInfo.vLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	
	m_fAttTime = 0.5f;
	m_bRectHit = true;
	m_tHitBox.fCX = 16.f;
	m_tHitBox.fCY = 16.f;
	m_bRender = true;

	m_iAtt = 4;

	return S_OK;
}

int CWeapon_Hand::Update()
{
	CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();
	m_bIsLeft = pPlayer->GetIsLeft();

	if (!m_bAttack)
	{
		m_tInfo.vPos.x = m_bIsLeft ? -22.f : 22.f;
		m_tInfo.vPos.y = 42.f;

		m_tInfo.vDir = (GetMousePos() + ScrollManager->GetScroll()) - (m_tInfo.vPos + pPlayer->GetInfo()->vPos);
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	}
	else
	{
		m_tInfo.vPos -= m_tInfo.vDir * 3.f;
		
		if (m_bTempLeft)
		{
			if (m_vOrigin.x <= m_tInfo.vPos.x)
				m_bAttack = false;
		}
		else
		{
			if (m_vOrigin.x >= m_tInfo.vPos.x)
				m_bAttack = false;
		}
	}
	UpdateMatrix();
	return 0;
}

void CWeapon_Hand::Render()
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

void CWeapon_Hand::Release()
{
}

void CWeapon_Hand::UpdateMatrix()
{
	CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();
	D3DXMATRIX matScale, matTrans, matRotate, matParent;
	
	m_fRotateAngle = D3DXToDegree(acosf(D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook)));
	
	if (m_bIsLeft)
		m_fRotateAngle *= -1.f;

	D3DXMatrixScaling(&matScale, (m_bIsLeft ? -1.f : 1.f), 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(m_fRotateAngle));
	D3DXMatrixTranslation(&matParent, pPlayer->GetInfo()->vPos.x - ScrollManager->GetScroll().x, pPlayer->GetInfo()->vPos.y- ScrollManager->GetScroll().y, 0.f);

	m_tInfo.matWorld = matScale * matRotate * matTrans * matParent;
}

void CWeapon_Hand::Attack()
{
	SoundManager->PlaySound(L"ATTACK_HAND.wav", CSoundManager::PATTACK);
	m_bAttack = true;
	m_bTempLeft = m_bIsLeft;
	m_vOrigin = m_tInfo.vPos;
	m_tInfo.vPos += m_tInfo.vDir * 30.f;
}
