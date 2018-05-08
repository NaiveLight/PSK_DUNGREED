#pragma once
#include "Texture.h"
class CSingleTexture final:
	public CTexture
{
public:
	CSingleTexture();
	virtual ~CSingleTexture();

public:
	virtual const TEXINFO * GetTexture(const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;

public:
	virtual HRESULT InsertTexture(const std::wstring & wstrFilePath, const std::wstring & wstrStateKey = L"", const int & iCount = 0) override;
	virtual void Release() override;

private:
	/*
		TEXINFO attributes
		LPDIRECT3DTEXTURE9 pTexture = nullptr;
		D3DXIMAGE_INFO tImgInfo = {};
	*/

	TEXINFO*	m_pTexInfo = nullptr;
};

