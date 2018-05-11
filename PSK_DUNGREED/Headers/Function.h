#pragma once

template <typename T>
void Safe_Release(T& obj)
{
	if (obj)
	{
		obj->Release();
		obj = nullptr;
	}
}

template <typename T>
void Safe_Delete(T& obj)
{
	if (obj)
	{
		delete obj;
		obj = nullptr;
	}
}

struct DeleteMap
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp.second)
		{
			delete Temp.second;
			Temp.second = nullptr;
		}
	}
};

struct DeleteObj
{
	template<typename T>
	void operator()(T& Temp)
	{
		if (Temp)
		{
			delete Temp;
			Temp = nullptr;
		}
	}
};

static D3DXVECTOR3 GetMousePos(void)
{
	POINT	pt;

	GetCursorPos(&pt);
	ScreenToClient(g_hWnd, &pt);

	return D3DXVECTOR3(float(pt.x), float(pt.y), 0.f);
}
