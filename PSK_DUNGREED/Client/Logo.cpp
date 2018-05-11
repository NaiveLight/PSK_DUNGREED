#include "stdafx.h"
#include "Logo.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

HRESULT CLogo::Initialize()
{
	Device->SetBuffColor(D3DCOLOR_ARGB(255, 0, 0, 0));
	
	ObjectManager->AddObject(OBJ_BACKGROUND, CAbstractFactory<CBackGround>::CreateBackGround(L"Town"));

	return S_OK;
}

int CLogo::Update()
{
	ObjectManager->Update();
	return 0;
}

void CLogo::Render()
{
	ObjectManager->Render();
}

void CLogo::Release()
{
}
