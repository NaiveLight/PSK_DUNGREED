#pragma once
#include "Obj.h"
class CPlayer :
	public CObj
{
public:
	enum PLAYEREFFECT {
		EFFECT_JUMP
		, EFFECT_DUST
	};

	enum STATE {
		IDLE = 0x00000001
		, MOVE = 0x00000002
		, JUMP = 0x00000004
		, DIE = 0x00000008
		, END
	};

public:
	CPlayer();
	virtual ~CPlayer();

public:
	const RECT& GetHitRect() { return m_tHitRect; }
	const bool& GetIsJump() { return m_bJump; }
	const bool& GetIsDown() { return m_bDown; }
	const bool& GetIsDash() { return m_bDash; }
	const float& GetVelocityY() { return m_fVelocityY; }

public:
	void SetVelocityY(const float& fVelY) { m_fVelocityY = fVelY; }
	void SetJump(const bool& bJump) { m_bJump = bJump; }
	void SetMinMaxPos(const float& fMinX, const float& fMaxX) { m_fMinPosX = fMinX; m_fMaxPosX = fMaxX; }

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
	void AddEffect(PLAYEREFFECT pEffect);

private:
	void FrameChange();
	void FrameMove();

private:
	void Move();
	void Jump();
	void Dash();
private:
	RECT m_tHitRect = {};
	DATA	m_tData = {};
	PDATA m_tPData = {};
	STATE m_eCurState = IDLE;
	STATE m_ePrevState = IDLE;
	DWORD  m_dwStance = 0;
	std::wstring m_wstrStateKey = L"";

	D3DXVECTOR3 m_vDashDir = D3DXVECTOR3(0.f, 0.f, 0.f);

	bool m_bIsLeft = false;
	bool m_bGround = false;
	bool m_bDown = false;
	bool m_bJump = true;
	bool m_bDash = false;

	float m_fVelocityX = 0.f;
	float m_fVelocityY = 0.f;
	float m_fMaxVelY = 0.f;
	float m_fGravity = 0.f;

	float m_fDashAccX = 0.f;
	float m_fDashAccY = 0.f;

	float m_fAlpha = 0.f;

	float m_fMinPosX = 0.f;
	float m_fMaxPosX = 0.f;

	float m_fAddScrollY = 0.f;

	float m_fDustTime = 0.f;
	//CWeapon*
};

