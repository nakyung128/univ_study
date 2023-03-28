#pragma once


// CBlendCtrlDlg 대화 상자

class CBlendCtrlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBlendCtrlDlg)

public:
	CBlendCtrlDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBlendCtrlDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBNClicked();
	int m_binBlendDisp;
	CSliderCtrl m_blendSlider;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnEnChangeEdit1();
};
