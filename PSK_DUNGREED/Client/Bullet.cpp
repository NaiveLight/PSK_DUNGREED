#include "stdafx.h"
#include "Bullet.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "ScrollManager.h"
#include "SoundManager.h"
#include "CollisionManager.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "TileMap.h"

CBullet::CBullet()
{
}

CBullet::~CBullet()
{
	Release();
}

HRESULT CBullet::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Bullet Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Bullet Get Sprite Failed");
		return E_FAIL;
	}

	m_fAlpha = 255.f;
	m_fTime = TimeManager->GetDeltaTime();
	m_fSpeed = 300.f;
	m_wstrObjKey = L"BULLET";
	m_tInfo.vLook = D3DXVECTOR3(0.f, -1.f, 0.f);

	return S_OK;
}

int CBullet::Update()
{
	if (m_bCollision)
	{
		CObj* pObj = CAbstractFactory<CEffect_Extinction>::CreateEffect(L"BulletBanshee", false, &m_tInfo.vPos, &FRAME(0.f, 12.f, 6.f), &D3DXVECTOR3(0.f, -1.f, 0.f));
		ObjectManager->AddObject(OBJ_EFFECT, pObj);
		return 1;
	}
		

	m_tInfo.vPos += m_tInfo.vDir * m_fSpeed * m_fTime;

	m_bCollision = CCollisionManager::BulletToTile(this, dynamic_cast<CTileMap*>(ObjectManager->GetObjectList(OBJ_TILEMAP)->front()));

	FrameMove();
	UpdateMatrix();
	UpdateHitBox();

	return 0;
}

void CBullet::Render()
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

void CBullet::Release()
{
}

void CBullet::UpdateHitBox()
{
	m_tHitBox.fX = m_tInfo.vPos.x;
	m_tHitBox.fY = m_tInfo.vPos.y;
}

void CBullet::UpdateMatrix()
{
	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x - ScrollManager->GetScroll().x
		, m_tInfo.vPos.y - ScrollManager->GetScroll().y
		, 0.f);
}

void CBullet::FrameMove()
{
	m_tFrame.fFrame += m_tFrame.fCount * m_fTime;

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;
}
