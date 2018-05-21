#include "stdafx.h"
#include "Belial_Particle.h"


CBelial_Particle::CBelial_Particle()
{
}

CBelial_Particle::~CBelial_Particle()
{
	Release();
}

HRESULT CBelial_Particle::Initialize()
{
	return E_NOTIMPL;
}

int CBelial_Particle::Update()
{
	m_tFrame.fFrame += m_tFrame.fCount * m_fTime;

	if (m_tFrame.fFrame > m_tFrame.fMax)
		return 1;

	return 0;
}

void CBelial_Particle::Render()
{
}

void CBelial_Particle::Release()
{
}
