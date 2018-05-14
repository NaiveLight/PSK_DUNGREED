#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	enum STATE {
		IDLE = 0x00000001
		, MOVE = 0x00000002
		, JUMP = 0x00000004
		, DIE = 0x00000008
		, END};

	const DWORD dwIdle = 0x00000001;
	const DWORD dwGround = 0x00000002;
	const DWORD dwCrouch = 0x00000004;
	const DWORD dwJump = 0x00000008;
	const DWORD dwDash = 0x00000016;
	const DWORD dwDead = 0x00000032;

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
	void CheckMousePos();
	void CheckInput();

	void Move();
	void Jump();
	void Dash();
	void Attack();

private:
	RECT m_tHitRect = {};
	DATA	m_tData = {};
	STATE m_eState = IDLE;
	DWORD  m_dwStance = 0;
	std::wstring m_wstrStateKey = L"";

	bool m_bIsLeft = false;

	float m_fVelocityX = 0.f;
	float m_fVelocityY = 0.f;
	float m_fAccelX = 0.f;
	float m_fAccelY = 0.f;

	//CWeapon*
};

