#pragma once

#include "Include.h"

class CToolView;
class CScene
{
public:
	CScene();
	~CScene();

public:
	void SetCurTile();
	void SetCurMapObj();
	void SetShowCollider() { m_bCollRender = !m_bCollRender; }
	void SetShowMapObj() { m_bMapObjRender = !m_bMapObjRender; }

public:
	HRESULT Initialize();
	void Update();
	void Render();
	void Release();

public:
	void TileRelease();
	void MapObjRelease();

public:
	void TileRender();
	void ColliderRender();
	void MapObjRender();
	void MiniViewRender();
	void ObjViewRender();

public:
	const int Picking(const D3DXVECTOR3& vMouse);
	void TileChange(const D3DXVECTOR3& vPos, const std::wstring& wstrStateKey = L"Default", const int& iOption = 0, const int& iDrawID = 0);
	void InsertMapObj(const D3DXVECTOR3& vPos, const std::wstring& wstrObjKey, const std::wstring& wstrStateKey, const int& iCount);
	void CreateTileMap(int iTileX, int iTileY);

private:
	std::vector<TILE*> m_vecTile;
	std::vector<MAPOBJ*> m_vecMapObj;

private:
	LPD3DXSPRITE m_pSprite = nullptr;
	LPD3DXFONT m_pFont = nullptr;

private:
	CToolView* m_pMainView = nullptr;

private:
	BYTE m_byOption = 0;
	BYTE m_byDrawID = 0;
	int m_iCount = 0;
	int m_iTileX = 0;
	int m_iTileY = 0;

	TILE* m_pCurTile = nullptr;
	MAPOBJ* m_pCurMapObj = nullptr;
	bool m_bisTile = false;
	bool m_bCollRender = false;
	bool m_bMapObjRender = false;
};

