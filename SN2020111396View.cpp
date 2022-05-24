
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

#include "CBinCntrlDlg.h"
#include "CBlendCtrlDlg.h"

#include<time.h>
#include<stdlib.h>

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
	ON_COMMAND(IDM_CONST_ADD, &CSN2020111396View::OnConstAdd)
	ON_COMMAND(IDM_CONST_SUB, &CSN2020111396View::OnConstSub)
	ON_COMMAND(IDM_CONST_MUL, &CSN2020111396View::OnConstMul)
	ON_COMMAND(IDM_CONST_DIV, &CSN2020111396View::OnConstDiv)
	ON_COMMAND(IDM_CONSTRSAT_UP, &CSN2020111396View::OnConstrsatUp)
	ON_COMMAND(IDM_CONSTRAST_DOWN, &CSN2020111396View::OnConstrastDown)
	ON_COMMAND(IDM_ADD_NOISE, &CSN2020111396View::OnAddNoise)
	ON_COMMAND(IDM_IMGHISTO, &CSN2020111396View::OnImghisto)
	ON_COMMAND(IDM_BINARIZATION, &CSN2020111396View::OnBinarization)
	ON_COMMAND(IDM_BIN_DYNAMIC, &CSN2020111396View::OnBinDynamic)
	ON_COMMAND(IDM_BIT_SEVEN, &CSN2020111396View::OnBitSeven)
	ON_COMMAND(IDM_BIT_FOUR, &CSN2020111396View::OnBitFour)
	ON_COMMAND(IDM_BIT_ZERO, &CSN2020111396View::OnBitZero)
	ON_COMMAND(IDM_MARK_INSERT, &CSN2020111396View::OnMarkInsert)
	ON_COMMAND(IDM_MARK_DETECT, &CSN2020111396View::OnMarkDetect)
	ON_COMMAND(IDM_HISTO_EQUAL, &CSN2020111396View::OnHistoEqual)
	ON_COMMAND(IDM_IMG_BLEND, &CSN2020111396View::OnImgBlend)
	ON_COMMAND(IDM_FRM_ADD, &CSN2020111396View::OnFrmAdd)
	ON_COMMAND(IDM_FRM_SUB, &CSN2020111396View::OnFrmSub)
	ON_COMMAND(IDM_FRM_MUL, &CSN2020111396View::OnFrmMul)
	ON_COMMAND(IDM_LUT_MUL, &CSN2020111396View::OnLutMul)
	ON_COMMAND(IDM_HISTO_STRETCH, &CSN2020111396View::OnHistoStretch)
	ON_COMMAND(IDM_HISTOUP_STRETCH, &CSN2020111396View::OnHistoUpStretch)
	ON_COMMAND(IDM_HISTO_SPEC, &CSN2020111396View::OnHistoSpec)
	ON_COMMAND(IDM_SMOOTHING_BOX, &CSN2020111396View::OnSmoothingBox)
	ON_COMMAND(IDM_SMOOTHING_GAUSSIAN, &CSN2020111396View::OnSmoothingGaussian)
	ON_COMMAND(IDM_SHARPENING_LAPLACIAN, &CSN2020111396View::OnSharpeningLaplacian)
END_MESSAGE_MAP()

// CSN2020111396View 생성/소멸

CSN2020111396View::CSN2020111396View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	height = width = 256;
	int rwsize = (((width)+31) / 32 * 4);

	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));

	BmInfo->bmiHeader.biBitCount = 8;
	BmInfo->bmiHeader.biClrImportant = 256;
	BmInfo->bmiHeader.biClrUsed = 256;
	BmInfo->bmiHeader.biCompression = 0;
	BmInfo->bmiHeader.biHeight = height;
	BmInfo->bmiHeader.biPlanes = 1;
	BmInfo->bmiHeader.biSize = 40;
	BmInfo->bmiHeader.biSizeImage = rwsize * height;
	BmInfo->bmiHeader.biWidth = width;
	BmInfo->bmiHeader.biXPelsPerMeter = 0;
	BmInfo->bmiHeader.biYPelsPerMeter = 0;

	for (int i = 0; i < 256; i++)
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen =
			BmInfo->bmiColors[i].rgbBlue = i;
		BmInfo->bmiColors[i].rgbReserved = 0;
	}
}

