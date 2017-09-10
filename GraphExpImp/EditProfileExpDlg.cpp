// EditProfileExpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "EditProfileExpDlg.h"

#include "NregionRead.h"
#include "DesspaceRead.h"

#pragma comment(lib,"OutGraf.lib")
#include "grafstr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef BIF_NEWDIALOGSTYLE
#define BIF_NEWDIALOGSTYLE 0x0040
#endif

/////////////////////////////////////////////////////////////////////////////
// EditProfileExpDlg dialog

static TCHAR path[MAX_PATH];
static bool enable = false;
static DesspaceRead rsd;


EditProfileExpDlg::EditProfileExpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(EditProfileExpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditProfileExpDlg)
	m_Name_profile_str = _T("");
	m_Factor_x_str = _T("");
	m_Factor_y_str = _T("");
	m_Shift_x_str = _T("");
	m_Shift_y_str = _T("");
	m_Turn_str = _T("");
	m_Graph_area_bool = FALSE;
	m_Metre_int = -1;
	m_Choosen_folder_str = _T("");
	//}}AFX_DATA_INIT
}


void EditProfileExpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditProfileExpDlg)
	DDX_Control(pDX, IDC_GRAPH_AREA_NAME, m_Graph_area_name);
	DDX_Control(pDX, IDC_GRAPH_AREA, m_Graph_area);
	DDX_Control(pDX, IDC_TURN, m_Turn);
	DDX_Control(pDX, IDC_SHIFT_Y, m_Shift_y);
	DDX_Control(pDX, IDC_SHIFT_X, m_Shift_x);
	DDX_Control(pDX, IDC_FACTOR_Y, m_Factor_y);
	DDX_Control(pDX, IDC_FACTOR_X, m_Factor_x);
	DDX_Control(pDX, IDC_FOLDER, m_Choosen_folder);
	DDX_Control(pDX, IDC_SECTION, m_Name_section);
	DDX_Control(pDX, IDC_NAME_PROFILE, m_Name_profile);
	DDX_Text(pDX, IDC_FACTOR_X, m_Factor_x_str);
	DDX_Text(pDX, IDC_FACTOR_Y, m_Factor_y_str);
	DDX_Text(pDX, IDC_SHIFT_X, m_Shift_x_str);
	DDX_Text(pDX, IDC_SHIFT_Y, m_Shift_y_str);
	DDX_Text(pDX, IDC_TURN, m_Turn_str);
	DDX_Check(pDX, IDC_GRAPH_AREA, m_Graph_area_bool);
	DDX_Radio(pDX, IDC_METRE, m_Metre_int);
	DDX_Text(pDX, IDC_FOLDER, m_Choosen_folder_str);
	DDX_Text(pDX, IDC_NAME_PROFILE, m_Name_profile_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditProfileExpDlg, CDialog)
	//{{AFX_MSG_MAP(EditProfileExpDlg)
	ON_EN_CHANGE(IDC_NAME_PROFILE, OnChangeNameProfile)
	ON_CBN_SELCHANGE(IDC_SECTION, OnSelchangeSection)
	ON_BN_CLICKED(IDC_OPEN_SELECT_FOLDER, OnOpenSelectFolder)
	ON_BN_CLICKED(IDC_GRAPH_AREA, OnGraphArea)
	ON_EN_CHANGE(IDC_FACTOR_X, OnChangeFactorX)
	ON_EN_CHANGE(IDC_FACTOR_Y, OnChangeFactorY)
	ON_EN_CHANGE(IDC_SHIFT_X, OnChangeShiftX)
	ON_EN_CHANGE(IDC_SHIFT_Y, OnChangeShiftY)
	ON_EN_CHANGE(IDC_TURN, OnChangeTurn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditProfileExpDlg message handlers

BOOL EditProfileExpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CDatabase db;
	char buffer[MAX_PATH], str_person[MAX_PATH];
	bool CurrentSelect = false;
	CString NameSection;
	CWnd* pWnd;
	NregionRead rsn, rsn_new;
	rsn.IniFile = IniFile;
	rsn_new.IniFile = IniFile;
	rsn.Open();
	rsn_new.Open();
	if (!rsn.IsBOF())
		rsn.MoveFirst();
	while (!rsn.IsEOF())
	{
		try
		{
			if (rsn.m_GRUPREG == 2 || rsn.m_GRUPREG == 14)
			{
				db.Open("ODBC;DSN=" + rsn.m_PATH);
				if (db.IsOpen())
					m_Name_section.AddString(rsn.m_NAMREG);
				db.Close();
			}
			if (rsn.m_GRUPREG == 4)
			{
				db.Open("ODBC;DSN=" + rsn.m_PATH);
				if (db.IsOpen())
				{
					if (!rsn_new.IsBOF())
						rsn_new.MoveFirst();
					while (!rsn_new.IsEOF())
					{
						if (rsn.m_PATH == rsn_new.m_PATH && rsn_new.m_GRUPREG == 14)
							m_Name_section.AddString(rsn.m_NAMREG);
						rsn_new.MoveNext();
					}
				}
				db.Close();
			}
			if (rsn.m_NUMREG == NumberSection)
				NameSection = rsn.m_NAMREG;
		}
		catch (...) { }
		rsn.MoveNext();
	}
	for (int i = 0; i < m_Name_section.GetCount(); i++)
	{
		m_Name_section.SetCurSel(i);
		m_Name_section.GetWindowText(buffer, MAX_PATH);
		if (buffer == NameSection)
		{
			CurrentSelect = true;
			break;
		}
	}
	if (!CurrentSelect)
		m_Name_section.SetCurSel(0);
	GetPrivateProfileString("Supshort", "PERSON", NULL, str_person, sizeof(str_person), IniFile);
	PERSON = atoi(str_person);
	rsn.Close();
	rsn_new.Close();
	if (m_Graph_area.GetCheck())
	{
		pWnd = GetDlgItem(IDC_SELECT_GRAPH_AREA_NAME);
		pWnd->EnableWindow(true);
		pWnd = GetDlgItem(IDC_GRAPH_AREA_NAME);
		pWnd->EnableWindow(true);
	}
	else
	{
		pWnd = GetDlgItem(IDC_SELECT_GRAPH_AREA_NAME);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDC_GRAPH_AREA_NAME);
		pWnd->EnableWindow(false);
	}
	OnSelchangeSection();
	CurrentSelect = false;
	for (i = 0; i < m_Graph_area_name.GetCount(); i++)
	{
		m_Graph_area_name.SetCurSel(i);
		m_Graph_area_name.GetWindowText(buffer, MAX_PATH);
		if (buffer == GraphAreaName)
		{
			CurrentSelect = true;
			break;
		}
	}
	if (!CurrentSelect)
		m_Graph_area_name.SetCurSel(0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void EditProfileExpDlg::OnSelchangeSection() 
{
	// TODO: Add your control notification handler code here
	if (m_Name_section.GetCount() == 0)
	{
		CWnd* pWnd = GetDlgItem(IDC_SELECT_SECTION);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDC_SECTION);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDOK);
		pWnd->EnableWindow(false);
	}
	else
	{
		CString NameSection;
		CWnd* pWnd;
		CDatabase db;
		NregionRead rsn, rsn_new;
		rsn.IniFile = IniFile;
		rsn_new.IniFile = IniFile;
		rsn.Open();
		rsn_new.Open();
		m_Name_section.GetWindowText(NameSection);
		m_Graph_area_name.ResetContent();
		if (!rsn.IsBOF())
			rsn.MoveFirst();
		while (!rsn.IsEOF())
		{
			try
			{
				if (rsn.m_NAMREG == NameSection && rsn.m_GRUPREG == 14)
				{
					db.Open("ODBC;DSN=" + rsn.m_PATH);
					if (db.IsOpen())
					{
						enable = true;
						rsd.StrConnection = rsn.m_PATH;
					}
					db.Close();
				}
				if (rsn.m_NAMREG == NameSection && rsn.m_GRUPREG == 4)
				{
					db.Open("ODBC;DSN=" + rsn.m_PATH);
					if (db.IsOpen())
					{
						if (!rsn_new.IsBOF())
							rsn_new.MoveFirst();
						while (!rsn_new.IsEOF())
						{
							if (rsn.m_PATH == rsn_new.m_PATH && rsn_new.m_GRUPREG == 14)
							{
								enable = true;
								rsd.StrConnection = rsn.m_PATH;
							}
							rsn_new.MoveNext();
						}
					}
					db.Close();
				}
			}
			catch (...) { }
			if (rsn.m_NAMREG == NameSection && rsn.m_GRUPREG == 2)
				enable = false;
			rsn.MoveNext();
		}
		if (enable)
		{
			rsd.Open();
			if (!rsd.IsBOF())
			{
				if (!rsd.IsBOF())
					rsd.MoveFirst();
				while (!rsd.IsEOF())
				{
					if (rsd.m_PERSON == PERSON)
					{
						m_Graph_area_name.AddString(rsd.m_NAMESPACE);
						if (rsd.m_NUMSPACE == GraphArea)
							GraphAreaName = rsd.m_NAMESPACE;
					}
					rsd.MoveNext();
				}
				m_Graph_area_name.SetCurSel(0);
				pWnd = GetDlgItem(IDC_GRAPH_AREA);
				pWnd->EnableWindow(true);
				if (m_Graph_area.GetCheck())
				{
					pWnd = GetDlgItem(IDC_SELECT_GRAPH_AREA_NAME);
					pWnd->EnableWindow(true);
					pWnd = GetDlgItem(IDC_GRAPH_AREA_NAME);
					pWnd->EnableWindow(true);
				}
			}
			rsd.Close();
		}
		else
		{
			pWnd = GetDlgItem(IDC_GRAPH_AREA);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_SELECT_GRAPH_AREA_NAME);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_GRAPH_AREA_NAME);
			pWnd->EnableWindow(false);
		}
		OnChangeFactorX();
		rsn.Close();
		rsn_new.Close();
	}
}

