#pragma once
#include "Monster.h"
class CMonster_Skell :
	public CMonster
{
public:
	CMonster_Skell();
	virtual ~CMonster_Skell();

	// CMonster��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

