// Miniview.cpp : 구현 파일입니다.
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


// CMiniview 그리기입니다.

void CMiniView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	CScene*	pScene= ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pScene;

	Device->BeginDraw();

	// Rendering Section
	pScene->MiniViewRender();

	Device->EndDraw(m_hWnd);
}


// CMiniview 진단입니다.

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


// CMiniview 메시지 처리기입니다.
