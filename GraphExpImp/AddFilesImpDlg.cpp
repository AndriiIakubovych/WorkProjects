// AddFilesImpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "AddFilesImpDlg.h"

#include "FilesExpImpRead.h"
#include "TplineRead.h"
#include "TpnameRead.h"
#include "TplevRead.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddFilesImpDlg dialog


AddFilesImpDlg::AddFilesImpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddFilesImpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddFilesImpDlg)
	m_File_name_str = _T("");
	m_Windows_int = -1;
	m_Size_denotations_str = _T("");
	m_Circles_int = -1;
	m_Break_lines_segments_bool = FALSE;
	m_Skip_superfluous_points_bool = FALSE;
	m_Name_field_charakteristics_int = -1;
	m_Import_charakteristics_bool = FALSE;
	m_Height_charakteristics_str = _T("");
	m_Delete_graph_object_bool = FALSE;
	//}}AFX_DATA_INIT
}


void AddFilesImpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddFilesImpDlg)
	DDX_Control(pDX, IDC_IMP_CHARAKTERISTICS, m_Import_charakteristics);
	DDX_Control(pDX, IDC_CIRCLES, m_Circles);
	DDX_Control(pDX, IDC_SIZE_CHARACTERISTICS, m_Height_charakteristics);
	DDX_Control(pDX, IDC_FIELD_CHARAKTERISTICS, m_Name_field_charakteristics);
	DDX_Control(pDX, IDC_SIZE_DENOTATIONS, m_Size_denotations);
	DDX_Control(pDX, IDC_WINDOWS, m_Windows);
	DDX_Control(pDX, IDC_TYPE_CHARAKTERISTICS, m_Accepting_type_charakteristics);
	DDX_Control(pDX, IDC_TYPE_DENOTATIONS, m_Type_transformed_denotations);
	DDX_Control(pDX, IDC_TYPE_TEXT, m_Accepting_type_text);
	DDX_Control(pDX, IDC_TYPE_LINES, m_Accepting_type_lines);
	DDX_Control(pDX, IDC_FILE_NAME, m_File_name);
	DDX_Text(pDX, IDC_FILE_NAME, m_File_name_str);
	DDX_Radio(pDX, IDC_WINDOWS, m_Windows_int);
	DDX_Text(pDX, IDC_SIZE_DENOTATIONS, m_Size_denotations_str);
	DDX_Radio(pDX, IDC_CIRCLES, m_Circles_int);
	DDX_Check(pDX, IDC_BREAK_LINES_SEGMENTS, m_Break_lines_segments_bool);
	DDX_Check(pDX, IDC_SKIP_SUPERFLUOUS_POINTS, m_Skip_superfluous_points_bool);
	DDX_CBIndex(pDX, IDC_FIELD_CHARAKTERISTICS, m_Name_field_charakteristics_int);
	DDX_Check(pDX, IDC_IMP_CHARAKTERISTICS, m_Import_charakteristics_bool);
	DDX_Text(pDX, IDC_SIZE_CHARACTERISTICS, m_Height_charakteristics_str);
	DDX_Control(pDX, IDC_DELETE_GRAPH_OBJECT, m_Delete_graph_object);
	DDX_Check(pDX, IDC_DELETE_GRAPH_OBJECT, m_Delete_graph_object_bool);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddFilesImpDlg, CDialog)
	//{{AFX_MSG_MAP(AddFilesImpDlg)
	ON_BN_CLICKED(IDC_CIRCLES, OnCircles)
	ON_BN_CLICKED(IDC_PRIMITIVES, OnPrimitives)
	ON_BN_CLICKED(IDC_IMP_CHARAKTERISTICS, OnImpCharakteristics)
	ON_BN_CLICKED(IDC_OPEN_SELECT_FILE, OnOpenSelectFile)
	ON_EN_CHANGE(IDC_FILE_NAME, OnChangeFileName)
	ON_EN_CHANGE(IDC_SIZE_DENOTATIONS, OnChangeSizeDenotations)
	ON_EN_CHANGE(IDC_SIZE_CHARACTERISTICS, OnChangeSizeCharacteristics)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddFilesImpDlg message handlers

