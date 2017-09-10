// AddFilesExpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "AddFilesExpDlg.h"

#include "FilesExpImpRead.h"
#include "TplineRead.h"
#include "TpnameRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddFilesExpDlg dialog

int CALLBACK AddExpSortFunc(LPARAM lParamFirst, LPARAM lParamSecond, LPARAM lParamSort);

typedef struct
{
	LPTSTR pszFileName;
	LPTSTR pszTypeGraphObject;
	LPTSTR pszTypeGraphObj;
}
ITEMDATA, *PITEMDATA;


AddFilesExpDlg::AddFilesExpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddFilesExpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddFilesExpDlg)
	m_Complement_areas_centers_knots_bool = FALSE;
	m_Query_exp_str = _T("");
	//}}AFX_DATA_INIT
}


void AddFilesExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddFilesExpDlg)
	DDX_Control(pDX, IDC_COMPLEMENT_CENTERS, m_Complement_areas_centers_knots);
	DDX_Control(pDX, IDC_LIST, m_List);
	DDX_Check(pDX, IDC_COMPLEMENT_CENTERS, m_Complement_areas_centers_knots_bool);
	DDX_Text(pDX, IDC_QUERY, m_Query_exp_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddFilesExpDlg, CDialog)
	//{{AFX_MSG_MAP(AddFilesExpDlg)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_LIST, OnEndlabeleditList)
	ON_NOTIFY(HDN_ITEMCLICK, IDC_LIST, OnItemclickList)
	ON_NOTIFY(HDN_ITEMCLICK, 0, OnItemclickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddFilesExpDlg message handlers

BOOL AddFilesExpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd* pWnd;
	CWindowDC winDC(this);
	int n = 0, j = 0, CountPixels;
	char buffer[MAX_PATH];
	CRect rect;
	m_List.GetClientRect(&rect);
	if (winDC.GetDeviceCaps(LOGPIXELSY) <= 96)
		CountPixels = 5;
	if (winDC.GetDeviceCaps(LOGPIXELSY) > 96 && winDC.GetDeviceCaps(LOGPIXELSY) < 140)
		CountPixels = 6;
	if (winDC.GetDeviceCaps(LOGPIXELSY) >= 140)
		CountPixels = 8;
	m_List.InsertColumn(0, "Имя файла для экспорта", LVCFMT_LEFT, rect.Width() / 3 - CountPixels, 0);
	m_List.InsertColumn(1, "Вид графического объекта", LVCFMT_LEFT, rect.Width() / 3 - CountPixels, 1);
	m_List.InsertColumn(2, "Тип графического объекта", LVCFMT_LEFT, rect.Width() / 3 - (CountPixels + 1), 2);
	TplineRead rstl;
	rstl.StrConnection = StrConnection;
	rstl.Open();
	if (!rstl.IsBOF())
		rstl.MoveFirst();
	while (!rstl.IsEOF())
	{
		n++;
		rstl.MoveNext();
	}
	TpnameRead rstn;
	rstn.StrConnection = StrConnection;
	rstn.Open();
	if (!rstn.IsBOF())
		rstn.MoveFirst();
	while (!rstn.IsEOF())
	{
		n++;
		rstn.MoveNext();
	}
	static CString** strData;
	strData = new CString *[n];
	for (int i = 0; i < n; i++)
		strData[i] = new CString[3];
	if (!rstl.IsBOF())
		rstl.MoveFirst();
	while (!rstl.IsEOF())
	{
		strcpy(buffer, rstl.m_NAMTP);
		for (i = 0; i < MAX_PATH; i++)
			if (buffer[i] == ' ' || buffer[i] == ',')
				buffer[i] = '_';
		strData[j][0] = buffer;
		strData[j][1] = rstl.m_NAMTP;
		strData[j][2] = "Ломанная";
		j++;
		rstl.MoveNext();
	}
	if (!rstn.IsBOF())
		rstn.MoveFirst();
	while (!rstn.IsEOF())
	{
		strcpy(buffer, rstn.m_NAMNAM);
		for (i = 0; i < MAX_PATH; i++)
			if (buffer[i] == ' ' || buffer[i] == ',')
				buffer[i] = '_';
		strData[j][0] = buffer;
		strData[j][1] = rstn.m_NAMNAM;
		if (rstn.m_VIDOBJ == 2)
			strData[j][2] = "Надпись";
		else
			strData[j][2] = rstn.m_NAMNAM;
		j++;
		rstn.MoveNext();
	}
	ITEMDATA* m_pData = new ITEMDATA[n];
	for (i = 0; i < n; i++)
	{
		m_pData[i].pszFileName = (LPTSTR)(LPCTSTR)strData[i][0];
		m_pData[i].pszTypeGraphObject = (LPTSTR)(LPCTSTR)strData[i][1];
		m_pData[i].pszTypeGraphObj = (LPTSTR)(LPCTSTR)strData[i][2];
		m_List.InsertItem(i, strData[i][0]);
		m_List.SetItemText(i, 1, strData[i][1]);
		m_List.SetItemText(i, 2, strData[i][2]);
		m_List.SetItemData(i, (LPARAM)&m_pData[i]);
	}
	if (GROUPREG != 2)
	{
		CWnd* pWnd = GetDlgItem(IDC_COMPLEMENT_CENTERS);
		pWnd->EnableWindow(true);
	}
	m_List.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_List.SetItem(0, 0, LVIF_STATE, NULL, 0, LVIS_SELECTED, LVIS_SELECTED, 0);
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		pWnd = GetDlgItem(IDOK);
		pWnd->EnableWindow(false);
	}
	else
	{
		pWnd = GetDlgItem(IDOK);
		pWnd->EnableWindow(true);
	}
	rstl.Close();
	rstn.Close();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AddFilesExpDlg::OnEndlabeleditList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	if (pDispInfo->item.pszText != NULL)
		m_List.SetItemText(pDispInfo->item.iItem, 0, pDispInfo->item.pszText);
	*pResult = 0;
}

