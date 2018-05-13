#pragma once
#include "Obj.h"
class CMapObj :
	public CObj
{
public:
	CMapObj();
	virtual ~CMapObj();

public:
	void SetDataPath(const std::wstring& wstrDataFileName) { m_wstrDataPath =  L"../Data/" + wstrDataFileName; }

public:
	std::vector<MAPOBJ*>* GetVecObj() { return &m_vecObj; }

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void LoadObj();

private:
	std::vector<MAPOBJ*> m_vecObj;

private:
	std::wstring m_wstrDataPath = L"";
};

