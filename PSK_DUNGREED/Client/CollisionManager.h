#pragma once

#include "Include.h"

class CObj;
class CPlayer;
class CWeapon;
class CTileMap;
class CCollisionManager :
	public CSingleton<CCollisionManager>
{
public:
	CCollisionManager();
	virtual ~CCollisionManager();

public:
	static bool PlayerToTile(CPlayer* pPlayer, CTileMap* pTIleMap);
	static void AttackToMonster(CWeapon* pWeapon, std::list<CObj*>* pMonsterList);
	static void BulletToTile();
	static void BulletToActor();
	static void ObjectToPlayer();

private:
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
	static bool CheckRect(CObj* pDst, CObj* pSrc);
	static bool CheckRect(CPlayer * pPlayer, TILE * pTile, float * pMoveX, float * pMoveY);
};

