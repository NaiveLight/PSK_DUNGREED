#pragma once

#include "Include.h"

class CObj;
class CPlayer;
class CTileMap;
class CCollisionManager :
	public CSingleton<CCollisionManager>
{
public:
	CCollisionManager();
	virtual ~CCollisionManager();

public:
	static bool PlayerToTile(CPlayer* pPlayer, CTileMap* pTIleMap);
	static void BulletToTile();
	static void BulletToActor();
	static void AttackToMonster();
	static void ObjectToPlayer();

private:
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
	static bool CheckRect(CPlayer * pPlayer, TILE * pTile, float * pMoveX, float * pMoveY);
};

