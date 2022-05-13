// CBlendCtrlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "SN2020111396.h"
#include "CBlendCtrlDlg.h"
#include "afxdialogex.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SN2020111396Doc.h"


// CBlendCtrlDlg 대화 상자

IMPLEMENT_DYNAMIC(CBlendCtrlDlg, CDialogEx)

CBlendCtrlDlg::CBlendCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_binBlendDisp(0)
{

}

CBlendCtrlDlg::~CBlendCtrlDlg()
{
}

void CBlendCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_binBlendDisp);
	DDX_Control(pDX, IDC_SLIDER1, m_blendSlider);
}


BEGIN_MESSAGE_MAP(CBlendCtrlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CBlendCtrlDlg::OnBNClicked)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CBlendCtrlDlg::OnNMCustomdrawSlider1)
	ON_EN_CHANGE(IDC_EDIT1, &CBlendCtrlDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CBlendCtrlDlg 메시지 처리기


void CBlendCtrlDlg::OnBNClicked()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	OnOK(); // 대화박스 종결
}


BOOL CBlendCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_blendSlider.SetRange(0, 255); // 슬라이드바의 값 범위 설정
	m_blendSlider.SetPos(128); // 슬라이드바의 초기 상태 설정

	m_binBlendDisp = m_blendSlider.GetPos(); // 현재 설정되어 있는 값을 잡아온다.
	UpdateData(FALSE); // 설정된 데이터값으로 다이얼로그박스의 표시부 갱신

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBlendCtrlDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	ASSERT(pFrame);
	CChildFrame *pChild = (CChildFrame*)pFrame->GetActiveFrame();
	ASSERT(pChild);
	CSN2020111396Doc *pDoc = (CSN2020111396Doc*)pChild->GetActiveDocument();
	ASSERT(pDoc);

	// Slider의 현재 위치를 잡아온다.
	m_binBlendDisp = m_blendSlider.GetPos();
	UpdateData(FALSE); // 잡아온 데이터값으로 다이얼로그 박스의 표시부 갱신

	// 현재 활성화 도큐먼트 클래스 아래의 함수 호출
	pDoc->ImageBlend(256, 256, m_binBlendDisp); // 슬라이드 설정 값 넘겨줌
	*pResult = 0;
}


void CBlendCtrlDlg::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (UpdateData(TRUE)) m_blendSlider.SetPos(m_binBlendDisp);
}
