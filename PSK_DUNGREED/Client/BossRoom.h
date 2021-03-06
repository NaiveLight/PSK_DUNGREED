#pragma once
#include "Scene.h"
class CBossRoom :
	public CScene
{
public:
	CBossRoom();
	virtual ~CBossRoom();

	// CScene을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

