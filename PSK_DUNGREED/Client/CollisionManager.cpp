#include "stdafx.h"
#include "CollisionManager.h"

#include "Obj.h"
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"
#include "HitBox.h"
#include "TileMap.h"
#include "Bullet.h"
#include "ScrollManager.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "SceneManager.h"
#include "SoundManager.h"

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
}

bool CCollisionManager::PlayerToTile(CPlayer * pPlayer, CTileMap* pTileMap)
{
	bool bResult = false;

	D3DXVECTOR3 vecPlayerPos = pPlayer->GetInfo()->vPos;
	int iTempTileX = pTileMap->GetTileX();
	int iTempTileY = pTileMap->GetTileY();

	std::vector<TILE*>* pVecTile = pTileMap->GetVecTile();

	int iPlayerIndex = int(vecPlayerPos.x) / TILECX + int(vecPlayerPos.y) / TILECY * iTempTileX;

	if (iPlayerIndex < 0 || iPlayerIndex >= (int)pTileMap->GetVecTile()->size() - iTempTileX)
		return bResult;

	int iTileX = WINCX / TILECX + 1;
	int iTileY = WINCY / TILECY + 1;

	int iCullX = int(ScrollManager->GetScroll().x / TILECX);
	int iCullY = int(ScrollManager->GetScroll().y / TILECY);

	int checkTileArray[9] =
	{
		iPlayerIndex - iTempTileX - 1
		, iPlayerIndex - iTempTileX
		, iPlayerIndex - iTempTileX + 1
		, iPlayerIndex - 1
		, iPlayerIndex
		, iPlayerIndex + 1
		, iPlayerIndex + iTempTileX - 1
		, iPlayerIndex + iTempTileX
		, iPlayerIndex + iTempTileX + 1
	};

	float fMoveX = 0.f;
	float fMoveY = 0.f;
	float x1, x2, y1, y2, fGradient;
	x1 = x2 = y1 = y2 = fGradient = 0.f;

	for (int i = 0; i < 8; ++i)
	{
		if (checkTileArray[i] < 0 || checkTileArray[i] >= iTempTileX * iTempTileY)
			continue;

		TILE* pTile = pTileMap->GetTile(checkTileArray[i]);

		if (pTile->byOption == COLL_DEFAULT)
		{
			continue;
		}

		// Ÿ�ϰ� ������ ������ ���
		if (CheckRect(pPlayer, pTile, &fMoveX, &fMoveY))
		{
			switch (pTile->byOption)
			{
				//��Ʈ �浹
			case COLL_RECT:
				// �� �Ʒ� �Ǻ�
				if (fMoveX > fMoveY)
				{
					// Ÿ�� �ϴ� �浹
					if (pPlayer->GetInfo()->vPos.y + 32.f > pTile->vPos.y)
					{
						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y + fMoveY, 0.f));
						pPlayer->SetVelocityY(0.f);
					}
					// Ÿ�� ��� �浹
					else
					{
						if (pPlayer->GetVelocityY() < 0.f)
							continue;

						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y - fMoveY, 0.f));
						pPlayer->SetVelocityY(0.f);
						pPlayer->SetJump(false);
						return true;
					}
				}
				else
				{
					//���� �浹
					if (pPlayer->GetInfo()->vPos.x < pTile->vPos.x)
					{
						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x - fMoveX - 6.f, pPlayer->GetInfo()->vPos.y, 0.f));
					}
					else
					{
						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x + fMoveX + 6.f , pPlayer->GetInfo()->vPos.y, 0.f));
					}
				}

				break;
			case COLL_DUNGEON:
				// �� �Ʒ� �Ǻ�
				if (fMoveX > fMoveY)
				{
					// Ÿ�� �ϴ� �浹
					if (pPlayer->GetInfo()->vPos.y + 32.f > pTile->vPos.y)
					{
						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y + fMoveY, 0.f));
						pPlayer->SetVelocityY(0.f);
					}
					// Ÿ�� ��� �浹
					else
					{
						if (pPlayer->GetVelocityY() < 0.f)
							continue;

						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y - fMoveY, 0.f));
						pPlayer->SetVelocityY(0.f);
						pPlayer->SetJump(false);
						pPlayer->SetInpuActive(false);

						if (ObjectManager->GetObjectList(OBJ_MAPOBJ)->size() == 1)
						{
							ScrollManager->ShakingStart(5.f, 0.1f);
							ObjectManager->AddObject(OBJ_MAPOBJ, CAbstractFactory<CObj_Dungeon>::CreateObj(&pPlayer->GetInfo()->vPos));
							SoundManager->PlaySound(L"DungeonOut.wav", CSoundManager::MONSTER);
							SoundManager->StopSound(CSoundManager::BGM);
						}
						return true;
					}
				}
				else
				{
					//���� �浹
					if (pPlayer->GetInfo()->vPos.x < pTile->vPos.x)
					{
						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x - fMoveX - 6.f, pPlayer->GetInfo()->vPos.y, 0.f));
					}
					else
					{
						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x + fMoveX + 6.f, pPlayer->GetInfo()->vPos.y, 0.f));
					}
				}
				break;
			case COLL_ROOM:
				if (fMoveX > fMoveY)
				{
					// Ÿ�� �ϴ� �浹
					if (pPlayer->GetInfo()->vPos.y + 32.f > pTile->vPos.y)
					{
						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y + fMoveY, 0.f));
						pPlayer->SetVelocityY(0.f);
					}
					// Ÿ�� ��� �浹
					else
					{
						if (pPlayer->GetVelocityY() < 0.f)
							continue;

						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y - fMoveY, 0.f));
						pPlayer->SetVelocityY(0.f);
						pPlayer->SetJump(false);
						pPlayer->SetInpuActive(false);
					}
				}
				else
				{
					//���� �浹
					if (pPlayer->GetInfo()->vPos.x < pTile->vPos.x)
					{
						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x - fMoveX - 6.f, pPlayer->GetInfo()->vPos.y, 0.f));
					}
					else
					{
						pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x + fMoveX + 6.f, pPlayer->GetInfo()->vPos.y, 0.f));
					}
				}

				SceneManager->ChangeScene(SceneManager->GetCurSceneID() == 5 ?  3 : SceneManager->GetCurSceneID() + 1);
				return true;

				break;
				//���� ���� �浹
			case COLL_LINE:
				// ���� �� �϶�
				// 1. �������� ���̸� �浹 üũ O
				// 2. �ö󰡴� ���̸� �浹 üũ X

				// ���� ���� �ƴ� ��
				// 1. ���κ��� ���� �ְ� �������� ��Ȳ�� �� �浹 üũ O
				// 2. ���κ��� �ؿ� ���� �� �浹 üũ X
				if (pPlayer->GetIsJump() && pPlayer->GetVelocityY() > 0.f)
				{
					if (pPlayer->GetIsDown() || pPlayer->GetIsDash())
						continue;

					if (pTile->vPos.y - 28.f < pPlayer->GetInfo()->vPos.y + 60.f)
						continue;

					pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y - fMoveY, 0.f));
					pPlayer->SetVelocityY(0.f);
					pPlayer->SetJump(false);
					return true;
				}
				else if (pPlayer->GetIsJump() && pPlayer->GetVelocityY() < 0.f)
					continue;
				else
				{
					if (pTile->vPos.y - 28.f < pPlayer->GetInfo()->vPos.y + 60.f)
						continue;

					pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y - fMoveY, 0.f));
					//pPlayer->SetVelocityY(0.f);
					pPlayer->SetJump(false);
					return true;
				}
				break;

				// ���� �밢�� �浹
			case COLL_UPDIG:
				x1 = pTile->vPos.x - 32.f;
				x2 = pTile->vPos.x + 32.f;

				if (x1 <= pPlayer->GetInfo()->vPos.x && pPlayer->GetInfo()->vPos.x <= x2)
				{
					// X ��ġ�� ���� �ȿ� ������
					y1 = pTile->vPos.y + 32.f;
					y2 = pTile->vPos.y - 32.f;

					fGradient = (y2 - y1) / (x2 - x1);

					// ���� ���������� �÷��̾��� x��ġ���� y���� ������ 
					fMoveY = fGradient * (pPlayer->GetInfo()->vPos.x - x1) + y1;

					// fMoveY �� �÷��̾� �ؽ�ó �߾� �������� ���´�. ���� ��Ʈ�ڽ� ��ġ�� ���� ������ش�.

					// ���� ���� �ƴ� ��
					// fMoveY ������ ��Ʈ�ڽ��� �߾� y ���� ������ ���󰡸� �ȵ�
					if (!pPlayer->GetIsJump())
					{
						if (fMoveY < pPlayer->GetInfo()->vPos.y + 32.f)
							continue;
						else
						{
							pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, fMoveY - 64.f, 0.f));
							return true;
						}
					}
					else
					{
						// ���� ���� ����
						// �������� ���̰� MoveY�� ��ĥ �� �浹 o
						if (pPlayer->GetVelocityY() > 0.f)
						{
							if (pPlayer->GetIsDown() || pPlayer->GetIsDash())
								continue;

							if (fMoveY >= pPlayer->GetInfo()->vPos.y + 32.f)
							{
								pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, fMoveY - 64.f, 0.f));
								return true;
							}
						}
					}
				}
				break;

				//���� �밢�� �浹
			case COLL_DOWNDIG:
				x1 = pTile->vPos.x - 32.f;
				x2 = pTile->vPos.x + 32.f;

				if (x1 <= pPlayer->GetInfo()->vPos.x && pPlayer->GetInfo()->vPos.x <= x2)
				{
					y1 = pTile->vPos.y - 32.f;
					y2 = pTile->vPos.y + 32.f;

					fGradient = (y2 - y1) / (x2 - x1);

					fMoveY = fGradient * (pPlayer->GetInfo()->vPos.x - x1) + y1;

					if (!pPlayer->GetIsJump())
					{
						if (fMoveY < pPlayer->GetInfo()->vPos.y + 32.f)
							continue;
						else
						{
							pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, fMoveY - 64.f, 0.f));
							return true;
						}
					}
					else
					{
						// ���� ���� ����
						// �������� ���̰� MoveY�� ��ĥ �� �浹 o
						if (pPlayer->GetVelocityY() > 0.f)
						{
							if (pPlayer->GetIsDown() || pPlayer->GetIsDash())
								continue;

							if (fMoveY >= pPlayer->GetInfo()->vPos.y + 34.f)
							{
								pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, fMoveY - 64.f, 0.f));
								return true;
							}
						}
					}
				}
				break;
			}
		}
	}

	pPlayer->SetJump(true);
	return bResult;
}

