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

public:
	CPlayer();
	virtual ~CPlayer();

public:
	const RECT& GetHitRect() { return m_tHitRect; }

public:
	void SetVelocityY(const float& fVelY) { m_fVelocityY = fVelY; }

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	virtual void UpdateMatrix() override;
	void UpdateHitRect();

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
	bool m_bGround = true;
	bool m_bCrouch = false;
	bool m_bJump = false;

	float m_fVelocityX = 0.f;
	float m_fVelocityY = 0.f;
	float m_fMaxY = 0.f;

	float m_fAlpha = 0.f;

	//CWeapon*
};

