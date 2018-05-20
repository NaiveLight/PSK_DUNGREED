#pragma once
#include "Obj.h"
class CObj_Dungeon :
	public CObj
{
public:
	CObj_Dungeon();
	virtual ~CObj_Dungeon();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

