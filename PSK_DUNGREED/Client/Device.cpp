#include "stdafx.h"
#include "Device.h"

CDevice::CDevice()
{
}

CDevice::~CDevice()
{
	Release();
}

void CDevice::SetBuffColor(const D3DXCOLOR & buffColor)
{
	m_backBuffColor = buffColor;
}

const LPDIRECT3DDEVICE9 CDevice::GetDevice()
{
	return m_pDevice;
}

const LPD3DXSPRITE CDevice::GetSprite()
{
	return m_pSprite;
}

const LPD3DXFONT CDevice::GetFont()
{
	return m_pFont;
}

HRESULT CDevice::Initialize()
{
	m_p3D = Direct3DCreate9(D3D_SDK_VERSION);

	D3DCAPS9		DeviceCaps;
	ZeroMemory(&DeviceCaps, sizeof(D3DCAPS9));
	if (FAILED(m_p3D->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &DeviceCaps)))
	{
		MessageBox(NULL, L"GetDeviceCaps Failed", L"System Error", MB_OK);
		return E_FAIL;
	}

	DWORD		vp = 0;
	if (DeviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//For thread
	vp |= D3DCREATE_MULTITHREADED;

	D3DPRESENT_PARAMETERS		d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));
	SetParameters(d3dpp);

	if (FAILED(m_p3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd
		, vp, &d3dpp, &m_pDevice)))
	{
		MessageBox(NULL, L"CreateDevice Failed", L"System Error", MB_OK);
		return E_FAIL;
	}

	if (FAILED(D3DXCreateSprite(m_pDevice, &m_pSprite)))
	{
		MessageBox(NULL, L"CreateSprite Failed", L"System Error", MB_OK);
		return E_FAIL;
	}

	D3DXFONT_DESC		tFontInfo;
	tFontInfo.Width = 10;
	tFontInfo.Height = 15;
	tFontInfo.Italic = FALSE;
	tFontInfo.Weight = FW_NORMAL;
	tFontInfo.CharSet = HANGUL_CHARSET;
	lstrcpy(tFontInfo.FaceName, L"메이플스토리");

	if (FAILED(D3DXCreateFontIndirect(m_pDevice, &tFontInfo, &m_pFont)))
	{
		MessageBox(NULL, L"CreateFont Failed", L"System Error", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void CDevice::BeginDraw()
{
	m_pDevice->Clear(0, nullptr , D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER | D3DCLEAR_TARGET, m_backBuffColor, 1.f, 0);
	m_pDevice->BeginScene();
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDevice::EndDraw(HWND hWnd)
{
	m_pSprite->End();
	m_pDevice->EndScene();
	m_pDevice->Present(nullptr, nullptr, hWnd, nullptr);
}

void CDevice::SetParameters(D3DPRESENT_PARAMETERS & d3dpp)
{
	d3dpp.BackBufferWidth = WINCX;
	d3dpp.BackBufferHeight = WINCY;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;

	d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality = 0;

	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = TRUE;

	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;

	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
}

void CDevice::Release()
{
	Safe_Release(m_pFont);
	Safe_Release(m_pSprite);
	Safe_Release(m_pDevice);
	Safe_Release(m_p3D);
}