bool CCollisionManager::MonsterToTile(CMonster * pMonster, CTileMap * pTileMap)
{
	bool bResult = false;

	float fX = pMonster->GetHitBox()->fX;
	float fY = pMonster->GetHitBox()->fY;
	
	int iTempTileX = pTileMap->GetTileX();
	int iTempTileY = pTileMap->GetTileY();

	std::vector<TILE*>* pVecTile = pTileMap->GetVecTile();

	int iIndex = int(fX) / TILECX + int(fY) / TILECY * iTempTileX;

	if (iIndex < 0 || iIndex >= (int)pTileMap->GetVecTile()->size() - iTempTileX)
		return bResult;

	int iTileX = WINCX / TILECX + 1;
	int iTileY = WINCY / TILECY + 1;

	int iCullX = int(ScrollManager->GetScroll().x / TILECX);
	int iCullY = int(ScrollManager->GetScroll().y / TILECY);

	int checkTileArray[9] =
	{
		iIndex - iTempTileX - 1
		, iIndex - iTempTileX
		, iIndex - iTempTileX + 1
		, iIndex - 1
		, iIndex
		, iIndex + 1
		, iIndex + iTempTileX - 1
		, iIndex + iTempTileX
		, iIndex + iTempTileX + 1
	};

	float fMoveX = 0.f;
	float fMoveY = 0.f;
	float x1, x2, y1, y2, fGradient;
	x1 = x2 = y1 = y2 = fGradient = 0.f;

	for (int i = 0; i < 8; ++i)
	{
		if (checkTileArray[i] < 0 || checkTileArray[i] >= iTempTileX * iTempTileY)
			continue;

		TILE* pTile = pTileMap->GetTile(checkTileArray[i]);

		if (pTile->byOption == COLL_DEFAULT)
		{
			continue;
		}

		// Ÿ�ϰ� ������ ������ ���
		if (CheckRect(pMonster, pTile, &fMoveX, &fMoveY))
		{
			switch (pTile->byOption)
			{
				//��Ʈ �浹
			case COLL_RECT: case COLL_DUNGEON:case COLL_ROOM:
				pMonster->SetPos(&D3DXVECTOR3(pMonster->GetInfo()->vPos.x, pMonster->GetInfo()->vPos.y - fMoveY, 0.f));
				return true;
				break;
			case COLL_UPDIG:
				x1 = pTile->vPos.x - 32.f;
				x2 = pTile->vPos.x + 32.f;

				if (x1 <= pMonster->GetInfo()->vPos.x && pMonster->GetInfo()->vPos.x <= x2)
				{
					// X ��ġ�� ���� �ȿ� ������
					y1 = pTile->vPos.y + 32.f;
					y2 = pTile->vPos.y - 32.f;

					fGradient = (y2 - y1) / (x2 - x1);

					// ���� ���������� �÷��̾��� x��ġ���� y���� ������ 
					fMoveY = fGradient * (pMonster->GetInfo()->vPos.x - x1) + y1;

					pMonster->SetPos(&D3DXVECTOR3(pMonster->GetInfo()->vPos.x, fMoveY - 64.f, 0.f));
					return true;
				}
				break;

				//���� �밢�� �浹
			case COLL_DOWNDIG:
				x1 = pTile->vPos.x - 32.f;
				x2 = pTile->vPos.x + 32.f;

				if (x1 <= pMonster->GetInfo()->vPos.x && pMonster->GetInfo()->vPos.x <= x2)
				{
					// X ��ġ�� ���� �ȿ� ������
					y1 = pTile->vPos.y - 32.f;
					y2 = pTile->vPos.y + 32.f;

					fGradient = (y2 - y1) / (x2 - x1);

					fMoveY = fGradient * (pMonster->GetInfo()->vPos.x - x1) + y1;

					pMonster->SetPos(&D3DXVECTOR3(pMonster->GetInfo()->vPos.x, fMoveY - 64.f, 0.f));
					return true;
				}
				break;
			}
		}
	}
	return bResult;
}

