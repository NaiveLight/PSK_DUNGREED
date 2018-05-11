#include "stdafx.h"
#include "UIBridge.h"

#include "TextureManager.h"

#include "Obj.h"

CUIBridge::CUIBridge()
{
}

CUIBridge::~CUIBridge()
{
}

void CUIBridge::Render(void)
{
	const TEXINFO*		pTexInfo = TextureManager->GetTexture(m_pObj->GetObjKey()
		, m_pObj->GetStateKey(), (int)m_tFrame.fFrame);

	if (pTexInfo == nullptr)
		return;

	m_pSprite->SetTransform(&m_pObj->GetInfo()->matWorld);
	m_pSprite->Draw(pTexInfo->pTexture
		, nullptr
		, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
		, nullptr
		, D3DCOLOR_ARGB(m_iAlpha, 255, 255, 255));
}
