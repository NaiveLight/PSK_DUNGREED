#pragma once


// CObjView ���Դϴ�.

class CObjView : public CView
{
	DECLARE_DYNCREATE(CObjView)

protected:
	CObjView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CObjView();

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


