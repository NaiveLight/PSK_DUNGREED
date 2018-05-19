#include "stdafx.h"
#include "Effect_Extinction.h"

#include "Device.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "ScrollManager.h"
#include "Obj.h"

CEffect_Extinction::CEffect_Extinction()
{
}

CEffect_Extinction::~CEffect_Extinction()
{
	Release();
}

HRESULT CEffect_Extinction::Initialize()
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

	return S_OK;
}

int CEffect_Extinction::Update(INFO & rInfo)
{
	D3DXMATRIX matScale, matRotate, matTrans;

	D3DXMatrixIdentity(&matScale);

	float 	m_fRotateAngle = D3DXToDegree(acosf(D3DXVec3Dot(&rInfo.vDir, &rInfo.vLook)));

	if (m_bIsLeft)
		m_fRotateAngle *= -1.f;

	if (m_bIsLeft)
		D3DXMatrixScaling(&matScale, -1.f, 1.f, 0.f);

	D3DXMatrixRotationZ(&matRotate, D3DXToRadian(m_fRotateAngle));
	D3DXMatrixTranslation(&matTrans, rInfo.vPos.x - ScrollManager->GetScroll().x, rInfo.vPos.y - ScrollManager->GetScroll().y, 0.f);

	rInfo.matWorld = matScale * matRotate * matTrans;

	m_tFrame.fFrame += m_tFrame.fCount * TimeManager->GetDeltaTime();
	if (m_tFrame.fFrame > m_tFrame.fMax)
		return 1;

	return 0;
}

void CEffect_Extinction::Render()
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

void CEffect_Extinction::Release()
{
}
