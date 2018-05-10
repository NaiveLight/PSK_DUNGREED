#include "stdafx.h"
#include "Logo.h"


CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

HRESULT CLogo::Initialize()
{
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
