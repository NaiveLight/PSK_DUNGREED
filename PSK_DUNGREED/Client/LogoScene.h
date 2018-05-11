#pragma once
#include "Scene.h"

class CLogoScene final:
	public CScene
{
public:
	CLogoScene();
	virtual ~CLogoScene();

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

public:
	static unsigned int _stdcall ThreadFunc(void* pArg);

private:
	CRITICAL_SECTION	m_CSKey = {};
	HANDLE m_hThread;
	bool			m_bComplete = false;
	bool			m_bLogo = false;
};

