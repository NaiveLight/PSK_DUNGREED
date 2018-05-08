// Miniview.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "Miniview.h"

#include "MainFrm.h"
#include "ToolView.h"

#include "Device.h"
#include "Scene.h"

// CMiniview

IMPLEMENT_DYNCREATE(CMiniView, CView)

CMiniView::CMiniView()
{

}

CMiniView::~CMiniView()
{
}

BEGIN_MESSAGE_MAP(CMiniView, CView)
END_MESSAGE_MAP()


// CMiniview �׸����Դϴ�.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

	CScene*	pScene= ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pScene;

	Device->BeginDraw();

	// Rendering Section
	pScene->MiniViewRender();

	Device->EndDraw(m_hWnd);
}


// CMiniview �����Դϴ�.

#ifdef _DEBUG
void CMiniView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniview �޽��� ó�����Դϴ�.
