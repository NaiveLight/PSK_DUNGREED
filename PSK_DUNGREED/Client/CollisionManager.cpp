#include "stdafx.h"
#include "CollisionManager.h"

#include "Obj.h"
#include "Player.h"
#include "TileMap.h"
#include "ScrollManager.h"

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
			case COLL_RECT: case COLL_DUNGEON:
				if (pPlayer->GetVelocityY() < 0.f)
					continue;

				pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y - fMoveY, 0.f));
				pPlayer->SetVelocityY(0.f);
				pPlayer->SetJump(false);
				return true;

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
					if (pPlayer->GetIsDown())
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
					if (pTile->vPos.y - 32.f < pPlayer->GetInfo()->vPos.y + 64.f)
						continue;

					pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y - fMoveY, 0.f));
					pPlayer->SetVelocityY(0.f);
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
							if (pPlayer->GetIsDown())
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
							if (pPlayer->GetIsDown())
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

bool CCollisionManager::CheckSphere(CObj * pDst, CObj * pSrc)
{
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
