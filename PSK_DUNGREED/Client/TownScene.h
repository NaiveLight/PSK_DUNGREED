#pragma once
#include "Scene.h"
class CTownScene :
	public CScene
{
public:
	CTownScene();
	virtual ~CTownScene();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

