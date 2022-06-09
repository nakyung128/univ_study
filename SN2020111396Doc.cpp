
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
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSN2020111396Doc

IMPLEMENT_DYNCREATE(CSN2020111396Doc, CDocument)

BEGIN_MESSAGE_MAP(CSN2020111396Doc, CDocument)
	ON_COMMAND(IDM_BINAR_OTZU, &CSN2020111396Doc::OnBinarOtzu)
	ON_COMMAND(IDM_BINAR_ADAP, &CSN2020111396Doc::OnBinarAdap)
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
		file.Open(opendlg1.GetPathName(), CFile::modeRead);
		file.Read(m_InImg1, sizeof(m_InImg1));
		file.Close();
	}

	CFileDialog opendlg2(TRUE);
	if (opendlg2.DoModal() == IDOK)
	{
		// 두 번째 이미지 읽기
		file.Open(opendlg2.GetPathName(), CFile::modeRead);
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


// 이미지 블렌드 함수
void CSN2020111396Doc::ImageBlend(int height, int width, int alpha)
{
	// TODO: 여기에 구현 코드 추가.
	FILE* infile = NULL;
	errno_t err;
	
	float w;
	w = alpha / 255.0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			m_OutImg[i][j] = w * m_InImg2[i][j] + (1 - w) * m_InImg1[i][j];
		}
	}
	UpdateAllViews(FALSE); // 화면 출력 갱신
}


void CSN2020111396Doc::m_HistoStretch(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	int lowvalue = 255, highvalue = 0;

	// 가장 작은 밝기값 설정 
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (m_InImg[i][j] < lowvalue) lowvalue = m_InImg[i][j];
		}
	}

	// 가장 큰 밝기값 설정
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			if (m_InImg[i][j] > highvalue) highvalue = m_InImg[i][j];
		}
	}

	// Histogram 스트레칭 계산
	float mult = 255.0f / (float)(highvalue - lowvalue);
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = (unsigned char)((m_InImg[i][j] - lowvalue)*mult);
		}
	}
}


void CSN2020111396Doc::m_HistoUpStretch(int height, int width, int lowPercent, int highPercent)
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;

	// 히스토그램 연산을 위해 사용할 배열을 할당
	unsigned int *histogram = new unsigned int[256];

	// 히스토그램 배열 초기화
	for (i = 0; i < 256; i++) histogram[i] = 0;

	// 영상의 히스토그램을 계산
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			histogram[m_InImg[i][j]]++;
		}
	}

	// 0으로 만들 픽셀 비율에 대응하는 픽셀 밝기값 lowthresh
	unsigned int runsum = 0;
	int lowthresh = 0, highthresh = 255;
	for (i = 0; i < height; i++)
	{
		runsum += histogram[i];
		if ((runsum*100.0 / (float)(height*width)) >= lowPercent)
		{
			lowthresh = i;
			break;
		}
	}

	// 255로 만들 픽셀 비율에 대응하는 픽셀 밝기값 highthresh
	runsum = 0;
	for (i = 255; i >= 0; i--)
	{
		runsum += histogram[i];
		if ((runsum*100.0 / (float)(height*width)) >= highPercent)
		{
			highthresh = i;
			break;
		}
	}

	// 변환을 위한 LUT를 계산
	unsigned char *LUT = new unsigned char[256];
	for (i = 0; i < lowthresh; i++) LUT[i] = 0;
	for (i = 255; i > highthresh; i--) LUT[i] = 255;

	float scale = 255.0f / (float)(highthresh - lowthresh);
	for (i = lowthresh; i <= highthresh; i++)
	{
		LUT[i] = (unsigned char)((i - lowthresh)*scale);
	}

	// LUT를 사용하여 영상 변환
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = LUT[m_InImg[i][j]];
		}
	}

	// 메모리 해제
	delete[]histogram;
	delete[]LUT;
}

