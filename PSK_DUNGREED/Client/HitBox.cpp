#include "stdafx.h"
#include "HitBox.h"

#include "ObjectManager.h"
#include "CollisionManager.h"

CHitBox::CHitBox()
{
}

CHitBox::~CHitBox()
{
}

HRESULT CHitBox::Initialize()
{
	return S_OK;
}

int CHitBox::Update()
{
	if (m_bPlayer)
	{
		CCollisionManager::HitBoxToMonster(this, ObjectManager->GetObjectList(OBJ_MONSTER));
	}
	else
	{
		CCollisionManager::HitBoxToPlayer(this, ObjectManager->GetObjectList(OBJ_PLAYER)->front());
	}
	return 1;
}

void CHitBox::Render()
{
}

void CHitBox::Release()
{
}
