#pragma once


// CMiniview ���Դϴ�.

class CMiniview : public CView
{
	DECLARE_DYNCREATE(CMiniview)

protected:
	CMiniview();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMiniview();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