BOOL AddFilesImpDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char value_parameter[MAX_PATH];
	CString lpEXEName, a;
	TplineRead rstl;
	rstl.StrConnection = StrConnection;
	rstl.Open();
	if (!rstl.IsBOF())
		rstl.MoveFirst();
	m_Accepting_type_lines.AddString("НИКАКОЙ");
	m_Type_transformed_denotations.AddString("НИКАКОЙ");
	while (!rstl.IsEOF())
	{
		if (rstl.m_VIDOBJ == 1)
		{
			m_Accepting_type_lines.AddString(rstl.m_NAMTP);
			m_Type_transformed_denotations.AddString(rstl.m_NAMTP);
		}
		rstl.MoveNext();
	}
	m_Accepting_type_lines.SetCurSel(0);
	m_Type_transformed_denotations.SetCurSel(0);
	rstl.Close();
	TpnameRead rstn;
	rstn.StrConnection = StrConnection;
	rstn.Open();
	if (!rstn.IsBOF())
		rstn.MoveFirst();
	m_Accepting_type_text.AddString("НИКАКОЙ");
	m_Name_field_charakteristics.AddString("НЕТ");
	m_Accepting_type_charakteristics.AddString("НИКАКОЙ");
	while (!rstn.IsEOF())
	{
		if (rstn.m_VIDOBJ == 2)
		{
			m_Accepting_type_text.AddString(rstn.m_NAMNAM);
			m_Accepting_type_charakteristics.AddString(rstn.m_NAMNAM);
		}
		rstn.MoveNext();
	}
	m_Accepting_type_text.SetCurSel(0);
	m_Name_field_charakteristics.SetCurSel(0);
	m_Accepting_type_charakteristics.SetCurSel(0);
	rstn.Close();
	if (!access(Folder + "\\expimp.ini", 0))
	{
		GetPrivateProfileString("IMPPAR", "radp", NULL, value_parameter, sizeof(value_parameter), Folder + "\\expimp.ini");
		if (strcmp(value_parameter, "") != 0)
			m_Size_denotations.SetWindowText(value_parameter);
		else
			m_Size_denotations.SetWindowText("5.000000");
	}
	else
		m_Size_denotations.SetWindowText("5.000000");
	m_Height_charakteristics.SetWindowText("3.00");
	m_Windows.SetCheck(1);
	m_Circles.SetCheck(1);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AddFilesImpDlg::OnCircles() 
{
	// TODO: Add your control notification handler code here
	TplineRead rstl;
	CWnd* pWnd = GetDlgItem(IDC_SELECT_TYPE_DENOTATIONS);
	pWnd->SetWindowText("Тип преобразуемых ломанных:");
	m_Type_transformed_denotations.ResetContent();
	m_Type_transformed_denotations.AddString("НИКАКОЙ");
	rstl.StrConnection = StrConnection;
	rstl.Open();
	if (!rstl.IsBOF())
		rstl.MoveFirst();
	while (!rstl.IsEOF())
	{
		if (rstl.m_VIDOBJ == 1)
			m_Type_transformed_denotations.AddString(rstl.m_NAMTP);
		rstl.MoveNext();
	}
	m_Type_transformed_denotations.SetCurSel(0);
	rstl.Close();
}

void AddFilesImpDlg::OnPrimitives() 
{
	// TODO: Add your control notification handler code here
	CWnd* pWnd = GetDlgItem(IDC_SELECT_TYPE_DENOTATIONS);
	pWnd->SetWindowText("Тип преобразуемых обозначений:");
	m_Type_transformed_denotations.ResetContent();
	m_Type_transformed_denotations.AddString("НИКАКОЙ");
	m_Type_transformed_denotations.SetCurSel(0);
}

