#pragma once

#include "stdafx.h"
#include "Obj.h"
#include "BackGround.h"

template <typename T>
class CAbstractFactory
{
public:
	static CObj* CreateObj()
	{
		CObj* pObj = new T;
		if (FAILED(pObj->Initialize()))
			Safe_Delete(pObj);

		return pObj;
	}

	static CObj* CreateBackGround(const std::wstring& wstrStateKey)
	{
		CObj* pObj = new CBackGround;
		if (FAILED(pObj->Initialize()))
			Safe_Delete(pObj);

		pObj->SetPos(&D3DXVECTOR3(WINCX * 0.5f, WINCY* 0.5f, 0.f));
		pObj->SetObjKey(L"BACKGROUND");
		pObj->SetStateKey(wstrStateKey);

		return pObj;
	}
};