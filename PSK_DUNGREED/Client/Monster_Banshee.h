#pragma once
#include "Monster.h"
class CMonster_Banshee :
	public CMonster
{
public:
	CMonster_Banshee();
	virtual ~CMonster_Banshee();

	// CMonster을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void InitAttributes();

private:
	void UpdateMatrix();
	void UpdateHitBox();

private:
	void FrameChange();
	void FrameMove();

private:
	float m_fAttackTime = 0.f;
	bool m_bAttack = false;
	bool m_bHitCreated = false;
	bool m_bGround = false;
};

