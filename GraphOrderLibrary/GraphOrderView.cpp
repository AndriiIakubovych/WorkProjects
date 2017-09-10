
// GraphOrderView.cpp : реализация класса CGraphOrderView
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "GraphOrder.h"
#endif

#include "GraphOrderDoc.h"
#include "GraphOrderView.h"

#include "MetaTableRead.h"
#include "NregionRead.h"
#include "OrdAllRead.h"
#include "CodTechRead.h"
#include "ServiceRead.h"
#include "AdmRead.h"
#include "DescrRead.h"
#include "DescrdocRead.h"
#include "ListdocsRead.h"

#include "NameAdr.h"

#include "GeneralSettingsDlg.h"
#include "AdditionalSettingsDlg.h"
#include "ChooseOrderDlg.h"
#include "AboutProgramDlg.h"

#include "OrderSay.h"
#include "OrderSayDoc.h"
#include "OrderMainFrm.h"
#include "OrderSayView.h"

#pragma comment(lib, "ParSear.lib")
#include "I:\CiWin5\bibuni6\ParseFull.h"

#pragma comment(lib, "OutGraf.lib")
#include "I:\CiWin5\bibuni6\grafstr.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGraphOrderView

HBITMAP Create_hBitmap(HDC, int, int);
HBITMAP CreateClientWindwowBitmap(HWND);

CString IniFile, StrConnectionOrdAll, StrConnectionArea, StrConnectionDescrcol, StrConnectionDescrdoc, WcomtxWay, TableName = "ordall";
int WorkspaceWidth, CountOnDrawCall = 0, ViewGrid, ViewLegend, DurationPeriod, ValueStep, WidthColumn, CountEnlarge = 0, CountMove = 0, CurrentNumberOrder = 0, NumberFindOrder;
CTime DateBeginPeriod, DateEndPeriod;
LOGFONT lfh, lfv, lfn;
CFont HorizontalInscriptionFont, VerticalInscriptionFont, NameFont;
COLORREF fci, fcn;
CDialog* lp;
HBITMAP hBitmap;
CBitmap m_bmpBitmap;
bool SaveBitmap = false;
bool OpenInformationOrder = false;
TOOLINFO ti;
HWND hwndTT;
CMenu* m_Menu;

bool Obman = false;
bool HasRegiServ = false;

BOOL ViewReduce = FALSE;

vector <int> NumberOrder;
vector <int> CodOrder;
vector <int> yy;
vector <CTime> DateTimeBegin;
vector <CTime> DateTimeEnd;
vector <int> StateOrder;
vector <int> CodsClass;
vector <CString> StateName;
vector <int> Red;
vector <int> Green;
vector <int> Blue;
vector <int> Coordinates;
vector <int> ServiceNumber;
vector <int> ServiceNumber2;
vector <int> NumberService;
vector <CString> NameService;
vector <int> AdmNumber;
vector <int> NumberAdm;
vector <CString> NameAdm;
vector <CString> Address;
vector <int> CodDoc;
vector <int> CodDocDescr;
vector <CString> SearchOperations;
vector <CString> SearchOperationsDescr;
vector <int> FindOrder;
vector <int> FindOrderYear;
vector <int> FindOrderAdm;
vector <int> FindOrderService;
vector <CString> FindOrderAddress;
vector <CString> FindOrderStr;

typedef BOOL(_cdecl *PFN_OrderView)(long, CArray<bool, bool>&, CArray<CString, CString>&);
typedef BOOL(_cdecl *PFN_OrderOperation)(long);

IMPLEMENT_DYNCREATE(CGraphOrderView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphOrderView, CScrollView)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_VIEW_ENLARGE, OnViewEnlarge)
	ON_COMMAND(ID_VIEW_REDUCE, OnViewReduce)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REDUCE, OnUpdateViewReduce)
	ON_COMMAND(ID_VIEW_GENERAL_SETTINGS, OnViewGeneralSettings)
	ON_COMMAND(ID_VIEW_ADDITIONAL_SETTINGS, OnViewAdditionalSettings)
	ON_COMMAND(ID_VIEW_NEXT, OnViewNext)
	ON_COMMAND(ID_VIEW_BACK, OnViewBack)
	ON_COMMAND(ID_POPUP_OPEN_ORDER, OnPopupOpenOrder)
	ON_COMMAND_RANGE(ID_POPUP_OPERATION_ORDER, ID_POPUP_OPERATION_ORDER + 24, OnPopupOperationOrder)
	ON_COMMAND_RANGE(ID_POPUP_SEARCH_ORDER, ID_POPUP_SEARCH_ORDER + 30, OnPopupSearchOrder)
	ON_COMMAND(ID_POPUP_REGISTR_ORDER, OnPopupRegistrOrder)
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_COMMAND(ID_INCREASE, OnViewEnlarge)
	ON_COMMAND(ID_REDUCE, OnViewReduce)
	ON_UPDATE_COMMAND_UI(ID_REDUCE, OnUpdateViewReduce)
	ON_COMMAND(ID_GENERAL_SETTINGS, OnViewGeneralSettings)
	ON_COMMAND(ID_ADDITIONAL_SETTINGS, OnViewAdditionalSettings)
	ON_COMMAND(ID_NEXT, OnViewNext)
	ON_COMMAND(ID_BACK, OnViewBack)
	ON_COMMAND(ID_EXIT, OnAppExit)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_OPEN_ABOUT, &CGraphOrderView::OnOpenAbout)
	ON_WM_DESTROY()
	ON_WM_KILLFOCUS()
END_MESSAGE_MAP()

// создание/уничтожение CGraphOrderView

CGraphOrderView::CGraphOrderView()
{
	// TODO: добавьте код создания

}

CGraphOrderView::~CGraphOrderView()
{
}

BOOL CGraphOrderView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	char buffer[MAX_PATH];
	CString WorkFolder;
	GetCurrentDirectory(MAX_PATH, buffer);
	WorkFolder = buffer;
	if (_access(WorkFolder + "\\Svisor.ini", 0))
	{
		CFileDialog fd(true);
		fd.m_ofn.lpstrFilter = "Svisor.ini\0Svisor.ini";
		if (fd.DoModal() == IDOK)
		{
			IniFile = fd.m_ofn.lpstrFile;
			return CScrollView::PreCreateWindow(cs);
		}
		else
		{
			PostQuitMessage(0);
			return FALSE;
		}
	}
	else
	{
		IniFile = WorkFolder + "\\Svisor.ini";
		return CScrollView::PreCreateWindow(cs);
	}
}

// рисование CGraphOrderView

void CGraphOrderView::OnDraw(CDC* pDC)
{
	CGraphOrderDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: добавьте здесь код отрисовки для собственных данных
	CPaintDC paintDC(this);
	int MainScopeWidth, MainScopeHeight, Space = 30, RightSpace, IntervalX, IntervalY, WidthOrderName, WidthText, HeightText, ChartBegin, NumberColor = 0;
	double BeginCountMinutes, EndCountMinutes, Fractional, Res;
	char buffer[MAX_PATH];
	bool Open = false;
	CTimeSpan ChangeHours;
	CString LongestNameState;
	CRect Rect;
	CTime Date;
	CFont* UsualFont;
	GetClientRect(&Rect);
	CPen MainScopePen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen DivisionPen(PS_DASH, 1, RGB(0, 0, 0));
	CPen ChartPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen ChartPen1(PS_SOLID, 1, RGB(0, 0, 0));
	CPen ChartPen2(PS_SOLID, 1, RGB(0, 0, 0));
	CBrush* ChartBrush;
	UsualFont = pDC->SelectObject(&VerticalInscriptionFont);
	WidthText = pDC->GetTextExtent(DateBeginPeriod.Format("%d.%m.%y %H")).cx;
	HeightText = pDC->GetTextExtent(DateBeginPeriod.Format("%d.%m.%y %H")).cy;
	pDC->SelectObject(UsualFont);
	UsualFont = pDC->SelectObject(&NameFont);
	for (int i = 0; i < StateName.size(); i++)
		if (StateName[i].GetLength() > LongestNameState.GetLength())
			LongestNameState = StateName[i];
	if (CountEnlarge == 0)
		WorkspaceWidth = Rect.right;
	if (CountOnDrawCall == 0)
		OnInitialUpdate();
	if (ViewLegend == 1)
		RightSpace = WorkspaceWidth - Space - pDC->GetTextExtent(LongestNameState).cx - HeightText / 2 - HeightText - HeightText * 2;
	else
		RightSpace = WorkspaceWidth - Space;
	pDC->SelectObject(UsualFont);
	UsualFont = pDC->SelectObject(&VerticalInscriptionFont);
	pDC->SetTextColor(fci);
	if (NumberOrder.size() > 0)
		sprintf_s(buffer, "%i", NumberOrder[NumberOrder.size() - 1]);
	else
		sprintf_s(buffer, "%i", "");
	WidthOrderName = paintDC.GetTextExtent(buffer).cx;
	MainScopeWidth = RightSpace - HeightText / 2 - WidthText - Space;
	MainScopeHeight = Rect.bottom - Space * 2 - WidthOrderName - HeightText / 2;
	pDC->SelectObject(MainScopePen);
	pDC->Rectangle(WidthText + Space + HeightText / 2, Space, RightSpace, Rect.bottom - Space - WidthOrderName - HeightText / 2);
	IntervalX = WidthText + Space + HeightText / 2;
	for (int i = 0; i < NumberOrder.size(); i++)
	{
		for (int j = 0; j < CodsClass.size(); j++)
			if (CodsClass[j] == StateOrder[i])
			{
				NumberColor = j;
				if ((StateName[NumberColor] != "ЗАКРЫТА" && StateName[NumberColor] != "закрыта") || (DateTimeBegin[i] > DateTimeEnd[i]))
					Open = true;
				else
					Open = false;
				break;
			}
		/*if (Fractional >= 0.5)
			Res += 1;*/
		//sprintf(buffer, "%i %i %f", MainScopeWidth, NumberOrder.size(), Fractional);
		//MessageBox(buffer, "", MB_ICONINFORMATION);
		Res = double(MainScopeWidth) / double((NumberOrder.size()));
		if (i < MainScopeWidth - Res - (int)Res * NumberOrder.size())
			IntervalX = IntervalX + Res + 1;
		else
			IntervalX = IntervalX + Res;
		/*if (i % 2 == 0)
			IntervalX = IntervalX + Res;
		else
		{
			if ((NumberOrder.size() * Res) < MainScopeWidth)
			{
				if ((NumberOrder.size() * Res) < (MainScopeWidth - Res))
					IntervalX = IntervalX + Res + 1;
				else
					IntervalX = IntervalX + Res;
			}
			else
				IntervalX = IntervalX + Res - 1;
		}*/
		//sprintf(buffer, "%i %i %f", MainScopeWidth, NumberOrder.size(), Res);
		//MessageBox(buffer, "", MB_ICONINFORMATION);
		sprintf(buffer, "%i", CodOrder[i]);
		pDC->TextOut(IntervalX + paintDC.GetTextExtent(buffer).cy / 2, MainScopeHeight + Space + HeightText / 2, buffer);
		pDC->SelectObject(DivisionPen);
		BeginCountMinutes = (DateTimeBegin[i] - DateBeginPeriod).GetTotalMinutes();
		EndCountMinutes = (DateEndPeriod - DateBeginPeriod).GetTotalMinutes();
		IntervalY = (int)(Rect.bottom - Space - WidthOrderName - HeightText / 2 - (BeginCountMinutes / EndCountMinutes * MainScopeHeight));
		strcpy_s(buffer, DateTimeBegin[i].Format("%d.%m.%y %H"));
		pDC->MoveTo(IntervalX, Rect.bottom - Space - WidthOrderName - HeightText / 2);
		pDC->LineTo(IntervalX, IntervalY);
		ChartBegin = IntervalY + 1;
		if (!Open)
			BeginCountMinutes = (DateTimeEnd[i] - DateBeginPeriod).GetTotalMinutes();
		else
			BeginCountMinutes += 20;
		IntervalY = (int)(Rect.bottom - Space - WidthOrderName - HeightText / 2 - (BeginCountMinutes / EndCountMinutes * MainScopeHeight));
		strcpy_s(buffer, DateTimeEnd[i].Format("%d.%m.%y %H"));
		pDC->SelectObject(ChartPen);
		if (CodOrder[i] != NumberFindOrder)
		{
			ChartBrush = new CBrush(RGB(Red[NumberColor], Green[NumberColor], Blue[NumberColor]));
			pDC->SelectObject(ChartBrush);
		}
		else
		{
			ChartBrush = new CBrush(RGB(Red[0], Green[0], Blue[0]));
			pDC->SelectObject(ChartBrush);
		}
		pDC->Rectangle(IntervalX - WidthColumn, ChartBegin, IntervalX + WidthColumn + 1, IntervalY);
		pDC->SelectObject(ChartPen1);
		Coordinates[i * 4] = IntervalX - WidthColumn;
		Coordinates[i * 4 + 1] = ChartBegin;
		Coordinates[i * 4 + 2] = IntervalX + WidthColumn + 1;
		Coordinates[i * 4 + 3] = IntervalY;
		if (!Open)
		{
			pDC->MoveTo(IntervalX - WidthColumn, ChartBegin + (IntervalY - ChartBegin) / 3);
			pDC->LineTo(IntervalX + WidthColumn + 1, ChartBegin + (IntervalY - ChartBegin) / 3);
			pDC->SelectObject(ChartPen2);
			pDC->MoveTo(IntervalX - WidthColumn, ChartBegin + (IntervalY - ChartBegin) / 3 + (IntervalY - ChartBegin) / 3);
			pDC->LineTo(IntervalX + WidthColumn + 1, ChartBegin + (IntervalY - ChartBegin) / 3 + (IntervalY - ChartBegin) / 3);
		}
	}
	pDC->SelectObject(UsualFont);
	strcpy_s(buffer, DateBeginPeriod.Format("%d.%m.%y %H"));
	UsualFont = pDC->SelectObject(&HorizontalInscriptionFont);
	pDC->TextOut(Space, MainScopeHeight + Space - HeightText / 2, buffer);
	if (ViewGrid == 1)
	{
		pDC->SelectObject(DivisionPen);
		for (int i = 1; Date < DateEndPeriod; i++)
		{
			ChangeHours = CTimeSpan(0, ValueStep * i, 0, 0);
			Date = CTime(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay(), DateBeginPeriod.GetHour(), DateBeginPeriod.GetMinute(), DateBeginPeriod.GetSecond()) + ChangeHours;
			if (Date > DateEndPeriod)
				break;
			BeginCountMinutes = (Date - DateBeginPeriod).GetTotalMinutes();
			EndCountMinutes = (DateEndPeriod - DateBeginPeriod).GetTotalMinutes();
			IntervalY = (int)(Rect.bottom - Space - WidthOrderName - HeightText / 2 - (BeginCountMinutes / EndCountMinutes * MainScopeHeight));
			if (Date < DateEndPeriod)
			{
				pDC->MoveTo(WidthText + Space + HeightText / 2, IntervalY);
				pDC->LineTo(RightSpace, IntervalY);
			}
			strcpy_s(buffer, Date.Format("%d.%m.%y %H"));
			pDC->TextOut(Space, IntervalY - HeightText / 2, buffer);
		}
	}
	Date = CTime(DateEndPeriod.GetYear(), DateEndPeriod.GetMonth(), DateEndPeriod.GetDay(), DateEndPeriod.GetHour(), DateEndPeriod.GetMinute(), DateEndPeriod.GetSecond() + 1);
	strcpy_s(buffer, Date.Format("%d.%m.%y %H"));
	pDC->TextOut(Space, Space - HeightText / 2, buffer);
	pDC->SelectObject(UsualFont);
	pDC->SetTextColor(fcn);
	UsualFont = pDC->SelectObject(&NameFont);
	if (ViewLegend == 1)
	{
		pDC->SelectObject(ChartPen);
		for (int i = 0; i < CodsClass.size(); i++)
		{
			CBrush ChartBrush(RGB(Red[i], Green[i], Blue[i]));
			pDC->SelectObject(ChartBrush);
			pDC->Rectangle(RightSpace + HeightText * 2, HeightText * i + i * 4 + Space, HeightText + (RightSpace + HeightText * 2), HeightText * (i + 1) + i * 4 + Space);
			pDC->TextOut(HeightText + (RightSpace + HeightText * 2 + HeightText / 2), HeightText * i + i * 4 + Space, StateName[i]);
		}
	}
	pDC->SelectObject(UsualFont);
	if (SaveBitmap)
	{
		hBitmap = CreateClientWindwowBitmap(this->m_hWnd);
		m_bmpBitmap.Detach();
		m_bmpBitmap.Attach(hBitmap);
		SaveBitmap = false;
	}
	CountOnDrawCall++;
}

