#include "stdafx.h"
#include "MultiTexture.h"

#include "Device.h"

CMultiTexture::CMultiTexture()
{
}


CMultiTexture::~CMultiTexture()
{
	Release();
}

const TEXINFO * CMultiTexture::GetTexture(const std::wstring & wstrStateKey /*= L""*/, const int & iCount /*= 0*/)
{
	auto iter = m_mapMulti.find(wstrStateKey);
	if (iter == m_mapMulti.end())
		return nullptr;

	return iter->second[iCount];
}

HRESULT CMultiTexture::InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey /*= L""*/, const int & iCount /*= 0*/)
{
	TCHAR szPath[MAX_PATH] = L"";
	std::vector<TEXINFO*> vecTexture;

	for (int i = 0; i < iCount; ++i)
	{
		wsprintf(szPath, wstrFilePath.c_str(), i);

		TEXINFO*	pTexInfo = new TEXINFO;
		ZeroMemory(pTexInfo, sizeof(TEXINFO));
		if (FAILED(D3DXGetImageInfoFromFile(szPath, &pTexInfo->tImgInfo)))
		{
			MSG_BOX(L"Insert Multi Texture Get ImageInfo Failed");
			return E_FAIL;
		}

		if (FAILED(D3DXCreateTextureFromFileEx(Device->GetDevice()
			, szPath
			, pTexInfo->tImgInfo.Width
			, pTexInfo->tImgInfo.Height
			, pTexInfo->tImgInfo.MipLevels
			, 0
			, pTexInfo->tImgInfo.Format
			, D3DPOOL_MANAGED
			, D3DX_DEFAULT
			, D3DX_DEFAULT
			, NULL //D3DCOLOR_ARGB(255, 255, 255, 255) 
			, &pTexInfo->tImgInfo
			, nullptr
			, &pTexInfo->pTexture)))
		{
			MSG_BOX(L"Insert Multi Texture Create Texture Failed");
			return E_FAIL;
		}

		vecTexture.emplace_back(pTexInfo);
	}

	m_mapMulti.emplace(wstrStateKey, vecTexture);

	return S_OK;
}

void CMultiTexture::Release()
{
	for (auto& mapIter : m_mapMulti)
	{
		for (auto& vecIter : mapIter.second)
		{
			Safe_Release(vecIter->pTexture);
			Safe_Delete(vecIter);
		}
		mapIter.second.clear();
		mapIter.second.shrink_to_fit();
	}
	m_mapMulti.clear();
}
