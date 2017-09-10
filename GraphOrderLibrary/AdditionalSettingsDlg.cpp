// AdditionalSettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "AdditionalSettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdditionalSettingsDlg dialog

int Hour;

CAdditionalSettingsDlg::CAdditionalSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdditionalSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdditionalSettingsDlg)
	//}}AFX_DATA_INIT
}


void CAdditionalSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdditionalSettingsDlg)
	DDX_Control(pDX, IDC_INCREASE_DATE, m_Increase_date);
	DDX_Control(pDX, IDC_REDUCE_DATE, m_Reduce_date);
	DDX_Control(pDX, IDC_INPUT_DURATION_PERIOD, m_Duration_period);
	DDX_Control(pDX, IDC_INPUT_STEP, m_Value_step);
	DDX_Control(pDX, IDC_SELECT_TIME_BEGIN_PERIOD, m_Time_begin_period);
	DDX_Control(pDX, IDC_SELECT_DATE_BEGIN_PERIOD, m_Date_begin_period);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdditionalSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CAdditionalSettingsDlg)
	ON_BN_CLICKED(IDC_REDUCE_DATE, OnReduceDate)
	ON_BN_CLICKED(IDC_INCREASE_DATE, OnIncreaseDate)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_SELECT_DATE_BEGIN_PERIOD, OnDatetimechangeSelectDateBeginPeriod)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_SELECT_TIME_BEGIN_PERIOD, OnDatetimechangeSelectTimeBeginPeriod)
	ON_EN_CHANGE(IDC_INPUT_DURATION_PERIOD, OnChangeInputDurationPeriod)
	ON_EN_CHANGE(IDC_INPUT_STEP, OnChangeInputStep)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdditionalSettingsDlg message handlers

