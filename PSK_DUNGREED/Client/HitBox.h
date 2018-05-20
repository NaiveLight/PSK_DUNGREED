#pragma once
#include "Obj.h"
class CHitBox :
	public CObj
{
public:
	CHitBox();
	virtual ~CHitBox();

public:
	const bool&  GetRect() { return m_bRect; }
	const bool&  GetPlayer() { return m_bPlayer; }
	const int&  GetAtt() { return m_iAtt; }

public:
	void SetRect(const bool& bRect) { m_bRect = bRect; }
	void SetPlayer(const bool& bPlayer) { m_bPlayer = bPlayer; }
	void SetAtt(const int& iAtt) { m_iAtt = iAtt; }

	// CObj을(를) 통해 상속됨
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

private:
	int m_iAtt;
	bool m_bRect;
	bool m_bPlayer;
};

