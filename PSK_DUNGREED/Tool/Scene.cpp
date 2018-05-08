#include "stdafx.h"
#include "Scene.h"

#include "ToolView.h"
#include "Device.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

HRESULT CScene::Initialize()
{
	m_pSprite = Device->GetSprite();
	m_pFont = Device->GetFont();

	return S_OK;
}

void CScene::Update()
{
}

void CScene::Render()
{
}

void CScene::Release()
{
}

void CScene::TileRelease()
{
}

void CScene::MapObjRelease()
{
}

void CScene::TileRender()
{
}

void CScene::ColliderRender()
{
}

void CScene::MapObjRender()
{
}

void CScene::MiniViewRender()
{
}

void CScene::ObjViewRender()
{
	if (m_bisTile)
	{
		if (m_pCurTile == nullptr)
			return;
	}
	else
	{
		if (m_pCurMapObj == nullptr)
			return;
	}
}

void CScene::Picking()
{
}

void CScene::TileChange()
{
}

void CScene::CreateMapObj()
{
}
