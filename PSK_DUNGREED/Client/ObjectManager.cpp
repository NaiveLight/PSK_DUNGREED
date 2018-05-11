#include "stdafx.h"
#include "ObjectManager.h"

#include "Obj.h"

CObjectManager::CObjectManager()
{
}

CObjectManager::~CObjectManager()
{
	Release();
}

std::list<CObj*>* CObjectManager::GetObjectList(OBJID eObjID)
{
	if (eObjID == OBJ_END)
		return nullptr;
	return &m_ObjList[eObjID];
}

void CObjectManager::AddObject(OBJID eObjID, CObj * pObj)
{
	if (pObj == nullptr)
		return;

	m_ObjList[eObjID].push_back(pObj);
}

void CObjectManager::ReleaseObject(OBJID eObjID)
{
	std::for_each(m_ObjList[eObjID].begin(), m_ObjList[eObjID].end(), DeleteObj());
	m_ObjList[eObjID].clear();
}

int CObjectManager::Update()
{
	int iResult = 0;

	for (int i = 0; i < OBJ_END; ++i)
	{
		auto iter = m_ObjList[i].begin();
		auto iter_end = m_ObjList[i].end();

		for (; iter != iter_end;)
		{
			iResult = (*iter)->Update();

			if (iResult == 1)
				iter = m_ObjList[i].erase(iter);
			else
				++iter;
		}
	}

	return iResult;
}

void CObjectManager::Render()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		for (auto& iter : m_ObjList[i])
			iter->Render();
	}
}

void CObjectManager::Release()
{
	for (int i = 0; i < OBJ_END; ++i)
	{
		std::for_each(m_ObjList[i].begin(), m_ObjList[i].end(), DeleteObj());
		m_ObjList[i].clear();
	}
}
