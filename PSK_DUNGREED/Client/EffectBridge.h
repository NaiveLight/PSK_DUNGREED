#pragma once
#include "Bridge.h"
class CEffectBridge :
	public CBridge
{
public:
	CEffectBridge();
	virtual ~CEffectBridge();

public:
	virtual HRESULT Initialize() PURE;
	virtual int Update(INFO & rInfo) PURE;
	virtual void Render() PURE;
	virtual void Release() PURE;

protected:
	LPDIRECT3DDEVICE9 m_pDevice = nullptr;
	LPD3DXSPRITE			m_pSprite = nullptr;
};