void AddFilesImpDlg::OnImpCharakteristics() 
{
	// TODO: Add your control notification handler code here
	if (m_Import_charakteristics.GetCheck())
	{
		CWnd* pWnd = GetDlgItem(IDC_SELECT_NAME_CHARAKTERISTICS);
		pWnd->EnableWindow(true);
		pWnd = GetDlgItem(IDC_FIELD_CHARAKTERISTICS);
		pWnd->EnableWindow(true);
		pWnd = GetDlgItem(IDC_SELECT_TYPE_CHARAKTERISTICS);
		pWnd->EnableWindow(true);
		pWnd = GetDlgItem(IDC_TYPE_CHARAKTERISTICS);
		pWnd->EnableWindow(true);
		pWnd = GetDlgItem(IDC_INPUT_SIZE_CHARACTERISTICS);
		pWnd->EnableWindow(true);
		pWnd = GetDlgItem(IDC_SIZE_CHARACTERISTICS);
		pWnd->EnableWindow(true);
	}
	else
	{
		CWnd* pWnd = GetDlgItem(IDC_SELECT_NAME_CHARAKTERISTICS);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDC_FIELD_CHARAKTERISTICS);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDC_SELECT_TYPE_CHARAKTERISTICS);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDC_TYPE_CHARAKTERISTICS);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDC_INPUT_SIZE_CHARACTERISTICS);
		pWnd->EnableWindow(false);
		pWnd = GetDlgItem(IDC_SIZE_CHARACTERISTICS);
		pWnd->EnableWindow(false);
	}
}

