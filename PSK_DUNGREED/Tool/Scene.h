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
	void Picking();
	void TileChange();
	void CreateMapObj();

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
	int m_iTileX = 0;
	int m_iTileY = 0;

	TILE* m_pCurTile = nullptr;
	MAPOBJ* m_pCurMapObj = nullptr;
	bool m_bisTile = false;
	bool m_bCollRender = false;
	bool m_bMapObjRender = false;
};

