#include "stdafx.h"
#include "Weapon_Sword.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "ScrollManager.h"
#include "TextureManager.h"
#include "CollisionManager.h"
#include "TimeManager.h"
#include "SoundManager.h"

CWeapon_Sword::CWeapon_Sword()
{
}


CWeapon_Sword::~CWeapon_Sword()
{
	Release();
}

HRESULT CWeapon_Sword::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Weapon_Sword Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Weapon_Sword Get Sprite Failed");
		return E_FAIL;
	}

	m_wstrObjKey = L"WEAPON";
	m_wstrStateKey = L"ShortSword";
	m_tFrame = FRAME(0.f, 0.f, 0.f);

	m_tInfo.vLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);

	m_fAttTime = 0.3f;
	m_bRectHit = false;
	m_tHitBox.fCX = 28.f;
	m_tHitBox.fCY = 72.f;
	m_bRender = true;

	m_iAtt = 20;

	return S_OK;
}

int CWeapon_Sword::Update()
{
	CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();
	m_bIsLeft = pPlayer->GetIsLeft();

	m_tInfo.vPos = m_bIsLeft ? D3DXVECTOR3(-10.f, -32.f, 0.f) : D3DXVECTOR3(10.f, -32.f, 0.f);
	m_tInfo.vDir = (GetMousePos() + ScrollManager->GetScroll()) - (m_tInfo.vPos + pPlayer->GetInfo()->vPos);
	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);

	UpdateMatrix();

	return 0;
}

void CWeapon_Sword::Render()
{
	const TEXINFO*		pTexInfo = TextureManager->GetTexture(m_wstrObjKey, m_wstrStateKey, (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
		return;

	m_pSprite->SetTransform(&m_tInfo.matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(BYTE((ObjectManager->GetPlayer()->GetAlpha())), 255, 255, 255));
}

void CWeapon_Sword::Release()
{
}

void CWeapon_Sword::UpdateMatrix()
{
	CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();
	D3DXMATRIX matScale, matTrans, matRevolve,matParent;

	m_fRevolveAngle = D3DXToDegree(acosf(D3DXVec3Dot(&m_tInfo.vDir, &m_tInfo.vLook)));

	m_fRevolveAngle -= 90.f;
	m_fRevolveAngle += m_fAngleOffset;
	if (m_bIsLeft)
		m_fRevolveAngle *= -1.f;

	D3DXMatrixScaling(&matScale, (m_bIsLeft ? -1.f : 1.f), 1.f, 0.f);
	D3DXMatrixTranslation(&matTrans, m_tInfo.vPos.x, m_tInfo.vPos.y, 0.f);
	D3DXMatrixRotationZ(&matRevolve, D3DXToRadian(m_fRevolveAngle));
	D3DXMatrixTranslation(&matParent, pPlayer->GetInfo()->vPos.x + (m_bIsLeft ? -20.f - m_fOffsetX: 20.f + m_fOffsetX) - ScrollManager->GetScroll().x, pPlayer->GetInfo()->vPos.y + m_fOffsetY + 32.f - ScrollManager->GetScroll().y, 0.f);

	m_tInfo.matWorld = matScale *  matTrans * matRevolve * matParent;
}

void CWeapon_Sword::Attack()
{
	SoundManager->PlaySound(L"Swing.wav", CSoundManager::PATTACK);
	ScrollManager->ShakingStart(4.f, 0.1f);
	
	CObj* pPlayer = ObjectManager->GetObjectList(OBJ_PLAYER)->front();
	D3DXVECTOR3 vPos = D3DXVECTOR3(
		pPlayer->GetInfo()->vPos.x + (m_bIsLeft ? -25.f - m_fOffsetX : 25.f + m_fOffsetX) + (m_tInfo.vDir.x * 10.f)
		,pPlayer->GetInfo()->vPos.y + m_fOffsetY + 32.f + (m_tInfo.vDir.y * 10.f)
		, 0.f
	);

	CObj* pObj = CAbstractFactory<CEffect_Extinction>::CreateEffect(L"Swing", m_bIsLeft, &vPos, &FRAME(0.f, 12.f, 3.f), &m_tInfo.vDir);
	ObjectManager->AddObject(OBJ_EFFECT, pObj);
	ObjectManager->AddObject(OBJ_PATTACK, CAbstractFactory<CHitBox>::CreateHitBox(dynamic_cast<CPlayer*>(pPlayer)->GetAtt(), false, true, &HITBOX{ vPos.x, vPos.y, 160.f, 112.f }, &vPos));

	if (!m_bAttack)
	{
		m_fAngleOffset = 200.f;
		m_fOffsetX = -5.f;
		m_fOffsetY = 10.f;
	}
	else
	{
		m_fAngleOffset = m_fOffsetX = m_fOffsetY = 0.f;
	}

	m_bAttack = !m_bAttack;
	m_bRender = !m_bRender;
}
