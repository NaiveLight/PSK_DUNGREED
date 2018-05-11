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
	void SetFrame(const FRAME* pFrame);

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update(INFO& tInfo) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	CObj* m_pObj = nullptr;
	FRAME	m_tFrame = {};
};