void CGraphOrderView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: рассчитайте полный размер этого представления
	sizeTotal.cx = WorkspaceWidth;
	sizeTotal.cy = 0;
	SetScrollSizes(MM_TEXT, sizeTotal);
	Invalidate(TRUE);
}

HBITMAP Create_hBitmap(HDC hDC, int w, int h)
{
	HDC hDCmem;
	HBITMAP hbm, holdBM;
	hDCmem = CreateCompatibleDC(hDC);
	hbm = CreateCompatibleBitmap(hDC, w, h);
	holdBM = (HBITMAP)SelectObject(hDCmem, hbm);
	BitBlt(hDCmem, 0, 0, w, h, hDC, 0, 0, SRCCOPY);
	SelectObject(hDCmem, holdBM);
	DeleteDC(hDCmem);
	DeleteObject(holdBM);
	return hbm;
}

HBITMAP CreateClientWindwowBitmap(HWND hWND)
{
	RECT r;
	GetClientRect(hWND, &r);
	return(Create_hBitmap(GetDC(hWND), r.right, r.bottom));
}

BOOL CGraphOrderView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation		
	return DoPreparePrinting(pInfo);
}

void CGraphOrderView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
}

void CGraphOrderView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	CSize sizePaper;
	sizePaper.cx = pDC->GetDeviceCaps(HORZSIZE);
	sizePaper.cy = pDC->GetDeviceCaps(VERTSIZE);

	CRect Rect;
	GetClientRect(Rect);
	CDC dcTemp;
	dcTemp.CreateCompatibleDC(pDC);
	dcTemp.SelectObject(m_bmpBitmap);
	BITMAP bm;
	if (m_bmpBitmap.GetSafeHandle() != NULL)
		m_bmpBitmap.GetBitmap(&bm);
	pDC->StretchBlt(0, 0, sizePaper.cx * 24, sizePaper.cy * 12, &dcTemp, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	/*pDC->MoveTo(0, 0);
	pDC->LineTo(sizePaper.cx * 25, sizePaper.cy * 25);*/
}

void CGraphOrderView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add cleanup after printing
}

// диагностика CGraphOrderView

#ifdef _DEBUG
void CGraphOrderView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphOrderView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphOrderDoc* CGraphOrderView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphOrderDoc)));
	return (CGraphOrderDoc*)m_pDocument;
}
#endif //_DEBUG

// обработчики сообщений CGraphOrderView

int CGraphOrderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO: Add your specialized creation code here
	try
	{
		HKEY Key;
		char buffer[MAX_PATH], buffer_str[MAX_PATH];
		int AdmRegionNumber, OperationalService, RedColor, GreenColor, BlueColor, NumOrd = 0;
		CString IniWay, Date_str, S, S1, StrConnectionCodTech, StrConnectionService, StrConnectionAdm, StrConnectionListdocs, PlSizeWay;
		CTimeSpan ChangeHours;
		DWORD RegetPath = MAX_PATH;
		COleDateTime Date;
		MetaTableRead rsmt;
		NregionRead rsn;
		OrdAllRead OrdAllRS;
		CodTechRead CodTechRS;
		ServiceRead rss;
		AdmRead rsa;
		DescrRead rdc;
		DescrdocRead rdd;
		ListdocsRead rld;
		IniWay = IniFile;
		IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));
		GetParentFrame()->SetWindowText("График заявок");
		GetParentFrame()->SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		GetPrivateProfileString("Supshort", "Sup", NULL, buffer, sizeof(buffer), IniFile);
		S = buffer;
		RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\ODBC\\ODBC.INI\\" + S, NULL, KEY_QUERY_VALUE, &Key);
		RegQueryValueEx(Key, "DBQ", NULL, NULL, (LPBYTE)&buffer, &RegetPath);
		S = buffer;
		while (S.GetAt(S.GetLength() - 1) != '\\')
			S.Delete(S.GetLength() - 1, 1);
		WcomtxWay = S;
		PlSizeWay = S + "PLSIZE.ini";
		GetPrivateProfileString("Main", "orderc", NULL, buffer, sizeof(buffer), PlSizeWay);
		if (atoi(buffer) != 0)
			TableName = "ordallC";
		rsmt.IniFile = IniFile;
		rsmt.Open();
		rsn.IniFile = IniFile;
		rsn.Open();
		if (!rsmt.IsBOF())
			rsmt.MoveFirst();
		while (!rsmt.IsEOF())
		{
			if (rsmt.m_TableName == TableName)
			{
				if (!rsn.IsBOF())
					rsn.MoveFirst();
				while (!rsn.IsEOF())
				{
					if (rsn.m_GRUPREG == rsmt.m_BaseType)
					{
						StrConnectionOrdAll = rsn.m_PATH;
						break;
					}
					rsn.MoveNext();
				}
			}
			if (rsmt.m_TableName == "codtech")
			{
				if (!rsn.IsBOF())
					rsn.MoveFirst();
				while (!rsn.IsEOF())
				{
					if (rsn.m_GRUPREG == rsmt.m_BaseType)
					{
						StrConnectionCodTech = rsn.m_PATH;
						break;
					}
					rsn.MoveNext();
				}
			}
			if (rsmt.m_TableName == "adm")
			{
				if (!rsn.IsBOF())
					rsn.MoveFirst();
				while (!rsn.IsEOF())
				{
					if (rsn.m_GRUPREG == rsmt.m_BaseType)
					{
						StrConnectionAdm = rsn.m_PATH;
						break;
					}
					rsn.MoveNext();
				}
			}
			if (rsmt.m_TableName == "service")
			{
				if (!rsn.IsBOF())
					rsn.MoveFirst();
				while (!rsn.IsEOF())
				{
					if (rsn.m_GRUPREG == rsmt.m_BaseType)
					{
						StrConnectionService = rsn.m_PATH;
						break;
					}
					rsn.MoveNext();
				}
			}
			if (rsmt.m_TableName == "area")
			{
				if (!rsn.IsBOF())
					rsn.MoveFirst();
				while (!rsn.IsEOF())
				{
					if (rsn.m_GRUPREG == rsmt.m_BaseType)
					{
						StrConnectionArea = rsn.m_PATH;
						break;
					}
					rsn.MoveNext();
				}
			}
			if (rsmt.m_TableName == "descrcol")
			{
				if (!rsn.IsBOF())
					rsn.MoveFirst();
				while (!rsn.IsEOF())
				{
					if (rsn.m_GRUPREG == rsmt.m_BaseType)
					{
						StrConnectionDescrcol = rsn.m_PATH;
						break;
					}
					rsn.MoveNext();
				}
			}
			if (rsmt.m_TableName == "descrdoc")
			{
				if (!rsn.IsBOF())
					rsn.MoveFirst();
				while (!rsn.IsEOF())
				{
					if (rsn.m_GRUPREG == rsmt.m_BaseType)
					{
						StrConnectionDescrdoc = rsn.m_PATH;
						break;
					}
					rsn.MoveNext();
				}
			}
			if (rsmt.m_TableName == "listdocs")
			{
				if (!rsn.IsBOF())
					rsn.MoveFirst();
				while (!rsn.IsEOF())
				{
					if (rsn.m_GRUPREG == rsmt.m_BaseType)
					{
						StrConnectionListdocs = rsn.m_PATH;
						break;
					}
					rsn.MoveNext();
				}
			}
			rsmt.MoveNext();
		}
		rsn.Close();
		rsmt.Close();
		if (_access(IniWay + "\\GraphSettings.ini", 0))
		{
			WritePrivateProfileString("View", "Grid", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("View", "Legend", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("View", "WidthColumn", "1", IniWay + "GraphSettings.ini");
			CodTechRS.StrConnection = StrConnectionCodTech;
			CodTechRS.Open();
			if (!CodTechRS.IsBOF())
				CodTechRS.MoveFirst();
			while (!CodTechRS.IsEOF())
			{
				if (CodTechRS.m_CODCLAS == 51)
				{
					sprintf_s(buffer_str, "State%i", CodTechRS.m_CODSCLAS);
					sprintf_s(buffer, "RGB(%i, %i, %i)", 0, 0, 0);
					WritePrivateProfileString("ColorState", buffer_str, buffer, IniWay + "GraphSettings.ini");
				}
				CodTechRS.MoveNext();
			}
			CodTechRS.Close();
			WritePrivateProfileString("Sort", "TypeSort", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Sort", "DataSort", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "AdmRegionNumber", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalService", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "AdmRegionNumberValue", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalServiceValue", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("InscriptionFont", "FaceName", "Times New Roman", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("InscriptionFont", "Weight", "400", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("InscriptionFont", "Italic", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("InscriptionFont", "Width", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("InscriptionFont", "Height", "-13", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("InscriptionFont", "StrikeOut", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("InscriptionFont", "Underline", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("InscriptionFont", "Color", "RGB(0, 0, 0)", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("InscriptionFont", "CharSet", "204", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("NameFont", "FaceName", "Times New Roman", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("NameFont", "Weight", "400", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("NameFont", "Italic", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("NameFont", "Width", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("NameFont", "Height", "-13", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("NameFont", "StrikeOut", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("NameFont", "Underline", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("NameFont", "Color", "RGB(0, 0, 0)", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("NameFont", "CharSet", "204", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Period", "DateBegin", "01.01.01 00:00:00", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Period", "DurationPeriod", "24", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Period", "ValueStep", "24", IniWay + "GraphSettings.ini");
		}
		GetPrivateProfileString("Period", "DateBegin", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		Date_str = buffer;
		Date.ParseDateTime(Date_str);
		DateBeginPeriod = CTime(Date.GetYear(), Date.GetMonth(), Date.GetDay(), Date.GetHour(), Date.GetMinute(), Date.GetSecond());
		GetPrivateProfileString("Period", "DurationPeriod", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		DurationPeriod = atoi(buffer);
		ChangeHours = CTimeSpan(0, DurationPeriod, 0, 0);
		DateEndPeriod = CTime(Date.GetYear(), Date.GetMonth(), Date.GetDay(), Date.GetHour(), Date.GetMinute(), Date.GetSecond()) + ChangeHours;
		GetPrivateProfileString("Period", "ValueStep", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		ValueStep = atoi(buffer);
		Red.clear();
		Green.clear();
		Blue.clear();
		NumberOrder.clear();
		CodOrder.clear();
		yy.clear();
		ServiceNumber.clear();
		AdmNumber.clear();
		Address.clear();
		StateOrder.clear();
		DateTimeBegin.clear();
		DateTimeEnd.clear();
		CodsClass.clear();
		StateName.clear();
		Coordinates.clear();
		NumberService.clear();
		NameService.clear();
		NumberAdm.clear();
		NameAdm.clear();
		if (StrConnectionOrdAll.GetLength() > 0)
		{
			OrdAllRS.StrConnection = StrConnectionOrdAll;
			OrdAllRS.TableName = TableName;

			CDatabNet* dn = new CDatabNet;
			CRecordNet rn;
			dn->OpenNet("ODBC;DSN=" + StrConnectionOrdAll, false);
			rn.InitRecordNet(dn, TableName);
			if (rn.isField("RegiServ") == -1)
			{
				OrdAllRS.HasRegiServ = false;
				HasRegiServ = false;
			}
			else
			{
				OrdAllRS.HasRegiServ = true;
				HasRegiServ = true;
			}

			GetPrivateProfileString("Sort", "TypeSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			if (atoi(buffer) == 1)
			{
				GetPrivateProfileString("Sort", "DataSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
				if (atoi(buffer) == 1)
					OrdAllRS.m_strSort = "NUMORD";
				if (atoi(buffer) == 2)
					OrdAllRS.m_strSort = "NREGADM";
				if (atoi(buffer) == 3)
					OrdAllRS.m_strSort = "DATREC";
				if (atoi(buffer) == 4)
					OrdAllRS.m_strSort = "NREGSERV";
			}
			else
			{
				GetPrivateProfileString("Sort", "DataSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
				if (atoi(buffer) == 1)
					OrdAllRS.m_strSort = "NUMORD DESC";
				if (atoi(buffer) == 2)
					OrdAllRS.m_strSort = "NREGADM DESC";
				if (atoi(buffer) == 3)
					OrdAllRS.m_strSort = "DATREC DESC";
				if (atoi(buffer) == 4)
					OrdAllRS.m_strSort = "NREGSERV DESC";
			}
			GetPrivateProfileString("Filter", "AdmRegionNumber", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			AdmRegionNumber = atoi(buffer);
			GetPrivateProfileString("Filter", "OperationalService", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			OperationalService = atoi(buffer);
			if (AdmRegionNumber == 1 && OperationalService == 0)
			{
				GetPrivateProfileString("Filter", "AdmRegionNumberValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
				S = buffer;
				OrdAllRS.m_strFilter = "NREGADM = " + S;
			}
			if (AdmRegionNumber == 0 && OperationalService == 1)
			{
				GetPrivateProfileString("Filter", "OperationalServiceValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
				S = buffer;
				if (HasRegiServ)
					OrdAllRS.m_strFilter = "RegiServ = " + S;
				else
					OrdAllRS.m_strFilter = "NREGSERV = " + S;
			}
			if (AdmRegionNumber == 1 && OperationalService == 1)
			{
				GetPrivateProfileString("Filter", "AdmRegionNumberValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
				S = buffer;
				GetPrivateProfileString("Filter", "OperationalServiceValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
				S1 = buffer;
				if (HasRegiServ)
					OrdAllRS.m_strFilter = "NREGADM = " + S + " AND RegiServ = " + S1;
				else
					OrdAllRS.m_strFilter = "NREGADM = " + S + " AND NREGSERV = " + S1;
			}
			OrdAllRS.Open();
			if (!OrdAllRS.IsBOF())
				OrdAllRS.MoveFirst();
			while (!OrdAllRS.IsEOF())
			{
				if (OrdAllRS.m_DATREC >= DateBeginPeriod && OrdAllRS.m_DATREC <= DateEndPeriod && OrdAllRS.m_DATENDF <= DateEndPeriod)
				{
					NumberOrder.push_back(OrdAllRS.m_NUMORD);
					CodOrder.push_back(OrdAllRS.m_CODORD);
					yy.push_back(OrdAllRS.m_YY);
					StateOrder.push_back(OrdAllRS.m_STATEORD);
					DateTimeBegin.push_back(CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()));
					DateTimeEnd.push_back(CTime(OrdAllRS.m_DATENDF.GetYear(), OrdAllRS.m_DATENDF.GetMonth(), OrdAllRS.m_DATENDF.GetDay(), OrdAllRS.m_DATENDF.GetHour(), OrdAllRS.m_DATENDF.GetMinute(), OrdAllRS.m_DATENDF.GetSecond()));
					ServiceNumber.push_back(OrdAllRS.m_RegiServ);
					ServiceNumber2.push_back(OrdAllRS.m_NREGSERV);
					AdmNumber.push_back(OrdAllRS.m_NREGADM);
					CDatabNet* dn = new CDatabNet;
					dn->OpenNet("ODBC;DSN=" + StrConnectionArea, true);
					NameAdr na(dn, "NameAdr");
					sprintf(buffer, "Select area.NUMAREA, listname.NAME As street, area.ADDRESS, tplistnm.TYPADR From (area Left Join listname On area.STREET = listname.NUMNAME) Left Join tplistnm On listname.TYPNAM = tplistnm.NUMTPNAM Where (((area.NUMAREA) = %i) AND ((tplistnm.TYPADR) = 1))", OrdAllRS.m_CODORD);
					if (na.OpenNet(buffer, CRecordset::readOnly, "") == 1)
						Address.push_back(na.m_street + " " + na.m_ADDRESS);
					na.Close();
					dn->Close();
					for (int i = 0; i < 4; i++)
						Coordinates.push_back(0);
					NumOrd = OrdAllRS.m_CODORD;
				}
				OrdAllRS.MoveNext();
			}
			OrdAllRS.Close();
			GetPrivateProfileString("View", "Grid", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			ViewGrid = atoi(buffer);
			GetPrivateProfileString("View", "Legend", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			ViewLegend = atoi(buffer);
			GetPrivateProfileString("View", "WidthColumn", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			WidthColumn = atoi(buffer);
			CodTechRS.StrConnection = StrConnectionCodTech;
			CodTechRS.Open();
			if (!CodTechRS.IsBOF())
				CodTechRS.MoveFirst();
			while (!CodTechRS.IsEOF())
			{
				if (CodTechRS.m_CODCLAS == 51)
				{
					CodsClass.push_back(CodTechRS.m_CODSCLAS);
					if (CodTechRS.m_NAME == "ОТСУТСТВУЕТ" || CodTechRS.m_NAME == "отсутствует")
						StateName.push_back("НАЙДЕННЫЕ");
					else
						StateName.push_back(CodTechRS.m_NAME);
				}
				CodTechRS.MoveNext();
			}
			CodTechRS.Close();

			rss.StrConnection = StrConnectionService;
			rss.Open();
			if (!rss.IsBOF())
				rss.MoveFirst();
			while (!rss.IsEOF())
			{
				NumberService.push_back(rss.m_NREGSERV);
				NameService.push_back(rss.m_NAMSERV);
				rss.MoveNext();
			}
			rss.Close();

			rsa.StrConnection = StrConnectionAdm;
			rsa.Open();
			if (!rsa.IsBOF())
				rsa.MoveFirst();
			while (!rsa.IsEOF())
			{
				NumberAdm.push_back(rsa.m_NREGADM);
				NameAdm.push_back(rsa.m_NAMADM);
				rsa.MoveNext();
			}
			rsa.Close();

			for (int i = 0; i < CodsClass.size(); i++)
			{
				S = "State";
				sprintf_s(buffer_str, "%i", CodsClass[i]);
				GetPrivateProfileString("ColorState", S + buffer_str, NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
				S = buffer;
				for (int j = 0; j < S.GetLength(); j++)
					if (buffer[j] == ',')
					{
						S.Delete(j, S.GetLength() - j);
						break;
					}
				for (int j = 0; j < S.GetLength(); j++)
					if (buffer[j] == '(')
					{
						S.Delete(0, j + 1);
						break;
					}
				Red.push_back(atoi(S));
				S = buffer;
				for (int j = 0; j < S.GetLength(); j++)
					if (buffer[j] == ',')
					{
						S.Delete(0, j + 1);
						if (buffer[j + 1] == ' ')
							S.Delete(0, 1);
						break;
					}
				strcpy_s(buffer_str, S);
				for (int j = 0; j < S.GetLength(); j++)
					if (buffer_str[j] == ',')
					{
						S.Delete(j, S.GetLength() - j);
						break;
					}
				Green.push_back(atoi(S));
				S = buffer;
				S.Delete(S.GetLength() - 1, 1);
				for (int j = S.GetLength() - 1; j >= 0; j--)
					if (buffer[j] == ',')
					{
						S.Delete(0, j + 1);
						if (buffer[j + 1] == ' ')
							S.Delete(0, 1);
						break;
					}
				Blue.push_back(atoi(S));
			}
			GetPrivateProfileString("InscriptionFont", "FaceName", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			strcpy_s(lfh.lfFaceName, buffer);
			GetPrivateProfileString("InscriptionFont", "Weight", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfh.lfWeight = atoi(buffer);
			GetPrivateProfileString("InscriptionFont", "Italic", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfh.lfItalic = atoi(buffer);
			GetPrivateProfileString("InscriptionFont", "Width", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfh.lfWidth = atoi(buffer);
			GetPrivateProfileString("InscriptionFont", "Height", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfh.lfHeight = atoi(buffer);
			GetPrivateProfileString("InscriptionFont", "StrikeOut", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfh.lfStrikeOut = atoi(buffer);
			GetPrivateProfileString("InscriptionFont", "Underline", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfh.lfUnderline = atoi(buffer);
			GetPrivateProfileString("InscriptionFont", "Color", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			S = buffer;
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer[j] == ',')
				{
					S.Delete(j, S.GetLength() - j);
					break;
				}
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer[j] == '(')
				{
					S.Delete(0, j + 1);
					break;
				}
			RedColor = atoi(S);
			S = buffer;
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer[j] == ',')
				{
					S.Delete(0, j + 1);
					if (buffer[j + 1] == ' ')
						S.Delete(0, 1);
					break;
				}
			strcpy_s(buffer_str, S);
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer_str[j] == ',')
				{
					S.Delete(j, S.GetLength() - j);
					break;
				}
			GreenColor = atoi(S);
			S = buffer;
			S.Delete(S.GetLength() - 1, 1);
			for (int j = S.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == ',')
				{
					S.Delete(0, j + 1);
					if (buffer[j + 1] == ' ')
						S.Delete(0, 1);
					break;
				}
			BlueColor = atoi(S);
			fci = RGB(RedColor, GreenColor, BlueColor);
			GetPrivateProfileString("InscriptionFont", "CharSet", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfh.lfCharSet = atoi(buffer);
			HorizontalInscriptionFont.CreateFontIndirect(&lfh);
			lfv = lfh;
			lfv.lfEscapement = -900;
			VerticalInscriptionFont.CreateFontIndirect(&lfv);
			GetPrivateProfileString("NameFont", "FaceName", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			strcpy_s(lfn.lfFaceName, buffer);
			GetPrivateProfileString("NameFont", "Weight", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfn.lfWeight = atoi(buffer);
			GetPrivateProfileString("NameFont", "Italic", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfn.lfItalic = atoi(buffer);
			GetPrivateProfileString("NameFont", "Width", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfn.lfWidth = atoi(buffer);
			GetPrivateProfileString("NameFont", "Height", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfn.lfHeight = atoi(buffer);
			GetPrivateProfileString("NameFont", "StrikeOut", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfn.lfStrikeOut = atoi(buffer);
			GetPrivateProfileString("NameFont", "Underline", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfn.lfUnderline = atoi(buffer);
			GetPrivateProfileString("NameFont", "Color", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			S = buffer;
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer[j] == ',')
				{
					S.Delete(j, S.GetLength() - j);
					break;
				}
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer[j] == '(')
				{
					S.Delete(0, j + 1);
					break;
				}
			RedColor = atoi(S);
			S = buffer;
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer[j] == ',')
				{
					S.Delete(0, j + 1);
					if (buffer[j + 1] == ' ')
						S.Delete(0, 1);
					break;
				}
			strcpy_s(buffer_str, S);
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer_str[j] == ',')
				{
					S.Delete(j, S.GetLength() - j);
					break;
				}
			GreenColor = atoi(S);
			S = buffer;
			S.Delete(S.GetLength() - 1, 1);
			for (int j = S.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == ',')
				{
					S.Delete(0, j + 1);
					if (buffer[j + 1] == ' ')
						S.Delete(0, 1);
					break;
				}
			BlueColor = atoi(S);
			fcn = RGB(RedColor, GreenColor, BlueColor);
			GetPrivateProfileString("NameFont", "CharSet", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			lfn.lfCharSet = atoi(buffer);
			NameFont.CreateFontIndirect(&lfn);
			SaveBitmap = true;
			CodDoc.clear();
			CodDocDescr.clear();
			SearchOperations.clear();
			SearchOperationsDescr.clear();
			rld.StrConnection = StrConnectionListdocs;
			rld.Open();
			if (!rld.IsBOF())
				rld.MoveFirst();
			while (!rld.IsEOF())
			{
				if (rld.m_LISTDOC == 251 || rld.m_LISTDOC == 255)
					CodDoc.push_back(rld.m_CODDOC);
				rld.MoveNext();
			}
			rld.Close();
			rdd.StrConnection = StrConnectionDescrdoc;
			rdd.Open();
			if (!rdd.IsBOF())
				rdd.MoveFirst();
			while (!rdd.IsEOF())
			{
				for (int i = 0; i < CodDoc.size(); i++)
					if (CodDoc[i] == rdd.m_CODDOC)
					{
						CodDocDescr.push_back(rdd.m_CODDOC);
						SearchOperationsDescr.push_back(rdd.m_NAMEDOC);
					}
				rdd.MoveNext();
			}
			rdd.Close();
			for (int i = 0; i < CodDoc.size(); i++)
				for (int j = 0; j < CodDoc.size(); j++)
					if (CodDoc[i] == CodDocDescr[j])
						SearchOperations.push_back(SearchOperationsDescr[j]);
		}
		else
		{
			MessageBox("Источник данных не найден или отсутствуют соответствующие таблицы!", "Ошибка", MB_OK | MB_ICONERROR);
			PostQuitMessage(0);
		}
	}
	catch (...)
	{
		MessageBox("Источник данных не найден или отсутствуют соответствующие таблицы!", "Ошибка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}

	return 0;
}

void CGraphOrderView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	char buffer[MAX_PATH];
	CString StateNameStr, ServiceNameStr, AdmNameStr;
	CRect Rect;
	int i, x0 = 0, x1 = 0, y0 = 0, y1 = 0;
	for (i = 0; i < Coordinates.size(); i = i + 4)
		if (point.x >= Coordinates[i] && point.x <= Coordinates[i + 2] && point.y <= Coordinates[i + 1] && point.y >= Coordinates[i + 3])
		{
			x0 = Coordinates[i];
			x1 = Coordinates[i + 2];
			y0 = Coordinates[i + 1];
			y1 = Coordinates[i + 3];
			break;
		}
	if (point.x >= x0 && point.x <= x1 && point.y <= y0 && point.y >= y1)
	{
		if (CountMove == 0)
		{
			Sleep(500);
			GetClientRect(&Rect);
			ClientToScreen(Rect);
			for (int j = 0; j < CodsClass.size(); j++)
				if (CodsClass[j] == StateOrder[i / 4])
				{
					StateNameStr = StateName[j];
					break;
				}
			for (int j = 0; j < NumberService.size(); j++)
				if (NumberService[j] == ServiceNumber2[i / 4])
				{
					ServiceNameStr = NameService[j];
					break;
				}
			for (int j = 0; j < NumberAdm.size(); j++)
				if (NumberAdm[j] == AdmNumber[i / 4])
				{
					AdmNameStr = NameAdm[j];
					break;
				}
			sprintf_s(buffer, "%i %i %s %s %s", yy[i / 4], CodOrder[i / 4], Address[i / 4], AdmNameStr, ServiceNameStr);
			//sprintf_s(buffer, "%i %i %s %s %s %s", yy[i / 4], CodOrder[i / 4], Address[i / 4], StateNameStr, AdmNameStr, ServiceNameStr);
			hwndTT = CreateWindowEx(WS_EX_TOPMOST, TOOLTIPS_CLASS, NULL, TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);
			ti.cbSize = 0;
			ti.uFlags = TTF_TRACK;
			ti.hwnd = NULL;
			ti.hinst = NULL;
			ti.uId = 0;
			ti.lpszText = buffer;
			ti.rect.left = 0;
			ti.rect.top = 0;
			ti.rect.right = 0;
			ti.rect.bottom = 0;
			::SendMessage(hwndTT, TTM_ADDTOOL, 0, (LPARAM)(LPTOOLINFO)&ti);
			::SendMessage(hwndTT, TTM_TRACKPOSITION, 0, (LPARAM)(DWORD)MAKELONG(Rect.left + point.x, Rect.top + point.y));
			::SendMessage(hwndTT, TTM_TRACKACTIVATE, true, (LPARAM)(LPTOOLINFO)&ti);
			CountMove++;
		}
	}
	else
	{
		::SendMessage(hwndTT, TTM_TRACKACTIVATE, false, (LPARAM)(LPTOOLINFO)&ti);
		CountMove = 0;
	}

	CScrollView::OnMouseMove(nFlags, point);
}

void CGraphOrderView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	POINT cp;
	GetCursorPos(&cp);
	int i, x0 = 0, x1 = 0, y0 = 0, y1 = 0;
	for (i = 0; i < Coordinates.size(); i = i + 4)
		if (point.x >= Coordinates[i] && point.x <= Coordinates[i + 2] && point.y <= Coordinates[i + 1] && point.y >= Coordinates[i + 3])
		{
			x0 = Coordinates[i];
			x1 = Coordinates[i + 2];
			y0 = Coordinates[i + 1];
			y1 = Coordinates[i + 3];
			break;
		}
	if (point.x >= x0 && point.x <= x1 && point.y <= y0 && point.y >= y1)
	{
		CurrentNumberOrder = NumberOrder[i / 4];
		m_Menu = new CMenu;
		CArray<bool, bool> moper;
		CArray<CString, CString> mnameoper;
		HINSTANCE hWorder = ::AfxLoadLibrary("worder.dll");
		PFN_OrderView pfnOrderView = (PFN_OrderView)GetProcAddress(hWorder, "OrderView");
		BOOL iCode = (*pfnOrderView)(CurrentNumberOrder, moper, mnameoper);
		m_Menu->LoadMenu(IDR_POPUP_MENU);
		for (i = 0; i < moper.GetCount(); i++)
			if (moper[i])
				m_Menu->GetSubMenu(0)->AppendMenu(MF_STRING, ID_POPUP_OPERATION_ORDER + i, mnameoper[i]);
		m_Menu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, cp.x, cp.y, this);
	}
	else
	{
		m_Menu = new CMenu;
		m_Menu->LoadMenu(IDR_SECOND_POPUP_MENU);
		CMenu* m_PopupMenu = new CMenu;
		m_PopupMenu->CreatePopupMenu();
		for (i = 0; i < SearchOperations.size(); i++)
			m_PopupMenu->AppendMenu(MF_STRING, ID_POPUP_SEARCH_ORDER + i, SearchOperations[i]);
		m_Menu->GetSubMenu(0)->AppendMenu(MF_STRING | MF_POPUP, (UINT)m_PopupMenu->m_hMenu, "Поиск");
		m_Menu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, cp.x, cp.y, this);
	}
	::SendMessage(hwndTT, TTM_TRACKACTIVATE, false, (LPARAM)(LPTOOLINFO)&ti);

	CScrollView::OnRButtonDown(nFlags, point);
}

void CGraphOrderView::OnViewEnlarge()
{
	// TODO: Add your command handler code here
	CountEnlarge++;
	WorkspaceWidth = (int)((double)(WorkspaceWidth * 1.5));
	OnInitialUpdate();
	ViewReduce = TRUE;
}

void CGraphOrderView::OnViewReduce()
{
	// TODO: Add your command handler code here
	CountEnlarge--;
	WorkspaceWidth = (int)((double)(WorkspaceWidth / 1.5));
	OnInitialUpdate();
	if (CountEnlarge == 0)
		ViewReduce = FALSE;
}

void CGraphOrderView::OnUpdateViewReduce(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(ViewReduce);
}

void CGraphOrderView::OnViewGeneralSettings()
{
	// TODO: Add your command handler code here

	int NumOrd = 0;
	char buffer[MAX_PATH], buffer_str[MAX_PATH];
	CString IniWay;
	OrdAllRead OrdAllRS;
	CGeneralSettingsDlg dlg;
	IniWay = IniFile;
	IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));
	dlg.IniFile = IniFile;
	dlg.lfh = lfh;
	dlg.lfn = lfn;
	dlg.fci = fci;
	dlg.fcn = fcn;
	dlg.Red = Red;
	dlg.Green = Green;
	dlg.Blue = Blue;
	if (dlg.DoModal() == IDOK)
	{
		ViewGrid = dlg.ViewGrid;
		ViewLegend = dlg.ViewLegend;
		WidthColumn = atoi(dlg.WidthColumn);
		Red.clear();
		Green.clear();
		Blue.clear();
		Red = dlg.Red;
		Green = dlg.Green;
		Blue = dlg.Blue;
		Invalidate();
		sprintf_s(buffer, "%i", ViewGrid);
		WritePrivateProfileString("View", "Grid", buffer, IniWay + "GraphSettings.ini");
		sprintf_s(buffer, "%i", ViewLegend);
		WritePrivateProfileString("View", "Legend", buffer, IniWay + "GraphSettings.ini");
		sprintf_s(buffer, "%i", WidthColumn);
		WritePrivateProfileString("View", "WidthColumn", buffer, IniWay + "GraphSettings.ini");
		for (int i = 0; i < CodsClass.size(); i++)
		{
			sprintf_s(buffer_str, "State%i", CodsClass[i]);
			sprintf_s(buffer, "RGB(%i, %i, %i)", Red[i], Green[i], Blue[i]);
			WritePrivateProfileString("ColorState", buffer_str, buffer, IniWay + "GraphSettings.ini");
		}
		NumberOrder.clear();
		CodOrder.clear();
		yy.clear();
		ServiceNumber.clear();
		AdmNumber.clear();
		Address.clear();
		StateOrder.clear();
		DateTimeBegin.clear();
		DateTimeEnd.clear();
		Coordinates.clear();
		ServiceNumber.clear();
		ServiceNumber2.clear();
		//NumberService.clear();
		//NameService.clear();
		//NumberAdm.clear();
		//NameAdm.clear();
		OrdAllRS.StrConnection = StrConnectionOrdAll;
		OrdAllRS.TableName = TableName;


		CDatabNet* dn = new CDatabNet;
		CRecordNet rn;
		dn->OpenNet("ODBC;DSN=" + StrConnectionOrdAll, false);
		rn.InitRecordNet(dn, TableName);
		if (rn.isField("RegiServ") == -1)
			OrdAllRS.HasRegiServ = false;
		else
			OrdAllRS.HasRegiServ = true;

		if (dlg.IncreaseSort)
		{
			WritePrivateProfileString("Sort", "TypeSort", "1", IniWay + "GraphSettings.ini");
			if (dlg.NumberOrderSort)
			{
				OrdAllRS.m_strSort = "NUMORD";
				WritePrivateProfileString("Sort", "DataSort", "1", IniWay + "GraphSettings.ini");
			}
			if (dlg.AdmRegionNumberSort)
			{
				OrdAllRS.m_strSort = "NREGADM";
				WritePrivateProfileString("Sort", "DataSort", "2", IniWay + "GraphSettings.ini");
			}
			if (dlg.DateReceiptOrderSort)
			{
				OrdAllRS.m_strSort = "DATREC";
				WritePrivateProfileString("Sort", "DataSort", "3", IniWay + "GraphSettings.ini");
			}
			if (dlg.OperationalServiceSort)
			{
				OrdAllRS.m_strSort = "NREGSERV";
				WritePrivateProfileString("Sort", "DataSort", "4", IniWay + "GraphSettings.ini");
			}
		}
		if (dlg.DecreaseSort)
		{
			WritePrivateProfileString("Sort", "TypeSort", "2", IniWay + "GraphSettings.ini");
			if (dlg.NumberOrderSort)
			{
				OrdAllRS.m_strSort = "NUMORD DESC";
				WritePrivateProfileString("Sort", "DataSort", "1", IniWay + "GraphSettings.ini");
			}
			if (dlg.AdmRegionNumberSort)
			{
				OrdAllRS.m_strSort = "NREGADM DESC";
				WritePrivateProfileString("Sort", "DataSort", "2", IniWay + "GraphSettings.ini");
			}
			if (dlg.DateReceiptOrderSort)
			{
				OrdAllRS.m_strSort = "DATREC DESC";
				WritePrivateProfileString("Sort", "DataSort", "3", IniWay + "GraphSettings.ini");
			}
			if (dlg.OperationalServiceSort)
			{
				OrdAllRS.m_strSort = "NREGSERV DESC";
				WritePrivateProfileString("Sort", "DataSort", "4", IniWay + "GraphSettings.ini");
			}
		}
		if (dlg.AdmRegNumFilter && !dlg.OperatServFilter)
		{
			OrdAllRS.m_strFilter = "NREGADM = " + dlg.AdmRegionNumber;
			WritePrivateProfileString("Filter", "AdmRegionNumber", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalService", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "AdmRegionNumberValue", dlg.AdmRegionNumber, IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalServiceValue", "1", IniWay + "GraphSettings.ini");
		}
		if (!dlg.AdmRegNumFilter && dlg.OperatServFilter)
		{
			if (HasRegiServ)
				OrdAllRS.m_strFilter = "RegiServ = " + dlg.OperationalService;
			else
				OrdAllRS.m_strFilter = "NREGSERV = " + dlg.OperationalService;
			WritePrivateProfileString("Filter", "AdmRegionNumber", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalService", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "AdmRegionNumberValue", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalServiceValue", dlg.OperationalService, IniWay + "GraphSettings.ini");
		}
		if (dlg.AdmRegNumFilter && dlg.OperatServFilter)
		{
			if (HasRegiServ)
				OrdAllRS.m_strFilter = "NREGADM = " + dlg.AdmRegionNumber + " AND RegiServ = " + dlg.OperationalService;
			else
				OrdAllRS.m_strFilter = "NREGADM = " + dlg.AdmRegionNumber + " AND NREGSERV = " + dlg.OperationalService;
			WritePrivateProfileString("Filter", "AdmRegionNumber", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalService", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "AdmRegionNumberValue", dlg.AdmRegionNumber, IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalServiceValue", dlg.OperationalService, IniWay + "GraphSettings.ini");
		}
		if (!dlg.AdmRegNumFilter && !dlg.OperatServFilter)
		{
			WritePrivateProfileString("Filter", "AdmRegionNumber", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalService", "0", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "AdmRegionNumberValue", "1", IniWay + "GraphSettings.ini");
			WritePrivateProfileString("Filter", "OperationalServiceValue", "1", IniWay + "GraphSettings.ini");
		}
		OrdAllRS.Open();
		if (!OrdAllRS.IsBOF())
			OrdAllRS.MoveFirst();
		while (!OrdAllRS.IsEOF())
		{
			if (OrdAllRS.m_DATREC >= DateBeginPeriod && OrdAllRS.m_DATREC <= DateEndPeriod && OrdAllRS.m_DATENDF <= DateEndPeriod)
			{
				NumberOrder.push_back(OrdAllRS.m_NUMORD);
				CodOrder.push_back(OrdAllRS.m_CODORD);
				StateOrder.push_back(OrdAllRS.m_STATEORD);
				DateTimeBegin.push_back(CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()));
				DateTimeEnd.push_back(CTime(OrdAllRS.m_DATENDF.GetYear(), OrdAllRS.m_DATENDF.GetMonth(), OrdAllRS.m_DATENDF.GetDay(), OrdAllRS.m_DATENDF.GetHour(), OrdAllRS.m_DATENDF.GetMinute(), OrdAllRS.m_DATENDF.GetSecond()));
				ServiceNumber.push_back(OrdAllRS.m_RegiServ);
				ServiceNumber2.push_back(OrdAllRS.m_NREGSERV);
				AdmNumber.push_back(OrdAllRS.m_NREGADM);
				CDatabNet* dn = new CDatabNet;
				dn->OpenNet("ODBC;DSN=" + StrConnectionArea, true);
				NameAdr na(dn, "NameAdr");
				sprintf(buffer, "Select area.NUMAREA, listname.NAME As street, area.ADDRESS, tplistnm.TYPADR From (area Left Join listname On area.STREET = listname.NUMNAME) Left Join tplistnm On listname.TYPNAM = tplistnm.NUMTPNAM Where (((area.NUMAREA) = %i) AND ((tplistnm.TYPADR) = 1))", OrdAllRS.m_CODORD);
				if (na.OpenNet(buffer, CRecordset::readOnly, "") == 1)
					Address.push_back(na.m_street + " " + na.m_ADDRESS);
				na.Close();
				dn->Close();
				for (int i = 0; i < 4; i++)
					Coordinates.push_back(0);
				NumOrd = OrdAllRS.m_CODORD;
			}
			OrdAllRS.MoveNext();
		}
		OrdAllRS.Close();
		if (dlg.ChangeInscriptionFont)
		{
			HorizontalInscriptionFont.DeleteObject();
			VerticalInscriptionFont.DeleteObject();
			lfh = dlg.lfh;
			lfv = dlg.lfv;
			HorizontalInscriptionFont.CreateFontIndirect(&lfh);
			VerticalInscriptionFont.CreateFontIndirect(&lfv);
			WritePrivateProfileString("InscriptionFont", "FaceName", lfh.lfFaceName, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfh.lfWeight);
			WritePrivateProfileString("InscriptionFont", "Weight", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfh.lfItalic);
			WritePrivateProfileString("InscriptionFont", "Italic", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfh.lfWidth);
			WritePrivateProfileString("InscriptionFont", "Width", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfh.lfHeight);
			WritePrivateProfileString("InscriptionFont", "Height", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfh.lfStrikeOut);
			WritePrivateProfileString("InscriptionFont", "StrikeOut", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfh.lfUnderline);
			WritePrivateProfileString("InscriptionFont", "Underline", buffer, IniWay + "GraphSettings.ini");
			fci = dlg.fci;
			sprintf_s(buffer, "RGB(%i, %i, %i)", GetRValue(dlg.fci), GetGValue(dlg.fci), GetBValue(dlg.fci));
			WritePrivateProfileString("InscriptionFont", "Color", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfh.lfCharSet);
			WritePrivateProfileString("InscriptionFont", "CharSet", buffer, IniWay + "GraphSettings.ini");
		}
		if (dlg.ChangeNameFont)
		{
			NameFont.DeleteObject();
			lfn = dlg.lfn;
			NameFont.CreateFontIndirect(&lfn);
			WritePrivateProfileString("NameFont", "FaceName", lfn.lfFaceName, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfn.lfWeight);
			WritePrivateProfileString("NameFont", "Weight", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfn.lfItalic);
			WritePrivateProfileString("NameFont", "Italic", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfn.lfWidth);
			WritePrivateProfileString("NameFont", "Width", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfn.lfHeight);
			WritePrivateProfileString("NameFont", "Height", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfn.lfStrikeOut);
			WritePrivateProfileString("NameFont", "StrikeOut", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfn.lfUnderline);
			WritePrivateProfileString("NameFont", "Underline", buffer, IniWay + "GraphSettings.ini");
			fcn = dlg.fcn;
			sprintf_s(buffer, "RGB(%i, %i, %i)", GetRValue(dlg.fcn), GetGValue(dlg.fcn), GetBValue(dlg.fcn));
			WritePrivateProfileString("NameFont", "Color", buffer, IniWay + "GraphSettings.ini");
			sprintf_s(buffer, "%i", lfn.lfCharSet);
			WritePrivateProfileString("NameFont", "CharSet", buffer, IniWay + "GraphSettings.ini");
		}
		Invalidate();
		SaveBitmap = true;
	}
}

void CGraphOrderView::OnViewAdditionalSettings()
{
	// TODO: Add your command handler code here
	int NumOrd = 0;
	char buffer[MAX_PATH];
	int AdmRegionNumber, OperationalService;
	CString IniWay, S, S1;
	CAdditionalSettingsDlg dlg;
	OrdAllRead OrdAllRS;
	IniWay = IniFile;
	IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));
	dlg.IniFile = IniFile;
	if (dlg.DoModal() == IDOK)
	{
		DateBeginPeriod = CTime(dlg.DateBeginPeriod.GetYear(), dlg.DateBeginPeriod.GetMonth(), dlg.DateBeginPeriod.GetDay(), dlg.TimeBeginPeriod.GetHour(), dlg.TimeBeginPeriod.GetMinute(), dlg.TimeBeginPeriod.GetSecond());
		DateEndPeriod = CTime(dlg.DateEndPeriod.GetYear(), dlg.DateEndPeriod.GetMonth(), dlg.DateEndPeriod.GetDay(), dlg.DateEndPeriod.GetHour(), dlg.DateEndPeriod.GetMinute(), dlg.DateEndPeriod.GetSecond());
		DurationPeriod = atoi(dlg.DurationPeriod);
		ValueStep = atoi(dlg.ValueStep);
		NumberOrder.clear();
		CodOrder.clear();
		yy.clear();
		ServiceNumber.clear();
		AdmNumber.clear();
		Address.clear();
		StateOrder.clear();
		DateTimeBegin.clear();
		DateTimeEnd.clear();
		Coordinates.clear();
		ServiceNumber.clear();
		ServiceNumber2.clear();
		//NumberService.clear();
		//NameService.clear();
		//NumberAdm.clear();
		//NameAdm.clear();
		OrdAllRS.StrConnection = StrConnectionOrdAll;
		OrdAllRS.TableName = TableName;

		CDatabNet* dn = new CDatabNet;
		CRecordNet rn;
		dn->OpenNet("ODBC;DSN=" + StrConnectionOrdAll, false);
		rn.InitRecordNet(dn, TableName);
		if (rn.isField("RegiServ") == -1)
			OrdAllRS.HasRegiServ = false;
		else
			OrdAllRS.HasRegiServ = true;


		GetPrivateProfileString("Sort", "TypeSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		if (!strcmp(buffer, "1"))
		{
			GetPrivateProfileString("Sort", "DataSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			if (!strcmp(buffer, "1"))
				OrdAllRS.m_strSort = "NUMORD";
			if (!strcmp(buffer, "2"))
				OrdAllRS.m_strSort = "NREGADM";
			if (!strcmp(buffer, "3"))
				OrdAllRS.m_strSort = "DATREC";
			if (!strcmp(buffer, "4"))
				OrdAllRS.m_strSort = "NREGSERV";
		}
		else
		{
			GetPrivateProfileString("Sort", "DataSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			if (!strcmp(buffer, "1"))
				OrdAllRS.m_strSort = "NUMORD DESC";
			if (!strcmp(buffer, "2"))
				OrdAllRS.m_strSort = "NREGADM DESC";
			if (!strcmp(buffer, "3"))
				OrdAllRS.m_strSort = "DATREC DESC";
			if (!strcmp(buffer, "4"))
				OrdAllRS.m_strSort = "NREGSERV DESC";
		}
		GetPrivateProfileString("Filter", "AdmRegionNumber", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		AdmRegionNumber = atoi(buffer);
		GetPrivateProfileString("Filter", "OperationalService", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		OperationalService = atoi(buffer);
		if (AdmRegionNumber == 1 && OperationalService == 0)
		{
			GetPrivateProfileString("Filter", "AdmRegionNumberValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			S = buffer;
			OrdAllRS.m_strFilter = "NREGADM = " + S;
		}
		if (AdmRegionNumber == 0 && OperationalService == 1)
		{
			GetPrivateProfileString("Filter", "OperationalServiceValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			S = buffer;
			if (HasRegiServ)
				OrdAllRS.m_strFilter = "RegiServ = " + S;
			else
				OrdAllRS.m_strFilter = "NREGSERV = " + S;
		}
		if (AdmRegionNumber == 1 && OperationalService == 1)
		{
			GetPrivateProfileString("Filter", "AdmRegionNumberValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			S = buffer;
			GetPrivateProfileString("Filter", "OperationalServiceValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			S1 = buffer;
			if (HasRegiServ)
				OrdAllRS.m_strFilter = "NREGADM = " + S + " AND RegiServ = " + S1;
			else
				OrdAllRS.m_strFilter = "NREGADM = " + S + " AND NREGSERV = " + S1;
		}
		OrdAllRS.Open();
		if (!OrdAllRS.IsBOF())
			OrdAllRS.MoveFirst();
		while (!OrdAllRS.IsEOF())
		{
			if (OrdAllRS.m_DATREC >= DateBeginPeriod && OrdAllRS.m_DATREC <= DateEndPeriod && OrdAllRS.m_DATENDF <= DateEndPeriod)
			{
				NumberOrder.push_back(OrdAllRS.m_NUMORD);
				CodOrder.push_back(OrdAllRS.m_CODORD);
				StateOrder.push_back(OrdAllRS.m_STATEORD);
				DateTimeBegin.push_back(CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()));
				DateTimeEnd.push_back(CTime(OrdAllRS.m_DATENDF.GetYear(), OrdAllRS.m_DATENDF.GetMonth(), OrdAllRS.m_DATENDF.GetDay(), OrdAllRS.m_DATENDF.GetHour(), OrdAllRS.m_DATENDF.GetMinute(), OrdAllRS.m_DATENDF.GetSecond()));
				ServiceNumber.push_back(OrdAllRS.m_RegiServ);
				ServiceNumber2.push_back(OrdAllRS.m_NREGSERV);
				AdmNumber.push_back(OrdAllRS.m_NREGADM);
				CDatabNet* dn = new CDatabNet;
				dn->OpenNet("ODBC;DSN=" + StrConnectionArea, true);
				NameAdr na(dn, "NameAdr");
				sprintf(buffer, "Select area.NUMAREA, listname.NAME As street, area.ADDRESS, tplistnm.TYPADR From (area Left Join listname On area.STREET = listname.NUMNAME) Left Join tplistnm On listname.TYPNAM = tplistnm.NUMTPNAM Where (((area.NUMAREA) = %i) AND ((tplistnm.TYPADR) = 1))", OrdAllRS.m_CODORD);
				if (na.OpenNet(buffer, CRecordset::readOnly, "") == 1)
					Address.push_back(na.m_street + " " + na.m_ADDRESS);
				na.Close();
				dn->Close();
				for (int i = 0; i < 4; i++)
					Coordinates.push_back(0);
				NumOrd = OrdAllRS.m_CODORD;
			}
			OrdAllRS.MoveNext();
		}
		OrdAllRS.Close();
		Invalidate();
		strcpy_s(buffer, DateBeginPeriod.Format("%d.%m.%y %H:%M:%S"));
		WritePrivateProfileString("Period", "DateBegin", buffer, IniWay + "GraphSettings.ini");
		sprintf_s(buffer, "%i", atoi(dlg.DurationPeriod));
		WritePrivateProfileString("Period", "DurationPeriod", buffer, IniWay + "GraphSettings.ini");
		sprintf_s(buffer, "%i", atoi(dlg.ValueStep));
		WritePrivateProfileString("Period", "ValueStep", buffer, IniWay + "GraphSettings.ini");
		SaveBitmap = true;
	}
}

void CGraphOrderView::OnViewNext()
{
	char buffer[MAX_PATH];
	int AdmRegionNumber, OperationalService, NumOrd = 0;
	CString IniWay, S, S1;
	CTimeSpan ChangeHours;
	OrdAllRead OrdAllRS;
	IniWay = IniFile;
	IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));
	ChangeHours = CTimeSpan(0, DurationPeriod, 0, 0);
	DateBeginPeriod = CTime(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay(), DateBeginPeriod.GetHour(), DateBeginPeriod.GetMinute(), DateBeginPeriod.GetSecond()) + ChangeHours;
	DateEndPeriod = CTime(DateEndPeriod.GetYear(), DateEndPeriod.GetMonth(), DateEndPeriod.GetDay(), DateEndPeriod.GetHour(), DateEndPeriod.GetMinute(), DateEndPeriod.GetSecond()) + ChangeHours;
	NumberOrder.clear();
	CodOrder.clear();
	yy.clear();
	ServiceNumber.clear();
	AdmNumber.clear();
	Address.clear();
	StateOrder.clear();
	DateTimeBegin.clear();
	DateTimeEnd.clear();
	Coordinates.clear();
	ServiceNumber.clear();
	ServiceNumber2.clear();
	//NumberService.clear();
	//NameService.clear();
	//NumberAdm.clear();
	//NameAdm.clear();
	OrdAllRS.StrConnection = StrConnectionOrdAll;
	OrdAllRS.TableName = TableName;

	CDatabNet* dn = new CDatabNet;
	CRecordNet rn;
	dn->OpenNet("ODBC;DSN=" + StrConnectionOrdAll, false);
	rn.InitRecordNet(dn, TableName);
	if (rn.isField("RegiServ") == -1)
		OrdAllRS.HasRegiServ = false;
	else
		OrdAllRS.HasRegiServ = true;


	GetPrivateProfileString("Sort", "TypeSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	if (!strcmp(buffer, "1"))
	{
		GetPrivateProfileString("Sort", "DataSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		if (!strcmp(buffer, "1"))
			OrdAllRS.m_strSort = "NUMORD";
		if (!strcmp(buffer, "2"))
			OrdAllRS.m_strSort = "NREGADM";
		if (!strcmp(buffer, "3"))
			OrdAllRS.m_strSort = "DATREC";
		if (!strcmp(buffer, "4"))
			OrdAllRS.m_strSort = "NREGSERV";
	}
	else
	{
		GetPrivateProfileString("Sort", "DataSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		if (!strcmp(buffer, "1"))
			OrdAllRS.m_strSort = "NUMORD DESC";
		if (!strcmp(buffer, "2"))
			OrdAllRS.m_strSort = "NREGADM DESC";
		if (!strcmp(buffer, "3"))
			OrdAllRS.m_strSort = "DATREC DESC";
		if (!strcmp(buffer, "4"))
			OrdAllRS.m_strSort = "NREGSERV DESC";
	}
	GetPrivateProfileString("Filter", "AdmRegionNumber", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	AdmRegionNumber = atoi(buffer);
	GetPrivateProfileString("Filter", "OperationalService", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	OperationalService = atoi(buffer);
	if (AdmRegionNumber == 1 && OperationalService == 0)
	{
		GetPrivateProfileString("Filter", "AdmRegionNumberValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		S = buffer;
		OrdAllRS.m_strFilter = "NREGADM = " + S;
	}
	if (AdmRegionNumber == 0 && OperationalService == 1)
	{
		GetPrivateProfileString("Filter", "OperationalServiceValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		S = buffer;
		if (HasRegiServ)
			OrdAllRS.m_strFilter = "RegiServ = " + S;
		else
			OrdAllRS.m_strFilter = "NREGSERV = " + S;
	}
	if (AdmRegionNumber == 1 && OperationalService == 1)
	{
		GetPrivateProfileString("Filter", "AdmRegionNumberValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		S = buffer;
		GetPrivateProfileString("Filter", "OperationalServiceValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		S1 = buffer;
		if (HasRegiServ)
			OrdAllRS.m_strFilter = "NREGADM = " + S + " AND RegiServ = " + S1;
		else
			OrdAllRS.m_strFilter = "NREGADM = " + S + " AND NREGSERV = " + S1;
	}
	OrdAllRS.Open();
	if (!OrdAllRS.IsBOF())
		OrdAllRS.MoveFirst();
	while (!OrdAllRS.IsEOF())
	{
		if (OrdAllRS.m_DATREC >= DateBeginPeriod && OrdAllRS.m_DATREC <= DateEndPeriod && OrdAllRS.m_DATENDF <= DateEndPeriod)
		{
			NumberOrder.push_back(OrdAllRS.m_NUMORD);
			CodOrder.push_back(OrdAllRS.m_CODORD);
			StateOrder.push_back(OrdAllRS.m_STATEORD);
			DateTimeBegin.push_back(CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()));
			DateTimeEnd.push_back(CTime(OrdAllRS.m_DATENDF.GetYear(), OrdAllRS.m_DATENDF.GetMonth(), OrdAllRS.m_DATENDF.GetDay(), OrdAllRS.m_DATENDF.GetHour(), OrdAllRS.m_DATENDF.GetMinute(), OrdAllRS.m_DATENDF.GetSecond()));
			ServiceNumber.push_back(OrdAllRS.m_RegiServ);
			ServiceNumber2.push_back(OrdAllRS.m_NREGSERV);
			AdmNumber.push_back(OrdAllRS.m_NREGADM);
			CDatabNet* dn = new CDatabNet;
			dn->OpenNet("ODBC;DSN=" + StrConnectionArea, true);
			NameAdr na(dn, "NameAdr");
			sprintf(buffer, "Select area.NUMAREA, listname.NAME As street, area.ADDRESS, tplistnm.TYPADR From (area Left Join listname On area.STREET = listname.NUMNAME) Left Join tplistnm On listname.TYPNAM = tplistnm.NUMTPNAM Where (((area.NUMAREA) = %i) AND ((tplistnm.TYPADR) = 1))", OrdAllRS.m_CODORD);
			if (na.OpenNet(buffer, CRecordset::readOnly, "") == 1)
				Address.push_back(na.m_street + " " + na.m_ADDRESS);
			na.Close();
			dn->Close();
			for (int i = 0; i < 4; i++)
				Coordinates.push_back(0);
			NumOrd = OrdAllRS.m_CODORD;
		}
		OrdAllRS.MoveNext();
	}
	OrdAllRS.Close();
	Invalidate();
	strcpy_s(buffer, DateBeginPeriod.Format("%d.%m.%y %H:%M:%S"));
	WritePrivateProfileString("Period", "DateBegin", buffer, IniWay + "GraphSettings.ini");
	SaveBitmap = true;
}

void CGraphOrderView::OnViewBack()
{
	char buffer[MAX_PATH];
	int AdmRegionNumber, OperationalService, NumOrd = 0;
	CString IniWay, S, S1;
	CTimeSpan ChangeHours;
	OrdAllRead OrdAllRS;
	IniWay = IniFile;
	IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));
	ChangeHours = CTimeSpan(0, DurationPeriod, 0, 0);
	DateBeginPeriod = CTime(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay(), DateBeginPeriod.GetHour(), DateBeginPeriod.GetMinute(), DateBeginPeriod.GetSecond()) - ChangeHours;
	DateEndPeriod = CTime(DateEndPeriod.GetYear(), DateEndPeriod.GetMonth(), DateEndPeriod.GetDay(), DateEndPeriod.GetHour(), DateEndPeriod.GetMinute(), DateEndPeriod.GetSecond()) - ChangeHours;
	NumberOrder.clear();
	CodOrder.clear();
	yy.clear();
	ServiceNumber.clear();
	AdmNumber.clear();
	Address.clear();
	StateOrder.clear();
	DateTimeBegin.clear();
	DateTimeEnd.clear();
	Coordinates.clear();
	ServiceNumber.clear();
	ServiceNumber2.clear();
	//NumberService.clear();
	//NameService.clear();
	//NumberAdm.clear();
	//NameAdm.clear();
	OrdAllRS.StrConnection = StrConnectionOrdAll;
	OrdAllRS.TableName = TableName;

	CDatabNet* dn = new CDatabNet;
	CRecordNet rn;
	dn->OpenNet("ODBC;DSN=" + StrConnectionOrdAll, false);
	rn.InitRecordNet(dn, TableName);
	if (rn.isField("RegiServ") == -1)
		OrdAllRS.HasRegiServ = false;
	else
		OrdAllRS.HasRegiServ = true;


	GetPrivateProfileString("Sort", "TypeSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	if (!strcmp(buffer, "1"))
	{
		GetPrivateProfileString("Sort", "DataSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		if (!strcmp(buffer, "1"))
			OrdAllRS.m_strSort = "NUMORD";
		if (!strcmp(buffer, "2"))
			OrdAllRS.m_strSort = "NREGADM";
		if (!strcmp(buffer, "3"))
			OrdAllRS.m_strSort = "DATREC";
		if (!strcmp(buffer, "4"))
			OrdAllRS.m_strSort = "NREGSERV";
	}
	else
	{
		GetPrivateProfileString("Sort", "DataSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		if (!strcmp(buffer, "1"))
			OrdAllRS.m_strSort = "NUMORD DESC";
		if (!strcmp(buffer, "2"))
			OrdAllRS.m_strSort = "NREGADM DESC";
		if (!strcmp(buffer, "3"))
			OrdAllRS.m_strSort = "DATREC DESC";
		if (!strcmp(buffer, "4"))
			OrdAllRS.m_strSort = "NREGSERV DESC";
	}
	GetPrivateProfileString("Filter", "AdmRegionNumber", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	AdmRegionNumber = atoi(buffer);
	GetPrivateProfileString("Filter", "OperationalService", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	OperationalService = atoi(buffer);
	if (AdmRegionNumber == 1 && OperationalService == 0)
	{
		GetPrivateProfileString("Filter", "AdmRegionNumberValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		S = buffer;
		OrdAllRS.m_strFilter = "NREGADM = " + S;
	}
	if (AdmRegionNumber == 0 && OperationalService == 1)
	{
		GetPrivateProfileString("Filter", "OperationalServiceValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		S = buffer;
		if (HasRegiServ)
			OrdAllRS.m_strFilter = "RegiServ = " + S;
		else
			OrdAllRS.m_strFilter = "NREGSERV = " + S;
	}
	if (AdmRegionNumber == 1 && OperationalService == 1)
	{
		GetPrivateProfileString("Filter", "AdmRegionNumberValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		S = buffer;
		GetPrivateProfileString("Filter", "OperationalServiceValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		S1 = buffer;
		if (HasRegiServ)
			OrdAllRS.m_strFilter = "NREGADM = " + S + " AND RegiServ = " + S1;
		else
			OrdAllRS.m_strFilter = "NREGADM = " + S + " AND NREGSERV = " + S1;
	}
	OrdAllRS.Open();
	if (!OrdAllRS.IsBOF())
		OrdAllRS.MoveFirst();
	while (!OrdAllRS.IsEOF())
	{
		if (OrdAllRS.m_DATREC >= DateBeginPeriod && OrdAllRS.m_DATREC <= DateEndPeriod && OrdAllRS.m_DATENDF <= DateEndPeriod)
		{
			NumberOrder.push_back(OrdAllRS.m_NUMORD);
			CodOrder.push_back(OrdAllRS.m_CODORD);
			StateOrder.push_back(OrdAllRS.m_STATEORD);
			DateTimeBegin.push_back(CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()));
			DateTimeEnd.push_back(CTime(OrdAllRS.m_DATENDF.GetYear(), OrdAllRS.m_DATENDF.GetMonth(), OrdAllRS.m_DATENDF.GetDay(), OrdAllRS.m_DATENDF.GetHour(), OrdAllRS.m_DATENDF.GetMinute(), OrdAllRS.m_DATENDF.GetSecond()));
			ServiceNumber.push_back(OrdAllRS.m_RegiServ);
			ServiceNumber2.push_back(OrdAllRS.m_NREGSERV);
			AdmNumber.push_back(OrdAllRS.m_NREGADM);
			CDatabNet* dn = new CDatabNet;
			dn->OpenNet("ODBC;DSN=" + StrConnectionArea, true);
			NameAdr na(dn, "NameAdr");
			sprintf(buffer, "Select area.NUMAREA, listname.NAME As street, area.ADDRESS, tplistnm.TYPADR From (area Left Join listname On area.STREET = listname.NUMNAME) Left Join tplistnm On listname.TYPNAM = tplistnm.NUMTPNAM Where (((area.NUMAREA) = %i) AND ((tplistnm.TYPADR) = 1))", OrdAllRS.m_CODORD);
			if (na.OpenNet(buffer, CRecordset::readOnly, "") == 1)
				Address.push_back(na.m_street + " " + na.m_ADDRESS);
			na.Close();
			dn->Close();
			for (int i = 0; i < 4; i++)
				Coordinates.push_back(0);
			NumOrd = OrdAllRS.m_CODORD;
		}
		OrdAllRS.MoveNext();
	}
	OrdAllRS.Close();
	Invalidate();
	strcpy_s(buffer, DateBeginPeriod.Format("%d.%m.%y %H:%M:%S"));
	WritePrivateProfileString("Period", "DateBegin", buffer, IniWay + "GraphSettings.ini");
	SaveBitmap = true;
}

void CGraphOrderView::OnPopupOpenOrder()
{
	// TODO: Add your command handler code here
	CGraphOrderApp* theAppMain = (CGraphOrderApp*)AfxGetApp();
	theAppMain->m_pMainWnd = theAppMain->pMainFrame;
	COrderSayApp* theApp = (COrderSayApp*)AfxGetApp();
	theApp->pDocTemplate = new CMultiDocTemplate(IDR_CHILDFRAME, RUNTIME_CLASS(COrderSayDoc), RUNTIME_CLASS(COrderMainFrame), RUNTIME_CLASS(COrderSayView));
	theApp->AddDocTemplate(theApp->pDocTemplate);
	COrderSayDoc* doc = (COrderSayDoc*)theApp->pDocTemplate->CreateNewDocument();
	COrderMainFrame* frm = (COrderMainFrame*)theApp->pDocTemplate->CreateNewFrame(doc, NULL);
	theApp->pDocTemplate->InitialUpdateFrame(frm, doc);
	theAppMain->m_pMainWnd = theAppMain->Wnd;
}

void CGraphOrderView::OnPopupOperationOrder(UINT nID)
{
	// TODO: Add your command handler code here
	HINSTANCE hWorder = ::AfxLoadLibrary("worder.dll");
	PFN_OrderOperation pfnOrderOperation;
	BOOL iCode;
	switch (nID)
	{
	case ID_POPUP_OPERATION_ORDER:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileProvExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 1:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileSoglExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 2:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileOpenzExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 3:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileClosExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 4:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileOtkaExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 5:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileKonsExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 6:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileRknsExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 7:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileWorkExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 8:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FilePsrkExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 9:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileCdpExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 10:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileRdpExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 11:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileDepartExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 12:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileRazrExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 13:
		MessageBox("Невозможно выполнить данную операцию!", "Сообщение", MB_ICONINFORMATION);
		break;
	case ID_POPUP_OPERATION_ORDER + 14:
		MessageBox("Невозможно выполнить данную операцию!", "Сообщение", MB_ICONINFORMATION);
		break;
	case ID_POPUP_OPERATION_ORDER + 15:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FilePereExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 16:
		MessageBox("Невозможно выполнить данную операцию!", "Сообщение", MB_ICONINFORMATION);
		break;
	case ID_POPUP_OPERATION_ORDER + 17:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FilePovrExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 18:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileNagrExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 19:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileAcciExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 20:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileMatExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 21:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileAssExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 22:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileNotExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	case ID_POPUP_OPERATION_ORDER + 23:
		MessageBox("Невозможно выполнить данную операцию!", "Сообщение", MB_ICONINFORMATION);
		break;
	case ID_POPUP_OPERATION_ORDER + 24:
		pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileCheckExt");
		iCode = (*pfnOrderOperation)(CurrentNumberOrder);
		break;
	default:
		MessageBox("Невозможно выполнить данную операцию!", "Сообщение", MB_ICONINFORMATION);
		break;
	}
}

void CGraphOrderView::OnPopupSearchOrder(UINT nID)
{
	// TODO: Add your command handler code here
	bool kz;
	CString *szValue;
	CRECQDATA *rsQData;
	DescrdocRead rdd;
	rdd.StrConnection = StrConnectionDescrdoc;
	rdd.Open();
	if (!rdd.IsBOF())
		rdd.MoveFirst();
	while (!rdd.IsEOF())
	{
		if (rdd.m_NAMEDOC == SearchOperations[nID - ID_POPUP_SEARCH_ORDER])
		{
			kz = OrderSearchData(WcomtxWay + "\\wcomtx.ini", "Region", rdd.m_NAMEDOC, rdd.m_CODDOC, rdd.m_QUERYDATA, &rsQData);
			break;
		}
		rdd.MoveNext();
	}
	rdd.Close();
	if (kz)
	{
		FindOrder.clear();
		FindOrderYear.clear();
		FindOrderAdm.clear();
		FindOrderService.clear();
		FindOrderStr.clear();
		rsQData->RequeryNet();
		while (!rsQData->IsEOF())
		{
			rsQData->FindValue("[CODORD]", szValue);
			FindOrder.push_back(atoi(*szValue));
			rsQData->FindValue("[YY]", szValue);
			FindOrderYear.push_back(atoi(*szValue));
			rsQData->MoveNext();
		}
		rsQData->Close();
		FindOrderResult();
		CGraphOrderApp* theAppMain = (CGraphOrderApp*)AfxGetApp();
		theAppMain->pMainFrame->SetActiveWindow();
	}
}

void CGraphOrderView::FindOrderResult()
{
	char buffer[MAX_PATH];
	int AdmRegionNumber, OperationalService, temp, CountOrders = 0, NumberPosition, NumOrd = 0;
	bool Found = false;
	CString IniWay, S, S1, AdmNameStr, ServiceNameStr;
	OrdAllRead OrdAllRS;
	CTimeSpan ChangeHours;
	CChooseOrderDlg dlg;

	IniWay = IniFile;
	IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));
	GetPrivateProfileString("Filter", "AdmRegionNumber", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	AdmRegionNumber = atoi(buffer);
	GetPrivateProfileString("Filter", "OperationalService", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	OperationalService = atoi(buffer);
	if (AdmRegionNumber == 1 || OperationalService == 1)
	MessageBox("Включена фильтрация! Заявка может быть найдена, но не отображена!", "Сообщение", MB_ICONINFORMATION);


	for (int i = 0; i < FindOrder.size() - 1; i++)
		for (int j = 0; j < FindOrder.size() - i - 1; j++)
		if (FindOrder[j] > FindOrder[j + 1])
		{
			temp = FindOrder[j];
			FindOrder[j] = FindOrder[j + 1];
			FindOrder[j + 1] = temp;
		}
	if (FindOrder.size() == 1)
	{
		NumberFindOrder = FindOrder[0];
		Found = true;


		IniWay = IniFile;
		IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));

		OrdAllRS.StrConnection = StrConnectionOrdAll;
		OrdAllRS.TableName = TableName;

		CDatabNet* dn = new CDatabNet;
		CRecordNet rn;
		dn->OpenNet("ODBC;DSN=" + StrConnectionOrdAll, false);
		rn.InitRecordNet(dn, TableName);
		if (rn.isField("RegiServ") == -1)
			OrdAllRS.HasRegiServ = false;
		else
			OrdAllRS.HasRegiServ = true;

		OrdAllRS.Open();
		if (!OrdAllRS.IsBOF())
			OrdAllRS.MoveFirst();
		while (!OrdAllRS.IsEOF())
		{
			if (OrdAllRS.m_CODORD == NumberFindOrder && OrdAllRS.m_YY == FindOrderYear[0])
			{
				ChangeHours = CTimeSpan(0, DurationPeriod / 2, 0, 0);
				DateBeginPeriod = CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()) - ChangeHours;
				DateEndPeriod = CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()) + ChangeHours;
				break;
			}
			OrdAllRS.MoveNext();
		}
		OrdAllRS.Close();

		NumberOrder.clear();
		CodOrder.clear();
		yy.clear();
		ServiceNumber.clear();
		AdmNumber.clear();
		Address.clear();
		StateOrder.clear();
		DateTimeBegin.clear();
		DateTimeEnd.clear();
		Coordinates.clear();
		ServiceNumber.clear();
		ServiceNumber2.clear();
		//NumberService.clear();
		//NameService.clear();
		//NumberAdm.clear();
		//NameAdm.clear();
		OrdAllRS.StrConnection = StrConnectionOrdAll;
		OrdAllRS.TableName = TableName;
		OrdAllRS.Open();
		if (!OrdAllRS.IsBOF())
			OrdAllRS.MoveFirst();
		while (!OrdAllRS.IsEOF())
		{
			if (OrdAllRS.m_DATREC >= DateBeginPeriod && OrdAllRS.m_DATREC <= DateEndPeriod && OrdAllRS.m_DATENDF <= DateEndPeriod)
			{
				NumberOrder.push_back(OrdAllRS.m_NUMORD);
				CodOrder.push_back(OrdAllRS.m_CODORD);
				StateOrder.push_back(OrdAllRS.m_STATEORD);
				DateTimeBegin.push_back(CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()));
				DateTimeEnd.push_back(CTime(OrdAllRS.m_DATENDF.GetYear(), OrdAllRS.m_DATENDF.GetMonth(), OrdAllRS.m_DATENDF.GetDay(), OrdAllRS.m_DATENDF.GetHour(), OrdAllRS.m_DATENDF.GetMinute(), OrdAllRS.m_DATENDF.GetSecond()));
				ServiceNumber.push_back(OrdAllRS.m_RegiServ);
				ServiceNumber2.push_back(OrdAllRS.m_NREGSERV);
				AdmNumber.push_back(OrdAllRS.m_NREGADM);
				CDatabNet* dn = new CDatabNet;
				dn->OpenNet("ODBC;DSN=" + StrConnectionArea, true);
				NameAdr na(dn, "NameAdr");
				sprintf(buffer, "Select area.NUMAREA, listname.NAME As street, area.ADDRESS, tplistnm.TYPADR From (area Left Join listname On area.STREET = listname.NUMNAME) Left Join tplistnm On listname.TYPNAM = tplistnm.NUMTPNAM Where (((area.NUMAREA) = %i) AND ((tplistnm.TYPADR) = 1))", OrdAllRS.m_CODORD);
				if (na.OpenNet(buffer, CRecordset::readOnly, "") == 1)
					Address.push_back(na.m_street + " " + na.m_ADDRESS);
				na.Close();
				dn->Close();
				for (int i = 0; i < 4; i++)
					Coordinates.push_back(0);
				NumOrd = OrdAllRS.m_CODORD;
			}
			OrdAllRS.MoveNext();
		}
		OrdAllRS.Close();
		Invalidate();
		strcpy_s(buffer, DateBeginPeriod.Format("%d.%m.%y %H:%M:%S"));
		WritePrivateProfileString("Period", "DateBegin", buffer, IniWay + "GraphSettings.ini");
		SaveBitmap = true;

		CDC* dc = GetDC();
		OnDraw(dc);
		RECT rtFrameArea;
		AfxGetMainWnd()->GetWindowRect(&rtFrameArea);
		RECT rtViewArea;
		this->GetWindowRect(&rtViewArea);
		int iX = rtViewArea.left - rtFrameArea.left;
		int iY = rtViewArea.top - rtFrameArea.top;
		int ax, ay, bx, by;
		for (int i = 0; i < CodOrder.size(); i++)
		{
			if (CodOrder[i] == NumberFindOrder)
			{
				ax = Coordinates[i * 4];
				ay = Coordinates[i * 4 + 1];
				bx = Coordinates[i * 4 + 2];
				by = Coordinates[i * 4 + 3];
			}
		}
		SetCursorPos(iX + (ax + bx) / 2, iY + (ay + by) / 2);
	}
	if (FindOrder.size() > 1)
	{
		OrdAllRS.StrConnection = StrConnectionOrdAll;
		OrdAllRS.TableName = TableName;
		OrdAllRS.Open();
		if (!OrdAllRS.IsBOF())
			OrdAllRS.MoveFirst();
		while (!OrdAllRS.IsEOF())
		{
			for (int i = 0; i < FindOrder.size(); i++)
			{
				if (OrdAllRS.m_CODORD == FindOrder[i] && OrdAllRS.m_YY == FindOrderYear[i])
				{
					FindOrderAdm.push_back(OrdAllRS.m_NREGADM);
					FindOrderService.push_back(OrdAllRS.m_NREGSERV);

					CDatabNet* dn = new CDatabNet;
					dn->OpenNet("ODBC;DSN=" + StrConnectionArea, true);
					NameAdr na(dn, "NameAdr");
					sprintf(buffer, "Select area.NUMAREA, listname.NAME As street, area.ADDRESS, tplistnm.TYPADR From (area Left Join listname On area.STREET = listname.NUMNAME) Left Join tplistnm On listname.TYPNAM = tplistnm.NUMTPNAM Where (((area.NUMAREA) = %i) AND ((tplistnm.TYPADR) = 1))", OrdAllRS.m_CODORD);
					if (na.OpenNet(buffer, CRecordset::readOnly, "") == 1)
						FindOrderAddress.push_back(na.m_street + " " + na.m_ADDRESS);
					na.Close();
					dn->Close();

					break;
				}
			}
			OrdAllRS.MoveNext();
		}
		OrdAllRS.Close();
		
		for (int i = 0; i < FindOrder.size(); i++)
		{
			for (int k = 0; k < NumberService.size(); k++)
				if (NumberService[k] == FindOrderService[i])
				{
					ServiceNameStr = NameService[k];
					break;
				}
			for (int k = 0; k < NumberAdm.size(); k++)
				if (NumberAdm[k] == FindOrderAdm[i])
				{
					AdmNameStr = NameAdm[k];
					break;
				}
			sprintf_s(buffer, "%i %i %s %s %s", FindOrderYear[i], FindOrder[i], FindOrderAddress[i], AdmNameStr, ServiceNameStr);
			FindOrderStr.push_back(buffer);
		}
		dlg.FindOrder = FindOrder;
		dlg.FindOrderStr = FindOrderStr;

		if (dlg.DoModal() == IDOK)
		{
			NumberFindOrder = dlg.NumberOrder;
			Found = true;

			IniWay = IniFile;
			IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));

			OrdAllRS.StrConnection = StrConnectionOrdAll;
			OrdAllRS.TableName = TableName;
			OrdAllRS.Open();
			if (!OrdAllRS.IsBOF())
				OrdAllRS.MoveFirst();
			while (!OrdAllRS.IsEOF())
			{
				if (OrdAllRS.m_CODORD == NumberFindOrder && OrdAllRS.m_YY == FindOrderYear[0])
				{
					ChangeHours = CTimeSpan(0, DurationPeriod / 2, 0, 0);
					DateBeginPeriod = CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()) - ChangeHours;
					DateEndPeriod = CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()) + ChangeHours;
					break;
				}
				OrdAllRS.MoveNext();
			}
			OrdAllRS.Close();

			NumberOrder.clear();
			CodOrder.clear();
			yy.clear();
			ServiceNumber.clear();
			AdmNumber.clear();
			Address.clear();
			StateOrder.clear();
			DateTimeBegin.clear();
			DateTimeEnd.clear();
			Coordinates.clear();
			ServiceNumber.clear();
			ServiceNumber2.clear();
			//NumberService.clear();
			//NameService.clear();
			//NumberAdm.clear();
			//NameAdm.clear();
			OrdAllRS.StrConnection = StrConnectionOrdAll;
			OrdAllRS.TableName = TableName;
			OrdAllRS.Open();
			if (!OrdAllRS.IsBOF())
				OrdAllRS.MoveFirst();
			while (!OrdAllRS.IsEOF())
			{
				if (OrdAllRS.m_DATREC >= DateBeginPeriod && OrdAllRS.m_DATREC <= DateEndPeriod && OrdAllRS.m_DATENDF <= DateEndPeriod)
				{
					NumberOrder.push_back(OrdAllRS.m_NUMORD);
					CodOrder.push_back(OrdAllRS.m_CODORD);
					StateOrder.push_back(OrdAllRS.m_STATEORD);
					DateTimeBegin.push_back(CTime(OrdAllRS.m_DATREC.GetYear(), OrdAllRS.m_DATREC.GetMonth(), OrdAllRS.m_DATREC.GetDay(), OrdAllRS.m_DATREC.GetHour(), OrdAllRS.m_DATREC.GetMinute(), OrdAllRS.m_DATREC.GetSecond()));
					DateTimeEnd.push_back(CTime(OrdAllRS.m_DATENDF.GetYear(), OrdAllRS.m_DATENDF.GetMonth(), OrdAllRS.m_DATENDF.GetDay(), OrdAllRS.m_DATENDF.GetHour(), OrdAllRS.m_DATENDF.GetMinute(), OrdAllRS.m_DATENDF.GetSecond()));
					ServiceNumber.push_back(OrdAllRS.m_RegiServ);
					ServiceNumber2.push_back(OrdAllRS.m_NREGSERV);
					AdmNumber.push_back(OrdAllRS.m_NREGADM);
					CDatabNet* dn = new CDatabNet;
					dn->OpenNet("ODBC;DSN=" + StrConnectionArea, true);
					NameAdr na(dn, "NameAdr");
					sprintf(buffer, "Select area.NUMAREA, listname.NAME As street, area.ADDRESS, tplistnm.TYPADR From (area Left Join listname On area.STREET = listname.NUMNAME) Left Join tplistnm On listname.TYPNAM = tplistnm.NUMTPNAM Where (((area.NUMAREA) = %i) AND ((tplistnm.TYPADR) = 1))", OrdAllRS.m_CODORD);
					if (na.OpenNet(buffer, CRecordset::readOnly, "") == 1)
						Address.push_back(na.m_street + " " + na.m_ADDRESS);
					na.Close();
					dn->Close();
					for (int i = 0; i < 4; i++)
						Coordinates.push_back(0);
					NumOrd = OrdAllRS.m_CODORD;
				}
				OrdAllRS.MoveNext();
			}
			OrdAllRS.Close();
			Invalidate();
			strcpy_s(buffer, DateBeginPeriod.Format("%d.%m.%y %H:%M:%S"));
			WritePrivateProfileString("Period", "DateBegin", buffer, IniWay + "GraphSettings.ini");
			SaveBitmap = true;

			CDC* dc = GetDC();
			OnDraw(dc);
			RECT rtFrameArea;
			AfxGetMainWnd()->GetWindowRect(&rtFrameArea);
			RECT rtViewArea;
			this->GetWindowRect(&rtViewArea);
			int iX = rtViewArea.left - rtFrameArea.left;
			int iY = rtViewArea.top - rtFrameArea.top;
			int ax, ay, bx, by;
			for (int i = 0; i < CodOrder.size(); i++)
			{
				if (CodOrder[i] == NumberFindOrder)
				{
					ax = Coordinates[i * 4];
					ay = Coordinates[i * 4 + 1];
					bx = Coordinates[i * 4 + 2];
					by = Coordinates[i * 4 + 3];
				}
			}
			SetCursorPos(iX + (ax + bx) / 2, iY + (ay + by) / 2);

		}
	}
}

void CGraphOrderView::OnOpenAbout()
{
	// TODO: Add your command handler code here
	AboutProgramDlg dlg;
	dlg.DoModal();
}

void CGraphOrderView::OnPopupRegistrOrder()
{
	// TODO: Add your command handler code here
	HINSTANCE hWorder = ::AfxLoadLibrary("worder.dll");
	PFN_OrderOperation pfnOrderOperation;
	BOOL iCode;
	pfnOrderOperation = (PFN_OrderOperation)GetProcAddress(hWorder, "FileRegistrExt");
	iCode = (*pfnOrderOperation)(CurrentNumberOrder);
}

void CGraphOrderView::OnAppExit()
{
	// TODO: Add your command handler code here
	PostQuitMessage(0);
}

void CGraphOrderView::OnDestroy()
{
	CScrollView::OnDestroy();

	// TODO: Add your message handler code here
	::SendMessage(hwndTT, TTM_TRACKACTIVATE, false, (LPARAM)(LPTOOLINFO)&ti);
}

void CGraphOrderView::OnKillFocus(CWnd* pNewWnd)
{
	CScrollView::OnKillFocus(pNewWnd);

	// TODO: Add your message handler code here
	::SendMessage(hwndTT, TTM_TRACKACTIVATE, false, (LPARAM)(LPTOOLINFO)&ti);
}
