#pragma once

#include "Include.h"

class CObserver
{
public:
	CObserver();
	~CObserver();

public:
	virtual void Update(int Message, void* pData)PURE;
};

