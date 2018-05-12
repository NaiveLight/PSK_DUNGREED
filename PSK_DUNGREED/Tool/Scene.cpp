#include "stdafx.h"
#include "Scene.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "ObjView.h"
#include "Device.h"
#include "TextureManager.h"

CToolScene::CToolScene()
{
}

CToolScene::~CToolScene()
{
	Release();
}

HRESULT CToolScene::Initialize()
{
	m_pMainView = ((CMainFrame*)AfxGetMainWnd())->m_pMainView;
	m_pSprite = Device->GetSprite();
	m_pFont = Device->GetFont();

	CreateTileMap(50, 20);

	return S_OK;
}

void CToolScene::Update()
{
}

void CToolScene::Render()
{
	TileRender();
	if (m_bMapObjRender)
		MapObjRender();
	if (m_bCollRender)
		ColliderRender();
}

void CToolScene::Release()
{
	TileRelease();
	MapObjRelease();
}

void CToolScene::TileRelease()
{
	std::for_each(m_vecTile.begin(), m_vecTile.end(), DeleteObj());
	m_vecTile.clear();
	m_vecTile.shrink_to_fit();
}

void CToolScene::MapObjRelease()
{
	std::for_each(m_vecMapObj.begin(), m_vecMapObj.end(), DeleteObj());
	m_vecMapObj.clear();
	m_vecMapObj.shrink_to_fit();
}

