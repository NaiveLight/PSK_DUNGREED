#pragma once
#include "Monster.h"
class CBelial_Hand;
class CBelial_CenterParticle;
class CBelial :
	public CMonster
{
public:
	CBelial();
	virtual ~CBelial();

private:
	void InitAttributes();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void LateInit();

private:
	void UpdateMatrix();
	void UpdateHitBox();

private:
	void FrameChange();
	void FrameMove();

private:
	void Attack();

private:
	CObj* m_pLeftHand = nullptr;
	CObj* m_pRightHand = nullptr;
	CObj* m_pParticle = nullptr;

private:
	int m_iAttackPattern = 0;
	float m_fAttTime = 0.f;
	float m_fBulletTime = 0.f;
	float m_fFadeTime = 0.f;
	float m_fEffectTime = 0.2f;
	float m_fMaxDist = 800.f;
	float m_fCurDist = 0.f;
	float m_fAngle = 0.f;
	bool m_bFocused = false;
	bool m_bIsFade = false;
	bool m_bActive = false;
	bool m_bAttack = false;
	bool m_bInit = false;
	bool m_bCircleEffect = false;
	bool m_bDigEffect = false; // 대각선
	bool m_bIsOver = false;
	bool m_bUIAdded = false;
};

