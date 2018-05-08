#pragma once



// CToolForm 폼 뷰입니다.
#include "MapTool.h"
#include "PathFind.h"

class CToolForm : public CFormView
{
	DECLARE_DYNCREATE(CToolForm)

protected:
	CToolForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CToolForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMapTool();
	afx_msg void OnBnClickedPathFind();

public:
	CMapTool m_MapTool;
	CPathFind m_PathFind;
};


