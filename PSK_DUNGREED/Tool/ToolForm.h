#pragma once



// CToolForm �� ���Դϴ�.

class CToolForm : public CFormView
{
	DECLARE_DYNCREATE(CToolForm)

protected:
	CToolForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMapTool();
	afx_msg void OnBnClickedPathFind();
};


