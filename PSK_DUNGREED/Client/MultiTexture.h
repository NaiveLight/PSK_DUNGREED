#pragma once
#include "Texture.h"
class CMultiTexture final:
	public CTexture
{
public:
	CMultiTexture();
	virtual ~CMultiTexture();

public:
	virtual const TEXINFO * GetTexture(const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;
	
public:
	virtual HRESULT InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	std::unordered_map<std::wstring, std::vector<TEXINFO*>> m_mapMulti;
};

