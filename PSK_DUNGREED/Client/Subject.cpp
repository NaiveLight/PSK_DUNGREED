#include "stdafx.h"
#include "Subject.h"

#include "Observer.h"

CSubject::CSubject()
{
}

CSubject::~CSubject()
{
	Release();
}

void CSubject::Subscribe(CObserver * pObserver)
{
	if (pObserver == nullptr)
		return;

	m_Observerlist.push_back(pObserver);
}

void CSubject::UnSubScribe(CObserver * pObserver)
{
	for (auto iter = m_Observerlist.begin(); iter != m_Observerlist.end(); ++iter)
	{
		if (*iter == pObserver)
		{
			m_Observerlist.erase(iter);
			return;
		}
	}
}

void CSubject::Notify(int iMessage, void * pData /*= nullptr*/)
{
	for (auto& iter : m_Observerlist)
		iter->Update(iMessage, pData);
}

void CSubject::Release()
{
	m_Observerlist.clear();
}
