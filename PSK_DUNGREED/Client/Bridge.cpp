#include "stdafx.h"
#include "Bridge.h"


CBridge::CBridge()
{
}

CBridge::~CBridge()
{
}

void CBridge::SetObj(CObj * pObj)
{
	m_pObj = pObj;
}

void CBridge::SetFrame(const FRAME * pFrame)
{
	m_tFrame = *pFrame;
}
