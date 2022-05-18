#pragma once


// CHobbyCtrl 대화 상자

class CHobbyCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(CHobbyCtrl)

public:
	CHobbyCtrl(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CHobbyCtrl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnLbnSelchangeListHobby();
	CListBox m_listHobby;
	CComboBox m_cbSex;
	CString m_strName;
	virtual BOOL OnInitDialog();
	bool m_bSex; // 라디오 버튼 선택 나타내는 변수
	bool m_bChecked[3]; // 체크 박스 선택 나타내는 변수
	afx_msg void OnSelchangeComboSex();
//	afx_msg void OnClickedRadioMale();
	afx_msg void OnRadioFemale();
	afx_msg void OnRadioMale();
	afx_msg void OnSelchangeListHobby();
	afx_msg void OnClickedCheckReading();
	afx_msg void OnClickedCheckFishing();
	afx_msg void OnClickedCheckSports();
	afx_msg void OnClickedButtonResult();
};
