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

public:
	void SetBridge(CBridge* pBridge);
	void SetPos(const D3DXVECTOR3* pPos);
	void SetObjKey(const std::wstring& wstrObjKey);
	void SetStateKey(const std::wstring& wstrStateKey);

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update()	PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	LPDIRECT3DDEVICE9		m_pDevice = nullptr;
	LPD3DXSPRITE					m_pSprite = nullptr;

protected:
	INFO m_tInfo = {};	
	FRAME m_tFrame = {};
	std::wstring m_wstrObjKey = L"";
	std::wstring m_wstrStateKey = L"";

protected:
	CBridge* m_pBridge = nullptr;
};

