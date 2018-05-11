#pragma once
#include "Obj.h"

class CUI :
	public CObj
{
public:
	CUI();
	virtual ~CUI();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int	m_iAlpha = 0;
};

