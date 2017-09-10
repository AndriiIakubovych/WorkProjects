// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "GraphExpImp.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_MENUSELECT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] = { IDS_STATUS_STRING };

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_StatusBar.Create(this);
	m_StatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	m_StatusBar.SetPaneInfo(0, IDS_STATUS_STRING, SBPS_NOBORDERS, GetSystemMetrics(SM_CXSCREEN));

	if (!m_ToolBar.CreateAdvToolBar(this, IDR_TOOLBAR, CAdvToolBar::ADVT_COLOR_256, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC))
		return -1;      
	m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBar);
	LoadBarState(_T("AdvToolBar"));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	cs.style &= ~(LONG) FWS_ADDTOTITLE;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu) 
{
	CFrameWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);
	
	// TODO: Add your message handler code here
	switch (nItemID)
	{
		case ID_OPERATIONS_CREATE_PROFILE:
		{
			m_StatusBar.SetPaneText(0, "������� ���������� ���� ��� �������� ������ �������", TRUE);
			break;
		}
		case ID_OPERATIONS_CREATE_FILE:
		{
			m_StatusBar.SetPaneText(0, "������� ���������� ���� ��� ���������� ����� � �������", TRUE);
			break;
		}
		case ID_OPERATIONS_CREATE_SAMPLE:
		{
			m_StatusBar.SetPaneText(0, "������� ���������� ���� ��� �������� ������� �� ������� �����������", TRUE);
			break;
		}
		case ID_OPERATIONS_EDIT:
		{
			m_StatusBar.SetPaneText(0, "������� ���������� ���� ��� �������������� ����������� ������� ��� �����", TRUE);
			break;
		}
		case ID_OPERATIONS_DELETE:
		{
			m_StatusBar.SetPaneText(0, "������� ���������� ������� ��� ����", TRUE);
			break;
		}
		case ID_OPERATIONS_EXECUTE:
		{
			m_StatusBar.SetPaneText(0, "��������� ��������������� �������� � ����������� �� ���� �������", TRUE);
			break;
		}
		case ID_APP_EXIT:
		{
			m_StatusBar.SetPaneText(0, "����� �� ���������", TRUE);
			break;
		}
		case ID_PROGRAM_HELP:
		{
			m_StatusBar.SetPaneText(0, "������� ������������ �� ������ ���������", TRUE);
			break;
		}
		case ID_PROGRAM_ABOUT:
		{
			m_StatusBar.SetPaneText(0, "������� ���������� ���� � ����������� �� ������ � ���������� ������ ���������", TRUE);
			break;
		}
		default:
		{
			m_StatusBar.SetPaneText(0, "������", TRUE);
			break;
		}
	}
}
