﻿
// SN2020111396Doc.cpp: CSN2020111396Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "SN2020111396.h"
#endif

#include "SN2020111396Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSN2020111396Doc

IMPLEMENT_DYNCREATE(CSN2020111396Doc, CDocument)

BEGIN_MESSAGE_MAP(CSN2020111396Doc, CDocument)
END_MESSAGE_MAP()


// CSN2020111396Doc 생성/소멸

CSN2020111396Doc::CSN2020111396Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CSN2020111396Doc::~CSN2020111396Doc()
{
}

BOOL CSN2020111396Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CSN2020111396Doc serialization

void CSN2020111396Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar.Write(m_OutImg, 256 * 256); // 처리된 영상배열 m_OutImg를 파일로 저장
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		CFile* infile = ar.GetFile(); // 입력할 파일의 포인트를 가져옴
		if (infile->GetLength() != 256 * 256) // 파일 사이즈 검사
		{
			AfxMessageBox((LPCTSTR) "파일 크기가 256x256 사이즈가 아닙니다.");
			return;
		}
		ar.Read(m_InImg, (UINT)infile->GetLength()); // 영상 파일을 읽어 m_InImg 배열에 저장
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CSN2020111396Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CSN2020111396Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CSN2020111396Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSN2020111396Doc 진단

#ifdef _DEBUG
void CSN2020111396Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSN2020111396Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSN2020111396Doc 명령


void CSN2020111396Doc::TwoImgLoad()
{
	// TODO: 여기에 구현 코드 추가.
	CFile file;
	CFileDialog opendlg1(TRUE);
	if (opendlg1.DoModal() == IDOK)
	{
		// 첫 번째 이미지 읽기
		file.Open(opendlg1.GetFileName(), CFile::modeRead);
		file.Read(m_InImg1, sizeof(m_InImg1));
		file.Close();
	}

	CFileDialog opendlg2(TRUE);
	if (opendlg1.DoModal() == IDOK)
	{
		// 두 번째 이미지 읽기
		file.Open(opendlg2.GetFileName(), CFile::modeRead);
		file.Read(m_InImg2, sizeof(m_InImg2));
		file.Close();
	}
}


void CSN2020111396Doc::m_ImgHisto(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, gv, vmax, vmin;
	// 히스토그램 생성
	for (i = 0; i < 256; i++) m_HistoArr[i] = 0; // 히스토그램 배열 초기화
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			gv = (int)m_InImg[i][j];
			m_HistoArr[gv]++; // 밝기값에 따른 히스토그램 voting
		}
	}

	// 히스토그램 정규화 (화면 출력을 위해)
	vmin = 1000000; vmax = 0;
	for (i = 0; i < 256; i++)
	{
		if (m_HistoArr[i] <= vmin) vmin = m_HistoArr[i];
		if (m_HistoArr[i] >= vmax) vmax = m_HistoArr[i];
	}
	if (vmax == vmin) return;

	float vd = (float)(vmax - vmin);
	for (i = 0; i < 256; i++)
	{
		m_HistoArr[i] = (int)(((float)m_HistoArr[i] - vmin)*255.0 / vd);
	}

	// 히스토그램의 화면출력 (히스토그램 화면 출력을 위해 m_OutImg 사용)
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{	
			m_OutImg[i][j] = 255;
		}
	}

	// 검정색 테두리 만들기
	for (i = 0; i < 256; i++)
	{
		for (j = 0; j < 256; j++)
		{
			m_OutImg[i][0] = 0;
			m_OutImg[i][255] = 0;
			m_OutImg[0][j] = 0;
			m_OutImg[255][j] = 0;
		}
	}

	for (j = 0; j < width; j++)
	{
		for (i = 0; i < m_HistoArr[j]; i++) m_OutImg[255 - i][j] = 0;
	}
}


void CSN2020111396Doc::m_BinThres(int height, int width, int binThres)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (m_InImg[i][j] > binThres) m_OutImg[i][j] = 255;
			else m_OutImg[i][j] = 0;
		}
	}
	UpdateAllViews(FALSE); // 화면 출력 갱신
}


void CSN2020111396Doc::m_bitSlicing(int height, int width, int bit)
{
	// TODO: 여기에 구현 코드 추가.
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_OutImg[i][j] = (m_InImg[i][j] & (1 << bit)) ? 255 : 0;
		}
	}
}


void CSN2020111396Doc::m_HistoEqual(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;

	// histogram 연산을 위해 사용할 배열 메모리를 할당
	unsigned int *histogram = new unsigned int[256];
	unsigned int *sum_hist = new unsigned int[256];

	// histogram 배열을 초기화
	for (i = 0; i < 256; i++) histogram[i] = 0;

	// 영상의 히스토그램을 계산
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			histogram[m_InImg[i][j]]++;
		}
	}

	int sum = 0;
	float scale_factor = 255.0f / (float)(height*width);

	// 히스토그램의 정규화된 합을 계산
	for (i = 0; i < 256; i++)
	{
		sum += histogram[i];
		sum_hist[i] = (int)((sum*scale_factor) + 0.5);
	}

	// LUT로써 정규화합 배열을 사용하여 영상을 변환
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = sum_hist[m_InImg[i][j]];
		}
	}

	// 메모리 해제
	delete[]histogram;
	delete[]sum_hist;
}
