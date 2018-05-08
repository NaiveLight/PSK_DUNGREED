
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

class CToolView;
class CMiniView;
class CObjView;
class CToolForm;
class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

public:
	CSplitterWnd	m_MainSplitter;
	CSplitterWnd	m_SecondSplitter;

public:
	CToolView*	m_pMainView = nullptr;
	CMiniView*	m_pMiniView = nullptr;
	CObjView*		m_pObjView = nullptr;
	CToolForm*	m_pToolForm = nullptr;
};


