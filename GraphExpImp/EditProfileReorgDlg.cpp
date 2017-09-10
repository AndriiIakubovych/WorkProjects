// EditProfileReorgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "EditProfileReorgDlg.h"

#include "NregionRead.h"

#pragma comment(lib,"OutGraf.lib")
#include "grafstr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EditProfileReorgDlg dialog


EditProfileReorgDlg::EditProfileReorgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(EditProfileReorgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditProfileReorgDlg)
	m_Name_profile_str = _T("");
	//}}AFX_DATA_INIT
}


void EditProfileReorgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditProfileReorgDlg)
	DDX_Control(pDX, IDC_NAME_PROFILE, m_Name_profile);
	DDX_Control(pDX, IDC_SECTION, m_Name_section);
	DDX_Text(pDX, IDC_NAME_PROFILE, m_Name_profile_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditProfileReorgDlg, CDialog)
	//{{AFX_MSG_MAP(EditProfileReorgDlg)
	ON_EN_CHANGE(IDC_NAME_PROFILE, OnChangeNameProfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditProfileReorgDlg message handlers

BOOL EditProfileReorgDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char buffer[MAX_PATH];
	bool CurrentSelect = false;
	CString NameSection;
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

void EditProfileReorgDlg::OnOK() 
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

void EditProfileReorgDlg::OnChangeNameProfile() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString NameProfile;
	CWnd* pWnd = GetDlgItem(IDOK);
	m_Name_profile.GetWindowText(NameProfile);
	if (NameProfile.IsEmpty())
		pWnd->EnableWindow(false);
	else
		pWnd->EnableWindow(true);
}