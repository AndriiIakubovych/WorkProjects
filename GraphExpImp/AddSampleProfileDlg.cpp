// AddSampleProfileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "AddSampleProfileDlg.h"

#include "ProfilesExpImpRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddSampleProfileDlg dialog


AddSampleProfileDlg::AddSampleProfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddSampleProfileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddSampleProfileDlg)
	m_Name_profile_str = _T("");
	//}}AFX_DATA_INIT
}


void AddSampleProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddSampleProfileDlg)
	DDX_Control(pDX, IDC_NAME_PROFILE, m_Name_profile);
	DDX_Control(pDX, IDC_TYPE_PROFILE, m_Type_profile);
	DDX_Text(pDX, IDC_NAME_PROFILE, m_Name_profile_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddSampleProfileDlg, CDialog)
	//{{AFX_MSG_MAP(AddSampleProfileDlg)
	ON_EN_CHANGE(IDC_NAME_PROFILE, OnChangeNameProfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddSampleProfileDlg message handlers

BOOL AddSampleProfileDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int tp;
	for (int i = 0; i < m_Type_profile.GetCount(); i++)
	{
		m_Type_profile.SetCurSel(i);
		tp = m_Type_profile.GetCurSel() + 1;
		if (TypeProfile == tp)
			break;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AddSampleProfileDlg::OnChangeNameProfile()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString NameProfile;
	CWnd* pWnd = GetDlgItem(IDOK);
	m_Name_profile.GetWindowText(NameProfile);
	if (NameProfile.IsEmpty() || !NameProfile.Find(" ", 0))
		pWnd->EnableWindow(false);
	else
		pWnd->EnableWindow(true);
}

void AddSampleProfileDlg::OnOK()
{
	// TODO: Add extra validation here
	char buffer[MAX_PATH];
	ProfilesExpImpRead ProfilesRS;
	ProfilesRS.IniFile = IniFile;
	TypeProfile = m_Type_profile.GetCurSel() + 1;
	ProfilesRS.Open();
	if (!ProfilesRS.IsBOF())
		ProfilesRS.MoveFirst();
	while (!ProfilesRS.IsEOF())
	{
		m_Name_profile.GetWindowText(buffer, MAX_PATH);
		if (ProfilesRS.m_Name_profile == buffer)
		{
			MessageBox("Профиль с таким именем уже существует!", "Сообщение", MB_OK | MB_ICONINFORMATION);
			return;
		}
		ProfilesRS.MoveNext();
	}
	
	CDialog::OnOK();
}
