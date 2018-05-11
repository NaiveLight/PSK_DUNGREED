#include "stdafx.h"
#include "TitleScene.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"

CTitleScene::CTitleScene()
{
}

CTitleScene::~CTitleScene()
{
	Release();
}

HRESULT CTitleScene::Initialize()
{
	Device->SetBuffColor(D3DCOLOR_ARGB(255, 0, 0, 0));

	return S_OK;
}

int CTitleScene::Update()
{
	return 0;
}

void CTitleScene::Render()
{
}

void CTitleScene::Release()
{
}
