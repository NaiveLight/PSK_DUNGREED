// ObjView.cpp : 구현 파일입니다.
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


// CObjView 그리기입니다.

void CObjView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	CToolScene*	pScene = ((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pScene;

	Device->BeginDraw();

	// Rendering Section
	pScene->ObjViewRender();

	Device->EndDraw(m_hWnd);
}


// CObjView 진단입니다.

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


// CObjView 메시지 처리기입니다.
