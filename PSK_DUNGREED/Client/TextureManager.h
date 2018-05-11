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
	const TCHAR* GetLoadingMessage(void) const;

public:
	const TEXINFO* GetTexture(const std::wstring& wstrObjKey, const std::wstring& wstrStateKey = L"", const int& iCount = 0);

public:
	const TEXINFO* InsertTexture(const std::wstring& wstrObjKey, const std::wstring& wstrStateKey = L"", const int& iCount = 0);

public:
	HRESULT InsertTexture(const std::wstring& wstrFilePath, const std::wstring& wstrObjKey, TEXTYPE eTexType, const std::wstring& wstrStateKey = L"", const int& iCount = 0);
	HRESULT ReadImagePath(const std::wstring& wstrPath);

private:
	void Release();

private:
	std::unordered_map<std::wstring, CTexture*> m_mapTexture;

private:
	TCHAR		m_szLoadingMessage[MAX_PATH] = L"";
};

