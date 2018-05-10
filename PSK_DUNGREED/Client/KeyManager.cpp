#include "stdafx.h"
#include "KeyManager.h"

CKeyManager::CKeyManager()
{
}


CKeyManager::~CKeyManager()
{
}

bool CKeyManager::KeyPressing(int iVkey)
{
	if (GetAsyncKeyState(iVkey) & 0x8000)
		return true;
	return false;
}

bool CKeyManager::KeyDown(int iVkey)
{
	if ((GetAsyncKeyState(iVkey) & 0x8000) && !m_bKey[iVkey])
	{
		m_bKey[iVkey] = !m_bKey[iVkey];
		return true;
	}
	return false;
}

bool CKeyManager::KeyUp(int iVkey)
{
	if (!(GetAsyncKeyState(iVkey) & 0x8000) && m_bKey[iVkey])
	{
		m_bKey[iVkey] = !m_bKey[iVkey];
		return true;
	}
	return false;
}

void CKeyManager::Update()
{
	for (int i = 0; i < 0xff; ++i)
	{
		if ((GetAsyncKeyState(i) & 0x8000) && !m_bKey[i])
			m_bKey[i] = !m_bKey[i];
		else if (!(GetAsyncKeyState(i) & 0x8000) && m_bKey[i])
			m_bKey[i] = !m_bKey[i];
	}
}
