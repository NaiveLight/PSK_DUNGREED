#pragma once

#include "Include.h"

class CObj;
class CPlayer;
class CMonster;
class CWeapon;
class CHitBox;
class CTileMap;
class CCollisionManager :
	public CSingleton<CCollisionManager>
{
public:
	CCollisionManager();
	virtual ~CCollisionManager();

public:
	static bool PlayerToTile(CPlayer* pPlayer, CTileMap* pTIleMap);
	static bool MonsterToTile(CMonster* pMonster, CTileMap* pTileMap);
	static void HitBoxToPlayer(CHitBox* pHitBox, CObj * pPlayer);
	static void HitBoxToMonster(CHitBox* pHitBox, std::list<CObj*>* pMonsterList);
	static void BulletToTile();
	static void BulletToActor();
	static void ObjectToPlayer();

private:
	static bool CheckSphere(CObj* pDst, CObj* pSrc);
	static bool CheckRect(CObj* pDst, CObj* pSrc);
	static bool CheckRect(CPlayer * pPlayer, TILE * pTile, float * pMoveX, float * pMoveY);
	static bool CheckRect(CMonster * pMonster, TILE * pTile, float * pMoveX, float * pMoveY);
};

