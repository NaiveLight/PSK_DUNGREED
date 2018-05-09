
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "MainFrm.h"
#include "ToolForm.h"
#include "MapTool.h"

#include "Include.h"
#include "Device.h"
#include "TextureManager.h"
#include "Scene.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND g_hWnd;
// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView 그리기

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	Device->BeginDraw();

	// Rendering Section
	m_pScene->Render();

	Device->EndDraw(m_hWnd);
}


// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	g_hWnd = m_hWnd;

	SetScrollSizes(MM_TEXT, CSize(TILECX * TILEX, TILECY * TILEY));

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	RECT rcFrameWindows;
	pMainFrame->GetWindowRect(&rcFrameWindows);

	SetRect(&rcFrameWindows, 0, 0, rcFrameWindows.right - rcFrameWindows.left, rcFrameWindows.bottom - rcFrameWindows.top);

	RECT rcMainView;
	GetClientRect(&rcMainView);

	int iRowFrm = rcFrameWindows.right - rcMainView.right;
	int iColFrm = rcFrameWindows.bottom - rcMainView.bottom;

	pMainFrame->SetWindowPos(nullptr, 200, 200, int(WINCX + iRowFrm), int(WINCY + iColFrm), SWP_NOZORDER);

	if (FAILED(Device->Initialize()))
	{
		AfxMessageBox(L"Device Create Failed");
		return;
	}

	m_pDevice = Device->GetDevice();
	if (m_pDevice == nullptr)
		return;

	m_pSprite = Device->GetSprite();
	if (m_pSprite == nullptr)
		return;

	m_pFont = Device->GetFont();
	if (m_pFont == nullptr)
		return;

	TextureManager->ReadImagePath(L"../Data/ImgPath.txt");

	m_pScene = new CToolScene;
	if(FAILED(m_pScene->Initialize()))
	{
		AfxMessageBox(L"Scene Create Failed");
		return;
	}

}


void CToolView::PostNcDestroy()
{
	Safe_Delete(m_pScene);
	TextureManager->DestroyInstance();
	Device->DestroyInstance();
	CScrollView::PostNcDestroy();
}


void CToolView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch (nChar)
	{
	case VK_F1:
		m_pScene->SetShowCollider();
		break;
	case VK_F2:
		m_pScene->SetShowMapObj();
		break;
	}

	CScrollView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	D3DXVECTOR3		vMouse = D3DXVECTOR3(float(point.x) + GetScrollPos(0)	, float(point.y) + GetScrollPos(1), 0.f);

	if (m_bTilePicking)
	{
		m_wstrStateKey = ((CMainFrame*)AfxGetMainWnd())->m_pToolForm->m_MapTool.m_wstrStateKey;
		m_byOption = ((CMainFrame*)AfxGetMainWnd())->m_pToolForm->m_MapTool.m_byOption;
		m_byDrawID = ((CMainFrame*)AfxGetMainWnd())->m_pToolForm->m_MapTool.m_byDrawID;
		m_pScene->TileChange(vMouse, m_wstrStateKey, m_byOption, m_byDrawID);
	}
	else
	{
		m_wstrStateKey = ((CMainFrame*)AfxGetMainWnd())->m_pToolForm->m_MapTool.m_wstrStateKey;
		m_iCount= ((CMainFrame*)AfxGetMainWnd())->m_pToolForm->m_MapTool.m_iCount;
		m_pScene->InsertMapObj(vMouse, m_wstrStateKey, m_iCount);
	}

	CScrollView::OnLButtonDown(nFlags, point);
}


void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_bTilePicking)
			OnLButtonDown(nFlags, point);
	}
	CScrollView::OnMouseMove(nFlags, point);
}


void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_pScene->DeleteLastestMapObj();

	CScrollView::OnRButtonDown(nFlags, point);
}
