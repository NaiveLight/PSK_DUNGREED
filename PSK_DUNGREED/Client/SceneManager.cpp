#include "stdafx.h"
#include "SceneManager.h"

#include "LogoScene.h"
#include "TitleScene.h"
#include "TownScene.h"

CSceneManager::CSceneManager()
{
}


CSceneManager::~CSceneManager()
{
	Release();
}

HRESULT CSceneManager::ChangeScene(SCENEID eSceneID)
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
	case SCENE_TOWN:
		m_pScene = new CTownScene;
		break;
	}

	if (FAILED(m_pScene->Initialize()))
	{
		MSG_BOX(L"Scene Init Failed in SceneManager");
		return E_FAIL;
	}


	return S_OK;
}

void CSceneManager::Update()
{
	m_pScene->Update();
}

void CSceneManager::Render()
{
	m_pScene->Render();
}

void CSceneManager::Release()
{
	Safe_Delete(m_pScene);
}
