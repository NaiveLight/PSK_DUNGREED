#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	enum STATE{SPAWN, IDLE, MOVE, ATTACK, DEAD, END};

public:
	CMonster();
	virtual ~CMonster();

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;
};