void AddFilesExpDlg::OnItemclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HD_NOTIFY *phdn = (HD_NOTIFY *) pNMHDR;
	// TODO: Add your control notification handler code here
	NMLISTVIEW *pLV = (NMLISTVIEW*)pNMHDR;
	m_List.SortItems(AddExpSortFunc, pLV->iItem);
	*pResult = 0;
}

int CALLBACK AddExpSortFunc(LPARAM lParamFirst, LPARAM lParamSecond, LPARAM lParamSort)
{
	int nRetVal;
	PITEMDATA pDataFirst = (PITEMDATA)lParamFirst;
	PITEMDATA pDataSecond = (PITEMDATA)lParamSecond;
	switch (lParamSort)
	{
		case 0:
			nRetVal = strcmp(pDataFirst->pszFileName, pDataSecond->pszFileName);
			break;
		case 1:
			nRetVal = strcmp(pDataFirst->pszTypeGraphObject, pDataSecond->pszTypeGraphObject);
			break;
		case 2:
			nRetVal = strcmp(pDataFirst->pszTypeGraphObj, pDataSecond->pszTypeGraphObj);
			break;
		default:
			break;
	}
	return nRetVal;
}

void AddFilesExpDlg::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos == NULL)
	{
		CWnd* pWnd = GetDlgItem(IDOK);
		pWnd->EnableWindow(false);
	}
	else
	{
		CWnd* pWnd = GetDlgItem(IDOK);
		pWnd->EnableWindow(true);
	}
	*pResult = 0;
}

void AddFilesExpDlg::OnOK() 
{
	// TODO: Add extra validation here
	int iSelItem;
	char buffer_type_object[MAX_PATH], buffer_type_obj[MAX_PATH];
	CString buffer_type_obj_str;
	bool RepeateFile = false;
	FilesExpImpRead FilesRS;
	FilesRS.IniFile = IniFile;
	FilesRS.Open();
	TplineRead rstl;
	rstl.StrConnection = StrConnection;
	rstl.Open();
	TpnameRead rstn;
	rstn.StrConnection = StrConnection;
	rstn.Open();
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	if (pos != NULL)
		iSelItem = m_List.GetNextSelectedItem(pos);
	CountSelectedElements = m_List.GetSelectedCount();
	NameFile = new CString[CountSelectedElements];
	TypeGraphObject = new int[CountSelectedElements];
	TypeGraphObj = new int[CountSelectedElements];
	for (int i = 0; i < m_List.GetSelectedCount(); i++)
	{
		m_List.GetItemText(iSelItem + i, 0, buffer_type_object, MAX_PATH);
		NameFile[i] = buffer_type_object;
		m_List.GetItemText(iSelItem + i, 1, buffer_type_object, MAX_PATH);
		m_List.GetItemText(iSelItem + i, 2, buffer_type_obj, MAX_PATH);
		buffer_type_obj_str = buffer_type_obj;
		if (buffer_type_obj_str == "Ломанная")
		{
			if (!rstl.IsBOF())
				rstl.MoveFirst();
			while (!rstl.IsEOF())
			{
				if (rstl.m_NAMTP == buffer_type_object)
				{
					TypeGraphObject[i] = rstl.m_TYPBLINE;
					TypeGraphObj[i] = rstl.m_VIDOBJ;
					break;
				}
				rstl.MoveNext();
			}
		}
		else
		{
			if (!rstn.IsBOF())
				rstn.MoveFirst();
			while (!rstn.IsEOF())
			{
				if (rstn.m_NAMNAM == buffer_type_object)
				{
					TypeGraphObject[i] = rstn.m_TYPNAM;
					TypeGraphObj[i] = rstn.m_VIDOBJ;
					break;
				}
				rstn.MoveNext();
			}
		}
		if (!FilesRS.IsBOF())
			FilesRS.MoveFirst();
		while (!FilesRS.IsEOF())
		{
			if (FilesRS.m_Name_file == NameFile[i] && FilesRS.m_Id_profile == IdProfile)
			{
				RepeateFile = true;
				MessageBox("Файл для данного профиля с именем \"" + NameFile[i] + "\" уже существует!", "Сообщение", MB_OK | MB_ICONINFORMATION);
				break;
			}
			FilesRS.MoveNext();
		}
	}
	FilesRS.Close();
	rstl.Close();
	rstn.Close();
	if (RepeateFile)
		return;
	else
		CDialog::OnOK();
}