CSN2020111396View::~CSN2020111396View()
{
	free(BmInfo);
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
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_RevImg[i][j] = pDoc->m_InImg[height - i - 1][j];
		}
	}
	SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height,
		0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);

	// 처리한 결과 영상 (m_OutImg)의 화면 출력을 위한 부분
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_RevImg[i][j] = pDoc->m_OutImg[height - i - 1][j];
		}
	}
	SetDIBitsToDevice(pDC->GetSafeHdc(), 300, 0, width, height,
		0, 0, 0, height, m_RevImg, BmInfo, DIB_RGB_COLORS);

	/*for (int i = 0; i < 256; i++) // 세로 픽셀 인덱스는 'i'
	{
		for (int j = 0; j < 256; j++) // 가로 픽셀 인덱스는 'j'
		{
			unsigned char InVal = pDoc->m_InImg[i][j];
			unsigned char OutVal = pDoc->m_OutImg[i][j];

			pDC->SetPixel(j, i, RGB(InVal, InVal, InVal));
			pDC->SetPixel(j + 300, i, RGB(OutVal, OutVal, OutVal));
		}
	}*/
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


void CSN2020111396View::OnConstAdd()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = pDoc->m_InImg[i][j] + 60; // 더할 값은 60
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}

	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnConstSub()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = pDoc->m_InImg[i][j] - 60;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111396View::OnConstMul()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	unsigned char LUT[256]; // LUT로 사용할 메모리를 선언

	// LUT 값 계산
	for (int i = 0; i < 256; i++)
	{
		int temp = (int)(i*1.4);
		LUT[i] = temp > 255 ? 255 : temp;
	}

	// LUT 통해 영상처리
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pDoc->m_OutImg[i][j] = LUT[pDoc->m_InImg[i][j]];
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = (int)(pDoc->m_InImg[i][j] * 1.4);
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);

}


void CSN2020111396View::OnConstDiv()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = (int)(pDoc->m_InImg[i][j] / 2.0);
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}

// 명암비 증가
void CSN2020111396View::OnConstrsatUp()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = (int)(128 + 2.0*(pDoc->m_InImg[i][j] - 128));
			tempVal = tempVal < 0 ? 0 : tempVal;
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}

// 명암비 감소
void CSN2020111396View::OnConstrastDown()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = (int)(128 + 0.5*(pDoc->m_InImg[i][j] - 128));
			tempVal = tempVal < 0 ? 0 : tempVal;
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}

void CSN2020111396View::OnAddNoise()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int row, col;
	double num;
	int count = 0;
	srand(time(0));

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = (int)pDoc->m_InImg[i][j];
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}

	for (int i = 0; i < height*width*0.02; i++)
	{
		col = rand() % height;
		row = rand() % width;

		if (rand()%(1 + 1 + 1) - 1 >= 0.8)
		{
			int tempVal = 255;
			pDoc->m_OutImg[row][col] = (unsigned char)tempVal;
		}
		if (rand() % (1 + 1 + 1) - 1 <= -0.8)
		{
			int tempVal = 0;
			pDoc->m_OutImg[row][col] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111396View::OnImghisto()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->m_ImgHisto(256, 256); // 히스토그램 계산 함수 호출
	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnBinarization()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (pDoc->m_InImg[i][j] > 100) pDoc->m_OutImg[i][j] = 255;
			else pDoc->m_OutImg[i][j] = 0;
		}
	}
	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnBinDynamic()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CBinCntrlDlg pbinCtrlDlg; // 슬라이드 컨트롤 클래스 변수 선언
	pbinCtrlDlg.DoModal(); // 슬라이드 컨트롤 박스의 호출
}


void CSN2020111396View::OnBitSeven()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// Bit-Plane Slicing 함수 호출
	pDoc->m_bitSlicing(height, width, 7);
	Invalidate(FALSE);
}


void CSN2020111396View::OnBitFour()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// Bit-Plane Slicing 함수 호출
	pDoc->m_bitSlicing(height, width, 4);
	Invalidate(FALSE);
}


void CSN2020111396View::OnBitZero()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	// Bit-Plane Slicing 함수 호출
	pDoc->m_bitSlicing(height, width, 0);
	Invalidate(FALSE);
}


