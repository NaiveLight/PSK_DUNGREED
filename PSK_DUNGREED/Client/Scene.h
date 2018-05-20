#pragma once

class CScene abstract
{
public:
	CScene();
	virtual ~CScene();

public:
	const bool& GetClear() { return m_bClear; }

public:
	virtual HRESULT Initialize()	PURE;
	virtual void LateInit();
	virtual int Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

protected:
	bool m_bIsInit = false;
	bool m_bClear = false;
};

