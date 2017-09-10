// AddProfileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "AddProfileDlg.h"

#include "ProfilesExpImpRead.h"
#include "NregionRead.h"
#include "PlsizeRead.h"
#include "DesspaceRead.h"
#include "TplineRead.h"
#include "TpnameRead.h"

#pragma comment(lib, "OutGraf.lib")
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
// AddProfileDlg dialog

static TCHAR path[MAX_PATH];
static bool enable = false;
static DesspaceRead rsd;


AddProfileDlg::AddProfileDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AddProfileDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddProfileDlg)
	m_Name_profile_str = _T("");
	m_Factor_x_str = _T("");
	m_Factor_y_str = _T("");
	m_Choosen_folder_str = _T("");
	m_Shift_x_str = _T("");
	m_Shift_y_str = _T("");
	m_Turn_str = _T("");
	m_Type_profile_int = -1;
	m_Graph_area_bool = FALSE;
	m_Usual_int = -1;
	m_Metre_int = -1;
	m_Size_x_str = _T("");
	m_Size_y_str = _T("");
	//}}AFX_DATA_INIT
}


void AddProfileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddProfileDlg)
	DDX_Control(pDX, IDC_SIZE_Y, m_Size_y);
	DDX_Control(pDX, IDC_SIZE_X, m_Size_x);
	DDX_Control(pDX, IDC_USUAL, m_Usual);
	DDX_Control(pDX, IDC_METRE, m_Metre);
	DDX_Control(pDX, IDC_GRAPH_AREA_NAME, m_Graph_area_name);
	DDX_Control(pDX, IDC_GRAPH_AREA, m_Graph_area);
	DDX_Control(pDX, IDC_TURN, m_Turn);
	DDX_Control(pDX, IDC_SHIFT_Y, m_Shift_y);
	DDX_Control(pDX, IDC_SHIFT_X, m_Shift_x);
	DDX_Control(pDX, IDC_FOLDER, m_Choosen_folder);
	DDX_Control(pDX, IDC_FACTOR_Y, m_Factor_y);
	DDX_Control(pDX, IDC_FACTOR_X, m_Factor_x);
	DDX_Control(pDX, IDC_SECTION, m_Name_section);
	DDX_Control(pDX, IDC_NAME_PROFILE, m_Name_profile);
	DDX_Control(pDX, IDC_TYPE_PROFILE, m_Type_profile);
	DDX_Text(pDX, IDC_NAME_PROFILE, m_Name_profile_str);
	DDX_Text(pDX, IDC_FACTOR_X, m_Factor_x_str);
	DDX_Text(pDX, IDC_FACTOR_Y, m_Factor_y_str);
	DDX_Text(pDX, IDC_FOLDER, m_Choosen_folder_str);
	DDX_Text(pDX, IDC_SHIFT_X, m_Shift_x_str);
	DDX_Text(pDX, IDC_SHIFT_Y, m_Shift_y_str);
	DDX_Text(pDX, IDC_TURN, m_Turn_str);
	DDX_CBIndex(pDX, IDC_TYPE_PROFILE, m_Type_profile_int);
	DDX_Check(pDX, IDC_GRAPH_AREA, m_Graph_area_bool);
	DDX_Radio(pDX, IDC_USUAL, m_Usual_int);
	DDX_Radio(pDX, IDC_METRE, m_Metre_int);
	DDX_Text(pDX, IDC_SIZE_X, m_Size_x_str);
	DDX_Text(pDX, IDC_SIZE_Y, m_Size_y_str);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddProfileDlg, CDialog)
	//{{AFX_MSG_MAP(AddProfileDlg)
	ON_CBN_SELCHANGE(IDC_TYPE_PROFILE, OnSelchangeTypeProfile)
	ON_CBN_SELCHANGE(IDC_SECTION, OnSelchangeSection)
	ON_BN_CLICKED(IDC_OPEN_SELECT_FOLDER, OnOpenSelectFolder)
	ON_BN_CLICKED(IDC_GRAPH_AREA, OnGraphArea)
	ON_EN_CHANGE(IDC_NAME_PROFILE, OnChangeNameProfile)
	ON_EN_CHANGE(IDC_FOLDER, OnChangeFolder)
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
// AddProfileDlg message handlers

