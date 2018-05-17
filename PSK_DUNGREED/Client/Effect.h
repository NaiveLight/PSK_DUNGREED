#pragma once
#include "Obj.h"

class CEffect final:
	public CObj
{
public:
	CEffect();
	virtual ~CEffect();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

