// EditProfileImpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "EditProfileImpDlg.h"

#include "NregionRead.h"
#include "TplineRead.h"
#include "TpnameRead.h"

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
// EditProfileImpDlg dialog

static TCHAR path[MAX_PATH];

EditProfileImpDlg::EditProfileImpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(EditProfileImpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditProfileImpDlg)
	m_Name_profile_str = _T("");
	m_Factor_x_str = _T("");
	m_Choosen_folder_str = _T("");
	m_Factor_y_str = _T("");
	m_Shift_x_str = _T("");
	m_Shift_y_str = _T("");
	m_Turn_str = _T("");
	m_Usual_int = -1;
	//}}AFX_DATA_INIT
}


void EditProfileImpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditProfileImpDlg)
	DDX_Control(pDX, IDC_TURN, m_Turn);
	DDX_Control(pDX, IDC_SHIFT_Y, m_Shift_y);
	DDX_Control(pDX, IDC_SHIFT_X, m_Shift_x);
	DDX_Control(pDX, IDC_FACTOR_Y, m_Factor_y);
	DDX_Control(pDX, IDC_FACTOR_X, m_Factor_x);
	DDX_Control(pDX, IDC_FOLDER, m_Choosen_folder);
	DDX_Control(pDX, IDC_SECTION, m_Name_section);
	DDX_Control(pDX, IDC_NAME_PROFILE, m_Name_profile);
	DDX_Text(pDX, IDC_NAME_PROFILE, m_Name_profile_str);
	DDX_Text(pDX, IDC_FACTOR_X, m_Factor_x_str);
	DDX_Text(pDX, IDC_FOLDER, m_Choosen_folder_str);
	DDX_Text(pDX, IDC_FACTOR_Y, m_Factor_y_str);
	DDX_Text(pDX, IDC_SHIFT_X, m_Shift_x_str);
	DDX_Text(pDX, IDC_SHIFT_Y, m_Shift_y_str);
	DDX_Text(pDX, IDC_TURN, m_Turn_str);
	DDX_Radio(pDX, IDC_USUAL, m_Usual_int);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditProfileImpDlg, CDialog)
	//{{AFX_MSG_MAP(EditProfileImpDlg)
	ON_EN_CHANGE(IDC_NAME_PROFILE, OnChangeNameProfile)
	ON_BN_CLICKED(IDC_OPEN_SELECT_FOLDER, OnOpenSelectFolder)
	ON_EN_CHANGE(IDC_FACTOR_X, OnChangeFactorX)
	ON_EN_CHANGE(IDC_FACTOR_Y, OnChangeFactorY)
	ON_EN_CHANGE(IDC_SHIFT_X, OnChangeShiftX)
	ON_EN_CHANGE(IDC_SHIFT_Y, OnChangeShiftY)
	ON_EN_CHANGE(IDC_TURN, OnChangeTurn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditProfileImpDlg message handlers

BOOL EditProfileImpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char buffer[MAX_PATH];
	bool CurrentSelect = false;
	bool add_tpline, add_tpname;
	CString NameSection;
	m_Name_section.ResetContent();
	CDatabase db;
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
			add_tpline = false;
			add_tpname = false;
			if (rsn.m_GRUPREG == 2 || rsn.m_GRUPREG == 14)
			{
				db.Open("ODBC;DSN=" + rsn.m_PATH);
				if (db.IsOpen())
				{
					TplineRead rstl;
					rstl.StrConnection = rsn.m_PATH;
					rstl.Open();
					if (!rstl.IsBOF())
						rstl.MoveFirst();
					while (!rstl.IsEOF())
					{
						if (rstl.m_VIDOBJ == 1)
						{
							add_tpline = true;
							break;
						}
						rstl.MoveNext();
					}
					rstl.Close();
					TpnameRead rstn;
					rstn.StrConnection = rsn.m_PATH;
					rstn.Open();
					if (!rstn.IsBOF())
						rstn.MoveFirst();
					while (!rstn.IsEOF())
					{
						if (rstn.m_VIDOBJ == 2)
						{
							add_tpname = true;
							break;
						}
						rstn.MoveNext();
					}
					rstn.Close();
					if (add_tpline && add_tpname)
						m_Name_section.AddString(rsn.m_NAMREG);
				}
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
						{
							TplineRead rstl;
							rstl.StrConnection = rsn.m_PATH;
							rstl.Open();
							if (!rstl.IsBOF())
								rstl.MoveFirst();
							while (!rstl.IsEOF())
							{
								if (rstl.m_VIDOBJ == 1)
								{
									add_tpline = true;
									break;
								}
								rstl.MoveNext();
							}
							rstl.Close();
							TpnameRead rstn;
							rstn.StrConnection = rsn.m_PATH;
							rstn.Open();
							if (!rstn.IsBOF())
								rstn.MoveFirst();
							while (!rstn.IsEOF())
							{
								if (rstn.m_VIDOBJ == 2)
								{
									add_tpname = true;
									break;
								}
								rstn.MoveNext();
							}
							rstn.Close();
							if (add_tpline && add_tpname)
								m_Name_section.AddString(rsn.m_NAMREG);
						}
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
	rsn.Close();
	rsn_new.Close();
	if (m_Name_section.GetCount() == 0)
	{
		CWnd* pWnd = GetDlgItem(IDC_SELECT_SECTION);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDC_SECTION);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDOK);
		pWnd->EnableWindow(false);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
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

void EditProfileImpDlg::OnOpenSelectFolder() 
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

void EditProfileImpDlg::OnChangeNameProfile() 
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

void EditProfileImpDlg::OnChangeFactorX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileImpDlg::OnChangeFactorY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileImpDlg::OnChangeShiftX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileImpDlg::OnChangeShiftY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileImpDlg::OnChangeTurn() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileImpDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString NameSection;
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
	CDialog::OnOK();
}
