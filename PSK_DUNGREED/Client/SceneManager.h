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
	HRESULT	ChangeScene(SCENEID eSceneID);
	void Update();
	void Render();
	void Release();

public:
	void FadeIn();
	void FadeOut();
	void SwapScene(SCENEID eSceneID);

private:
	CScene* m_pScene = nullptr;
	SCENEID m_eCurScene = SCENE_LOGO;
	float m_fAlpha = 0.f;
	bool m_bIsSceneChange = false;
	bool m_bFade = false;
};

