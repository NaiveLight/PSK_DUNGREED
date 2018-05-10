#pragma once

#include "Include.h"

class CKeyManager :
	public CSingleton<CKeyManager>
{
public:
	CKeyManager();
	virtual ~CKeyManager();

public:
	bool KeyPressing(int iVkey);
	bool KeyDown(int iVkey);
	bool KeyUp(int iVkey);

public:
	void Update();

private:
	bool m_bKey[0xff];
};

