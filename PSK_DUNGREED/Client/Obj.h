#pragma once

#include "Include.h"
class CObj abstract
{
public:
	CObj();
	virtual ~CObj();

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update()	PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	INFO m_tInfo = {};	
	FRAME m_tFrame = {};
	std::wstring m_wstrObjKey = L"";
};

