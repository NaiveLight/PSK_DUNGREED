#pragma once
#include "Scene.h"
class CRoom_3 :
	public CScene
{
public:
	CRoom_3();
	virtual ~CRoom_3();

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void LateInit() override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;
};

