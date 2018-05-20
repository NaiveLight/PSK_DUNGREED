#include "stdafx.h"
#include "MapObj.h"

#include "Device.h"
#include "ObjectManager.h"
#include "AbstractObjFactory.h"
#include "TextureManager.h"
#include "ScrollManager.h"

CMapObj::CMapObj()
{
}

CMapObj::~CMapObj()
{
	Release();
}

HRESULT CMapObj::Initialize()
{
	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"MapObj Get Device Failed");
		return E_FAIL;
	}

	m_pSprite = Device->GetSprite();
	if (m_pDevice == nullptr)
	{
		MSG_BOX(L"MapObj Get Sprite Failed");
		return E_FAIL;
	}

	LoadObj();

	int a = 0;
	return S_OK;
}

int CMapObj::Update()
{
	return 0;
}

void CMapObj::Render()
{
	D3DXMATRIX		matTrans;

	for (auto& pObj : m_vecObj)
	{
		const TEXINFO*		pTexInfo = TextureManager->GetTexture(L"OBJECT", pObj->szStateKey, pObj->iCount);
		if (pTexInfo == nullptr)
			return;

		float fDiffX = pTexInfo->tImgInfo.Width * 0.5f - TILECX * 0.5f;
		float fDiffY = pTexInfo->tImgInfo.Height * 0.5f - TILECY * 0.5f;

		D3DXMatrixTranslation(&matTrans
			, pObj->vPos.x + fDiffX - ScrollManager->GetScroll().x
			, pObj->vPos.y - fDiffY - ScrollManager->GetScroll().y
			, 0.f);
		m_pSprite->SetTransform(&matTrans);
		m_pSprite->Draw(pTexInfo->pTexture
			, nullptr
			, &D3DXVECTOR3(pTexInfo->tImgInfo.Width * 0.5f, pTexInfo->tImgInfo.Height * 0.5f, 0.f)
			, nullptr
			, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
}

void CMapObj::Release()
{
	std::for_each(m_vecObj.begin(), m_vecObj.end(), DeleteObj());
	m_vecObj.clear();
	m_vecObj.shrink_to_fit();
}

void CMapObj::LoadObj()
{
	HANDLE hFile = CreateFile(m_wstrDataPath.c_str(), GENERIC_READ, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	DWORD dwByte = 0;

	int iVecSize = 0;
	ReadFile(hFile, &iVecSize, sizeof(int), &dwByte, nullptr);
	
	while (true)
	{
		MAPOBJ* pObj = new MAPOBJ;
		ReadFile(hFile, pObj, sizeof(MAPOBJ), &dwByte, nullptr);

		if (dwByte == 0)
		{
			Safe_Delete(pObj);
			break;
		}

		if (!lstrcmp(pObj->szStateKey, L"Torch"))
		{
			ObjectManager->AddObject(OBJ_MAPOBJ, CAbstractFactory<CObj_Torch>::CreateObj(&pObj->vPos));
			Safe_Delete(pObj);
			continue;
		}

		if (!lstrcmp(pObj->szStateKey, L"Door"))
		{
			ObjectManager->AddObject(OBJ_MAPOBJ, CAbstractFactory<CObj_Door>::CreateObj(&pObj->vPos));
			Safe_Delete(pObj);
			continue;
		}
		m_vecObj.push_back(pObj);
	}

	CloseHandle(hFile);
}
