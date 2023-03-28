
// Practice5_2020111396View.h: CPractice52020111396View 클래스의 인터페이스
//

#pragma once
#include "Practice5_2020111396Doc.h"

class CPractice52020111396View : public CView
{
protected: // serialization에서만 만들어집니다.
	CPractice52020111396View() noexcept;
	DECLARE_DYNCREATE(CPractice52020111396View)

// 특성입니다.
public:
	CPractice52020111396Doc* GetDocument() const;

// 작업입니다.
public:

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
	virtual ~CPractice52020111396View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strSex;
	CString m_strHobby;
};

#ifndef _DEBUG  // Practice5_2020111396View.cpp의 디버그 버전
inline CPractice52020111396Doc* CPractice52020111396View::GetDocument() const
   { return reinterpret_cast<CPractice52020111396Doc*>(m_pDocument); }
#endif

