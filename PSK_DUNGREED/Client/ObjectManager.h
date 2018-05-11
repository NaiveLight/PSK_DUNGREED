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
	void AddObject(OBJID eObjID, CObj* pObj);
	void ReleaseObject(OBJID eObjID);

public:
	int Update();
	void Render();
	void Release();

private:
	std::list<CObj*> m_ObjList[OBJ_END];
};

