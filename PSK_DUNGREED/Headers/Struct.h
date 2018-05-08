#pragma once

typedef struct tagTexture
{
	LPDIRECT3DTEXTURE9 pTexture = nullptr;
	D3DXIMAGE_INFO tImgInfo = {};
}TEXINFO;

typedef struct tagTile
{
	D3DXVECTOR3 vPos;
	BYTE byOption;
	BYTE byDrawID;
	TCHAR szStateKey[128] = {};
}TILE;

typedef struct tagMapObject
{
	D3DXVECTOR3 vPos;
	int iCount;
	TCHAR szObjKey[128] = {};
	TCHAR szStateKey[128] = {};
}MAPOBJ;

typedef struct tagData
{
	int		iLevel;
	int		iCurHp;
	int		iMaxHp;
	int		iDashCnt;
	int		iMaxDashCnt;

	int		iAtt;
	int		iDashAtt;
	int		iDefence;
	int		iGold;
	int		iFood;
	int		iCritical;

	int		iAttSpeed;
	int		iMoveSpeed;
}DATA;

typedef struct tagFrame
{
	float		fFrame = 0.f;
	float		fCount = 0.f;
	float		fMax = 0.f;

	tagFrame() {};
	tagFrame(float _fFrame, float _fCount, float _fMax)
		: fFrame(_fFrame), fCount(_fCount), fMax(_fMax) {}
}FRAME;

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vDir;
	D3DXVECTOR3 vLook;
	D3DXMATRIX matWorld;
}INFO;

typedef struct tagUnitData
{
	int iHp = 0;
	int iAtt = 0;
	BYTE byJob = 0;
	BYTE byCheck = 0;
	TCHAR szName[32] = {};
}UNITDATA;

typedef struct tagTexturePath
{
	std::wstring wstrObjKey = L"";
	std::wstring wstrStateKey = L"";
	std::wstring wstrPath = L"";
	int iCount = 0;
}IMGPATH;

typedef struct tagAStarNode
{
	tagAStarNode*	pParent;
	int				iIndex;
	float			fCost;
}NODE;
