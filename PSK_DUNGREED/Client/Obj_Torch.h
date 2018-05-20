#pragma once
#include "Obj.h"
class CObj_Torch :
	public CObj
{
public:
	CObj_Torch();
	virtual ~CObj_Torch();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

