#pragma once
#include "Obj.h"

class CEffect :
	public CObj
{
public:
	CEffect();
	virtual ~CEffect();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

