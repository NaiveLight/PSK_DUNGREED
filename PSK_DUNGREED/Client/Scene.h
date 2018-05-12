#pragma once

class CScene abstract
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual HRESULT Initialize()	PURE;
	virtual void LateInit();
	virtual int Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;

private:
	bool m_bIsInit = false;
	int m_bIsChange = 0;
};

