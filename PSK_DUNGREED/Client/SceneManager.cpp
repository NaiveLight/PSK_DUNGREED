#include "stdafx.h"
#include "SceneManager.h"

#include "Device.h"
#include "TextureManager.h"
#include "TimeManager.h"
#include "LogoScene.h"
#include "TitleScene.h"
#include "TownScene.h"
#include "Room_1.h"
#include "Room_2.h"
//#include "Room_3.h"

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
	Release();
}

HRESULT CSceneManager::ChangeScene(SCENEID eSceneID)
{
	if (eSceneID == SCENE_LOGO || eSceneID == SCENE_TITLE)
	{
		if (m_pScene != nullptr)
			Safe_Delete(m_pScene);

		switch (eSceneID)
		{
		case SCENE_LOGO:
			m_pScene = new CLogoScene;
			break;
		case SCENE_TITLE:
			m_pScene = new CTitleScene;
			break;
		}

		if (FAILED(m_pScene->Initialize()))
		{
			MSG_BOX(L"Scene Init Failed in SceneManager");
			return E_FAIL;
		}
		return S_OK;
	}

	m_bFade = true;
	m_bIsSceneChange = true;
	m_eCurScene = eSceneID;

	return S_OK;
}

void CSceneManager::Update()
{
	if (!m_bIsSceneChange)
		m_pScene->Update();
}

void CSceneManager::Render()
{
	if(!m_bIsSceneChange)
		m_pScene->Render();
	else
	{
		if (m_bFade)
			FadeIn();
		else
			FadeOut();
	}
}

void CSceneManager::Release()
{
	Safe_Delete(m_pScene);
}

void CSceneManager::FadeIn()
{
	if (m_pScene != nullptr)
		m_pScene->Render();

	m_fAlpha += 200.f * TimeManager->GetDeltaTime();

	if (m_fAlpha >= 250.f)
	{
		m_fAlpha = 255.f;
		m_bFade = false;
	}

	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	const TEXINFO* pTexInfo = TextureManager->GetTexture(L"BACKGROUND", L"Back", 0);
	
	Device->GetSprite()->SetTransform(&matIdentity);
	Device->GetSprite()->Draw(pTexInfo->pTexture, nullptr, nullptr, nullptr
		, D3DCOLOR_ARGB((int)m_fAlpha, 255, 255, 255));
}

void CSceneManager::FadeOut()
{
	if (m_pScene != nullptr)
		m_pScene->Render();

	if (m_fAlpha >= 10.f)
	{
		m_fAlpha -= 200.f * TimeManager->GetDeltaTime();

		D3DXMATRIX matIdentity;
		D3DXMatrixIdentity(&matIdentity);
		const TEXINFO* pTexInfo = TextureManager->GetTexture(L"BACKGROUND", L"Back", 0);
		Device->GetSprite()->SetTransform(&matIdentity);
		Device->GetSprite()->Draw(pTexInfo->pTexture, nullptr, nullptr, nullptr
			, D3DCOLOR_ARGB((int)m_fAlpha, 255, 255, 255));
	}

	if(m_eCurScene != SCENE_LOGO || m_eCurScene != SCENE_TITLE)
		SwapScene(m_eCurScene);
}

void CSceneManager::SwapScene(SCENEID eSceneID)
{
	if (m_pScene != nullptr)
		Safe_Delete(m_pScene);

	switch (eSceneID)
	{
	case SCENE_TOWN:
		m_pScene = new CTownScene;
		break;
	case SCENE_ROOM1:
		m_pScene = new CRoom_1;
		break;
	case SCENE_ROOM2:
		m_pScene = new CRoom_2;
		break;
	}

	if (FAILED(m_pScene->Initialize()))
	{
		MSG_BOX(L"Scene Init Failed in SceneManager");
		return;
	}

	m_bIsSceneChange = false;
}
