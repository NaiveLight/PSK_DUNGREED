#include "stdafx.h"
#include "BackGround.h"

#include "Device.h"
#include "TextureManager.h"

CBackGround::CBackGround()
{
}


CBackGround::~CBackGround()
{
	Release();
}

HRESULT CBackGround::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"BackGround Get Device Failed");
		return E_FAIL;
	}

	m_pSprite= Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"BackGround Get Sprite Failed");
		return E_FAIL;
	}

	return S_OK;
}

int CBackGround::Update()
{
	return 0;
}

void CBackGround::Render()
{
	//const TEXINFO* pTexInfo = TextureManager->
}

void CBackGround::Release()
{
}