static int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
    switch (uMsg)
	{
		case BFFM_INITIALIZED:
			if (lpData)
				SendMessage(hWnd,BFFM_SETSELECTION,TRUE,lpData);
        break;
    }
    return 0;
}

void EditProfileExpDlg::OnOpenSelectFolder() 
{
	// TODO: Add your control notification handler code here
	m_Choosen_folder.GetWindowText(path, MAX_PATH);
	BROWSEINFO bi = {0};
	bi.hwndOwner = this->GetSafeHwnd();
    bi.lpszTitle = _T("ѕуть к папке:");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = LPARAM(path);
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != 0)
    {
        if (SHGetPathFromIDList(pidl, path))
			m_Choosen_folder.SetWindowText(path);
        IMalloc* imalloc = 0;
        if (SUCCEEDED(SHGetMalloc(&imalloc)))
        {
            imalloc->Free(pidl);
            imalloc->Release();
        }
    }
}

void EditProfileExpDlg::OnGraphArea() 
{
	// TODO: Add your control notification handler code here
	if (m_Graph_area.GetCheck())
	{
		CWnd* pWnd = GetDlgItem(IDC_SELECT_GRAPH_AREA_NAME);
		pWnd->EnableWindow(true);
		pWnd = GetDlgItem(IDC_GRAPH_AREA_NAME);
		pWnd->EnableWindow(true);
	}
	else
	{
		CWnd* pWnd = GetDlgItem(IDC_SELECT_GRAPH_AREA_NAME);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDC_GRAPH_AREA_NAME);
		pWnd->EnableWindow(false);
	}
}

