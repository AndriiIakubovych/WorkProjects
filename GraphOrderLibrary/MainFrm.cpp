
// MainFrm.cpp : реализация класса CMainFrame
//

#include "stdafx.h"
#include "GraphOrder.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

static UINT indicators[] = { IDS_STATUS_STRING };

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
	ON_WM_CREATE()
	ON_WM_MENUSELECT()
END_MESSAGE_MAP()

// создание/уничтожение CMainFrame

CMainFrame::CMainFrame()
{
	// TODO: добавьте код инициализации члена
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_ToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) || !m_ToolBar.LoadToolBar(IDR_TOOLBAR))
		return -1;
	if (m_ImageList.Create(32, 32, ILC_MASK | ILC_COLOR24, 0, 0))
	{
		CBitmap bitmap;
		bitmap.LoadBitmap(IDB_TOOLBAR);
		m_ImageList.Add(&bitmap, RGB(240, 240, 240));
	}
	m_ToolBar.GetToolBarCtrl().SetImageList(&m_ImageList);
	m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_ToolBar);

	m_StatusBar.Create(this);
	m_StatusBar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	m_StatusBar.SetPaneInfo(0, IDS_STATUS_STRING, SBPS_NOBORDERS, GetSystemMetrics(SM_CXSCREEN));
	m_StatusBar.SetPaneText(0, "Готово", TRUE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CMDIFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return TRUE;
}

// диагностика CMainFrame

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CMDIFrameWnd::Dump(dc);
}
#endif //_DEBUG


// обработчики сообщений CMainFrame

void CMainFrame::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	CMDIFrameWnd::OnMenuSelect(nItemID, nFlags, hSysMenu);

	// TODO: Add your message handler code here
	switch (nItemID)
	{
		case ID_FILE_PRINT_SETUP:
			m_StatusBar.SetPaneText(0, "Открыть диалоговое окно для настройки параметров принтера и печати", TRUE);
			break;
		case ID_FILE_PRINT_PREVIEW:
			m_StatusBar.SetPaneText(0, "Отобразить печатаемую страницу", TRUE);
			break;
		case ID_FILE_PRINT:
			m_StatusBar.SetPaneText(0, "Открыть диалоговое окно для печати содержимого окна", TRUE);
			break;
		case ID_VIEW_ENLARGE:
			m_StatusBar.SetPaneText(0, "Увеличить область графика", TRUE);
			break;
		case ID_VIEW_REDUCE:
			m_StatusBar.SetPaneText(0, "Уменьшить область графика", TRUE);
			break;
		case ID_VIEW_GENERAL_SETTINGS:
			m_StatusBar.SetPaneText(0, "Открыть диалоговое окно для настройки параметров отображения и цвета", TRUE);
			break;
		case ID_VIEW_ADDITIONAL_SETTINGS:
			m_StatusBar.SetPaneText(0, "Открыть диалоговое окно для настройки параметров интервала", TRUE);
			break;
		case ID_VIEW_NEXT:
			m_StatusBar.SetPaneText(0, "Сдвинуть дату начала периода вперёд на заданный интервал", TRUE);
			break;
		case ID_VIEW_BACK:
			m_StatusBar.SetPaneText(0, "Сдвинуть дату начала периода назад на заданный интервал", TRUE);
			break;
		case ID_APP_EXIT:
			m_StatusBar.SetPaneText(0, "Выйти из программы", TRUE);
			break;
		case ID_OPEN_HELP:
			m_StatusBar.SetPaneText(0, "Открыть документацию по данной программе", TRUE);
			break;
		case ID_OPEN_ABOUT:
			m_StatusBar.SetPaneText(0, "Открыть диалоговое окно с информацией об авторе и назначении данной программы", TRUE);
			break;
		default:
			m_StatusBar.SetPaneText(0, "Готово", TRUE);
			break;
	}
}