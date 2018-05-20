#pragma once
#include "Obj.h"
class CBullet :
	public CObj
{
public:
	CBullet();
	virtual ~CBullet();

public:
	const int&  GetAtt() { return m_iAtt; }

public:
	void SetAtt(const int& iAtt) { m_iAtt = iAtt; }
	void SetCollision(const bool& bCollision) { m_bCollision = bCollision; }

public:
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	void UpdateHitBox();
	void UpdateMatrix();
	void FrameMove();

private:
	int m_iAtt = false;
	float m_fSpeed = false;
	bool m_bCollision = false;
};