void CSN2020111396Doc::m_HistoSpec(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	// 히스토그램 연산을 위해 사용할 배열을 할당
	unsigned int *histogram = new unsigned int[256];
	unsigned int *sum_hist = new unsigned int[256];
	unsigned int *desired_histogram = new unsigned int[256];
	unsigned int *desired_sum_hist = new unsigned int[256];

	// 히스토그램 배열 초기화
	for (i = 0; i < 256; i++) histogram[i] = desired_histogram[i] = 0;

	// 영상의 히스토그램 계산
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			histogram[m_InImg[i][j]]++; // 입력 영상의 히스토그램
			desired_histogram[m_InImg1[i][j]]++; // 지정 영상의 히스토그램
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

	// 지정 히스토그램에 대한 정규화된 합을 계산
	sum = 0;
	for (i = 0; i < 256; i++)
	{
		sum += desired_histogram[i];
		desired_sum_hist[i] = (int)(sum*scale_factor);
	}

	// 가장 가까운 정규화합 히스토그램 값을 주는 index를 찾음
	int *inv_hist = new int[256];
	int hist_min, hist_index, hist_diff;
	for (i = 0; i < 256; i++)
	{
		hist_min = 1000;
		for (j = 0; j < 256; j++)
		{
			hist_diff = abs((int)(sum_hist[i] - desired_sum_hist[j]));
			if (hist_diff < hist_min)
			{
				hist_min = hist_diff;
				hist_index = j;
			}
		}
		inv_hist[i] = hist_index; // 찾은 인덱스 저장
	}

	// 입력 영상의 변환 (역 히스토그램 변환)
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = inv_hist[m_InImg[i][j]];
		}
	}

	// 메모리 해제
	delete[] inv_hist;
	delete[] histogram;
	delete[] desired_histogram;
	delete[] sum_hist;
	delete[] desired_sum_hist;
}


void CSN2020111396Doc::Otzu_Threshold(unsigned char* orgImg, unsigned char* outImg, int height, int width)
{
	register int i, t;

	// Histogram set
	int hist[256];
	float prob[256];
	for (i = 0; i < 256; i++)
	{
		hist[i] = 0;
		prob[i] = 0.0f;
	}
	for (i = 0; i < height*width; i++) hist[(int)orgImg[i]]++;
	for (i = 0; i < 256; i++) prob[i] = (float)hist[i] / (float)(height*width);

	float wsv_min = 1000000.0f;
	float wsv_u1, wsv_u2, wsv_s1, wsv_s2;
	int wsv_t;

	for (t = 0; t < 256; t++)
	{
		// q1, q2 계산
		float q1 = 0.0f, q2 = 0.0f;

		for (i = 0; i < t; i++) q1 += prob[i];
		for (i = t; i < 256; i++) q2 += prob[i];
		if (q1 == 0 || q2 == 0) continue;

		// u1, u2 계산
		float u1 = 0.0f, u2 = 0.0f;
		for (i = 0; i < t; i++) u1 += i * prob[i];
		u1 /= q1;
		for (i = t; i < 256; i++) u2 += i * prob[i];
		u2 /= q2;

		// s1, s2 계산
		float s1 = 0.0f, s2 = 0.0f;
		for (i = 0; i < t; i++) s1 += (i - u1)*(i - u1)*prob[i];
		s1 /= q1;
		for (i = t; i < 256; i++) s2 += (i - u2)*(i - u2)*prob[i];
		s2 /= q2;

		float wsv = q1 * s1 + q2 * s2;

		if (wsv < wsv_min)
		{
			wsv_min = wsv; wsv_t = t;
			wsv_u1 = u1; wsv_u2 = u2;
			wsv_s1 = s1; wsv_s2 = s2;
		}
	}

	// thresholding
	for (i = 0; i < height*width; i++)
	{
		if (orgImg[i] < wsv_t) outImg[i] = 0;
		else outImg[i] = 255;
	}
}


