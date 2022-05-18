// CHobbyCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "Practice5_2020111396.h"
#include "CHobbyCtrl.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "Practice5_2020111396View.h"


// CHobbyCtrl 대화 상자

IMPLEMENT_DYNAMIC(CHobbyCtrl, CDialogEx)

CHobbyCtrl::CHobbyCtrl(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_strName(_T(""))
	, m_bSex(true)

{
	m_bChecked[0] = m_bChecked[1] = m_bChecked[2] = false;
}

CHobbyCtrl::~CHobbyCtrl()
{
}

void CHobbyCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HOBBY, m_listHobby);
	DDX_Control(pDX, IDC_COMBO_SEX, m_cbSex);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
}


BEGIN_MESSAGE_MAP(CHobbyCtrl, CDialogEx)
ON_CBN_SELCHANGE(IDC_COMBO_SEX, &CHobbyCtrl::OnSelchangeComboSex)
ON_COMMAND(IDC_RADIO_FEMALE, &CHobbyCtrl::OnRadioFemale)
ON_COMMAND(IDC_RADIO_MALE, &CHobbyCtrl::OnRadioMale)
ON_LBN_SELCHANGE(IDC_LIST_HOBBY, &CHobbyCtrl::OnSelchangeListHobby)
ON_BN_CLICKED(IDC_CHECK_READING, &CHobbyCtrl::OnClickedCheckReading)
ON_BN_CLICKED(IDC_CHECK_FISHING, &CHobbyCtrl::OnClickedCheckFishing)
ON_BN_CLICKED(IDC_CHECK_SPORTS, &CHobbyCtrl::OnClickedCheckSports)
ON_BN_CLICKED(IDC_BUTTON_RESULT, &CHobbyCtrl::OnClickedButtonResult)
END_MESSAGE_MAP()


// CHobbyCtrl 메시지 처리기



BOOL CHobbyCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// 리스트 박스 초기화
	m_listHobby.AddString(_T("독서"));
	m_listHobby.AddString(_T("낚시"));
	m_listHobby.AddString(_T("운동"));

	// 콤보 박스, 라디오 버튼 초기화
	m_cbSex.SetCurSel(0);
	CButton* pCheck = (CButton*)GetDlgItem(IDC_RADIO_MALE);
	pCheck->SetCheck(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CHobbyCtrl::OnSelchangeComboSex()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CButton* mCheck = (CButton*)GetDlgItem(IDC_RADIO_MALE);
	CButton* fCheck = (CButton*)GetDlgItem(IDC_RADIO_FEMALE);
	if (m_cbSex.GetCurSel() == 0)
	{
		fCheck->SetCheck(FALSE);
		mCheck->SetCheck(TRUE);
		m_bSex = true;
	}
	else
	{
		mCheck->SetCheck(FALSE);
		fCheck->SetCheck(TRUE);
		m_bSex = false;
	}
}

void CHobbyCtrl::OnRadioMale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_cbSex.SetCurSel(0);
	m_bSex = true;
}

void CHobbyCtrl::OnRadioFemale()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_cbSex.SetCurSel(1);
	m_bSex = false;
}


void CHobbyCtrl::OnSelchangeListHobby()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CButton* Check1 = (CButton*)GetDlgItem(IDC_CHECK_READING);
	CButton* Check2 = (CButton*)GetDlgItem(IDC_CHECK_FISHING);
	CButton* Check3 = (CButton*)GetDlgItem(IDC_CHECK_SPORTS);
	int index = m_listHobby.GetCurSel();

	switch (index)
	{
	case 0:
		if (Check1->GetCheck() == false)
		{
			Check1->SetCheck(1);
			m_bChecked[0] = true;
		}
		else
		{
			Check1->SetCheck(0);
			m_bChecked[0] = false;
		}
		break;
	case 1:
		if (Check2->GetCheck() == false)
		{
			Check2->SetCheck(1);
			m_bChecked[1] = true;
		}
		else
		{
			Check2->SetCheck(0);
			m_bChecked[1] = false;
		}
		break;
	case 2:
		if (Check3->GetCheck() == false)
		{
			Check3->SetCheck(1);
			m_bChecked[2] = true;
		}
		else
		{
			Check3->SetCheck(0);
			m_bChecked[2] = false;
		}
		break;
	}
}

void CHobbyCtrl::OnClickedCheckReading()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CButton* Check1 = (CButton*)GetDlgItem(IDC_CHECK_READING);

	if (m_bChecked[0] == false)
	{
		Check1->SetCheck(1);
		m_bChecked[0] = true;
		m_listHobby.SetSel(0, true);
	}
	else
	{
		Check1->SetCheck(0);
		m_bChecked[0] = false;
		m_listHobby.SetSel(0, false);
	}
}


void CHobbyCtrl::OnClickedCheckFishing()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CButton* Check2 = (CButton*)GetDlgItem(IDC_CHECK_FISHING);
	if (m_bChecked[1] == false)
	{
		Check2->SetCheck(1);
		m_bChecked[1] = true;
		m_listHobby.SetSel(1, true);
	}
	else
	{
		Check2->SetCheck(0);
		m_bChecked[1] = false;
		m_listHobby.SetSel(1, false);
	}
}


void CHobbyCtrl::OnClickedCheckSports()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CButton* Check3 = (CButton*)GetDlgItem(IDC_CHECK_SPORTS);
	if (m_bChecked[2] == false)
	{
		Check3->SetCheck(1);
		m_bChecked[2] = true;
		m_listHobby.SetSel(2, true);
	}
	else
	{
		Check3->SetCheck(0);
		m_bChecked[2] = false;
		m_listHobby.SetSel(2, false);
	}
}


void CHobbyCtrl::OnClickedButtonResult()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CPractice52020111396View* pView = (CPractice52020111396View*)pFrame->GetActiveView();

	GetDlgItemText(IDC_EDIT_NAME, pView->m_strName);

	if (m_bSex == true) GetDlgItemText(IDC_RADIO_MALE, pView->m_strSex);
	else GetDlgItemText(IDC_RADIO_FEMALE, pView->m_strSex);

	pView->m_strHobby.Empty();
	for (int i = 0; i < 3; i++)
	{
		if (m_bChecked[i] == true)
		{
			CString str;
			m_listHobby.GetText(i, str);
			pView->m_strHobby += str + _T(" ");
		}
	}
	
	if (pView->m_strName.IsEmpty()) AfxMessageBox(_T("이름을 입력하세요."));
	pView->Invalidate();
}
