#pragma once

#include "Scene.h"

class CTitleScene final:
	public CScene
{
public:
	CTitleScene();
	virtual ~CTitleScene();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

