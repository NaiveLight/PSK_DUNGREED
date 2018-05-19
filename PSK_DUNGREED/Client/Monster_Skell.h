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
};