void CSN2020111396Doc::OnBinarOtzu()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int height = 256, width = 256;
	register int i, j;

	unsigned char* orgImg = new unsigned char[height*width];
	unsigned char* outImg = new unsigned char[height*width];

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			orgImg[i*width + j] = m_InImg[i][j];
		}
	}

	Otzu_Threshold(orgImg, outImg, height, width);
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = outImg[i*width + j];
		}
	}

	delete[] orgImg;
	delete[] outImg;

	UpdateAllViews(NULL);
}


void CSN2020111396Doc::AdaptiveBinarization(unsigned char* orgImg, unsigned char* outImg, int height, int width)
{
	register int i, j, k, l;
	int gval, index1, index2;
	float mean, vari, thres;
	int W = 20;

	for (i = 0; i < height*width; i++) outImg[i] = 255;

	for (i = 0; i < height; i++)
	{
		index2 = i * width;
		for (j = 0; j < width; j++)
		{
			float gsum = 0.0f;
			float ssum = 0.0f;
			int count = 0;

			for (k = i - W; k <= i + W; k++)
			{
				index1 = k * width;
				if (k < 0 || k >= height) continue;

				for (l = j - W; l <= j + W; l++)
				{
					if (l < 0 || l >= width) continue;

					gval = orgImg[index1 + l];
					gsum += gval;
					ssum += gval * gval;
					count++;
				}
			}

			mean = gsum / (float)count;
			vari = ssum / (float)count - mean * mean;

			if (vari < 0) vari = 0.0f;

			thres = mean * (1.0f - 0.02f*(1 - (float)sqrt(vari) / 128));

			if (vari < 0) vari = 0.0f;

			thres = mean * (1.0f - 0.02f*(1 - (float)sqrt(vari) / 128));

			if (orgImg[index2 + j] < thres) outImg[index2 + j] = 0;
		}
	}
}


void CSN2020111396Doc::OnBinarAdap()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	int height = 256; int width = 256;
	register int i, j;

	unsigned char* orgImg = new unsigned char[height*width];
	unsigned char* outImg = new unsigned char[height*width];

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			orgImg[i*width + j] = m_InImg[i][j];
		}
	}

	AdaptiveBinarization(orgImg, outImg, height, width);

	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = outImg[i*width + j];
		}
	}

	delete[] orgImg;
	delete[] outImg;

	UpdateAllViews(NULL);
}


