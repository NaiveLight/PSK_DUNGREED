
// ToolView.h : CToolView 클래스의 인터페이스
//

#pragma once

class CToolScene;
class CToolDoc;
class CToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

// 작업입니다.
public:
	LPDIRECT3DTEXTURE9		m_pTexture = nullptr;
	LPDIRECT3DDEVICE9		m_pDevice = nullptr;
	LPD3DXSPRITE			m_pSprite = nullptr;
	LPD3DXFONT			m_pFont = nullptr;
	D3DXIMAGE_INFO			m_tImgInfo = {};

public:
	CToolScene* m_pScene = nullptr;
	bool			m_bTilePicking = true;

public:
	std::wstring m_wstrStateKey = L"";
	BYTE m_byOption = 0;
	BYTE m_byDrawID = 0;
	int m_iCount = 0;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	virtual void PostNcDestroy();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

