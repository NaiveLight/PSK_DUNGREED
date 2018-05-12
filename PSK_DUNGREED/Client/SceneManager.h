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

private:
	CScene* m_pScene = nullptr;
	bool m_bIsSceneChange = false;
};