BOOL AddProfileDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	char str_person[MAX_PATH], buffer[MAX_PATH];
	m_Factor_x.SetWindowText("1.000000");
	m_Factor_y.SetWindowText("1.000000");
	m_Shift_x.SetWindowText("0.000000");
	m_Shift_y.SetWindowText("0.000000");
	m_Turn.SetWindowText("0.000000");
	GetPrivateProfileString("Supshort", "PERSON", NULL, str_person, sizeof(str_person), IniFile);
	PERSON = atoi(str_person);
	m_Type_profile.SetCurSel(0);
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
		}
		catch (...) { }
		rsn.MoveNext();
	}
	m_Name_section.SetCurSel(0);
	m_Graph_area_name.SetCurSel(0);
	PlsizeRead rspls;
	rspls.IniFile = IniFile;
	rspls.Open();
	sprintf(buffer, "%.0f", rspls.m_SIZX);
	m_Size_x.SetWindowText(buffer);
	sprintf(buffer, "%.0f", rspls.m_SIZY);
	m_Size_y.SetWindowText(buffer);
	rsn.Close();
	rsn_new.Close();
	rspls.Close();
	m_Usual.SetCheck(1);
	m_Metre.SetCheck(1);
	OnSelchangeSection();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void AddProfileDlg::OnSelchangeTypeProfile() 
{
	// TODO: Add your control notification handler code here
	char value_parameter[MAX_PATH];
	CString buffer;
	CDatabase db;
	m_Name_section.ResetContent();
	NregionRead rsn, rsn_new;
	m_Choosen_folder.GetWindowText(buffer);
	if (buffer.IsEmpty() || access(buffer + "\\expimp.ini", 0))
	{
		m_Factor_x.SetWindowText("1.000000");
		m_Factor_y.SetWindowText("1.000000");
		m_Shift_x.SetWindowText("0.000000");
		m_Shift_y.SetWindowText("0.000000");
		m_Turn.SetWindowText("0.000000");
	}
	else
	{
		if (!access(buffer + "\\expimp.ini", 0))
		{
			GetPrivateProfileString("IMPPAR_MIFDBF", "cxx", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
			m_Factor_x.SetWindowText(value_parameter);
			GetPrivateProfileString("IMPPAR_MIFDBF", "cyy", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
			m_Factor_y.SetWindowText(value_parameter);
			GetPrivateProfileString("IMPPAR_MIFDBF", "ax", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
			m_Shift_x.SetWindowText(value_parameter);
			GetPrivateProfileString("IMPPAR_MIFDBF", "ay", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
			m_Shift_y.SetWindowText(value_parameter);
			GetPrivateProfileString("IMPPAR", "angl", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
			m_Turn.SetWindowText(value_parameter);
		}
	}
	rsn.IniFile = IniFile;
	rsn_new.IniFile = IniFile;
	rsn.Open();
	rsn_new.Open();
	if (!rsn.IsBOF())
		rsn.MoveFirst();
	switch (m_Type_profile.GetCurSel())
	{
		case 0:
		{
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
				}
				catch (...) { }
				rsn.MoveNext();
			}
			CWnd* pWnd = GetDlgItem(IDC_INPUT_NAME_PROFILE);
			pWnd->SetWindowText("Имя профиля экспорта:");
			pWnd = GetDlgItem(IDC_SELECT_FOLDER);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_OPEN_SELECT_FOLDER);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_PARAM_TRANS_COOR);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_FACTOR_X);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Коэффициент сжатия по оси абсцисс:");
			pWnd = GetDlgItem(IDC_FACTOR_X);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_FACTOR_Y);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Коэффициент сжатия по оси ординат:");
			pWnd = GetDlgItem(IDC_FACTOR_Y);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SHIFT_X);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Величина сдвига влево по оси абсцисс:");
			pWnd = GetDlgItem(IDC_SHIFT_X);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SHIFT_Y);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Величина сдвига вниз по оси ординат:");
			pWnd = GetDlgItem(IDC_SHIFT_Y);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_TURN);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Поворот в градусах по часовой стрелки:");
			pWnd = GetDlgItem(IDC_TURN);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SIZE_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_SIZE_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INPUT_SIZE_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_SIZE_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INITIAL_ORDER_COORDINATES);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_USUAL);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INVERT);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_PARAMETERS_EXPORT);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_UNIT);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_METRE);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_MILLIMETRE);
			pWnd->EnableWindow(true);
			OnSelchangeSection();
			break;
		}
		case 1:
		{
			bool add_tpline, add_tpname;
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
				}
				catch (...) { }
				rsn.MoveNext();
			}
			m_Graph_area_name.ResetContent();
			CWnd* pWnd = GetDlgItem(IDC_INPUT_NAME_PROFILE);
			pWnd->SetWindowText("Имя профиля импорта:");
			pWnd = GetDlgItem(IDC_SELECT_FOLDER);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_OPEN_SELECT_FOLDER);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_PARAM_TRANS_COOR);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_FACTOR_X);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Коэффициент расширения по оси абсцисс:");
			pWnd = GetDlgItem(IDC_FACTOR_X);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_FACTOR_Y);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Коэффициент расширения по оси ординат:");
			pWnd = GetDlgItem(IDC_FACTOR_Y);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SHIFT_X);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Величина сдвига вправо по оси абсцисс:");
			pWnd = GetDlgItem(IDC_SHIFT_X);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SHIFT_Y);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Величина сдвига вверх по оси ординат:");
			pWnd = GetDlgItem(IDC_SHIFT_Y);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_TURN);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Поворот в градусах пр. часовой стрелки:");
			pWnd = GetDlgItem(IDC_TURN);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SIZE_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_SIZE_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INPUT_SIZE_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_SIZE_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INITIAL_ORDER_COORDINATES);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_USUAL);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INVERT);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_PARAMETERS_EXPORT);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_UNIT);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_METRE);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_MILLIMETRE);
			pWnd->EnableWindow(false);
			OnSelchangeSection();
			break;
		}
		case 2:
		{
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
				}
				catch (...) { }
				rsn.MoveNext();
			}
			m_Graph_area_name.ResetContent();
			CWnd* pWnd = GetDlgItem(IDC_INPUT_NAME_PROFILE);
			pWnd->SetWindowText("Имя профиля преобразования координат:");
			pWnd = GetDlgItem(IDC_SELECT_FOLDER);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_OPEN_SELECT_FOLDER);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_PARAM_TRANS_COOR);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_FACTOR_X);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Коэффициент расширения по оси абсцисс:");
			pWnd = GetDlgItem(IDC_FACTOR_X);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_FACTOR_Y);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Коэффициент расширения по оси ординат:");
			pWnd = GetDlgItem(IDC_FACTOR_Y);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SHIFT_X);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Величина сдвига вправо по оси абсцисс:");
			pWnd = GetDlgItem(IDC_SHIFT_X);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SHIFT_Y);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Величина сдвига вверх по оси ординат:");
			pWnd = GetDlgItem(IDC_SHIFT_Y);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_TURN);
			pWnd->EnableWindow(true);
			pWnd->SetWindowText("Поворот в градусах пр. часовой стрелки:");
			pWnd = GetDlgItem(IDC_TURN);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SIZE_X);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_SIZE_X);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INPUT_SIZE_Y);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_SIZE_Y);
			pWnd->EnableWindow(true);
			pWnd = GetDlgItem(IDC_INITIAL_ORDER_COORDINATES);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_USUAL);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INVERT);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_PARAMETERS_EXPORT);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_UNIT);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_METRE);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_MILLIMETRE);
			pWnd->EnableWindow(false);
			OnSelchangeSection();
			break;
		}
		case 3:
		{
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
				}
				catch (...) { }
				rsn.MoveNext();
			}
			m_Graph_area_name.ResetContent();
			CWnd* pWnd = GetDlgItem(IDC_INPUT_NAME_PROFILE);
			pWnd->SetWindowText("Имя профиля реорганизации координат:");
			pWnd = GetDlgItem(IDC_SELECT_FOLDER);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_OPEN_SELECT_FOLDER);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_PARAM_TRANS_COOR);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INPUT_FACTOR_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_FACTOR_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INPUT_FACTOR_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_FACTOR_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INPUT_SHIFT_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_SHIFT_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INPUT_SHIFT_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_SHIFT_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INPUT_TURN);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_TURN);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INPUT_SIZE_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_SIZE_X);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INPUT_SIZE_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_SIZE_Y);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INITIAL_ORDER_COORDINATES);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_USUAL);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_INVERT);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_PARAMETERS_EXPORT);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_UNIT);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_METRE);
			pWnd->EnableWindow(false);
			pWnd = GetDlgItem(IDC_MILLIMETRE);
			pWnd->EnableWindow(false);
			OnSelchangeSection();
			break;
		}
	}
	m_Name_section.SetCurSel(0);
	rsn.Close();
	rsn_new.Close();
	OnChangeNameProfile();
}

