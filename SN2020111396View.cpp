
// SN2020111396View.cpp: CSN2020111396View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SN2020111396.h"
#endif

#include "SN2020111396Doc.h"
#include "SN2020111396View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSN2020111396View

IMPLEMENT_DYNCREATE(CSN2020111396View, CScrollView)

BEGIN_MESSAGE_MAP(CSN2020111396View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSN2020111396View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(IDM_REVERSE_IMG, &CSN2020111396View::OnReverseImg)
END_MESSAGE_MAP()

// CSN2020111396View 생성/소멸

CSN2020111396View::CSN2020111396View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CSN2020111396View::~CSN2020111396View()
{
}

BOOL CSN2020111396View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CSN2020111396View 그리기

void CSN2020111396View::OnDraw(CDC* pDC)
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	for (int i = 0; i < 256; i++) // 세로 픽셀 인덱스는 'i'
	{
		for (int j = 0; j < 256; j++) // 가로 픽셀 인덱스는 'j'
		{
			unsigned char InVal = pDoc->m_InImg[i][j];
			unsigned char OutVal = pDoc->m_OutImg[i][j];

			pDC->SetPixel(j, i, RGB(InVal, InVal, InVal));
			pDC->SetPixel(j + 300, i, RGB(OutVal, OutVal, OutVal));
		}
	}
}

void CSN2020111396View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CSN2020111396View 인쇄


void CSN2020111396View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSN2020111396View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CSN2020111396View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CSN2020111396View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CSN2020111396View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSN2020111396View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSN2020111396View 진단

#ifdef _DEBUG
void CSN2020111396View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CSN2020111396View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CSN2020111396Doc* CSN2020111396View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSN2020111396Doc)));
	return (CSN2020111396Doc*)m_pDocument;
}
#endif //_DEBUG


// CSN2020111396View 메시지 처리기


void CSN2020111396View::OnReverseImg()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			pDoc->m_OutImg[i][j] = 255 - pDoc->m_InImg[i][j];
		}
		// m_OutImg 변경되었기 때문에
		Invalidate(FALSE); // background는 갱신 안 함
	}
}
