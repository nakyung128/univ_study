// CBtnCntrlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "SN2020111396.h"
#include "CBinCntrlDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SN2020111396Doc.h"


// CBtnCntrlDlg 대화 상자

IMPLEMENT_DYNAMIC(CBinCntrlDlg, CDialogEx)

CBinCntrlDlg::CBinCntrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_binValDisp(0)
{

}

CBinCntrlDlg::~CBinCntrlDlg()
{
}

void CBinCntrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_binValDisp);
	DDX_Control(pDX, IDC_SLIDER1, m_ctrlSlider);
}


BEGIN_MESSAGE_MAP(CBinCntrlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CBinCntrlDlg::OnBNApply)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CBinCntrlDlg::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CBtnCntrlDlg 메시지 처리기


void CBinCntrlDlg::OnBNApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK(); // 대화박스 종결
}


BOOL CBinCntrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_ctrlSlider.SetRange(0, 255); // 슬라이드바 값의 범위 설정
	m_ctrlSlider.SetPos(100); // 슬라이드바의 초기 상태 설정

	m_binValDisp = m_ctrlSlider.GetPos(); // 현재 설정되어 있는 값을 잡아온다
	UpdateData(FALSE); // 설정된 데이터값으로 다이얼로그 박스의 표시부 갱신

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBinCntrlDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pFrame);
	CChildFrame *pChild = (CChildFrame*)pFrame->GetActiveFrame();
	ASSERT(pChild);
	CSN2020111396Doc *pDoc = (CSN2020111396Doc*)pChild->GetActiveDocument();
	ASSERT(pDoc);

	// 슬라이더의 현재 위치를 가져옴
	m_binValDisp = m_ctrlSlider.GetPos();
	UpdateData(FALSE); // 잡아온 데이터값으로 다이얼로그 박스의 표시부 갱신

	// 현재 활성화 도큐먼트 클래스 아래의 이치화 계산함수 호출
	pDoc->m_BinThres(256, 256, m_binValDisp); // 슬라이드 설정 이치화 계수치를 넘겨줌
	*pResult = 0;
}