bool CCollisionManager::BulletToTile(CBullet* pBullet, CTileMap * pTileMap)
{
	bool bResult = false;

	float fX = pBullet->GetHitBox()->fX;
	float fY = pBullet->GetHitBox()->fY;

	int iTempTileX = pTileMap->GetTileX();
	int iTempTileY = pTileMap->GetTileY();

	std::vector<TILE*>* pVecTile = pTileMap->GetVecTile();

	int iIndex = int(fX) / TILECX + int(fY) / TILECY * iTempTileX;

	if (iIndex < 0 || iIndex >= (int)pTileMap->GetVecTile()->size() - iTempTileX)
		return bResult;

	int iTileX = WINCX / TILECX + 1;
	int iTileY = WINCY / TILECY + 1;

	int iCullX = int(ScrollManager->GetScroll().x / TILECX);
	int iCullY = int(ScrollManager->GetScroll().y / TILECY);

	int checkTileArray[9] =
	{
		iIndex - iTempTileX - 1
		, iIndex - iTempTileX
		, iIndex - iTempTileX + 1
		, iIndex - 1
		, iIndex
		, iIndex + 1
		, iIndex + iTempTileX - 1
		, iIndex + iTempTileX
		, iIndex + iTempTileX + 1
	};

	float fMoveX = 0.f;
	float fMoveY = 0.f;
	float x1, x2, y1, y2, fGradient;
	x1 = x2 = y1 = y2 = fGradient = 0.f;

	for (int i = 0; i < 8; ++i)
	{
		if (checkTileArray[i] < 0 || checkTileArray[i] >= iTempTileX * iTempTileY)
			continue;

		TILE* pTile = pTileMap->GetTile(checkTileArray[i]);

		if (pTile->byOption != COLL_RECT)
		{
			continue;
		}

		// Ÿ�ϰ� ������ ������ ���
		if (CheckRect(pBullet, pTile, &fMoveX, &fMoveY))
		{
			return true;
		}
	}
	return bResult;
}

