#pragma once
#include "afxwin.h"


// CMapTool 대화 상자입니다.

class CScene;
class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeTileList();
	afx_msg void OnLbnSelchangeMapObjList();
	afx_msg void OnBnClickedTileSave();
	afx_msg void OnBnClickedTileLoad();
	afx_msg void OnBnClickedMapObjSave();
	afx_msg void OnBnClickedMapObjLoad();
	afx_msg void OnBnClickedCreateMap();

public:
	// for tile options
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();

private:
	void FindDirAddFile(const std::wstring& wstrPath, bool bIsTile);
	void AddFileInfo(const TCHAR* pFilePath, bool bIsTile);

public:
	CListBox m_TileList;
	CListBox m_ObjListBox;
	int m_iTileX = 0;
	int m_iTileY = 0;

public:
	std::wstring m_wstrStateKey = L"";
	BYTE m_byOption = 0;
	BYTE m_byDrawID = 0;
	int m_iCount = 0;

public:
	CScene* m_pScene = nullptr;
};
