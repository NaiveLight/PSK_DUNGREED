#include "stdafx.h"
#include "TileMap.h"

#include "Device.h"
#include "TextureManager.h"
#include "ScrollManager.h"

CTileMap::CTileMap()
{
}

CTileMap::~CTileMap()
{
	Release();
}

HRESULT CTileMap::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"TileMap Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"TileMap Get Sprite Failed");
		return E_FAIL;
	}

	LoadTile();

	return S_OK;
}

int CTileMap::Update()
{
	return 0;
}

void CTileMap::Render()
{
	TileRender();
}

void CTileMap::Release()
{
	std::for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CTileMap::LoadTile()
{
	HANDLE hFile = CreateFile(m_wstrDataPath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwByte = 0;

	ReadFile(hFile, &m_iTileX, sizeof(int), &dwByte, nullptr);
	ReadFile(hFile, &m_iTileY, sizeof(int), &dwByte, nullptr);

	ScrollManager->SetMinScroll(0.f, 0.f);
	ScrollManager->SetMaxScroll(float(m_iTileX * TILECX), float(m_iTileY * TILECY));

	while (true)
	{
		TILE* pTile = new TILE;
		ReadFile(hFile, pTile, sizeof(TILE), &dwByte, nullptr);

		if (dwByte == 0)
		{
			Safe_Delete(pTile);
			break;
		}

		m_vecTile.push_back(pTile);
	}

	CloseHandle(hFile);
}

void CTileMap::TileRender()
{
	D3DXMATRIX		matTrans;

	RECT rc = {};
	GetWindowRect(g_hWnd, &rc);

	int iTileX = (rc.right - rc.left) / TILECX + 1;
	int iTileY = (rc.bottom - rc.top) / TILECY + 1;

	int iCullX = int(ScrollManager->GetScroll().x / TILECX);
	int iCullY = int(ScrollManager->GetScroll().y / TILECY);

	for (int i = 0; i < iTileY; ++i)
	{
		for (int j = 0; j < iTileX; ++j)
		{
			int		iIndex = (i + iCullY) * m_iTileX + (j + iCullX);
			if (iIndex < 0 || iIndex >= m_iTileX * m_iTileY)
				continue;

			const TEXINFO*		pTexInfo = TextureManager->GetTexture(L"TILE", m_vecTile[iIndex]->szStateKey, m_vecTile[iIndex]->byDrawID);
			if (pTexInfo == nullptr)
				return;

			D3DXMatrixTranslation(&matTrans
				, m_vecTile[iIndex]->vPos.x - ScrollManager->GetScroll().x
				, m_vecTile[iIndex]->vPos.y - ScrollManager->GetScroll().y
				, 0.f);
			m_pSprite->SetTransform(&matTrans);
			m_pSprite->Draw(pTexInfo->pTexture
				, nullptr
				, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
				, nullptr
				, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CTileMap::ColliderRender()
{
	D3DXMATRIX		matTrans;

	RECT rc = {};
	GetWindowRect(g_hWnd, &rc);

	int iTileX = (rc.right - rc.left) / TILECX + 1;
	int iTileY = (rc.bottom - rc.top) / TILECY + 1;

	int iCullX = int(ScrollManager->GetScroll().x / TILECX);
	int iCullY = int(ScrollManager->GetScroll().y / TILECY);

	for (int i = 0; i < iTileY; ++i)
	{
		for (int j = 0; j < iTileX; ++j)
		{
			int		iIndex = (i + iCullY) * m_iTileX + (j + iCullX);
			if (iIndex < 0 || iIndex >= m_iTileX * m_iTileY)
				continue;

			const TEXINFO*		pTexInfo = TextureManager->GetTexture(L"TILE", L"Collider", m_vecTile[iIndex]->byOption);
			if (pTexInfo == nullptr)
				return;

			D3DXMatrixTranslation(&matTrans
				, m_vecTile[iIndex]->vPos.x - ScrollManager->GetScroll().x
				, m_vecTile[iIndex]->vPos.y - ScrollManager->GetScroll().y
				, 0.f);
			m_pSprite->SetTransform(&matTrans);
			m_pSprite->Draw(pTexInfo->pTexture
				, nullptr
				, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
				, nullptr
				, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}
