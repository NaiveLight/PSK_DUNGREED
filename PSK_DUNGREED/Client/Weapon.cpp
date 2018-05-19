#include "stdafx.h"
#include "Weapon.h"

#include "ObjectManager.h"
#include "AbstractObjFactory.h"

CWeapon::CWeapon()
{
}

CWeapon::~CWeapon()
{
}

void CWeapon::CreateHitBox()
{
	ObjectManager->AddObject(
		OBJ_PATTACK,
		CAbstractFactory<CHitBox>::CreateHitBox()
		)
}
