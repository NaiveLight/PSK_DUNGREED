#include "stdafx.h"
#include "Effect_Alpha.h"

#include "Device.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "ScrollManager.h"
#include "Obj.h"

CEffect_Alpha::CEffect_Alpha()
{
}


CEffect_Alpha::~CEffect_Alpha()
{
	Release();
}

HRESULT CEffect_Alpha::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Effect Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"Effect Get Sprite Failed");
		return E_FAIL;
	}

	m_wstrObjKey = m_pObj->GetObjKey();
	m_wstrStateKey = m_pObj->GetStateKey();
	m_tFrame = *m_pObj->GetFrame();
	m_bIsLeft = m_pObj->GetIsLeft();

	m_fAlpha = 255.f;

	return S_OK;
}

int CEffect_Alpha::Update(INFO & rInfo)
{
	D3DXMATRIX matScale, matTrans;

	D3DXMatrixIdentity(&matScale);

	if (m_bIsLeft)
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);

	D3DXMatrixTranslation(&matTrans, rInfo.vPos.x - ScrollManager->GetScroll().x, rInfo.vPos.y - ScrollManager->GetScroll().y, 0.f);

	rInfo.matWorld = matScale * matTrans;

	m_tFrame.fFrame += m_tFrame.fCount * TimeManager->GetDeltaTime();
	
	m_fAlpha -= 10.f;

	if (m_fAlpha < 0.f)
		return 1;

	return 0;
}

void CEffect_Alpha::Render()
{
	const TEXINFO*		pTexInfo = TextureManager->GetTexture(m_wstrObjKey.c_str(), m_wstrStateKey.c_str(), (int)m_tFrame.fFrame);
	if (pTexInfo == nullptr)
		return;

	m_pSprite->SetTransform(&m_pObj->GetInfo()->matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(BYTE(m_fAlpha), 255, 255, 255));
}

void CEffect_Alpha::Release()
{
}
