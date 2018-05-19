#pragma once

#include "Include.h"

class CBridge;
class CObj abstract
{
public:
	CObj();
	virtual ~CObj();
	
public:
	const std::wstring& GetObjKey();
	const std::wstring& GetStateKey();
	const INFO* GetInfo();
	const FRAME* GetFrame();
	const HITBOX* GetHitBox();
	const bool& GetIsLeft();

public:
	void SetBridge(CBridge* pBridge);
	void SetPos(const D3DXVECTOR3* pPos);
	void SetHitBox(const HITBOX* pHitBox);
	void SetDir(const D3DXVECTOR3* pDir);
	void SetFrame(const FRAME* pFrame);
	void SetObjKey(const std::wstring& wstrObjKey);
	void SetStateKey(const std::wstring& wstrStateKey);
	void SetIsLeft(const bool& bIsLeft);

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update()	PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

public:
	virtual void UpdateMatrix();

protected:
	LPDIRECT3DDEVICE9		m_pDevice = nullptr;
	LPD3DXSPRITE					m_pSprite = nullptr;

protected:
	HITBOX m_tHitBox = {};
	INFO m_tInfo = {};	
	FRAME m_tFrame = {};
	std::wstring m_wstrObjKey = L"";
	std::wstring m_wstrStateKey = L"";
	float m_fTime = 0.f;
	float m_fAlpha = 0.f;
	float m_fGravity = 0.f;
	bool m_bIsLeft = false;

protected:
	CBridge* m_pBridge = nullptr;
};