void CSN2020111396Doc::m_SmoothingBox(int height, int width)
{
	int MaskBox[3][3] = { {1,1,1}, {1,1,1}, {1,1,1} }; // 3x3 박스 평활화 마스크
	int heightml = height - 1; // 중복 계산을 피하기 위해 사용
	int widthml = width - 1; // 중복 계산을 피하기 위해 사용
	int mr, mc;
	int newValue;
	int i, j;

	// 결과 이미지 0으로 초기화
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = 0;
		}
	}

	for (i = 1; i < heightml; i++)
	{
		for (j = 1; j < widthml; j++)
		{
			newValue = 0; // 0으로 초기화
			for (mr = 0; mr < 3; mr++)
			{
				for (mc = 0; mc < 3; mc++)
				{
					newValue += (MaskBox[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
				}
			}
			newValue /= 9; // 마스크의 합의 크기로 나누기: 값의 범위를 0에서 255로 함
			m_OutImg[i][j] = (BYTE)newValue; // BYTE 값으로 변환
		}
	}
}

void CSN2020111396Doc::SmoothingGaussian(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	int MaskBox[3][3] = { {1,2,1}, {2,4,2}, {1,2,1} }; // 3x3 박스 평활화 마스크
	int heightml = height - 1; // 중복 계산을 피하기 위해 사용
	int widthml = width - 1; // 중복 계산을 피하기 위해 사용
	int mr, mc;
	int newValue;
	int i, j;

	// 결과 이미지 0으로 초기화
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = 0;
		}
	}

	for (i = 1; i < heightml; i++)
	{
		for (j = 1; j < widthml; j++)
		{
			newValue = 0; // 0으로 초기화
			for (mr = 0; mr < 3; mr++)
			{
				for (mc = 0; mc < 3; mc++)
				{
					newValue += (MaskBox[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
				}
			}
			newValue /= 16; // 마스크의 합의 크기로 나누기: 값의 범위를 0에서 255로 함
			m_OutImg[i][j] = (BYTE)newValue; // BYTE 값으로 변환
		}
	}
}

// 에지 검출 (Laplacian)
void CSN2020111396Doc::m_SharpeningLaplacian(int height, int width)
{
	int MaskBox[3][3] = { {-1,-1,-1}, {-1,8,-1}, {-1,-1,-1} };
	int heightml = height - 1;
	int widthml = width - 1;
	int mr, mc, newValue, i, j, min, max;
	int *pTmpImg;
	float constVal1, constVal2;

	// 정수값을 갖는 이미지 동적 메모리 할당
	pTmpImg = new int[height*width];

	// 결과 이미지 0으로 초기화
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = 0;
			pTmpImg[i*width + j] = 0;
		}
	}

	for (i = 1; i < heightml; i++)
	{
		for (j = 1; j < widthml; j++)
		{
			newValue = 0; // 0으로 초기화
			for (mr = 0; mr < 3; mr++)
			{
				for (mc = 0; mc < 3; mc++)
				{
					newValue += (MaskBox[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
				}
			}
			// 값을 양수로 변환
			if (newValue < 0) newValue = -newValue;
			pTmpImg[i*width + j] = newValue;
		}
	}

	// 디스플레이를 위해 0에서 255 사이로 값의 범위를 매핑
	// 이를 위해 먼저 최대, 최소값을 찾은 후 이를 이용하여 매핑한다
	// min = (int)10e10;
	// max = (int)-10e10;
	min = INT_MIN;
	max = INT_MAX;
	for (i = 1; i < heightml; i++)
	{
		for (j = 1; j < widthml; j++)
		{
			newValue = pTmpImg[i*width + j];
			if (newValue < min)min = newValue;
			if (newValue > max) max = newValue;
		}
	}

	// 변환 시 상수값을 미리 계산
	constVal1 = (float)(255.0 / (max - min));
	constVal2 = (float)(-255.0 / (max - min));
	for (i = 1; i < heightml; i++)
	{
		for (j = 1; j < widthml; j++)
		{
			// [min, max] 사이의 값을 [0, 255] 값으로 변환
			newValue = pTmpImg[i*width + j];
			newValue = constVal1 * newValue + constVal2;
			m_OutImg[i][j] = (BYTE)newValue;
		}
	}

	// 동적 할당 메모리 해제
	delete[] pTmpImg;
}

// 에지 검출 함수 (Prewitt)
void CSN2020111396Doc::EdgePrewitt(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	int MaskPrewittX[3][3] = { {-1,0,1}, {-1,0,1}, {-1,0,1} };
	int MaskPrewittY[3][3] = { {1,1,1}, {0,0,0}, {-1,-1,-1} };
	int heightm1 = height - 1, widthm1 = width - 1;
	int mr, mc, newValue, i, j;
	int *pImgPrewittX, *pImgPrewittY;
	int min, max, where;
	float constVal1, constVal2;

	// 정수값을 갖는 이미지 동적 메모리 할당
	pImgPrewittX = new int[height*width];
	pImgPrewittY = new int[height*width];

	// 결과 이미지 0으로 초기화
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = 0;
			where = i * width + j;
			pImgPrewittX[where] = 0;
			pImgPrewittY[where] = 0;
		}
	}

	// X 방향 에지 강도 계산
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = 0; // 0으로 초기화
			for (mr = 0; mr < 3; mr++)
			{
				for (mc = 0; mc < 3; mc++)
				{
					newValue += (MaskPrewittX[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
				}
			}
			pImgPrewittX[i*width + j] = newValue;
		}
	}

	// Y 방향 에지 강도 계산
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = 0; // 0으로 초기화
			for (mr = 0; mr < 3; mr++)
			{
				for (mc = 0; mc < 3; mc++)
				{
					newValue += (MaskPrewittY[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
				}
			}
			pImgPrewittY[i*width + j] = newValue;
		}
	}

	// 에지 강도 계산 절대값(X) + 절대값 (Y) 후 pImgPrewittX[]에 저장
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			where = i * width + j;
			constVal1 = pImgPrewittX[where];
			constVal2 = pImgPrewittY[where];
			if (constVal1 < 0) constVal1 = -constVal1;
			if (constVal2 < 0) constVal2 = -constVal2;
			pImgPrewittX[where] = constVal1 + constVal2;
		}
	}

	// 디스플레이를 위해 0에서 255 사이로 값의 범위를 매핑
	// 이를 위해 먼저 최대, 최소값을 찾은 후 이를 이용하여 매핑한다
	min = (int)10e10;
	max = (int)-10e10;
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = pImgPrewittX[i*width + j];
			if (newValue < min) min = newValue;
			if (newValue > max) max = newValue;
		}
	}

	// 변환 시 상수값을 미리 계산
	constVal1 = (float)(255.0 / (max - min));
	constVal2 = (float)(-255.0*min / (max - min));
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			// [min, max] 사이의 값을 [0, 255] 값으로 변환
			newValue = pImgPrewittX[i*width + j];
			newValue = constVal1 * newValue + constVal2;
			m_OutImg[i][j] = (BYTE)newValue;
		}
	}

	// 동적 할당 메모리 삭제
	delete[] pImgPrewittX;
	delete[] pImgPrewittY;
}

