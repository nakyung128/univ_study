﻿
// SN2020111396Doc.h: CSN2020111396Doc 클래스의 인터페이스
//


#pragma once


class CSN2020111396Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CSN2020111396Doc() noexcept;
	DECLARE_DYNCREATE(CSN2020111396Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CSN2020111396Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char m_InImg[256][256];
	unsigned char m_OutImg[256][256];
	void TwoImgLoad();
	unsigned char m_InImg1[256][256];
	unsigned char m_InImg2[256][256];
	int m_HistoArr[256];
	void m_ImgHisto(int height, int width);
	void m_BinThres(int height, int width, int binThres);
	int temp[256][256];
	void m_bitSlicing(int height, int width, int bit);
	void m_HistoEqual(int height, int width);
	void ImageBlend(int height, int width, int alpha);
	void m_HistoStretch(int height, int width);
};
