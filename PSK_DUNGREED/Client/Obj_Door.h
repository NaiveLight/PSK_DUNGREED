#pragma once
#include "Obj.h"
class CObj_Door :
	public CObj
{
public:
	CObj_Door();
	virtual ~CObj_Door();

	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

