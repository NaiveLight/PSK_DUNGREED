#pragma once
#include "Obj.h"
class CBackGround :
	public CObj
{
public:
	CBackGround();
	virtual ~CBackGround();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void InitBackGroundAttributes();

private:
	std::wstring m_wstrStateKey;
};

