#pragma once
#include "Include.h"

class CTexture;
class CTextureManager :
	public CSingleton<CTextureManager>
{
public:
	CTextureManager();
	virtual ~CTextureManager();

public:
	const TEXINFO* InsertTexture(const std::wstring& wstrObjKey, const std::wstring& wstrStateKey = L"", const int& iCount = 0);

public:
	virtual HRESULT InsertTexture(const std::wstring& wstrFilePath, const std::wstring& wstrObjKey, TEXTYPE eTexType, const std::wstring& wstrStateKey = L"", const int& iCount = 0);

private:
	void Release();

private:
	std::unordered_map<std::wstring, CTexture*> m_mapTexture;
};

