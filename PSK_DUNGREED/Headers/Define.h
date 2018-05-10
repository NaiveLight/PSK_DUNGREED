#pragma once

#define MSG_BOX(text) MessageBox(NULL, text, L"System Message", MB_OK);

#define		Device CDevice::GetInstance()
#define		TextureManager CTextureManager::GetInstance()
#define		SceneManager CSceneManager::GetInstance()
#define		TimeManager CTimeManager::GetInstance()
#define		KeyManager CKeyManager::GetInstance()
#define		ScrollManager CScrollManager::GetInstance()
#define		ObjectManager CObjectManager::GetInstance()