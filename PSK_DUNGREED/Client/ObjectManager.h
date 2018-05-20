#pragma once

#include "Include.h"

class CObj;
class CObjectManager :
	public CSingleton<CObjectManager>
{
public:
	CObjectManager();
	virtual ~CObjectManager();

public:
	void SetPlayer(CObj* pPlayer) { m_pPlayer = pPlayer; }

public:
	void RemovePlayer() { if(!m_ObjList[OBJ_PLAYER].empty()) m_ObjList[OBJ_PLAYER].pop_front(); }

public:
	CObj* GetPlayer() { return m_pPlayer; }

public:
	void SetSceneChange(const bool bChange) { m_bIsSceneChange = bChange; }

public:
	std::list<CObj*>* GetObjectList(OBJID eObjID);

public:
	void AddObject(OBJID eObjID, CObj* pObj);
	void ReleaseObject(OBJID eObjID);

public:
	int Update();
	void Render();
	void Release();

private:
	std::list<CObj*> m_ObjList[OBJ_END];
	CObj* m_pPlayer = nullptr;
	bool m_bIsSceneChange = false;
};

