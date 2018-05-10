#pragma once

#define MSG_BOX(text) MessageBox(NULL, text, L"System Message", MB_OK);

#define DECLARE_SINGLETON(ClassName)			\
public:											\
	static ClassName* GetInstance()				\
	{											\
		if (m_pInstance == nullptr)				\
			m_pInstance = new ClassName;		\
												\
		return m_pInstance;						\
	}											\
												\
	void DestroyInstance()						\
	{											\
		if (m_pInstance)						\
		{										\
			delete m_pInstance;					\
			m_pInstance = nullptr;				\
		}										\
	}											\
												\
private:										\
	static ClassName* m_pInstance;				\

#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;

#define Device CDevice::GetInstance()
#define TextureManager CTextureManager::GetInstance()
#define KeyManager CKeyManager::GetInstance()
#define ObjectManager CObjectManager::GetInstance()