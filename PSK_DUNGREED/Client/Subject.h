#pragma once

class CObserver;
class CSubject
{
public:
	CSubject();
	virtual ~CSubject();

public:
	virtual void Subscribe(CObserver* pObserver);
	virtual void UnSubScribe(CObserver* pObserver);
	virtual void Notify(int iMessage, void* pData = nullptr);
	virtual void Release();

protected:
	std::list<CObserver*> m_Observerlist;
};