// 에지 검출 (Sobel)
void CSN2020111396Doc::EdgeSobel(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	int MaskSobelX[3][3] = { {-1,0,1}, {-2,0,2}, {-1,0,1} };
	int MaskSobelY[3][3] = { {-1,-2,-1}, {0,0,0}, {1,2,1} };

	int heightm1 = height - 1, widthm1 = width - 1;
	int mr, mc, i, j, newValue;
	int *pImgSobelX, *pImgSobelY;
	int min, max, where;
	float constVal1, constVal2;

	// 정수값을 갖는 이미지 동적 메모리 할당
	pImgSobelX = new int[height*width];
	pImgSobelY = new int[height*width];

	// 결과 이미지 0으로 초기화
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			m_OutImg[i][j] = 0;
			where = i * width + j;
			pImgSobelX[where] = 0;
			pImgSobelY[where] = 0;
		}
	}

	// X 방향 에지 강도 계산
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = 0; // 0으로 초기화
			for (mr = 0; mr < 3; mr++)
			{
				for (mc = 0; mc < 3; mc++)
				{
					newValue += (MaskSobelX[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
				}
			}
			pImgSobelX[i*width + j] = newValue;
		}
	}

	// Y 방향 에지 강도 계산
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = 0; // 0으로 초기화
			for (mr = 0; mr < 3; mr++)
			{
				for (mc = 0; mc < 3; mc++)
				{
					newValue += (MaskSobelY[mr][mc] * m_InImg[i + mr - 1][j + mc - 1]);
				}
			}
			pImgSobelY[i*width + j] = newValue;
		}
	}

	// 에지 강도 계산 절대값(X) + 절대값(Y) 후 pImgSobelX[]에 저장
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			where = i * width + j;
			constVal1 = pImgSobelX[where];
			constVal2 = pImgSobelY[where];
			if (constVal1 < 0) constVal1 = -constVal1;
			if (constVal2 < 0) constVal2 = -constVal2;
			pImgSobelX[where] = constVal1 + constVal2;
		}
	}

	// 디스플레이를 위해 0에서 255 사이로 값의 범위를 매핑
	// 이를 위해 먼저 최대, 최소값을 찾은 후 이를 이용하여 매핑한다
	min = (int)10e10;
	max = (int)-10e10;
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = pImgSobelX[i*width + j];
			if (newValue < min) min = newValue;
			if (newValue > max) max = newValue;
		}
	}

	// 변환 시 상수값을 미리 계산
	constVal1 = (float)(255.0 / (max - min));
	constVal2 = (float)(-255.0*min / (max - min));
	for (i = 1; i < heightm1; i++)
	{
		for (j = 1; j < widthm1; j++)
		{
			newValue = pImgSobelX[i*width + j];
			newValue = constVal1 * newValue + constVal2;
			m_OutImg[i][j] = (BYTE)newValue;
		}
	}

	// 동적 할당 메모리 해제
	delete[] pImgSobelX;
	delete[] pImgSobelY;
}


