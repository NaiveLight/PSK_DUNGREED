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
	TCHAR szStateKey[128] = {};
}MAPOBJ;

typedef struct tagData
{
	int		iCurHp;
	int		iMaxHp;

	int		iGold;

	int		iMinAtt;
	int		iMaxAtt;

	float		fAttSpeed;
	float		fMoveSpeed;
	float		fJumpSpeed;
}DATA;

typedef struct tagPlayerData
{
	int		iLevel;
	int		iCurExp;
	int		iMaxExp;
	int		iDashCnt;
	int		iMaxDashCnt;

	int		iCurFood;
	int		iMaxFood;

	// AP로 증가 시킬 수 있는 스탯
	int		iStr; //분노
	int		iDex; //신속
	int		iDef; //인내
	int		iInt; //신비
	int		iDeg; //탐욕

	
	float	fDashSpeed;
	float fDashTime;
	float	fDashChargeTime; // 대시 충전 시간
}PDATA;

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
	float					fCX;
	float					fCY;
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
