// Miniview.cpp : ���� �����Դϴ�.
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


// CMiniview �׸����Դϴ�.

void CMiniview::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.

	Device->BeginDraw();

	// Rendering Section

	Device->EndDraw(m_hWnd);
}


// CMiniview �����Դϴ�.

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


// CMiniview �޽��� ó�����Դϴ�.
