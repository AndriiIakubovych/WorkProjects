// GeneralSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "GeneralSettingsDlg.h"

#include "SelectStateOrder.h"

#include "MetaTableRead.h"
#include "NregionRead.h"
#include "CodTechRead.h"
#include "AdmRead.h"
#include "ServiceRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGeneralSettingsDlg dialog

CSelectStateOrder* pSSO;

CGeneralSettingsDlg::CGeneralSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGeneralSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGeneralSettingsDlg)
	//}}AFX_DATA_INIT
}


void CGeneralSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGeneralSettingsDlg)
	DDX_Control(pDX, IDC_SELECT_OPERATIONAL_FILTER, m_Operational_service);
	DDX_Control(pDX, IDC_SELECT_ADM_REGION_FILTER, m_Adm_region_name);
	DDX_Control(pDX, IDC_ADM_REGION_NAME_FILTER, m_Adm_region_name_filter);
	DDX_Control(pDX, IDC_OPERATIONAL_SERVICE_FILTER, m_Operational_service_filter);
	DDX_Control(pDX, IDC_INPUT_WIDTH_COLUMN, m_Width_column);
	DDX_Control(pDX, IDC_VIEW_LEGEND, m_View_legend);
	DDX_Control(pDX, IDC_VIEW_GRID, m_View_grid);
	DDX_Control(pDX, IDC_SELECT_STATE_ORDER, m_Select_state_order);
	DDX_Control(pDX, IDC_INCREASE_SORT, m_Increase_sort);
	DDX_Control(pDX, IDC_DECREASE_SORT, m_Decrease_sort);
	DDX_Control(pDX, IDC_NUMBER_ORDER_SORT, m_Number_order_sort);
	DDX_Control(pDX, IDC_ADM_REGION_NUMBER_SORT, m_Adm_region_number_sort);
	DDX_Control(pDX, IDC_DATE_RECEIPT_ORDER_SORT, m_Date_receipt_order_sort);
	DDX_Control(pDX, IDC_OPERATIONAL_SERVICE_SORT, m_Operational_service_sort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGeneralSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CGeneralSettingsDlg)
	ON_BN_CLICKED(IDC_CHANGE_COLOR_STATE, OnChangeColorState)
	ON_BN_CLICKED(IDC_VIEW_GRID, OnViewGrid)
	ON_BN_CLICKED(IDC_VIEW_LEGEND, OnViewLegend)
	ON_EN_CHANGE(IDC_INPUT_WIDTH_COLUMN, OnChangeInputWidthColumn)
	ON_BN_CLICKED(IDC_OPERATIONAL_SERVICE_FILTER, OnOperationalServiceFilter)
	ON_BN_CLICKED(IDC_ADM_REGION_NAME_FILTER, OnAdmRegionNameFilter)
	ON_BN_CLICKED(IDC_INSCRIPTION_FONT, OnInscriptionFont)
	ON_BN_CLICKED(IDC_NAME_FONT, OnNameFont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGeneralSettingsDlg message handlers

BOOL CGeneralSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	char buffer[MAX_PATH];
	CString IniWay, StrConnectionCodTech;
	int i = 0;
	MetaTableRead rsmt;
	NregionRead rsn;
	CodTechRead CodTechRS;
	AdmRead rsa;
	ServiceRead rss;
	CWnd* pWnd;
	bool select = false;
	IniWay = IniFile;
	IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));
	GetPrivateProfileString("View", "Grid", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	if (atoi(buffer) == 1)
	{
		m_View_grid.SetCheck(1);
		ViewGrid = 1;
	}
	else
		ViewGrid = 0;
	GetPrivateProfileString("View", "Legend", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	if (atoi(buffer) == 1)
	{
		m_View_legend.SetCheck(1);
		ViewLegend = 1;
	}
	else
		ViewLegend = 0;
	GetPrivateProfileString("View", "WidthColumn", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	m_Width_column.SetWindowText(buffer);
	rsmt.IniFile = IniFile;
	rsmt.Open();
	rsn.IniFile = IniFile;
	rsn.Open();
	if (!rsmt.IsBOF())
		rsmt.MoveFirst();
	while (!rsmt.IsEOF())
	{
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
		rsmt.MoveNext();
	}
	rsn.Close();
	rsmt.Close();
	CodTechRS.StrConnection = StrConnectionCodTech;
	CodTechRS.Open();
	if (!CodTechRS.IsBOF())
		CodTechRS.MoveFirst();
	while (!CodTechRS.IsEOF())
	{
		if (CodTechRS.m_CODCLAS == 51)
			m_Select_state_order.AddString(NULL);
		CodTechRS.MoveNext();
	}
	m_Select_state_order.SetCurSel(0);
	CodTechRS.Close();
	pSSO = (CSelectStateOrder*)GetDlgItem(IDC_SELECT_STATE_ORDER);
	pSSO->IniFile = IniFile;
	pSSO->StrConnection = StrConnectionCodTech;
	pSSO->DrawItemNumber = 0;
	GetPrivateProfileString("Sort", "TypeSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	if (atoi(buffer) == 1)
		m_Increase_sort.SetCheck(1);
	else
		m_Decrease_sort.SetCheck(1);
	GetPrivateProfileString("Sort", "DataSort", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	if (atoi(buffer) == 1)
		m_Number_order_sort.SetCheck(1);
	if (atoi(buffer) == 2)
		m_Adm_region_number_sort.SetCheck(1);
	if (atoi(buffer) == 3)
		m_Date_receipt_order_sort.SetCheck(1);
	if (atoi(buffer) == 4)
		m_Operational_service_sort.SetCheck(1);
	rsa.StrConnection = StrConnectionAdm;
	rsa.Open();
	if (!rsa.IsBOF())
		rsa.MoveFirst();
	while (!rsa.IsEOF())
	{
		m_Adm_region_name.AddString(rsa.m_NAMADM);
		GetPrivateProfileString("Filter", "AdmRegionNumberValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
		if (rsa.m_NREGADM == atoi(buffer))
		{
			m_Adm_region_name.SetCurSel(i);
			select = true;
		}
		i++;
		rsa.MoveNext();
	}
	rsa.Close();
	if (!select)
		m_Adm_region_name.SetCurSel(0);
	i = 0;
	select = false;
	rss.StrConnection = StrConnectionService;
	rss.Open();
	if (!rss.IsBOF())
		rss.MoveFirst();
	while (!rss.IsEOF())
	{
		if (rss.m_NREGSERV == 33 || rss.m_NREGSERV == 49 || rss.m_NREGSERV == 50 || rss.m_NREGSERV == 51 || rss.m_NREGSERV == 1 || rss.m_NREGSERV == 3 || rss.m_NREGSERV == 4)
		{
			m_Operational_service.AddString(rss.m_NAMSERV);
			GetPrivateProfileString("Filter", "OperationalServiceValue", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			if (rss.m_NREGSERV == atoi(buffer))
			{
				m_Operational_service.SetCurSel(i);
				select = true;
			}
			i++;
		}
		rss.MoveNext();
	}
	rss.Close();
	if (!select)
		m_Operational_service.SetCurSel(0);
	select = false;
	GetPrivateProfileString("Filter", "AdmRegionNumber", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	if (atoi(buffer) == 1)
	{
		m_Adm_region_name_filter.SetCheck(1);
		pWnd = GetDlgItem(IDC_SELECT_ADM_REGION_FILTER);
		pWnd->EnableWindow(true);
	}
	else
	{
		m_Adm_region_name_filter.SetCheck(0);
		pWnd = GetDlgItem(IDC_SELECT_ADM_REGION_FILTER);
		pWnd->EnableWindow(false);
	}
	GetPrivateProfileString("Filter", "OperationalService", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	if (atoi(buffer) == 1)
	{
		m_Operational_service_filter.SetCheck(1);
		pWnd = GetDlgItem(IDC_SELECT_OPERATIONAL_FILTER);
		pWnd->EnableWindow(true);
	}
	else
	{
		m_Operational_service_filter.SetCheck(0);
		pWnd = GetDlgItem(IDC_SELECT_OPERATIONAL_FILTER);
		pWnd->EnableWindow(false);
	}
	ChangeInscriptionFont = false;
	ChangeNameFont = false;

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CGeneralSettingsDlg::OnChangeColorState()
{
	// TODO: Add your control notification handler code here
	pSSO = (CSelectStateOrder*)GetDlgItem(IDC_SELECT_STATE_ORDER);
	CColorDialog cd(pSSO->Color, NULL, NULL);
	if (cd.DoModal() == IDOK)
	{
		Color = cd.GetColor();
		pSSO->Red[pSSO->SelectItem] = GetRValue(Color);
		pSSO->Green[pSSO->SelectItem] = GetGValue(Color);
		pSSO->Blue[pSSO->SelectItem] = GetBValue(Color);
		Red = pSSO->Red;
		Green = pSSO->Green;
		Blue = pSSO->Blue;
		m_Select_state_order.SetCurSel(pSSO->SelectItem);
	}
}

void CGeneralSettingsDlg::OnViewGrid()
{
	// TODO: Add your control notification handler code here
	ViewGrid = m_View_grid.GetCheck();
}

void CGeneralSettingsDlg::OnViewLegend()
{
	// TODO: Add your control notification handler code here
	ViewLegend = m_View_legend.GetCheck();
}

void CGeneralSettingsDlg::OnChangeInputWidthColumn()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	m_Width_column.GetWindowText(WidthColumn);
}

void CGeneralSettingsDlg::OnAdmRegionNameFilter()
{
	// TODO: Add your control notification handler code here
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_SELECT_ADM_REGION_FILTER);
	pWnd->EnableWindow(m_Adm_region_name_filter.GetCheck());
}

void CGeneralSettingsDlg::OnOperationalServiceFilter()
{
	// TODO: Add your control notification handler code here
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_SELECT_OPERATIONAL_FILTER);
	pWnd->EnableWindow(m_Operational_service_filter.GetCheck());
}

void CGeneralSettingsDlg::OnOK()
{
	// TODO: Add extra validation here
	char buffer[MAX_PATH];
	CString IniWay, AdmRegionNameStr, OperationalServiceStr;
	AdmRead rsa;
	ServiceRead rss;
	if (atoi(WidthColumn) > 0)
	{
		if (m_Increase_sort.GetCheck())
			IncreaseSort = true;
		else
			IncreaseSort = false;
		if (m_Decrease_sort.GetCheck())
			DecreaseSort = true;
		else
			DecreaseSort = false;
		if (m_Number_order_sort.GetCheck())
			NumberOrderSort = true;
		else
			NumberOrderSort = false;
		if (m_Adm_region_number_sort.GetCheck())
			AdmRegionNumberSort = true;
		else
			AdmRegionNumberSort = false;
		if (m_Date_receipt_order_sort.GetCheck())
			DateReceiptOrderSort = true;
		else
			DateReceiptOrderSort = false;
		if (m_Operational_service_sort.GetCheck())
			OperationalServiceSort = true;
		else
			OperationalServiceSort = false;
		m_Adm_region_name.GetWindowText(AdmRegionNameStr);
		rsa.StrConnection = StrConnectionAdm;
		rsa.Open();
		if (!rsa.IsBOF())
			rsa.MoveFirst();
		while (!rsa.IsEOF())
		{
			if (rsa.m_NAMADM == AdmRegionNameStr)
			{
				sprintf(buffer, "%i", rsa.m_NREGADM);
				AdmRegionNumber = buffer;
			}
			rsa.MoveNext();
		}
		rsa.Close();
		m_Operational_service.GetWindowText(OperationalServiceStr);
		rss.StrConnection = StrConnectionService;
		rss.Open();
		if (!rss.IsBOF())
			rss.MoveFirst();
		while (!rss.IsEOF())
		{
			if (rss.m_NAMSERV == OperationalServiceStr)
			{
				sprintf(buffer, "%i", rss.m_NREGSERV);
				OperationalService = buffer;
			}
			rss.MoveNext();
		}
		rss.Close();
		if (m_Adm_region_name_filter.GetCheck())
			AdmRegNumFilter = true;
		else
			AdmRegNumFilter = false;
		if (m_Operational_service_filter.GetCheck())
			OperatServFilter = true;
		else
			OperatServFilter = false;
		CDialog::OnOK();
	}
	else
		MessageBox("Данные заданы неверно!", "Сообщение", MB_OK | MB_ICONINFORMATION);
}

void CGeneralSettingsDlg::OnInscriptionFont()
{
	// TODO: Add extra validation here
	CFontDialog dlg(&lfh);
	dlg.m_cf.rgbColors = fci;
	if (dlg.DoModal() == IDOK)
	{
		ChangeInscriptionFont = true;
		memcpy(&lfh, dlg.m_cf.lpLogFont, sizeof(LOGFONT));
		memcpy(&lfv, dlg.m_cf.lpLogFont, sizeof(LOGFONT));
		fci = dlg.GetColor();
		lfv.lfEscapement = -900;
	}
}

void CGeneralSettingsDlg::OnNameFont()
{
	// TODO: Add extra validation here
	CFontDialog dlg(&lfn);
	dlg.m_cf.rgbColors = fcn;
	if (dlg.DoModal() == IDOK)
	{
		ChangeNameFont = true;
		memcpy(&lfn, dlg.m_cf.lpLogFont, sizeof(LOGFONT));
		fcn = dlg.GetColor();
	}
}