void EditProfileExpDlg::OnChangeNameProfile() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString NameProfile, FactorX, FactorY, ShiftX, ShiftY, Turn;
	CWnd* pWnd = GetDlgItem(IDOK);
	m_Name_profile.GetWindowText(NameProfile);
	m_Factor_x.GetWindowText(FactorX);
	m_Factor_y.GetWindowText(FactorY);
	m_Shift_x.GetWindowText(ShiftX);
	m_Shift_y.GetWindowText(ShiftY);
	m_Turn.GetWindowText(Turn);
	if (NameProfile.IsEmpty() || FactorX.IsEmpty() || FactorY.IsEmpty() || ShiftX.IsEmpty() || ShiftY.IsEmpty() || Turn.IsEmpty() || !FactorX.Find(" ", 0) || !FactorY.Find(" ", 0) || !ShiftX.Find(" ", 0) || !ShiftY.Find(" ", 0) || !Turn.Find(" ", 0) || m_Name_section.GetCount() == 0)
		pWnd->EnableWindow(false);
	else
		pWnd->EnableWindow(true);
}


void EditProfileExpDlg::OnChangeFactorX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileExpDlg::OnChangeFactorY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileExpDlg::OnChangeShiftX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileExpDlg::OnChangeShiftY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileExpDlg::OnChangeTurn() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileExpDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString NameSection, GraphAreaName;
	m_Name_section.GetWindowText(NameSection);
	NregionRead rsn;
	CDatabNet* dn;
	CRecordNet rn;
	rsn.IniFile = IniFile;
	rsn.Open();
	if (!rsn.IsBOF())
		rsn.MoveFirst();
	while (!rsn.IsEOF())
	{
		if (rsn.m_NAMREG == NameSection)
		{
			NumberSection = rsn.m_NUMREG;
			GroupSection = rsn.m_GRUPREG;
			PathSection = rsn.m_PATH;
			break;
		}
		rsn.MoveNext();
	}
	dn = new CDatabNet;
	dn->OpenNet("ODBC;DSN=" + PathSection, true);
	if (dn->isTable("scr") > -1)
		rn.InitRecordNet(dn, "scr");
	else
		rn.InitRecordNet(dn, "scrc");
	dn->Close();
	if (rn.isField("XYB") > -1)
		TypeSourceData = 2;
	else
		if (rn.isField("XY") > -1)
			TypeSourceData = 1;
		else
			TypeSourceData = 0;
	GraphAreaEnable = m_Graph_area.IsWindowEnabled();
	m_Graph_area_name.GetWindowText(GraphAreaName);
	if (enable)
	{
		rsd.Open();
		if (!rsd.IsBOF())
		{
			if (!rsd.IsBOF())
				rsd.MoveFirst();
			while (!rsd.IsEOF())
			{
				if (rsd.m_NAMESPACE == GraphAreaName)
				{
					GraphArea = rsd.m_NUMSPACE;
					break;
				}
				rsd.MoveNext();
			}
		}
		rsd.Close();
	}
	CDialog::OnOK();
}
