#include "stdafx.h"
#include "Weapon_Hand.h"

#include "Device.h"
#include "TimeManager.h"
#include "TextureManager.h"
#include "ScrollManager.h"
#include "Obj.h"

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
		MSG_BOX(L"Weapon Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Weapon Get Sprite Failed");
		return E_FAIL;
	}

	m_wstrObjKey = m_pObj->GetObjKey();
	m_wstrStateKey = m_pObj->GetStateKey();
	m_tFrame = *m_pObj->GetFrame();

	return S_OK;
}

int CWeapon_Hand::Update(INFO & rInfo)
{
	//플레이어가 공격하면 공전 각도 바꾸어줌
	return 0;
}

void CWeapon_Hand::Render()
{
	const TEXINFO*		pTexInfo = TextureManager->GetTexture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
		return;

	m_pSprite->SetTransform(&m_pObj->GetInfo()->matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(255, 255, 255, 255));
}

void CWeapon_Hand::Release()
{
}

void CWeapon_Hand::UpdateMatrix(INFO & rInfo)
{
	D3DXMATRIX matRot, matTrans, matRevolve, matParent;

}
