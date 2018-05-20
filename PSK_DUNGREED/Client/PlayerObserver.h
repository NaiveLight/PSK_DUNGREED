#pragma once
#include "Observer.h"
class CPlayerObserver :
	public CObserver
{
public:
	CPlayerObserver();
	virtual ~CPlayerObserver();

public:
	const DATA* GetData() const;
	const PDATA* GetPlayerData() const;
	const D3DXMATRIX* GetMatrix() const;

public:
	virtual void Update(int iMessage, void* pData);

private:
	DATA			m_tData = {};
	PDATA			m_tPData = {};
	D3DXMATRIX		m_matPlayer;
};

