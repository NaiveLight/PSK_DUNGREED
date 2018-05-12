#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
}

CScene::~CScene()
{
}

void CScene::LateInit()
{
	if (!m_bIsInit)
	{
		this->LateInit();
		m_bIsInit = true;
	}
}
