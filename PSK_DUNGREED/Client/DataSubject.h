#pragma once
#include "Subject.h"

#include "Include.h"

class CDataSubject :
	public CSubject, public CSingleton<CDataSubject>
{
public:
	CDataSubject();
	virtual ~CDataSubject();

public:
	std::list<void*>* GetDatalist(int iMessage);

public:
	void AddData(int iMessage, void* pData);
	void RemoveData(int iMessage, void* pData);
	void Release(void);

private:
	std::map<int, std::list<void*>>		m_mapData;
};

