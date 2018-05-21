#include "stdafx.h"
#include "Belial_CenterParticle.h"

#include "Device.h"
#include "TextureManager.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "KeyManager.h"
#include "ScrollManager.h"
#include "TimeManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"

CBelial_CenterParticle::CBelial_CenterParticle()
{
}

CBelial_CenterParticle::~CBelial_CenterParticle()
{
	Release();
}

HRESULT CBelial_CenterParticle::Initialize()
{
	m_fTime = TimeManager->GetDeltaTime();
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Belial Back Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Belial Back Get Sprite Failed");
		return E_FAIL;
	}

	m_wstrObjKey = L"OBJECT";
	m_wstrStateKey = L"BossBack";
	m_tFrame = FRAME(0.f, 20.f, 10.f);
	m_tInfo.vLook = D3DXVECTOR3(0.f, -1.f, 0.f);
	m_fAngle = 90.f;
	m_fAlpha = 0.f;
	m_fEffectTime = 1.f;

	return S_OK;
}

int CBelial_CenterParticle::Update()
{
	m_fAngle += float(rand() % 11 + 1);

	if (m_fAngle > 360.f)
		m_fAngle -= 360.f;

	m_fEffectTime -= m_fTime;

	UpdateMatrix();
	FrameMove();
	return 0;
}

void CBelial_CenterParticle::Render()
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

void CBelial_CenterParticle::Release()
{
}

void CBelial_CenterParticle::UpdateMatrix()
{
	D3DXMatrixTranslation(&m_tInfo.matWorld
		, m_tInfo.vPos.x - ScrollManager->GetScroll().x
		, m_tInfo.vPos.y - ScrollManager->GetScroll().y
		, 0.f);
}

void CBelial_CenterParticle::FrameMove()
{
	m_tFrame.fFrame += m_tFrame.fCount * m_fTime;

	if (m_tFrame.fFrame > m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;
}
