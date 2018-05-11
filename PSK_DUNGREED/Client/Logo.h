#pragma once
#include "Scene.h"

class CLogo :
	public CScene
{
public:
	CLogo();
	virtual ~CLogo();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

