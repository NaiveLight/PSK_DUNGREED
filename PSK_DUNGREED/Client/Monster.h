#pragma once
#include "Obj.h"
class CMonster :
	public CObj
{
public:
	enum STATE{SPAWN, IDLE, MOVE, ATTACK, END};

public:
	CMonster();
	virtual ~CMonster();

public:
	void ApplyDamage(const int& iAtt);

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update() PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	DATA m_tData;
	STATE m_eCurState;
	STATE m_ePrevState;
	bool m_bIsDead;
};

