#pragma once
#include "Obj.h"

class CEffect :
	public CObj
{
public:
	CEffect();
	virtual ~CEffect();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

