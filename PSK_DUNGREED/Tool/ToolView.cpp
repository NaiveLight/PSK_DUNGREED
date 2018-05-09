
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView �׸���

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	Device->BeginDraw();

	// Rendering Section
	m_pScene->Render();

	Device->EndDraw(m_hWnd);
}


// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


void CToolView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
	{
		if (m_bTilePicking)
			OnLButtonDown(nFlags, point);
	}
	CScrollView::OnMouseMove(nFlags, point);
}


void CToolView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_pScene->DeleteLastestMapObj();

	CScrollView::OnRButtonDown(nFlags, point);
}
