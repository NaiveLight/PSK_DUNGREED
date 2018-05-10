#include "stdafx.h"
#include "Logo.h"

#include "Device.h"
#include "ObjectManager.h"


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
	return S_OK;
}

int CLogo::Update()
{
	return 0;
}

void CLogo::Render()
{
}

void CLogo::Release()
{
}
