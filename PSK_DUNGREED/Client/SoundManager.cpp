#include "stdafx.h"
#include "SoundManager.h"

CSoundManager::CSoundManager()
{
	Init();
}


CSoundManager::~CSoundManager()
{
	Release();
}

void CSoundManager::Init()
{
	FMOD_System_Create(&m_pSystem);	// 시스템 할당
	FMOD_System_Init(m_pSystem, END, FMOD_INIT_NORMAL, nullptr); // 시스템 초기화
	LoadSoundFile();
}

void CSoundManager::Update()
{
	FMOD_System_Update(m_pSystem);
}

void CSoundManager::PlaySound(const TCHAR* pSoundKey, CHANNEL_ID eID)
{
	auto iter_find = find_if(m_MapSound.begin(), m_MapSound.end(),
		[&](auto& MyPair)
	{
		return !lstrcmp(pSoundKey, MyPair.first);
	});

	if (m_MapSound.end() == iter_find)
	{
		MessageBox(g_hWnd, L"Not Found Sound!", L"Error!", MB_OK);
		return;
	}

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter_find->second, FALSE, &m_pChannel[eID]);
}

void CSoundManager::PlayBGM(const TCHAR * pSoundKey)
{
	auto iter_find = find_if(m_MapSound.begin(), m_MapSound.end(),
		[&](auto& MyPair)
	{
		return !lstrcmp(pSoundKey, MyPair.first);
	});

	if (m_MapSound.end() == iter_find)
	{
		MessageBox(g_hWnd, L"Not Found Sound!", L"Error!", MB_OK);
		return;
	}

	FMOD_System_PlaySound(m_pSystem, FMOD_CHANNEL_FREE, iter_find->second, FALSE, &m_pChannel[BGM]);
	FMOD_Channel_SetMode(m_pChannel[BGM], FMOD_LOOP_NORMAL);
}

void CSoundManager::StopSound(CHANNEL_ID eID)
{
	FMOD_Channel_Stop(m_pChannel[eID]);
}

void CSoundManager::StopAll()
{
	for (int i = 0; i < END; ++i)
		FMOD_Channel_Stop(m_pChannel[i]);
}

void CSoundManager::PauseSound(CHANNEL_ID eID, BOOL bPause/* = TRUE*/)
{
	FMOD_Channel_SetPaused(m_pChannel[eID], bPause);
}

void CSoundManager::PauseAll(CHANNEL_ID eID, BOOL bPause/* = TRUE*/)
{
	for (int i = 0; i < END; ++i)
		FMOD_Channel_SetPaused(m_pChannel[i], bPause);
}

void CSoundManager::LoadSoundFile()
{
	_finddata_t	fd;

	long handle = _findfirst("../Sound/*.*", &fd);
	int iResult = 0;

	if (0 == handle)
	{
		MessageBox(g_hWnd, L"Empty Sound folder!!", L"Error!", MB_OK);
		return;
	}

	while (-1 != iResult)
	{
		char szFullPath[128] = "../Sound/";
		strcat_s(szFullPath, fd.name);

		FMOD_SOUND* pSound = nullptr;
		FMOD_RESULT res = FMOD_System_CreateSound(m_pSystem, szFullPath, FMOD_HARDWARE, nullptr, &pSound);

		if (FMOD_OK == res)
		{
			TCHAR* pSoundKey = new TCHAR[strlen(fd.name) + 1];
			ZeroMemory(pSoundKey, sizeof(TCHAR) * strlen(fd.name) + 1);

			MultiByteToWideChar(CP_ACP, 0, fd.name, strlen(fd.name) + 1,
				pSoundKey, strlen(fd.name) + 1);

			m_MapSound.insert({ pSoundKey, pSound });
		}

		iResult = _findnext(handle, &fd);
	}

	_findclose(handle);

	FMOD_System_Update(m_pSystem);
}

void CSoundManager::Release()
{
	for (auto& MyPair : m_MapSound)
	{
		delete[] MyPair.first;
		FMOD_Sound_Release(MyPair.second);	// 사운드 객체 해제
	}

	m_MapSound.clear();

	FMOD_System_Release(m_pSystem);
	FMOD_System_Close(m_pSystem);
}
