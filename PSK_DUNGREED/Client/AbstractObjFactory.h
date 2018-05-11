#pragma once

#include "stdafx.h"

#include "Obj.h"
#include "Bridge.h"

#include "BackGround.h"
#include "UI.h"

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

	static CObj* CreateUI(const std::wstring& wstrStateKey, const D3DXVECTOR3* pPos = nullptr, const FRAME* pFrame = nullptr)
	{
		CObj* pObj = new CUI;
		CBridge* pBridge = new T;

		if (FAILED(pObj->Initialize()))
			return nullptr;

		if (FAILED(pBridge->Initialize()))
			return nullptr;

		pObj->SetObjKey(L"UI");
		pObj->SetStateKey(wstrStateKey);

		if (pPos != nullptr)
			pObj->SetPos(pPos);
		if (pFrame != nullptr)
			pBridge->SetFrame(pFrame);

		return pObj;
	}
};