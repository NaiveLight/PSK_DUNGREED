// ToolForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ToolForm.h"


// CToolForm

IMPLEMENT_DYNCREATE(CToolForm, CFormView)

CToolForm::CToolForm()
	: CFormView(IDD_TOOLFORM)
{

}

CToolForm::~CToolForm()
{
}

void CToolForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CToolForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CToolForm::OnBnClickedMapTool)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolForm::OnBnClickedPathFind)
END_MESSAGE_MAP()


// CToolForm 진단입니다.

#ifdef _DEBUG
void CToolForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CToolForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CToolForm 메시지 처리기입니다.


void CToolForm::OnBnClickedMapTool()
{
	if (m_MapTool.GetSafeHwnd() == NULL)
		m_MapTool.Create(IDD_MAPTOOL);

	m_MapTool.ShowWindow(SW_SHOW);
}


void CToolForm::OnBnClickedPathFind()
{
	if (m_PathFind.GetSafeHwnd() == NULL)
		m_PathFind.Create(IDD_PATHFIND);

	m_PathFind.ShowWindow(SW_SHOW);
}
