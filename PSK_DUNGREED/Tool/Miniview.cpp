// Miniview.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "Miniview.h"

#include "Device.h"

// CMiniview

IMPLEMENT_DYNCREATE(CMiniview, CView)

CMiniview::CMiniview()
{

}

CMiniview::~CMiniview()
{
}

BEGIN_MESSAGE_MAP(CMiniview, CView)
END_MESSAGE_MAP()


// CMiniview 그리기입니다.

void CMiniview::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 여기에 그리기 코드를 추가합니다.

	Device->BeginDraw();

	// Rendering Section

	Device->EndDraw(m_hWnd);
}


// CMiniview 진단입니다.

#ifdef _DEBUG
void CMiniview::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CMiniview::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMiniview 메시지 처리기입니다.
