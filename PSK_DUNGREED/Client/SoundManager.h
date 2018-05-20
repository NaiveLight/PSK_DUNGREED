#pragma once

#include "Include.h"

class CSoundManager
	:public CSingleton<CSoundManager>
{
public:
	enum CHANNEL_ID { BGM, MAPOBJ, PLAYER, MONSTER, PATTACK, MATTACK, COLLISION, EFFECT, UI, END };

public:
	CSoundManager();
	~CSoundManager();

public:
	void Init();
	void Update();
	void PlaySound(const TCHAR* pSoundKey, CHANNEL_ID eID);
	void PlayBGM(const TCHAR* pSoundKey);
	void StopSound(CHANNEL_ID eID);
	void StopAll();
	void PauseSound(CHANNEL_ID eID, BOOL bPause = TRUE);
	void PauseAll(CHANNEL_ID eID, BOOL bPause = TRUE);

private:
	void Release();
	void LoadSoundFile();


private:
	std::map<const TCHAR*, FMOD_SOUND*>	m_MapSound;	// 사운드 리소스 관리를 위한 map
	FMOD_SYSTEM*	m_pSystem;			// 사운드 재생 및 관리를 주도하는 시스템
	FMOD_CHANNEL*	m_pChannel[END];	// 사운드 재생을 위한 채널
};