void CCollisionManager::HitBoxToPlayer(CHitBox * pHitBox, CObj * pPlayer)
{
	if (CheckSphere(pHitBox, pPlayer))
		dynamic_cast<CPlayer*>(pPlayer)->ApplyDamage(pHitBox->GetAtt());
}

void CCollisionManager::HitBoxToMonster(CHitBox * pHitBox, std::list<CObj*>* pMonsterList)
{
	if (pMonsterList->empty())
		return;

	if (pHitBox->GetRect())
	{
		for (auto& pMonster : *pMonsterList)
		{
			if (CheckRect(pHitBox, pMonster))
			{
				dynamic_cast<CMonster*>(pMonster)->ApplyDamage(pHitBox->GetAtt());
				CObj* pObj = CAbstractFactory<CEffect_Extinction>::CreateEffect(L"Slash",
					false, &D3DXVECTOR3(pMonster->GetInfo()->vPos.x, pMonster->GetInfo()->vPos.y + 32.f, 0.f), &FRAME{ 0.f, 12.f, 4.f }, &D3DXVECTOR3(0.f, -1.f, 0.f));
				ObjectManager->AddObject(OBJ_EFFECT, pObj);
				SoundManager->PlaySound(L"Hit_Monster.wav", CSoundManager::COLLISION);
			}
		}
	}
	else
	{
		for (auto& pMonster : *pMonsterList)
		{
			if (CheckSphere(pHitBox, pMonster))
			{
				dynamic_cast<CMonster*>(pMonster)->ApplyDamage(pHitBox->GetAtt());
				CObj* pObj = CAbstractFactory<CEffect_Extinction>::CreateEffect(L"Slash",
					false, &D3DXVECTOR3(pMonster->GetInfo()->vPos.x, pMonster->GetInfo()->vPos.y + 32.f, 0.f), &FRAME{ 0.f, 12.f, 4.f }, &D3DXVECTOR3(0.f, -1.f, 0.f));
				ObjectManager->AddObject(OBJ_EFFECT, pObj);
				SoundManager->PlaySound(L"Hit_Monster.wav", CSoundManager::COLLISION);
			}
		}
	}
}

