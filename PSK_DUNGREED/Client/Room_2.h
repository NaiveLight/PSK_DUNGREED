#pragma once
#include "Scene.h"
class CRoom_2 :
	public CScene
{
public:
	CRoom_2();
	virtual ~CRoom_2();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

