#pragma once
#include "Obj.h"
#include "Monster.h"
class CBelial_Hand :
	public CMonster
{
public:
	CBelial_Hand();
	virtual ~CBelial_Hand();

public:
	const bool& GetIsAttack() { return m_bAttack; }

	// CMonster을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	void Attack();

private:
	void UpdateMatrix();

private:
	void FrameChange();
	void FrameMove();

private:
	D3DXVECTOR3 m_vPlayerPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	bool m_bAttack = false;
	bool m_bHitCreated = false;
	bool m_bFixed = false;
};