void AddProfileDlg::OnSelchangeSection() 
{
	// TODO: Add your control notification handler code here
	int CountGraphArea = 0;
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
		if (!rsn.IsBOF())
			rsn.MoveFirst();
		m_Name_section.GetWindowText(NameSection);
		m_Graph_area_name.ResetContent();
		while (!rsn.IsEOF())
		{
			try
			{
				if (rsn.m_NAMREG == NameSection && rsn.m_GRUPREG == 14)
				{
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
				if (rsn.m_NAMREG == NameSection && rsn.m_GRUPREG == 2)
					enable = false;
			}
			catch (...) { }
			rsn.MoveNext();
		}
		if (enable && m_Type_profile.GetCurSel() == 0)
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
						CountGraphArea++;
					}
					rsd.MoveNext();
				}
				m_Graph_area_name.SetCurSel(0);
				if (CountGraphArea > 0)
				{
					pWnd = GetDlgItem(IDC_GRAPH_AREA);
					pWnd->EnableWindow(true);
				}
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
		pWnd = GetDlgItem(IDC_SELECT_SECTION);
		pWnd->EnableWindow(true);
		pWnd = GetDlgItem(IDC_SECTION);
		pWnd->EnableWindow(true);
		OnChangeNameProfile();
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

void AddProfileDlg::OnOpenSelectFolder() 
{
	// TODO: Add your control notification handler code here
	char value_parameter[MAX_PATH];
	CString buffer;
	BROWSEINFO bi = {0};
	bi.hwndOwner = this->GetSafeHwnd();
    bi.lpszTitle = _T("Путь к папке:");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
	bi.lpfn = BrowseCallbackProc;
	bi.lParam = LPARAM(path);
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != 0)
    {
        if (SHGetPathFromIDList(pidl, path))
		{
			m_Choosen_folder.SetWindowText(path);
			m_Choosen_folder.GetWindowText(buffer);
			if (!access(buffer + "\\expimp.ini", 0))
			{
				GetPrivateProfileString("IMPPAR_MIFDBF", "cxx", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
				m_Factor_x.SetWindowText(value_parameter);
				GetPrivateProfileString("IMPPAR_MIFDBF", "cyy", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
				m_Factor_y.SetWindowText(value_parameter);
				GetPrivateProfileString("IMPPAR_MIFDBF", "ax", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
				m_Shift_x.SetWindowText(value_parameter);
				GetPrivateProfileString("IMPPAR_MIFDBF", "ay", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
				m_Shift_y.SetWindowText(value_parameter);
				GetPrivateProfileString("IMPPAR", "angl", NULL, value_parameter, sizeof(value_parameter), buffer + "\\expimp.ini");
				m_Turn.SetWindowText(value_parameter);
			}
		}
        IMalloc* imalloc = 0;
        if (SUCCEEDED(SHGetMalloc(&imalloc)))
        {
            imalloc->Free(pidl);
            imalloc->Release();
        }
    }
}

void AddProfileDlg::OnGraphArea() 
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

void AddProfileDlg::OnChangeNameProfile() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	CString FactorX, FactorY, ShiftX, ShiftY, Turn, SizeX, SizeY, NameProfile, ChoosenFolder;
	CWnd* pWnd = GetDlgItem(IDOK);
	m_Name_profile.GetWindowText(NameProfile);
	m_Choosen_folder.GetWindowText(ChoosenFolder);
	m_Factor_x.GetWindowText(FactorX);
	m_Factor_y.GetWindowText(FactorY);
	m_Shift_x.GetWindowText(ShiftX);
	m_Shift_y.GetWindowText(ShiftY);
	m_Turn.GetWindowText(Turn);
	m_Size_x.GetWindowText(SizeX);
	m_Size_y.GetWindowText(SizeY);
	if (m_Type_profile.GetCurSel() < 2)
	{
		if (FactorX.IsEmpty() || FactorY.IsEmpty() || ShiftX.IsEmpty() || ShiftY.IsEmpty() || Turn.IsEmpty() || NameProfile.IsEmpty() || ChoosenFolder.IsEmpty() || !NameProfile.Find(" ", 0) || !FactorX.Find(" ", 0) || !FactorY.Find(" ", 0) || !ShiftX.Find(" ", 0) || !ShiftY.Find(" ", 0) || !Turn.Find(" ", 0) || m_Name_section.GetCount() == 0)
			pWnd->EnableWindow(false);
		else
			pWnd->EnableWindow(true);
	}
	else
	{
		if (m_Type_profile.GetCurSel() == 2)
		{
			if (FactorX.IsEmpty() || FactorY.IsEmpty() || ShiftX.IsEmpty() || ShiftY.IsEmpty() || Turn.IsEmpty() || SizeX.IsEmpty() || SizeY.IsEmpty() || NameProfile.IsEmpty() || !NameProfile.Find(" ", 0) || !FactorX.Find(" ", 0) || !FactorY.Find(" ", 0) || !ShiftX.Find(" ", 0) || !ShiftY.Find(" ", 0) || !Turn.Find(" ", 0) || !SizeX.Find(" ", 0) || !SizeY.Find(" ", 0) || m_Name_section.GetCount() == 0)
				pWnd->EnableWindow(false);
			else
				pWnd->EnableWindow(true);
		}
		else
		{
			if (FactorX.IsEmpty() || FactorY.IsEmpty() || ShiftX.IsEmpty() || ShiftY.IsEmpty() || Turn.IsEmpty() || NameProfile.IsEmpty() || !NameProfile.Find(" ", 0) || !FactorX.Find(" ", 0) || !FactorY.Find(" ", 0) || !ShiftX.Find(" ", 0) || !ShiftY.Find(" ", 0) || !Turn.Find(" ", 0) || m_Name_section.GetCount() == 0)
				pWnd->EnableWindow(false);
			else
				pWnd->EnableWindow(true);
		}
	}
}

void AddProfileDlg::OnChangeFolder() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void AddProfileDlg::OnChangeFactorX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void AddProfileDlg::OnChangeFactorY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void AddProfileDlg::OnChangeShiftX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void AddProfileDlg::OnChangeShiftY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void AddProfileDlg::OnChangeTurn() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void AddProfileDlg::OnChangeSizeX() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void AddProfileDlg::OnChangeSizeY() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	OnChangeNameProfile();
}

void AddProfileDlg::OnOK() 
{
	// TODO: Add extra validation here
	char buffer[MAX_PATH];
	CString NameSection, GraphAreaName;
	m_Name_section.GetWindowText(NameSection);
	ProfilesExpImpRead ProfilesRS;
	ProfilesRS.IniFile = IniFile;
	ProfilesRS.Open();
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
	TypeProfile = m_Type_profile.GetCurSel() + 1;
	GraphAreaEnable = m_Graph_area.IsWindowEnabled();
	m_Graph_area_name.GetWindowText(GraphAreaName);
	if (enable && m_Type_profile.GetCurSel() == 0)
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
					GraphAreaId = rsd.m_NUMSPACE;
					break;
				}
				rsd.MoveNext();
			}
		}
		rsd.Close();
	}
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
	ProfilesRS.Close();
	CDialog::OnOK();
}
