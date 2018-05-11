#pragma once
#include "Obj.h"

class CUI :
	public CObj
{
public:
	CUI();
	virtual ~CUI();

public:
	void SetAlpha(const float& fAlpha) { m_fAlpha = fAlpha; }

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	float	m_fAlpha = 0.f;
};

