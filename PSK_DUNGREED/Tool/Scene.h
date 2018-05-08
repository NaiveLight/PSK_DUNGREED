#pragma once

#include "Include.h"

class CToolView;
class CScene
{
public:
	CScene();
	~CScene();

public:
	std::vector<TILE*>* GetVecTile() { return &m_vecTile; }
	std::vector<MAPOBJ*>* GetVecMapObj() { return &m_vecMapObj; }

public:
	void SetCurTile();
	void SetCurMapObj();
	void SetShowCollider() { m_bCollRender = !m_bCollRender; }
	void SetShowMapObj() { m_bMapObjRender = !m_bMapObjRender; }
	void SetObjViewRenderMode(bool bisTile) { m_bisTile = bisTile; }

public:
	HRESULT Initialize();
	void Update();
	void Render();
	void Release();

public:
	void TileRelease();
	void MapObjRelease();
	void CurTileRelease() { Safe_Delete(m_pCurTile); }
	void CurMapObjRelease() { Safe_Delete(m_pCurMapObj); }

public:
	void TileRender();
	void ColliderRender();
	void MapObjRender();
	void MiniViewRender();
	void ObjViewRender();

public:
	const int Picking(const D3DXVECTOR3& vMouse);
	void TileChange(const D3DXVECTOR3& vPos, const std::wstring& wstrStateKey = L"Default", const int& iOption = 0, const int& iDrawID = 0);
	void InsertMapObj(const D3DXVECTOR3& vPos, const std::wstring& wstrStateKey, const int& iCount);
	void CreateTileMap(int iTileX, int iTileY);
	void DeleteLastestMapObj() { if (m_vecMapObj.empty()) { return; } Safe_Delete(m_vecMapObj[m_vecMapObj.size() - 1]); m_vecMapObj.pop_back(); }

private:
	std::vector<TILE*> m_vecTile;
	std::vector<MAPOBJ*> m_vecMapObj;

private:
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;

private:
	CToolView* m_pMainView = nullptr;

private:
	int m_iTileX = 0;
	int m_iTileY = 0;

	TILE* m_pCurTile = nullptr;
	MAPOBJ* m_pCurMapObj = nullptr;
	bool m_bisTile = false;
	bool m_bCollRender = true;
	bool m_bMapObjRender = true;
};

