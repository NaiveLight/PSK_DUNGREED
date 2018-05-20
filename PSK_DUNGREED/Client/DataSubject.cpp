#include "stdafx.h"
#include "DataSubject.h"


CDataSubject::CDataSubject()
{
}

CDataSubject::~CDataSubject()
{
	Release();
}

std::list<void*>* CDataSubject::GetDatalist(int iMessage)
{
	auto iter = m_mapData.find(iMessage);
	if (iter == m_mapData.end())
		return nullptr;

	return &iter->second;
}

void CDataSubject::AddData(int iMessage, void * pData)
{
	if (pData != nullptr)
	{
		auto iter = m_mapData.find(iMessage);
		if (iter == m_mapData.end())
		{
			m_mapData[iMessage] = std::list<void*>();
		}
		m_mapData[iMessage].push_back(pData);
	}
}

void CDataSubject::RemoveData(int iMessage, void * pData)
{
	auto mapiter = m_mapData.find(iMessage);
	if (mapiter != m_mapData.end())
	{
		for (auto iterlist = mapiter->second.begin();
			iterlist != mapiter->second.end(); ++iterlist)
		{
			if ((*iterlist) == pData)
			{
				mapiter->second.erase(iterlist);
				return;
			}
		}
	}
}

void CDataSubject::Release(void)
{
	for (auto& mapiter : m_mapData)
		mapiter.second.clear();

	m_mapData.clear();
}
