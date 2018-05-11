#include "stdafx.h"
#include "TextureManager.h"

#include "SingleTexture.h"
#include "MultiTexture.h"

CTextureManager::CTextureManager()
{
}

CTextureManager::~CTextureManager()
{
	Release();
}

const TCHAR * CTextureManager::GetLoadingMessage(void) const
{
	return m_szLoadingMessage;
}

const TEXINFO * CTextureManager::GetTexture(const std::wstring & wstrObjKey, const std::wstring & wstrStateKey, const int & iCount)
{
	auto iter = m_mapTexture.find(wstrObjKey);
	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second->GetTexture(wstrStateKey, iCount);
}

const TEXINFO * CTextureManager::InsertTexture(const std::wstring & wstrObjKey, const std::wstring & wstrStateKey, const int & iCount)
{
	auto iter = m_mapTexture.find(wstrObjKey);
	if (iter == m_mapTexture.end())
		return nullptr;

	return iter->second->GetTexture(wstrStateKey, iCount);
}

HRESULT CTextureManager::InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrObjKey, TEXTYPE eTexType, const std::wstring & wstrStateKey, const int & iCount)
{
	auto iter = m_mapTexture.find(wstrObjKey);

	if (iter == m_mapTexture.end())
	{
		CTexture* pTexture = nullptr;
		
		switch (eTexType)
		{
		case TEX_SINGLE:
			pTexture = new CSingleTexture;
			break;
		case TEX_MULTI:
			pTexture = new CMultiTexture;
			break;
		}

		if (FAILED(pTexture->InsertTexture(wstrFilePath, wstrStateKey, iCount)))
		{
			MSG_BOX(L"Texture Manager InsertTexture Failed");
			return E_FAIL;
		}

		m_mapTexture.emplace(wstrObjKey, pTexture);
	}
	else
	{
		if (eTexType == TEX_MULTI)
		{
			if (FAILED(iter->second->InsertTexture(wstrFilePath, wstrStateKey, iCount)))
			{
				MSG_BOX(L"Texture Manager Insert MultiTexture Failed");
				return E_FAIL;
			}
		}
	}

	return S_OK;
}

HRESULT CTextureManager::ReadImagePath(const std::wstring & wstrPath)
{
	std::wifstream		LoadFile;
	LoadFile.open(wstrPath.c_str(), std::ios::in);

	TCHAR		szObjKey[128] = L"";
	TCHAR		szStateKey[128] = L"";
	TCHAR		szCount[128] = L"";
	TCHAR		szImgPath[MAX_PATH] = L"";

	while (!LoadFile.eof())
	{
		LoadFile.getline(szObjKey, 128, '|');
		LoadFile.getline(szStateKey, 128, '|');
		LoadFile.getline(szCount, 128, '|');
		LoadFile.getline(szImgPath, MAX_PATH);

		int		iCount = _ttoi(szCount);

		if (FAILED(InsertTexture(szImgPath, szObjKey, TEX_MULTI, szStateKey, iCount)))
		{
			MSG_BOX(szObjKey);
			return E_FAIL;
		}
		lstrcpy(m_szLoadingMessage, szImgPath);
	}

	LoadFile.close();

	lstrcpy(m_szLoadingMessage, L"Loading Complete...");

	return S_OK;
}

void CTextureManager::Release()
{
	std::for_each(m_mapTexture.begin(), m_mapTexture.end(), DeleteMap());
	m_mapTexture.clear();
}
