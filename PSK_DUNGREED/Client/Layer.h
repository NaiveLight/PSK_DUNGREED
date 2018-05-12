#pragma once
#include "Obj.h"
class CLayer :
	public CObj
{
public:
	CLayer();
	virtual ~CLayer();

public:
	void SetSpeed(const float& fSpeed) { m_fSpeed = fSpeed; }

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	float m_fSpeed = 0.f;
};

