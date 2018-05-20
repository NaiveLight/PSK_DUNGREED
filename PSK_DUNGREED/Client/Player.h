#pragma once
#include "Obj.h"

class CWeapon;
class CWeaponBridge;
class CPlayer :
	public CObj
{
public:
	enum PLAYEREFFECT {
		EFFECT_JUMP
		, EFFECT_DUST
		, EFFECT_DASH
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
	const bool& GetIsJump() { return m_bJump; }
	const bool& GetIsDown() { return m_bDown; }
	const bool& GetIsDash() { return m_bDash; }
	const float& GetVelocityY() { return m_fVelocityY; }
	const int& GetAtt() { return m_tData.iMinAtt; }

public:
	void SetVelocityY(const float& fVelY) { m_fVelocityY = fVelY; }
	void SetJump(const bool& bJump) { m_bJump = bJump; }
	void SetMinMaxPos(const float& fMinX, const float& fMaxX) { m_fMinPosX = fMinX; m_fMaxPosX = fMaxX; }
	void SetInpuActive(const bool& bActive) { m_bInputActive = bActive; }
	void SetDungeonEnter(const bool& bDE) { m_bDungeonEnter = bDE; }

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void RenderCollider();

private:
	virtual void UpdateMatrix() override;
	void UpdateHitBox();

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
	void Attack();

private:
	void SwapWeapon();

private:
	DATA	m_tData = {};
	PDATA m_tPData = {};
	STATE m_eCurState = IDLE;
	STATE m_ePrevState = IDLE;

private:
	D3DXVECTOR3 m_vDashDir = D3DXVECTOR3(0.f, 0.f, 0.f);

private:
	CWeapon*			   m_pWeapon;
	CWeaponBridge* m_pWeaponBridge;

private:
	bool m_bGround = false;
	bool m_bDown = false;
	bool m_bJump = true;
	bool m_bDash = false;
	bool m_bAttack = false;
	bool m_bIsDead = false;

private:
	float m_fVelocityX = 0.f;
	float m_fVelocityY = 0.f;
	float m_fMaxVelY = 0.f;

private:
	float m_fDashAccX = 0.f;
	float m_fDashAccY = 0.f;

private:
	float m_fMinPosX = 0.f;
	float m_fMaxPosX = 0.f;

private:
	float m_fAddScrollY = 0.f;

private:
	float m_fAttTime = 0.f;
	float m_fDustTime = 0.f;

private:
	bool m_bWeaponRender = false;

private:
	bool m_bInputActive = true;
	bool m_bDungeonEnter = false;
	bool m_bStageEnter = false;
	bool m_bRoomEnter = false;
};