void AddFilesImpDlg::OnOpenSelectFile() 
{
	// TODO: Add your control notification handler code here
	string s;
	ifstream in;
	CString FileName, S;
	CWnd* pWnd;
	int position = 0, start = 0, end = 0;
	bool Pline = false, Text = false, Point = false;
	char buffer[MAX_PATH];
	CFileDialog fd(true);
	fd.m_ofn.lpstrFilter = "MIF-файлы (*.mif)\0*.mif\0";
	fd.m_ofn.lpstrInitialDir = Folder;
	if (fd.DoModal() == IDOK)
	{
		FileName = fd.m_ofn.lpstrFile;
		strcpy(buffer, FileName);
		for (int j = FileName.GetLength() - 1; j >= 0; j--)
			if (buffer[j] == '\\')
			{
				position = j;
				break;
			}
		FileName.Delete(0, position + 1);
		FileName.Delete(FileName.GetLength() - 4, 4);
		m_File_name.SetWindowText(FileName);
		in.open(fd.m_ofn.lpstrFile);
		if (in.is_open())
		{
			m_Name_field_charakteristics.ResetContent();
			while (!in.eof())
			{
				getline(in, s);
				S = s.c_str();
				if (S.Left(5).CompareNoCase("pline") == 0)
					Pline = true;
				if (S.Left(6).CompareNoCase("region") == 0)
					Pline = true;
				if (S.Left(4).CompareNoCase("text") == 0)
					Text = true;
				if (S.Left(5).CompareNoCase("point") == 0)
					Point = true;
				if (start == 1)
					start++;
				if (S.Left(7).CompareNoCase("columns") == 0)
					start++;
				if (S.Left(4).CompareNoCase("data") == 0)
					end++;
				if (start > 1 && end == 0 && S.GetLength() > 0)
				{
					strcpy(buffer, S);
					for (int j = 0; buffer[j] == ' '; j++)
						S.Delete(0, 1);
					strcpy(buffer, S);
					for (j = 0; j < S.GetLength(); j++)
						if (buffer[j] == ' ')
						{
							S.Delete(j, S.GetLength() - j);
							break;
						}
					m_Name_field_charakteristics.AddString(S);
					m_Name_field_charakteristics.SetCurSel(0);
				}
			}
			if (Pline)
			{
				pWnd = GetDlgItem(IDC_IMPORT_LINES);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_SELECT_TYPE_LINES);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_TYPE_LINES);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_BREAK_LINES_SEGMENTS);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_SKIP_SUPERFLUOUS_POINTS);
				pWnd->EnableWindow(true);
			}
			else
			{
				pWnd = GetDlgItem(IDC_IMPORT_LINES);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_SELECT_TYPE_LINES);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_TYPE_LINES);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_BREAK_LINES_SEGMENTS);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_SKIP_SUPERFLUOUS_POINTS);
				pWnd->EnableWindow(false);
			}
			if (Text)
			{
				pWnd = GetDlgItem(IDC_SELECT_TYPE_TEXT);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_TYPE_TEXT);
				pWnd->EnableWindow(true);
			}
			else
			{
				pWnd = GetDlgItem(IDC_SELECT_TYPE_TEXT);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_TYPE_TEXT);
				pWnd->EnableWindow(false);
			}
			if (Point)
			{
				pWnd = GetDlgItem(IDC_IMPORT_DENOTATIONS);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_TRANSFORM_DENOTATIONS);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_CIRCLES);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_PRIMITIVES);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_SELECT_TYPE_DENOTATIONS);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_TYPE_DENOTATIONS);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_INPUT_SIZE_DENOTATIONS);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_SIZE_DENOTATIONS);
				pWnd->EnableWindow(true);
			}
			else
			{
				pWnd = GetDlgItem(IDC_IMPORT_DENOTATIONS);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_TRANSFORM_DENOTATIONS);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_CIRCLES);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_PRIMITIVES);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_SELECT_TYPE_DENOTATIONS);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_TYPE_DENOTATIONS);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_INPUT_SIZE_DENOTATIONS);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_SIZE_DENOTATIONS);
				pWnd->EnableWindow(false);
			}
			if (m_Name_field_charakteristics.GetCount() > 0)
			{
				pWnd = GetDlgItem(IDC_IMPORT_CHARAKTERISTICS);
				pWnd->EnableWindow(true);
				pWnd = GetDlgItem(IDC_IMP_CHARAKTERISTICS);
				pWnd->EnableWindow(true);
			}
			else
			{
				pWnd = GetDlgItem(IDC_IMPORT_CHARAKTERISTICS);
				pWnd->EnableWindow(false);
				pWnd = GetDlgItem(IDC_IMP_CHARAKTERISTICS);
				pWnd->EnableWindow(false);
			}
		}
	}
}

void AddFilesImpDlg::OnChangeFileName() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString FileName, SizeDenotations, HeightCharakteristics;
	CWnd* pWnd = GetDlgItem(IDOK);
	m_File_name.GetWindowText(FileName);
	m_Size_denotations.GetWindowText(SizeDenotations);
	m_Height_charakteristics.GetWindowText(HeightCharakteristics);
	if (FileName.IsEmpty() || SizeDenotations.IsEmpty() || HeightCharakteristics.IsEmpty() || !FileName.Find(" ", 0) || !SizeDenotations.Find(" ", 0) || !HeightCharakteristics.Find(" ", 0))
		pWnd->EnableWindow(false);
	else
		pWnd->EnableWindow(true);
}

void AddFilesImpDlg::OnChangeSizeDenotations() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeFileName();
}

void AddFilesImpDlg::OnChangeSizeCharacteristics() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeFileName();
}

void AddFilesImpDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString buffer;
	ImportLinesEnable = m_Accepting_type_lines.IsWindowEnabled();
	FilesExpImpRead FilesRS;
	FilesRS.IniFile = IniFile;
	FilesRS.Open();
	TplineRead rstl;
	rstl.StrConnection = StrConnection;
	rstl.Open();
	m_Accepting_type_lines.GetWindowText(buffer);
	AcceptingTypeLines = -1;
	LevelLines = -1;
	if (!rstl.IsBOF())
		rstl.MoveFirst();
	while (!rstl.IsEOF())
	{
		if (rstl.m_NAMTP == buffer)
		{
			AcceptingTypeLines = rstl.m_TYPBLINE;
			break;
		}
		rstl.MoveNext();
	}
	TplevRead rstlev;
	rstlev.StrConnection = StrConnection;
	rstlev.Open();
	if (!rstlev.IsBOF())
		rstlev.MoveFirst();
	while (!rstlev.IsEOF())
	{
		if (rstlev.m_type == AcceptingTypeLines && rstlev.m_vidobj == 1)
		{
			LevelLines = rstlev.m_dlevel;
			break;
		}
		rstlev.MoveNext();
	}
	ImportTextEnable = m_Accepting_type_text.IsWindowEnabled();
	TpnameRead rstn;
	rstn.StrConnection = StrConnection;
	rstn.Open();
	m_Accepting_type_text.GetWindowText(buffer);
	AcceptingTypeText = -1;
	LevelText = -1;
	if (!rstn.IsBOF())
		rstn.MoveFirst();
	while (!rstn.IsEOF())
	{
		if (rstn.m_NAMNAM == buffer)
		{
			AcceptingTypeText = rstn.m_TYPNAM;
			break;
		}
		rstn.MoveNext();
	}
	if (!rstlev.IsBOF())
		rstlev.MoveFirst();
	while (!rstlev.IsEOF())
	{
		if (rstlev.m_type == AcceptingTypeText && rstlev.m_vidobj != 1)
		{
			LevelText = rstlev.m_dlevel;
			break;
		}
		rstlev.MoveNext();
	}
	ImportDenotationsEnable = m_Type_transformed_denotations.IsWindowEnabled();
	m_Type_transformed_denotations.GetWindowText(buffer);
	TypeTransformedDenotations = -1;
	LevelDenotations = -1;
	if (!rstl.IsBOF())
		rstl.MoveFirst();
	while (!rstl.IsEOF())
	{
		if (rstl.m_NAMTP == buffer)
		{
			TypeTransformedDenotations = rstl.m_TYPBLINE;
			break;
		}
		rstl.MoveNext();
	}
	if (!rstlev.IsBOF())
		rstlev.MoveFirst();
	while (!rstlev.IsEOF())
	{
		if (rstlev.m_type == TypeTransformedDenotations && rstlev.m_vidobj == 1)
		{
			LevelDenotations = rstlev.m_dlevel;
			break;
		}
		rstlev.MoveNext();
	}
	m_Accepting_type_charakteristics.GetWindowText(buffer);
	AcceptingTypeCharakteristics = -1;
	LevelCharakteristics = -1;
	if (!rstn.IsBOF())
		rstn.MoveFirst();
	while (!rstn.IsEOF())
	{
		if (rstn.m_NAMNAM == buffer)
		{
			AcceptingTypeCharakteristics = rstn.m_TYPNAM;
			break;
		}
		rstn.MoveNext();
	}
	if (!rstlev.IsBOF())
		rstlev.MoveFirst();
	while (!rstlev.IsEOF())
	{
		if (rstlev.m_type == AcceptingTypeCharakteristics && rstlev.m_vidobj != 1)
		{
			LevelCharakteristics = rstlev.m_dlevel;
			break;
		}
		rstlev.MoveNext();
	}
	ImportCharakteristicsEnable = m_Import_charakteristics.IsWindowEnabled();
	if (!FilesRS.IsBOF())
		FilesRS.MoveFirst();
	while (!FilesRS.IsEOF())
	{
		m_File_name.GetWindowText(buffer);
		if (FilesRS.m_Name_file == buffer && FilesRS.m_Id_profile == IdProfile)
		{
			MessageBox("Файл для данного профиля с таким именем уже существует!", "Сообщение", MB_OK | MB_ICONINFORMATION);
			return;
		}
		FilesRS.MoveNext();
	}
	FilesRS.Close();
	rstl.Close();
	rstn.Close();
	rstlev.Close();
	CDialog::OnOK();
}