void CToolScene::TileRender()
{
	D3DXMATRIX		matTrans;
	TCHAR			szBuf[128] = L"";

	RECT rc = {};
	m_pMainView->GetWindowRect(&rc);

	int iTileX = (rc.right - rc.left) / TILECX + 1;
	int iTileY = (rc.bottom - rc.top) / TILECY + 1;

	int iCullX = m_pMainView->GetScrollPos(0) / TILECX;
	int iCullY = m_pMainView->GetScrollPos(1) / TILECY;

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
				, m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0)
				, m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1)
				, 0.f);
			m_pSprite->SetTransform(&matTrans);
			m_pSprite->Draw(pTexInfo->pTexture
				, nullptr
				, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
				, nullptr
				, D3DCOLOR_ARGB(255, 255, 255, 255));

			wsprintf(szBuf, L"%d", iIndex);
			CDevice::GetInstance()->GetFont()->DrawTextW(m_pSprite
				, szBuf, lstrlen(szBuf), nullptr, 0
				, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CToolScene::ColliderRender()
{
	D3DXMATRIX		matTrans;

	RECT rc = {};
	m_pMainView->GetWindowRect(&rc);

	int iTileX = (rc.right - rc.left) / TILECX + 1;
	int iTileY = (rc.bottom - rc.top) / TILECY + 1;

	int iCullX = m_pMainView->GetScrollPos(0) / TILECX;
	int iCullY = m_pMainView->GetScrollPos(1) / TILECY;

	for (int i = 0; i < iTileY; ++i)
	{
		for (int j = 0; j < iTileX; ++j)
		{
			int		iIndex = (i + iCullY) * m_iTileX + (j + iCullX);
			if (iIndex < 0 || iIndex >= m_iTileX * m_iTileY)
				continue;

			const TEXINFO*		pColInfo = TextureManager->GetTexture(L"TILE", L"Collider", m_vecTile[iIndex]->byOption);
			if (pColInfo == nullptr)
				return;

			D3DXMatrixTranslation(&matTrans
				, m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0)
				, m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1)
				, 0.f);
			m_pSprite->SetTransform(&matTrans);
			m_pSprite->Draw(pColInfo->pTexture
				, nullptr
				, &D3DXVECTOR3(pColInfo->tImgInfo.Width * 0.5f, pColInfo->tImgInfo.Height * 0.5f, 0.f)
				, nullptr
				, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}
}

void CToolScene::MapObjRender()
{
	D3DXMATRIX		matTrans;

	for (size_t i = 0; i < m_vecMapObj.size(); ++i)
	{
		const TEXINFO*		pTexInfo = TextureManager->GetTexture(L"OBJECT", m_vecMapObj[i]->szStateKey, m_vecMapObj[i]->iCount);
		if (pTexInfo == nullptr)
			return;

		float fDiffX = pTexInfo->tImgInfo.Width * 0.5f - TILECX * 0.5f;
		float fDiffY = pTexInfo->tImgInfo.Height * 0.5f - TILECY * 0.5f;

		D3DXMatrixTranslation(&matTrans
			, m_vecMapObj[i]->vPos.x + fDiffX - m_pMainView->GetScrollPos(0)
			, m_vecMapObj[i]->vPos.y - fDiffY - m_pMainView->GetScrollPos(1)
			, 0.f);
		m_pSprite->SetTransform(&matTrans);
		m_pSprite->Draw(pTexInfo->pTexture
			, nullptr
			, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CToolScene::MiniViewRender()
{
	D3DXMATRIX		matScale, matTrans, matWorld;

	for (int i = 0; i < m_iTileY; ++i)
	{
		for (int j = 0; j < m_iTileX; ++j)
		{
			int		iIndex = i * m_iTileX + j;

			const TEXINFO*		pTexInfo = TextureManager->GetTexture(L"TILE", m_vecTile[iIndex]->szStateKey, m_vecTile[iIndex]->byDrawID);
			if (pTexInfo == nullptr)
				return;

			D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.f);
			D3DXMatrixTranslation(&matTrans
				, (m_vecTile[iIndex]->vPos.x - m_pMainView->GetScrollPos(0)) * 0.3f
				, (m_vecTile[iIndex]->vPos.y - m_pMainView->GetScrollPos(1)) * 0.3f
				, 0.f);

			matWorld = matScale * matTrans;

			m_pSprite->SetTransform(&matWorld);
			m_pSprite->Draw(pTexInfo->pTexture
				, nullptr
				, &D3DXVECTOR3(TILECX * 0.5f, TILECY * 0.5f, 0.f)
				, nullptr
				, D3DCOLOR_ARGB(255, 255, 255, 255));
		}
	}

	for (size_t i = 0; i < m_vecMapObj.size(); ++i)
	{
		const TEXINFO*		pTexInfo = TextureManager->GetTexture(L"OBJECT", m_vecMapObj[i]->szStateKey, m_vecMapObj[i]->iCount);
		if (pTexInfo == nullptr)
			return;

		float fDiffX = pTexInfo->tImgInfo.Width * 0.5f - TILECX * 0.5f;
		float fDiffY = pTexInfo->tImgInfo.Height * 0.5f - TILECY * 0.5f;

		D3DXMatrixScaling(&matScale, 0.3f, 0.3f, 0.f);
		D3DXMatrixTranslation(&matTrans
			, (m_vecMapObj[i]->vPos.x + fDiffX - m_pMainView->GetScrollPos(0)) * 0.3f
			, (m_vecMapObj[i]->vPos.y - fDiffY - m_pMainView->GetScrollPos(1)) * 0.3f
			, 0.f);

		matWorld = matScale * matTrans;

		m_pSprite->SetTransform(&matWorld);
		m_pSprite->Draw(pTexInfo->pTexture
			, nullptr
			, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CToolScene::ObjViewRender()
{
	RECT rc = {};

	((CMainFrame*)AfxGetMainWnd())->m_pObjView->GetWindowRect(&rc);

	float fX = WINCX;
	float fY = WINCY;

	float fScale = 2.0f;

	if (m_bisTile)
	{
		if (m_pCurTile == nullptr)
			return;

		D3DXMATRIX matWorld, matScale, matTrans;

		const TEXINFO*		pTexInfo = TextureManager->GetTexture(L"TILE", m_pCurTile->szStateKey, m_pCurTile->byDrawID);
		if (pTexInfo == nullptr)
			return;

		if (pTexInfo->tImgInfo.Width > 300.f)
			fScale = 2.0f;

		D3DXMatrixScaling(&matScale, fScale, fScale, 0.f);
		D3DXMatrixTranslation(&matTrans	, (fX * 0.5f), (fX * 0.5f), 0.f);

		matWorld = matScale * matTrans;

		m_pSprite->SetTransform(&matWorld);
		m_pSprite->Draw(pTexInfo->pTexture
			, nullptr
			, &D3DXVECTOR3(TILECX * 0.5f, TILECY * 0.5f, 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	else
	{
		if (m_pCurMapObj == nullptr)
			return;

		D3DXMATRIX matWorld, matScale, matTrans;

		const TEXINFO*		pTexInfo = TextureManager->GetTexture(L"OBJECT", m_pCurMapObj->szStateKey, m_pCurMapObj->iCount);
		if (pTexInfo == nullptr)
			return;

		if (pTexInfo->tImgInfo.Width > 300.f)
			fScale = 0.5f;

		D3DXMatrixScaling(&matScale, fScale, fScale, 0.f);
		D3DXMatrixTranslation(&matTrans, (fX * 0.5f), (fY * 0.5f), 0.f);

		matWorld = matScale * matTrans;

		m_pSprite->SetTransform(&matWorld);
		m_pSprite->Draw(pTexInfo->pTexture
			, nullptr
			, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

const int CToolScene::Picking(const D3DXVECTOR3& vMouse)
{
	int x = int(vMouse.x / TILECX);
	int y = int(vMouse.y / TILECY);
	int iPicked = x + (m_iTileX * y);

	if (iPicked < 0 || iPicked >= m_iTileX * m_iTileY)
		iPicked = -1;

	return iPicked;
}

void CToolScene::TileChange(const D3DXVECTOR3& vPos, const std::wstring& wstrStateKey /*= L"Default"*/, const int& iOption /*= 0*/, const int& iDrawID /*= 0*/)
{
	int	iIndex = Picking(vPos);
	if (iIndex == -1)
		return;

	m_vecTile[iIndex]->byDrawID = iDrawID;
	m_vecTile[iIndex]->byOption = iOption;
	lstrcpy(m_vecTile[iIndex]->szStateKey, wstrStateKey.c_str());
}

void CToolScene::InsertMapObj(const D3DXVECTOR3& vPos, const std::wstring& wstrStateKey, const int& iCount)
{
	int	iIndex = Picking(vPos);
	if (iIndex == -1)
		return;

	D3DXVECTOR3 vTempPos = m_vecTile[iIndex]->vPos;

	MAPOBJ* pMapObj = new MAPOBJ;

	pMapObj->vPos = vTempPos;
	lstrcpy(pMapObj->szStateKey, wstrStateKey.c_str());
	pMapObj->iCount = iCount;

	m_vecMapObj.push_back(pMapObj);
}

void CToolScene::CreateTileMap(int iTileX, int iTileY)
{
	TileRelease();

	m_iTileX = iTileX;
	m_iTileY = iTileY;

	m_pMainView->SetScrollSizes(MM_TEXT, CSize((m_iTileX + 1) * TILECX, (m_iTileY + 1)* TILECY));

	for (int i = 0; i < m_iTileY; ++i)
	{
		for (int j = 0; j < m_iTileX; ++j)
		{
			TILE*		pTile = new TILE;

			float		fX = j * TILECX + TILECX * 0.5f;
			float		fY = i * TILECY + TILECY * 0.5f;

			pTile->vPos = D3DXVECTOR3(fX, fY, 0.f);
			pTile->byOption = 0;
			pTile->byDrawID = 0;
			lstrcpy(pTile->szStateKey, L"Default");

			m_vecTile.push_back(pTile);
		}
	}
}

