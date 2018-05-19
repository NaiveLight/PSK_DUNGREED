#pragma once
#include "Scene.h"
class CRoom_1 :
	public CScene
{
public:
	CRoom_1();
	virtual ~CRoom_1();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