void CCollisionManager::BulletToPlayer(std::list<CObj*>* pBulletList, CPlayer * pPlayer)
{
	for (auto& pBullet : *pBulletList)
	{
		if (CheckSphere(pBullet, pPlayer))
		{
			pPlayer->ApplyDamage(dynamic_cast<CBullet*>(pBullet)->GetAtt());
			dynamic_cast<CBullet*>(pBullet)->SetCollision(true);
		}
	}
}

bool CCollisionManager::CheckSphere(CObj * pDst, CObj * pSrc)
{
	float fRadSum = pDst->GetHitBox()->fCX * 0.5f + pSrc->GetHitBox()->fCX * 0.5f;

	float fW = pDst->GetHitBox()->fX- pSrc->GetHitBox()->fX;
	float fH = pDst->GetHitBox()->fY- pSrc->GetHitBox()->fY;

	float fDist = sqrtf(fW * fW + fH * fH);

	if (fRadSum >= fDist)
		return true;

	return false;
}

bool CCollisionManager::CheckRect(CObj * pDst, CObj * pSrc)
{
	float fRadSumX = pDst->GetHitBox()->fCX * 0.5f + pSrc->GetHitBox()->fCX * 0.5f;
	float fDistX = abs(pDst->GetHitBox()->fX- pSrc->GetHitBox()->fX);
	float fRadSumY = pDst->GetHitBox()->fCY * 0.5f + pSrc->GetHitBox()->fCY * 0.5f;
	float fDistY = abs(pDst->GetHitBox()->fY- pSrc->GetHitBox()->fY);

	if (fRadSumX >= fDistX && fRadSumY >= fDistY)
		return true;

	return false;
}

bool CCollisionManager::CheckRect(CPlayer * pPlayer, TILE * pTile, float * pMoveX, float * pMoveY)
{
	float fRadSumX = pPlayer->GetInfo()->fCX * 0.5f + 32.f;
	float fDistX = abs(pPlayer->GetInfo()->vPos.x -pTile->vPos.x);
	float fRadSumY = pPlayer->GetInfo()->fCY * 0.5f + 32.f;
	float fDistY = abs(pPlayer->GetInfo()->vPos.y + 32.f - pTile->vPos.y);

	if (fRadSumX >= fDistX && fRadSumY >= fDistY)
	{
		*pMoveX = fRadSumX - fDistX;
		*pMoveY = fRadSumY - fDistY;
		return true;
	}

	return false;
}

bool CCollisionManager::CheckRect(CObj * pMonster, TILE * pTile, float * pMoveX, float * pMoveY)
{
	float fRadSumX = pMonster->GetHitBox()->fCX * 0.5f + 32.f;
	float fDistX = abs(pMonster->GetHitBox()->fX - pTile->vPos.x);
	float fRadSumY = pMonster->GetHitBox()->fCY * 0.5f + 32.f;
	float fDistY = abs(pMonster->GetHitBox()->fY - pTile->vPos.y);

	if (fRadSumX >= fDistX && fRadSumY >= fDistY)
	{
		*pMoveX = fRadSumX - fDistX;
		*pMoveY = fRadSumY - fDistY;
		return true;
	}

	return false;
}
