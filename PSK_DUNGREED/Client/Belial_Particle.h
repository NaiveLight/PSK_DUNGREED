#pragma once
#include "Obj.h"
class CBelial_Particle :
	public CObj
{
public:
	CBelial_Particle();
	virtual ~CBelial_Particle();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

