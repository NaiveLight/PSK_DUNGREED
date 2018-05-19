#pragma once
#include "Monster.h"
class CMonster_Skell :
	public CMonster
{
public:
	CMonster_Skell();
	virtual ~CMonster_Skell();

private:
	void InitAttributes();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void UpdateMatrix();
	void UpdateHitBox();

private:
	void FrameChange();
	void FrameMove();

private:
	float m_fVelocityX = 0.f;
	float m_fVelocityY = 0.f;
	float m_fMinPosX = 0.f;
	float m_fMaxPosX = 0.f;
	bool m_bAttack = false;
	bool m_bHitCreated = false;
	bool m_bGround = false;
};

