#pragma once
#include "Obj.h"
class CLayer :
	public CObj
{
public:
	CLayer();
	virtual ~CLayer();

public:
	void SetScrollRatio(const float& fSpeed) { m_fScrollRatio = fSpeed; }

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	virtual void UpdateMatrix() override;

private:
	float m_fScrollRatio = 0.f;
};

