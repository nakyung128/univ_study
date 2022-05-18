#pragma once
#include <afxdockablepane.h>
#include "CHobbyCtrl.h"
class CTextOutPane :
    public CDockablePane
{
public:
    CHobbyCtrl m_ctrlHobby;
    DECLARE_MESSAGE_MAP()
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

