#pragma once
#include "Obj.h"
class CHpEffect :
	public CObj
{
public:
	CHpEffect();
	virtual ~CHpEffect();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

