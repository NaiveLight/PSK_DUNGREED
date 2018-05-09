// ObjView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjView.h"

#include "Device.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "Scene.h"
// CObjView

IMPLEMENT_DYNCREATE(CObjView, CView)

CObjView::CObjView()
{

}

CObjView::~CObjView()
{
}

BEGIN_MESSAGE_MAP(CObjView, CView)
END_MESSAGE_MAP()


// CObjView �׸����Դϴ�.

void CObjView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

	CToolScene*	pScene = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pScene;

	Device->BeginDraw();

	// Rendering Section
	pScene->ObjViewRender();

	Device->EndDraw(m_hWnd);
}


// CObjView �����Դϴ�.

#ifdef _DEBUG
void CObjView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CObjView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CObjView �޽��� ó�����Դϴ�.