BOOL CAdditionalSettingsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	char buffer[MAX_PATH];
	CString IniWay, Date_str;
	CTimeSpan ChangeHours;
	COleDateTime Date;
	m_Reduce_date.SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_REDUCE)));
	m_Increase_date.SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_INCREASE)));
	IniWay = IniFile;
	IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));
	GetPrivateProfileString("Period", "DateBegin", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	Date_str = buffer;
	Date.ParseDateTime(Date_str);
	m_Date_begin_period.SetTime(Date);
	m_Time_begin_period.SetTime(Date);
	m_Date_begin_period.GetTime(DateBeginPeriod);
	TimeBeginPeriod = DateBeginPeriod;
	Hour = TimeBeginPeriod.GetHour();
	GetPrivateProfileString("Period", "DurationPeriod", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	m_Duration_period.SetWindowText(buffer);
	m_Duration_period.GetWindowText(DurationPeriod);
	ChangeHours = CTimeSpan(0, atoi(DurationPeriod), 0, 0);
	DateEndPeriod = CTime(Date.GetYear(), Date.GetMonth(), Date.GetDay(), Date.GetHour(), Date.GetMinute(), Date.GetSecond()) + ChangeHours;
	GetPrivateProfileString("Period", "ValueStep", NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
	m_Value_step.SetWindowText(buffer);
	m_Value_step.GetWindowText(ValueStep);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CAdditionalSettingsDlg::OnReduceDate()
{
	// TODO: Add your control notification handler code here
	char buffer[MAX_PATH];
	CString Time;
	CTimeSpan ChangeHours;
	COleDateTime DateTime;
	if (atoi(DurationPeriod) > 0)
	{
		Hour -= atoi(DurationPeriod);
		while (Hour < 0)
		{
			Hour = 24 + Hour;
			DateTime.SetDate(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay() - 1);
			m_Date_begin_period.SetTime(DateTime);
		}
		sprintf(buffer, "%i.%i.%i %i:%i:%i", DateBeginPeriod.GetDay(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetYear(), Hour, TimeBeginPeriod.GetMinute(), TimeBeginPeriod.GetSecond());
		Time = buffer;
		DateTime.ParseDateTime(Time);
		m_Time_begin_period.SetTime(DateTime);
		m_Date_begin_period.GetTime(DateBeginPeriod);
		m_Time_begin_period.GetTime(TimeBeginPeriod);
		ChangeHours = CTimeSpan(0, atoi(DurationPeriod), 0, 0);
		DateEndPeriod = CTime(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay(), TimeBeginPeriod.GetHour(), TimeBeginPeriod.GetMinute(), TimeBeginPeriod.GetSecond()) + ChangeHours;
	}
	else
		MessageBox("Длительность периода указана неверно!");
}

void CAdditionalSettingsDlg::OnIncreaseDate()
{
	// TODO: Add your control notification handler code here
	char buffer[MAX_PATH];
	CString Time;
	CTimeSpan ChangeHours;
	COleDateTime DateTime;
	if (atoi(DurationPeriod) > 0)
	{
		Hour += atoi(DurationPeriod);
		while (Hour >= 24)
		{
			Hour = Hour - 24;
			DateTime.SetDate(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay() + 1);
			m_Date_begin_period.SetTime(DateTime);
		}
		sprintf(buffer, "%i.%i.%i %i:%i:%i", DateBeginPeriod.GetDay(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetYear(), Hour, TimeBeginPeriod.GetMinute(), TimeBeginPeriod.GetSecond());
		Time = buffer;
		DateTime.ParseDateTime(Time);
		m_Time_begin_period.SetTime(DateTime);
		m_Date_begin_period.GetTime(DateBeginPeriod);
		m_Time_begin_period.GetTime(TimeBeginPeriod);
		ChangeHours = CTimeSpan(0, atoi(DurationPeriod), 0, 0);
		DateEndPeriod = CTime(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay(), TimeBeginPeriod.GetHour(), TimeBeginPeriod.GetMinute(), TimeBeginPeriod.GetSecond()) + ChangeHours;
	}
	else
		MessageBox("Длительность периода указана неверно!");
}

void CAdditionalSettingsDlg::OnDatetimechangeSelectDateBeginPeriod(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CTimeSpan ChangeHours;
	m_Date_begin_period.GetTime(DateBeginPeriod);
	ChangeHours = CTimeSpan(0, atoi(DurationPeriod), 0, 0);
	DateEndPeriod = CTime(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay(), TimeBeginPeriod.GetHour(), TimeBeginPeriod.GetMinute(), TimeBeginPeriod.GetSecond()) + ChangeHours;

	*pResult = 0;
}

void CAdditionalSettingsDlg::OnDatetimechangeSelectTimeBeginPeriod(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	CTimeSpan ChangeHours;
	m_Time_begin_period.GetTime(TimeBeginPeriod);
	Hour = TimeBeginPeriod.GetHour();
	ChangeHours = CTimeSpan(0, atoi(DurationPeriod), 0, 0);
	DateEndPeriod = CTime(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay(), TimeBeginPeriod.GetHour(), TimeBeginPeriod.GetMinute(), TimeBeginPeriod.GetSecond()) + ChangeHours;

	*pResult = 0;
}

void CAdditionalSettingsDlg::OnChangeInputDurationPeriod()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	CTimeSpan ChangeHours;
	m_Duration_period.GetWindowText(DurationPeriod);
	ChangeHours = CTimeSpan(0, atoi(DurationPeriod), 0, 0);
	DateEndPeriod = CTime(DateBeginPeriod.GetYear(), DateBeginPeriod.GetMonth(), DateBeginPeriod.GetDay(), TimeBeginPeriod.GetHour(), TimeBeginPeriod.GetMinute(), TimeBeginPeriod.GetSecond()) + ChangeHours;
}

void CAdditionalSettingsDlg::OnChangeInputStep()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here
	m_Value_step.GetWindowText(ValueStep);
}

void CAdditionalSettingsDlg::OnOK()
{
	// TODO: Add extra validation here
	if (atoi(DurationPeriod) > 0 && atoi(ValueStep) > 0)
		CDialog::OnOK();
	else
		MessageBox("Параметры интервала указаны неверно!");
}
