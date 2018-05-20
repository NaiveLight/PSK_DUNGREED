#pragma once

#include "Include.h"

class CScene;
class CSceneManager :
	public CSingleton<CSceneManager>
{
public:
	CSceneManager();
	virtual ~CSceneManager();

public:
	const int& GetCurSceneID() { return (int)m_eCurScene; }

public:
	HRESULT	ChangeScene(int eSceneID);
	void Update();
	void Render();
	void Release();

public:
	void FadeIn();
	void FadeOut();
	void SwapScene(int eSceneID);

private:
	CScene* m_pScene = nullptr;
	SCENEID m_eCurScene;
	float m_fAlpha = 0.f;
	bool m_bIsSceneChange = false;
	bool m_bFade = false;
};