void CSN2020111396Doc::ZoomOut(int height, int width, float zoomoutfactor)
{
	// TODO: 여기에 구현 코드 추가.
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int r, c; // 타겟 이미지 좌표
	float r_orgr, r_orgc; // 원 이미지 상의 해당 좌표 (실수값)
	int i_orgr, i_orgc; // 원 이미지 상의 해당 좌표 (정수값)
	float sr, sc; // 예 1.24 - 1 = 0.24
	float l1, l2, l3, l4;

	for (r = 0; r < height; r++)
	{
		for (c = 0; c < width; c++)
		{
			r_orgr = r / zoomoutfactor;
			r_orgc = c / zoomoutfactor;
			i_orgr = floor(r_orgr);
			i_orgc = floor(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;

			// 범위 조사
			// 원 이미지의 범위를 벗어나는 경우 0값 할당
			if (i_orgr<0 || i_orgr>heightm1 || i_orgc<0 || i_orgc>widthm1)
			{
				m_OutImg[r][c] = 0;
			}

			// 원 이미지의 범위 내에 존재 이중 선형 보간 수행
			else
			{
				l1 = (float)m_InImg[i_orgr][i_orgc]; // (org_r, org_c)
				l2 = (float)m_InImg[i_orgr][i_orgc + 1]; // (org_r, org_c + 1)
				l3 = (float)m_InImg[i_orgr + 1][i_orgc + 1]; // (org_r + 1, org_c + 1)
				l4 = (float)m_InImg[i_orgr + 1][i_orgc]; // (org_r + 1, org_c)

				// 이중 선형 보간을 통한 새로운 밝기값 계산
				m_OutImg[r][c] = (BYTE)(l1*(1 - sc)*(1 - sr) + l2 * sc*(1 - sr) + l3 * sc*sr + l4 * (1 - sc)*sr);
			}
		}
	}
}


void CSN2020111396Doc::ZoomIn(int height, int width, float zoomoutfactor)
{
	// TODO: 여기에 구현 코드 추가.
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int r, c; // 타겟 이미지 좌표
	float r_orgr, r_orgc; // 원 이미지 상의 해당 좌표 (실수값)
	int i_orgr, i_orgc; // 원 이미지 상의 해당 좌표 (정수값)
	float sr, sc; // 예 1.24 - 1 = 0.24
	float l1, l2, l3, l4;

	for (r = 0; r < height; r++)
	{
		for (c = 0; c < width; c++)
		{
			r_orgr = r / zoomoutfactor;
			r_orgc = c / zoomoutfactor;
			i_orgr = floor(r_orgr);
			i_orgc = floor(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;

			// 범위 조사
			// 원 이미지의 범위를 벗어나는 경우 0값 할당
			if (i_orgr<0 || i_orgr>heightm1 || i_orgc<0 || i_orgc>widthm1)
			{
				m_OutImg[r][c] = 0;
			}

			// 원 이미지의 범위 내에 존재 이중 선형 보간 수행
			else
			{
				l1 = (float)m_InImg[i_orgr][i_orgc]; // (org_r, org_c)
				l2 = (float)m_InImg[i_orgr][i_orgc + 1]; // (org_r, org_c + 1)
				l3 = (float)m_InImg[i_orgr + 1][i_orgc + 1]; // (org_r + 1, org_c + 1)
				l4 = (float)m_InImg[i_orgr + 1][i_orgc]; // (org_r + 1, org_c)

				// 이중 선형 보간을 통한 새로운 밝기값 계산
				m_OutImg[r][c] = (BYTE)(l1*(1 - sc)*(1 - sr) + l2 * sc*(1 - sr) + l3 * sc*sr + l4 * (1 - sc)*sr);
			}
		}
	}
}


void CSN2020111396Doc::Rotation(int height, int width, int center_r, int center_c, float rotationAngle)
{
	// TODO: 여기에 구현 코드 추가.
	int heightm1 = height - 1; // 계산의 중복을 피하기 위해 사용
	int widthm1 = width - 1; // 계산의 중복을 피하기 위해 사용
	int r, c; // 타겟 이미지 좌표
	float r_orgr, r_orgc; // 원 이미지 상의 해당 좌표 (실수값)
	int i_orgr, i_orgc; // 원 이미지 상의 해당 좌표 (정수값)
	float sr, sc; 
	float l1, l2, l3, l4;
	float cosAngle, sinAngle;
	float rotationAngleRad = (float)(rotationAngle*3.14159265/180); // angle->radian으로 변환

	for (r = 0; r < height; r++)
	{
		for (c = 0; c < width; c++)
		{
			cosAngle = (float)cos(rotationAngleRad);
			sinAngle = (float)sin(rotationAngleRad);
			// 회전 전의 원 이미지 상의 좌표 구함
			r_orgr = -sinAngle * (c - center_c) + cosAngle * (r - center_r) + center_r;
			r_orgc = cosAngle * (c - center_c) + sinAngle * (r - center_r) + center_c;
			i_orgr = floor(r_orgr);
			i_orgc = floor(r_orgc);
			sr = r_orgr - i_orgr;
			sc = r_orgc - i_orgc;

			// 범위 조사
			// 원 이미지의 범위를 벗어나는 경우 0값 할당
			if (i_orgr<0 || i_orgr>heightm1 || i_orgc<0 || i_orgc>widthm1)
			{
				m_OutImg[r][c] = 0;
			}
			// 원 이미지의 범위 내에 존재 이중 선형 보간 수행
			else
			{
				l1 = (float)m_InImg[i_orgr][i_orgc];
				l2 = (float)m_InImg[i_orgr][i_orgc + 1];
				l3 = (float)m_InImg[i_orgr + 1][i_orgc + 1];
				l4 = (float)m_InImg[i_orgr + 1][i_orgc];

				// 이중 선형 보간을 통한 새로운 밝기값 계산
				m_OutImg[r][c] = (BYTE)(l1*(1 - sc)*(1 - sr) + l2 * sc*(1 - sr) + l3 * sc*sr + l4 * (1 - sc)*sr);
			}
		}
	}
}


void CSN2020111396Doc::Rotation90(int height, int width)
{
	// TODO: 여기에 구현 코드 추가.
	int r, c; // 타겟 이미지 좌표
	int i_orgr, i_orgc; // 원 이미지 상의 해당 좌표 (정수값)

	for (r = 0; r < height; r++)
	{
		for (c = 0; c < width; c++)
		{
			i_orgc = r;
			i_orgr = height - 1 - c;
			m_OutImg[r][c] = m_InImg[i_orgr][i_orgc];
		}
	}
}


void CSN2020111396Doc::Translation(int height, int width, int dx, int dy)
{
	// TODO: 여기에 구현 코드 추가.
	int heightm1 = height - 1;
	int widthm1 = width - 1;
	int r, c; // 타겟 이미지 좌표
	int i_orgc, i_orgr; // 원 이미지 상의 해당 좌표 (정수값)

	for (r = 0; r < height; r++)
	{
		for (c = 0; c < width; c++)
		{
			i_orgc = c - dx;
			i_orgr = r - dy;
			if (i_orgr<0 || i_orgr>heightm1 || i_orgc<0 || i_orgc > widthm1) m_OutImg[r][c] = 0;
			else m_OutImg[r][c] = m_InImg[i_orgr][i_orgc];
		}
	}
}