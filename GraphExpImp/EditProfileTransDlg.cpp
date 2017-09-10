// EditProfileTransDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "EditProfileTransDlg.h"

#include "NregionRead.h"

#pragma comment(lib,"OutGraf.lib")
#include "grafstr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// EditProfileTransDlg dialog


EditProfileTransDlg::EditProfileTransDlg(CWnd* pParent /*=NULL*/)
	: CDialog(EditProfileTransDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditProfileTransDlg)
	m_Name_profile_str = _T("");
	m_Factor_x_str = _T("");
	m_Factor_y_str = _T("");
	m_Shift_x_str = _T("");
	m_Shift_y_str = _T("");
	m_Turn_str = _T("");
	m_Size_x_str = _T("");
	m_Size_y_str = _T("");
	//}}AFX_DATA_INIT
}


void EditProfileTransDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditProfileTransDlg)
	DDX_Control(pDX, IDC_SIZE_Y, m_Size_y);
	DDX_Control(pDX, IDC_SIZE_X, m_Size_x);
	DDX_Control(pDX, IDC_TURN, m_Turn);
	DDX_Control(pDX, IDC_SHIFT_Y, m_Shift_y);
	DDX_Control(pDX, IDC_SHIFT_X, m_Shift_x);
	DDX_Control(pDX, IDC_FACTOR_Y, m_Factor_y);
	DDX_Control(pDX, IDC_FACTOR_X, m_Factor_x);
	DDX_Control(pDX, IDC_SECTION, m_Name_section);
	DDX_Control(pDX, IDC_NAME_PROFILE, m_Name_profile);
	DDX_Text(pDX, IDC_NAME_PROFILE, m_Name_profile_str);
	DDX_Text(pDX, IDC_FACTOR_X, m_Factor_x_str);
	DDX_Text(pDX, IDC_FACTOR_Y, m_Factor_y_str);
	DDX_Text(pDX, IDC_SHIFT_X, m_Shift_x_str);
	DDX_Text(pDX, IDC_SHIFT_Y, m_Shift_y_str);
	DDX_Text(pDX, IDC_TURN, m_Turn_str);
	DDX_Text(pDX, IDC_SIZE_X, m_Size_x_str);
	DDX_Text(pDX, IDC_SIZE_Y, m_Size_y_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditProfileTransDlg, CDialog)
	//{{AFX_MSG_MAP(EditProfileTransDlg)
	ON_EN_CHANGE(IDC_NAME_PROFILE, OnChangeNameProfile)
	ON_EN_CHANGE(IDC_FACTOR_X, OnChangeFactorX)
	ON_EN_CHANGE(IDC_FACTOR_Y, OnChangeFactorY)
	ON_EN_CHANGE(IDC_SHIFT_X, OnChangeShiftX)
	ON_EN_CHANGE(IDC_SHIFT_Y, OnChangeShiftY)
	ON_EN_CHANGE(IDC_TURN, OnChangeTurn)
	ON_EN_CHANGE(IDC_SIZE_X, OnChangeSizeX)
	ON_EN_CHANGE(IDC_SIZE_Y, OnChangeSizeY)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditProfileTransDlg message handlers

BOOL EditProfileTransDlg::OnInitDialog() 
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

void EditProfileTransDlg::OnChangeNameProfile() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString NameProfile, FactorX, FactorY, ShiftX, ShiftY, Turn, SizeX, SizeY;
	CWnd* pWnd = GetDlgItem(IDOK);
	m_Name_profile.GetWindowText(NameProfile);
	m_Factor_x.GetWindowText(FactorX);
	m_Factor_y.GetWindowText(FactorY);
	m_Shift_x.GetWindowText(ShiftX);
	m_Shift_y.GetWindowText(ShiftY);
	m_Turn.GetWindowText(Turn);
	m_Size_x.GetWindowText(SizeX);
	m_Size_y.GetWindowText(SizeY);
	if (NameProfile.IsEmpty() || FactorX.IsEmpty() || FactorY.IsEmpty() || ShiftX.IsEmpty() || ShiftY.IsEmpty() || Turn.IsEmpty() || SizeX.IsEmpty() || SizeY.IsEmpty() || !FactorX.Find(" ", 0) || !FactorY.Find(" ", 0) || !ShiftX.Find(" ", 0) || !ShiftY.Find(" ", 0) || !Turn.Find(" ", 0) || !SizeX.Find(" ", 0) || !SizeY.Find(" ", 0) || m_Name_section.GetCount() == 0)
		pWnd->EnableWindow(false);
	else
		pWnd->EnableWindow(true);
}

void EditProfileTransDlg::OnChangeFactorX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileTransDlg::OnChangeFactorY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileTransDlg::OnChangeShiftX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileTransDlg::OnChangeShiftY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileTransDlg::OnChangeTurn() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileTransDlg::OnChangeSizeX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileTransDlg::OnChangeSizeY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void EditProfileTransDlg::OnOK() 
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
