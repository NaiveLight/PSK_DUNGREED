#pragma once

#include "stdafx.h"

#include "Obj.h"
#include "Bridge.h"

#include "BackGround.h"

#include "Layer.h"

#include "TileMap.h"
#include "MapObj.h"
#include "Obj_Dungeon.h"
#include "Obj_Door.h"
#include "Obj_Torch.h"

#include "Monster.h"
#include "Monster_Skell.h"
#include "Monster_Banshee.h"
#include "Belial.h"
#include "Belial_Hand.h"
#include "Belial_CenterParticle.h"
#include "Belial_Particle.h"

#include "Player.h"

#include "Effect.h"
#include "Effect_Extinction.h"
#include "Effect_Alpha.h"

#include "Weapon.h"
#include "Weapon_Hand.h"
#include "Weapon_Sword.h"
#include "Weapon_Halberd.h"

#include "HitBox.h"
#include "Bullet.h"

#include "UI_Logo.h"
#include "UI_Cursor.h"
#include "UI_Button.h"
#include "HpBar_Player.h"
#include "DashBar.h"
#include "HpBar_Boss.h"

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

	static CObj* CreateObj(const D3DXVECTOR3* pPos)
	{
		CObj* pObj = new T;
		if (FAILED(pObj->Initialize()))
			Safe_Delete(pObj);

		pObj->SetPos(pPos);

		return pObj;
	}

	static CObj* CreateObj(const bool& bIsLeft, const D3DXVECTOR3* pPos)
	{
		CObj* pObj = new T;
		if (FAILED(pObj->Initialize()))
			Safe_Delete(pObj);

		pObj->SetPos(pPos);
		pObj->SetIsLeft(bIsLeft);

		return pObj;
	}

	static CObj* CreateObj(const D3DXVECTOR3* pPos, const D3DXVECTOR3* pDir)
	{
		CObj* pObj = new T;
		if (FAILED(pObj->Initialize()))
			Safe_Delete(pObj);

		pObj->SetPos(pPos);
		pObj->SetDir(pDir);

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
	static CObj* CreateLayer(const std::wstring& wstrStateKey, const float& fScrollRatio, const D3DXVECTOR3* pPos = nullptr, const FRAME* pFrame = nullptr)
	{
		CObj* pObj = new CLayer;

		if (FAILED(pObj->Initialize()))
			return nullptr;

		if (pPos != nullptr)
			pObj->SetPos(pPos);
		else
			pObj->SetPos(&D3DXVECTOR3(WINCX *0.5f, WINCY * 0.5f, 0));

		if (pFrame != nullptr)
			pObj->SetFrame(pFrame);
		else
			pObj->SetFrame(&FRAME(0.f, 0.f, 0.f));

		pObj->SetObjKey(L"LAYER");
		pObj->SetStateKey(wstrStateKey);

		dynamic_cast<CLayer*>(pObj)->SetScrollRatio(fScrollRatio);

		return pObj;
	}

	// OBJ_TILEMAP
	static CObj* CreateTileMap(const std::wstring& wstrFileName)
	{
		CObj* pObj = new CTileMap;

		dynamic_cast<CTileMap*>(pObj)->SetDataPath(wstrFileName);

		if (FAILED(pObj->Initialize()))
			return nullptr;

		return pObj;
	}

	//	OBJ_MAPOBJ
	static CObj* CreateMapObj(const std::wstring& wstrFileName)
	{
		CObj* pObj = new CMapObj;

		dynamic_cast<CMapObj*>(pObj)->SetDataPath(wstrFileName);

		if (FAILED(pObj->Initialize()))
			return nullptr;

		return pObj;
	}

	// OBJ_ACTOR (monster, npc, etc.)

	// OBJ_WEAPON
	static CWeapon* CreateWeapon()
	{
		CWeapon* pWeapon = new T;

		if (FAILED(pWeapon->Initialize()))
			return nullptr;

		return pWeapon;
	}

	// OBJ_PAttack,OBJ_MAttack
	static CObj* CreateHitBox(const int& iAtt, const bool& bRect, const bool& bPlayer, const HITBOX* pHitBox, const D3DXVECTOR3* pPos = nullptr)
	{
		CObj* pObj = new CHitBox;

		pObj->SetHitBox(pHitBox);
		pObj->SetPos(pPos);
		dynamic_cast<CHitBox*>(pObj)->SetAtt(iAtt);
		dynamic_cast<CHitBox*>(pObj)->SetRect(bRect);
		dynamic_cast<CHitBox*>(pObj)->SetPlayer(bPlayer);

		if (FAILED(pObj->Initialize()))
			return nullptr;

		return pObj;
	}

	// OBJ_ITEM

	static CObj* CreateBullet(BULLETID eID, const std::wstring& wstrStateKey, const int& iAtt, const FRAME* pFrame, const HITBOX* pHitBox, const D3DXVECTOR3* pPos = nullptr, const D3DXVECTOR3* pDir = nullptr)
	{
		CObj* pObj = new CBullet;

		if (FAILED(pObj->Initialize()))
			return nullptr;

		pObj->SetFrame(pFrame);
		pObj->SetStateKey(wstrStateKey);
		pObj->SetHitBox(pHitBox);
		pObj->SetPos(pPos);
		pObj->SetDir(pDir);
		dynamic_cast<CBullet*>(pObj)->SetAtt(iAtt);
		dynamic_cast<CBullet*>(pObj)->SetBulletID(eID);

		return pObj;
	}

	// OBJ_EFFECT
	static CObj* CreateEffect(const std::wstring& wstrStateKey, const bool& bIsLeft, const D3DXVECTOR3* pPos = nullptr, const FRAME* pFrame = nullptr, const D3DXVECTOR3* pDir = nullptr)
	{
		CObj* pObj = new CEffect;
		CBridge* pBridge = new T;

		pObj->SetObjKey(L"EFFECT");
		pObj->SetStateKey(wstrStateKey);
		pObj->SetFrame(pFrame);
		pObj->SetIsLeft(bIsLeft);

		if (pDir != nullptr)
			pObj->SetDir(pDir);
		else
			pObj->SetDir(&D3DXVECTOR3(0.f, 0.f, 0.f));

		pObj->SetBridge(pBridge);

		if (FAILED(pObj->Initialize()))
			return nullptr;

		if (FAILED(pBridge->Initialize()))
			return nullptr;

		if (pPos != nullptr)
			pObj->SetPos(pPos);
		else
			pObj->SetPos(&D3DXVECTOR3(0.f, 0.f, 0.f));


		return pObj;
	}

	// OBJ_UI
	static CObj* CreateLogo(const std::wstring& wstrStateKey, const D3DXVECTOR3* pPos = nullptr, const FRAME* pFrame = nullptr, const bool bAlpha = false)
	{
		CObj* pObj = new CUI_Logo;

		if (FAILED(pObj->Initialize()))
			return nullptr;

		pObj->SetObjKey(L"UI_LOGO");
		pObj->SetStateKey(wstrStateKey);

		if (pPos != nullptr)
			pObj->SetPos(pPos);
		if (pFrame != nullptr)
			pObj->SetFrame(pFrame);

		dynamic_cast<CUI_Logo*>(pObj)->SetAlphaBlend(bAlpha);

		return pObj;
	}

	static CObj* CreateCursor(const FRAME* pFrame)
	{
		CObj* pObj = new CUI_Cursor;
		if (FAILED(pObj->Initialize()))
			return nullptr;

		pObj->SetObjKey(L"UI_CURSOR");
		pObj->SetStateKey(L"Cursor");
		pObj->SetFrame(pFrame);

		return pObj;
	}

	static CObj* CreateButton(const std::wstring& wstrStateKey, const D3DXVECTOR3* pPos, BUTTONID eBtID)
	{
		CObj* pObj = new CUI_Button;
		if (FAILED(pObj->Initialize()))
			return nullptr;

		pObj->SetObjKey(L"UI_BUTTON");
		pObj->SetStateKey(wstrStateKey);
		pObj->SetPos(pPos); 

		dynamic_cast<CUI_Button*>(pObj)->SetButtonID(eBtID);

		return pObj;
	}
};