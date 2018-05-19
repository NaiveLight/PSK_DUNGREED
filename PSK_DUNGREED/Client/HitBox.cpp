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
	CCollisionManager::HitBoxToMonster(this, ObjectManager->GetObjectList(OBJ_MONSTER));
	return 1;
}

void CHitBox::Render()
{
}

void CHitBox::Release()
{
}
