#include "pch.h"
#include "CTextOutPane.h"
#include "resource.h"
BEGIN_MESSAGE_MAP(CTextOutPane, CDockablePane)
	ON_WM_CREATE()
END_MESSAGE_MAP()


int CTextOutPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	if (!m_ctrlHobby.Create(IDD_DIALOG1, this))
	{
		TRACE0("문자열 출력 윈도우를 만들지 못했습니다.\n");
		return -1;
	}
	m_ctrlHobby.ShowWindow(SW_SHOW);

	return 0;
}
