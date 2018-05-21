#pragma once
#include "Obj.h"
class CBelial_CenterParticle :
	public CObj
{
public:
	CBelial_CenterParticle();
	virtual ~CBelial_CenterParticle();

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void UpdateMatrix();

private:
	void FrameMove();

private:
	float m_fEffectTime = 0.f;
	float m_fAngle = 0.f;
};

