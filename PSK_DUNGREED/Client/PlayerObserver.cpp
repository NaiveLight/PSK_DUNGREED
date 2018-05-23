#include "stdafx.h"
#include "PlayerObserver.h"
#include "DataSubject.h"

CPlayerObserver::CPlayerObserver()
{
	D3DXMatrixIdentity(&m_matPlayer);
}

CPlayerObserver::~CPlayerObserver()
{
}

const DATA * CPlayerObserver::GetData(void) const
{
	return &m_tData;
}

const PDATA * CPlayerObserver::GetPlayerData() const
{
	return &m_tPData;
}

const D3DXMATRIX * CPlayerObserver::GetMatrix(void) const
{
	return &m_matPlayer;
}

const DATA * CPlayerObserver::GetBossData() const
{
	return &m_tBossData;
}

void CPlayerObserver::Update(int iMessage, void * pData)
{
	auto* pDatalist = CDataSubject::GetInstance()->GetDatalist(iMessage);
	if (pDatalist == nullptr)
		return;

	std::list<void*>::iterator	iter = find(pDatalist->begin(), pDatalist->end(), pData);
	if (pData == nullptr)
		iter = pDatalist->begin();

	switch (iMessage)
	{
	case PLAYER_DATA:
		m_tData = *((DATA*)(*iter));
		break;

	case PLAYER_PDATA:
		m_tPData = *((PDATA*)(*iter));

	case PLAYER_MATRIX:
		m_matPlayer = *((D3DXMATRIX*)(*iter));
		break;

	case BOSS_DATA:
		m_tBossData = *((DATA*)(*iter));
		break;
	}
}
