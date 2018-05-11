#pragma once
#include "Scene.h"

class CLogoScene final:
	public CScene
{
public:
	CLogoScene();
	virtual ~CLogoScene();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