void CSN2020111396View::OnMarkInsert()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	FILE* outfile = NULL;
	errno_t err;
	unsigned char Img[256][256]; // 워터마크 저장할 배열
	
	// 워터마크 이미지 배열 생성
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j < 64)
			{
				Img[i][j] = 0;
			}
			if (j >= 64 && j < 128)
			{
				Img[i][j] = 255;
			}
			if (j >= 128 && j < 192)
			{
				Img[i][j] = 0;
			}
			if (j >= 192 && j < 256)
			{
				Img[i][j] = 255;
			}
		}
	}

	// 원본 이미지의 최하위 비트를 0으로 변경해 주기
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (Img[i][j] == 0)	pDoc->m_OutImg[i][j] = pDoc->m_InImg[i][j] & 254;
			else pDoc->m_OutImg[i][j] = pDoc->m_InImg[i][j] | 1;
		}
	}

	// 워터마크 삽입한 이미지 저장하기
	err = fopen_s(&outfile, "wm.raw", "wb");
	fwrite(pDoc->m_OutImg, sizeof(char), 256 * 256, outfile);
	fclose(outfile);

	Invalidate(FALSE);
}


void CSN2020111396View::OnMarkDetect()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->m_bitSlicing(height, width, 0); // 최하위 비트 (워터마크 검출)

	// 검은색 테두리 생성
	for (int i = 0; i < 256; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			pDoc->m_OutImg[i][0] = 0;
			pDoc->m_OutImg[i][255] = 0;
			pDoc->m_OutImg[0][j] = 0;
			pDoc->m_OutImg[255][j] = 0;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111396View::OnHistoEqual()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->m_HistoEqual(256, 256);
	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnImgBlend()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->TwoImgLoad();
	CBlendCtrlDlg pBlendCtrlDlg; // 슬라이드 컨트롤 클래스 변수 선언
	pBlendCtrlDlg.DoModal();
}


void CSN2020111396View::OnFrmAdd()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->TwoImgLoad();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = pDoc->m_InImg1[i][j] + pDoc->m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnFrmSub()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->TwoImgLoad();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = pDoc->m_InImg1[i][j] - pDoc->m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111396View::OnFrmMul()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->TwoImgLoad();
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int tempVal = pDoc->m_InImg1[i][j] & pDoc->m_InImg2[i][j];
			tempVal = tempVal > 255 ? 255 : tempVal;
			tempVal = tempVal < 0 ? 0 : tempVal;
			pDoc->m_OutImg[i][j] = (unsigned char)tempVal;
		}
	}
	Invalidate(FALSE);
}


void CSN2020111396View::OnLutMul()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	unsigned char LUT[256];

	// LUT 값을 계산한다
	for (int i = 0; i < 256; i++)
	{
		int temp = (int)((float)i*1.4);
		LUT[i] = temp;
	}

	// LUT를 통하여 영상을 처리한다
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			pDoc->m_OutImg[i][j] = LUT[pDoc->m_InImg[i][j]];
		}
	}
	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnHistoStretch()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	// 도큐먼트 클래스에 있는 히스토그램 스트레칭 함수 호출
	pDoc->m_HistoStretch(256, 256);

	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnHistoUpStretch()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	// 도큐먼트 클래스에 있는 개선된 히스토그램 스트레칭 함수 호출
	pDoc->m_HistoUpStretch(256, 256, 20, 20);
	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnHistoSpec()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CFile file;
	CFileDialog opendlg1(TRUE);

	if (opendlg1.DoModal() == IDOK)
	{
		// 첫 번째 이미지 읽기
		file.Open(opendlg1.GetPathName(), CFile::modeRead);
		file.Read(pDoc->m_InImg1, sizeof(pDoc->m_InImg1));
		file.Close();
	}

	// 도큐먼트 클래스에 있는 히스토그램 지정 연산 함수 호출
	pDoc->m_HistoSpec(256, 256);
	Invalidate(FALSE);
}


void CSN2020111396View::OnSmoothingBox()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->m_SmoothingBox(256, 256);
	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnSmoothingGaussian()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->SmoothingGaussian(256, 256);
	Invalidate(FALSE); // 화면 갱신
}


void CSN2020111396View::OnSharpeningLaplacian()
{
	CSN2020111396Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	pDoc->m_SharpeningLaplacian(256, 256);
	Invalidate(FALSE); // 화면 갱신
}
