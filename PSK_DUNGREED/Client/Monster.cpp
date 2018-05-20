#include "stdafx.h"
#include "Monster.h"

CMonster::CMonster()
{
}

CMonster::~CMonster()
{
}

void CMonster::ApplyDamage(const int& iAtt)
{
	m_tData.iCurHp -= iAtt;
	if (m_tData.iCurHp <= 0)
	{
		m_tData.iCurHp = 0;
		m_bIsDead = true;
	}
}
