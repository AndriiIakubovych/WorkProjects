
// GraphOrder.h : ������� ���� ��������� ��� ���������� GraphOrder
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"       // �������� �������
#include "MainFrm.h"


// CGraphOrderApp:
// � ���������� ������� ������ ��. GraphOrder.cpp
//

class CGraphOrderApp : public CWinApp
{
public:
	CMultiDocTemplate* pDocTemplate;
	CMainFrame* pMainFrame;
	CWnd* Wnd;

// ���������������
public:

// ����������
	DECLARE_MESSAGE_MAP()
};

extern CGraphOrderApp theApp;
