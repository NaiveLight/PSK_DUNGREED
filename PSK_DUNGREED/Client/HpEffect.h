#pragma once
#include "Obj.h"
class CHpEffect :
	public CObj
{
public:
	CHpEffect();
	virtual ~CHpEffect();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

