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

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.
	if (!m_ctrlHobby.Create(IDD_DIALOG1, this))
	{
		TRACE0("���ڿ� ��� �����츦 ������ ���߽��ϴ�.\n");
		return -1;
	}
	m_ctrlHobby.ShowWindow(SW_SHOW);

	return 0;
}
