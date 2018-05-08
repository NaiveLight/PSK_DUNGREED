#include "stdafx.h"
#include "SingleTexture.h"

#include "Device.h"

CSingleTexture::CSingleTexture()
{
}

CSingleTexture::~CSingleTexture()
{
	Release();
}

const TEXINFO * CSingleTexture::GetTexture(const std::wstring & wstrStateKey /*= L""*/, const int & iCount /*= 0*/)
{
	return m_pTexInfo;
}

HRESULT CSingleTexture::InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey /*= L""*/, const int & iCount /*= 0*/)
{
	m_pTexInfo = new TEXINFO;
	ZeroMemory(m_pTexInfo, sizeof(TEXINFO));

	if (FAILED(D3DXGetImageInfoFromFile(wstrFilePath.c_str(), &m_pTexInfo->tImgInfo)))
	{
		MSG_BOX(L"Insert Single Texture Get ImageInfo Failed");
		return E_FAIL;
	}

	if (FAILED(D3DXCreateTextureFromFileEx(Device->GetDevice()
		, wstrFilePath.c_str()
		, m_pTexInfo->tImgInfo.Width
		, m_pTexInfo->tImgInfo.Height
		, m_pTexInfo->tImgInfo.MipLevels
		, 0
		, m_pTexInfo->tImgInfo.Format
		, D3DPOOL_MANAGED
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, NULL
		, &m_pTexInfo->tImgInfo
		, nullptr
		, &m_pTexInfo->pTexture)))
	{
		MSG_BOX(L"Insert Single Texture Create Texture Failed");
		return E_FAIL;
	}

	return S_OK;
}

void CSingleTexture::Release()
{
	Safe_Release(m_pTexInfo->pTexture);
	Safe_Delete(m_pTexInfo);
}
