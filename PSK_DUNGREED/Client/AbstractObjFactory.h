#pragma once

#include "stdafx.h"

#include "Obj.h"
#include "Bridge.h"

#include "BackGround.h"
#include "UI_Logo.h"
#include "UI_Cursor.h"

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

	// OBJ_BACKGROUND
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
	// OBJ_LAYER

	// OBJ_TILEMAP

	//	OBJ_MAPOBJ

	// OBJ_ACTOR (monster, npc, etc.)

	// OBJ_WEAPON

	// OBJ_PLAYER

	// OBJ_BULLET

	// OBJ_ITEM

	// OBJ_EFFECT

	// OBJ_UI
	static CObj* CreateLogo(const std::wstring& wstrStateKey, const D3DXVECTOR3* pPos = nullptr, const FRAME* pFrame = nullptr, const bool bAlpha = false)
	{
		CObj* pObj = new CUI_Logo;

		if (FAILED(pObj->Initialize()))
			return nullptr;

		pObj->SetObjKey(L"UI");
		pObj->SetStateKey(wstrStateKey);

		if (pPos != nullptr)
			pObj->SetPos(pPos);
		if (pFrame != nullptr)
			pObj->SetFrame(pFrame);

		dynamic_cast<CUI_Logo*>(pObj)->SetAlphaBlend(bAlpha);

		return pObj;
	}

	static CObj* CreateCursor()
	{
		CObj* pObj = new CUI_Cursor;
		if (FAILED(pObj->Initialize()))
			return nullptr;

		pObj->SetObjKey(L"UI");
		pObj->SetStateKey(L"Cursor");
		pObj->SetFrame(&FRAME(0, 0, 1));

		return pObj;
	}
};