#pragma once

class CScene abstract
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual HRESULT Initialize()	PURE;
	virtual int Update()	PURE;
	virtual void Render()	PURE;
	virtual void Release()	PURE;
};

