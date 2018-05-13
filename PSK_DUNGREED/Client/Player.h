#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	enum STANCE {IDLE, MOVE, JUMP, DIE, END};

public:
	CPlayer();
	virtual ~CPlayer();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	virtual void UpdateMatrix() override;

private:
	void InitPlayerAttributes();
	void CheckInput();

	void Move();
	void Jump();
	void Dash();
	void Attack();

private:
	RECT m_tHitRect = {};
	DATA	m_tData = {};
	STANCE m_eStance = IDLE;
	std::wstring m_wstrStateKey = L"";
	//CWeapon*
};

