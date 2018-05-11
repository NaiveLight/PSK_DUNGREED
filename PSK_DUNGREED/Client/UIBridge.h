#pragma once

#include "Bridge.h"

class CUIBridge :
	public CBridge
{
public:
	CUIBridge();
	virtual ~CUIBridge();

public:
	virtual HRESULT Initialize(void)PURE;
	virtual int Update(INFO& rInfo)PURE;
	virtual void Render(void)PURE;
	virtual void Release(void)PURE;

protected:
	LPDIRECT3DDEVICE9		m_pDevice = nullptr;
	LPD3DXSPRITE			m_pSprite = nullptr;

private:
	int m_iAlpha = 255;
};

