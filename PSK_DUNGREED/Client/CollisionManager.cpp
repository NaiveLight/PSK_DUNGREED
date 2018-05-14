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

	/*std::cout << iPlayerIndex << std::endl;*/

	if (iPlayerIndex < 0 || iPlayerIndex >= pTileMap->GetVecTile()->size() - iTempTileX)
		return bResult;

	int iTileX = WINCX / TILECX + 1;
	int iTileY = WINCY / TILECY + 1;

	int iCullX = int(ScrollManager->GetScroll().x / TILECX);
	int iCullY = int(ScrollManager->GetScroll().y / TILECY);

	for (int i = 0; i < iTileY; ++i)
	{
		for (int j = 0; j < iTileX; ++j)
		{
			int		iIndex = (i + iCullY) * iTempTileX + (j + iCullX);
			if (iIndex < 0 || iIndex >= iTempTileX * iTempTileY)
				continue;

			if ((*pVecTile)[iIndex]->byOption == COLL_DEFAULT)
				continue;

			float fMoveX = 0.f;
			float fMoveY = 0.f;

			// Ÿ�ϰ� ������ ������ ���
			if (CheckRect(pPlayer, (*pVecTile)[iIndex], &fMoveX, &fMoveY))
			{
				switch ((*pVecTile)[iIndex]->byOption)
				{
				case COLL_RECT: case COLL_DUNGEON:
					pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y - fMoveY, 0.f));
					return true;
				}
			}
		}
	}

	//for (auto& pTile : *pVecTile)
	//{
	//	if (pTile->byOption == COLL_DEFAULT)
	//		continue;

	//	float fMoveX = 0.f;
	//	float fMoveY = 0.f;

	//	// Ÿ�ϰ� ������ ������ ���
	//	if (CheckRect(pPlayer, pTile, &fMoveX, &fMoveY))
	//	{
	//		switch (pTile->byOption)
	//		{
	//		case COLL_RECT: case COLL_DUNGEON:
	//			pPlayer->SetPos(&D3DXVECTOR3(pPlayer->GetInfo()->vPos.x, pPlayer->GetInfo()->vPos.y - fMoveY, 0.f));
	//			return true;
	//		}
	//	}
	//}
	return bResult;
}

bool CCollisionManager::CheckSphere(CObj * pDst, CObj * pSrc)
{
	return false;
}

bool CCollisionManager::CheckRect(CPlayer * pPlayer, TILE * pTile, float * pMoveX, float * pMoveY)
{
	// �� �簢���� ���� ������ ��
	float fRadSumX = pPlayer->GetInfo()->fCX * 0.5f + 32.f;

	// �� �簢���� x�� ����
	// abs�Լ�: ���� ���� ���ϴ� �Լ�.
	float fDistX = abs(pPlayer->GetInfo()->vPos.x -pTile->vPos.x);

	// �� �簢���� ���� ������ ��
	float fRadSumY = pPlayer->GetInfo()->fCY * 0.5f + 32.f;

	// �� �簢���� Y�� ����
	float fDistY = abs(pPlayer->GetInfo()->vPos.y + 32.f - pTile->vPos.y);

	if (fRadSumX >= fDistX && fRadSumY >= fDistY)
	{
		// �İ�� �� ���� ���̸� ����.
		*pMoveX = fRadSumX - fDistX;
		*pMoveY = fRadSumY - fDistY;
		return true;
	}

	return false;
}
