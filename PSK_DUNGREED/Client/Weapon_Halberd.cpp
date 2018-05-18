#include "stdafx.h"
#include "Weapon_Halberd.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "ScrollManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"

CWeapon_Halberd::CWeapon_Halberd()
{
}

CWeapon_Halberd::~CWeapon_Halberd()
{
	Release();
}

HRESULT CWeapon_Halberd::Initialize()
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
	m_wstrStateKey = L"Halberd";
	m_tFrame = FRAME(0.f, 0.f, 0.f);

	m_tInfo.vLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	
	m_fAttTime = 1.f;
	m_bRectHit = true;
	m_tHitBox.fCX = 28.f;
	m_tHitBox.fCY = 72.f;
	m_bRender = false;

	return S_OK;
}

int CWeapon_Halberd::Update()
{
	CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();
	m_bIsLeft = pPlayer->GetIsLeft();

	if (!m_bAttack)
	{
		//m_tInfo.vPos = m_bIsLeft ? D3DXVECTOR3(0.f, 32.f, 0.f) : D3DXVECTOR3(0.f, 32.f, 0.f);
		m_tInfo.vDir = (GetMousePos() + ScrollManager->GetScroll()) - (m_tInfo.vPos + pPlayer->GetInfo()->vPos);
		D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
	}
	else
	{
		m_tInfo.vPos += -m_tInfo.vDir;

		if (m_tInfo.vPos.x <= m_vOrigin.x && m_tInfo.vPos.y <= m_vOrigin.y)
		{
			m_tInfo.vPos = D3DXVECTOR3(22.f, 42.f, 0.f);
			m_bAttack = false;
		}
	}

	UpdateMatrix();

	return 0;
}

void CWeapon_Halberd::Render()
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

void CWeapon_Halberd::Release()
{
}

void CWeapon_Halberd::UpdateMatrix()
{
	CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();
	D3DXMATRIX matScale, matTrans, matRotate, matParent;

	m_fRotateAngle = D3DXToDegree(acosf(D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook)));
	if (m_bIsLeft)
		m_fRotateAngle *= -1.f;

	D3DXMatrixScaling(&matScale, (m_bIsLeft ? -1.f : 1.f), 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(m_fRotateAngle));
	D3DXMatrixTranslation(&matParent, pPlayer->GetInfo()->vPos.x + (m_bIsLeft ? - 24.f : 24.f)- ScrollManager->GetScroll().x, pPlayer->GetInfo()->vPos.y + 32.f - ScrollManager->GetScroll().y, 0.f);

	m_tInfo.matWorld = matScale * matRotate  * matTrans * matParent;
}

void CWeapon_Halberd::Attack()
{
}
