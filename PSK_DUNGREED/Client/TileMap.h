#pragma once
#include "Obj.h"
class CTileMap :
	public CObj
{
public:
	CTileMap();
	virtual ~CTileMap();

public:
	void SetTileSize(const int& iTileX, const int& iTileY) { m_iTileX = iTileX; m_iTileY = iTileY; }
	void SetDataPath(const std::wstring& wstrDataFileName) { m_wstrDataPath = L"../Data/" + wstrDataFileName; }

public:
	std::vector<TILE*>* GetVecTile() { return &m_vecTile; }
	TILE* GetTile(int idx) { return m_vecTile[idx]; }
	const int& GetTileX() { return m_iTileX; }
	const int& GetTileY() { return m_iTileY; }

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void LoadTile();
	void TileRender();
	void ColliderRender();

private:
	std::vector<TILE*> m_vecTile;

private:
	std::wstring m_wstrDataPath;
	int m_iTileX = 0;
	int m_iTileY = 0;
	bool m_bCollider = false;
};

