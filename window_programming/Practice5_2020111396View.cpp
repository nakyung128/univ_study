﻿
// Practice5_2020111396View.cpp: CPractice52020111396View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Practice5_2020111396.h"
#endif

#include "Practice5_2020111396Doc.h"
#include "Practice5_2020111396View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPractice52020111396View

IMPLEMENT_DYNCREATE(CPractice52020111396View, CView)

BEGIN_MESSAGE_MAP(CPractice52020111396View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPractice52020111396View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPractice52020111396View 생성/소멸

CPractice52020111396View::CPractice52020111396View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CPractice52020111396View::~CPractice52020111396View()
{
}

BOOL CPractice52020111396View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CPractice52020111396View 그리기

void CPractice52020111396View::OnDraw(CDC* pDC)
{
	CPractice52020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	pDC->TextOut(20, 20, _T("이름: ") + m_strName);
	pDC->TextOut(20, 50, _T("성별: ") + m_strSex);
	pDC->TextOut(20, 80, _T("내가 선택한 취미: ") + m_strHobby);
}


// CPractice52020111396View 인쇄


void CPractice52020111396View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPractice52020111396View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CPractice52020111396View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CPractice52020111396View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CPractice52020111396View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPractice52020111396View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPractice52020111396View 진단

#ifdef _DEBUG
void CPractice52020111396View::AssertValid() const
{
	CView::AssertValid();
}

void CPractice52020111396View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPractice52020111396Doc* CPractice52020111396View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPractice52020111396Doc)));
	return (CPractice52020111396Doc*)m_pDocument;
}
#endif //_DEBUG


// CPractice52020111396View 메시지 처리기
