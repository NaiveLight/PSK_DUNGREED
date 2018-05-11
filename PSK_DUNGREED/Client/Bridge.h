#pragma once

#include "Include.h"

class CObj;
class CBridge abstract
{
public:
	CBridge();
	virtual ~CBridge();

public:
	void SetObj(CObj* pObj);

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update(INFO& tInfo) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	CObj* m_pObj = nullptr;
	std::wstring m_wstrStateKey = L"";
	FRAME	m_tFrame = {};
};

