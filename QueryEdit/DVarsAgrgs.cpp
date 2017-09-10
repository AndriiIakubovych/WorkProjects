#include "stdafx.h"

#include "QueryEditRes\resource.h"

#include "DQueryEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CVarsDlg dialog
CVarsDlg::CVarsDlg(SMetaInfo* metainfo, LPCTSTR datasql, CWnd* pParent)
	: CSetDialog(CVarsDlg::IDD, metainfo, pParent)
{
	m_ctypvar = -1;
	m_ctypecntrl = -1;
	m_datasql=datasql;
}

void CVarsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

    DDX_Control(pDX, IDC_WIDTHCNTRL, m_cwidthcntrlctrl);
	DDX_Control(pDX, IDC_NCOLQUERY, m_cncolqueryctrl);
	DDX_Control(pDX, IDC_NUMROWLIST, m_cnumrowlistctrl);
	DDX_Control(pDX, IDC_NUMCOLLIST, m_cnumcollistctrl);
	DDX_Control(pDX, IDC_QUERYVAR, m_cqueryvarctrl);
	DDX_Control(pDX, IDC_TYPECNTRL, m_ctypecntrlctrl);
	DDX_Control(pDX, IDC_TYPVAR, m_ctypvarctrl);
	DDX_Text(pDX, IDC_DOCNAME, m_docname);
	DDX_Text(pDX, IDC_NUMVAR, m_numvar);
	DDX_Text(pDX, IDC_NAMEVAR, m_namevar);
	DDX_Text(pDX, IDC_FORMAT, m_cformat);
	DDX_Text(pDX, IDC_CODVAR, m_ccodvar);
	DDX_CBIndex(pDX, IDC_TYPVAR, m_ctypvar);
	DDX_Text(pDX, IDC_CONDITION, m_ccondition);
	DDX_Text(pDX, IDC_DEFVAL, m_cdefval);
	DDX_CBIndex(pDX, IDC_TYPECNTRL, m_ctypecntrl);
	DDX_CBString(pDX, IDC_QUERYVAR, m_cqueryvar);
	DDX_Text(pDX, IDC_NUMCOLLIST, m_cnumcollist);
	DDX_Text(pDX, IDC_NUMROWLIST, m_cnumrowlist);
	DDX_Text(pDX, IDC_WIDTHCNTRL, m_cwidthcntrl);
	DDX_Text(pDX, IDC_NCOLQUERY, m_cncolquery);
}

BEGIN_MESSAGE_MAP(CVarsDlg, CDialog)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_EN_CHANGE(IDC_NAMEVAR, OnSomeChanged)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_VERIFY, OnVerify)
	ON_CBN_SELCHANGE(IDC_TYPVAR, OnSelchangeTypVar)
	ON_EN_CHANGE(IDC_FORMAT, OnSomeChanged)
	ON_EN_CHANGE(IDC_CODVAR, OnSomeChanged)
	ON_EN_CHANGE(IDC_CONDITION, OnSomeChanged)
	ON_EN_CHANGE(IDC_DEFVAL, OnSomeChanged)
	ON_CBN_SELCHANGE(IDC_TYPECNTRL, OnSomeChanged)
	ON_EN_CHANGE(IDC_NUMCOLLIST, OnSomeChanged)
	ON_EN_CHANGE(IDC_NUMROWLIST, OnSomeChanged)
	ON_EN_CHANGE(IDC_WIDTHCNTRL, OnSomeChanged)
	ON_EN_CHANGE(IDC_NCOLQUERY, OnSomeChanged)
	ON_CBN_EDITCHANGE(IDC_QUERYVAR, OnSomeChanged)
	ON_CBN_SELCHANGE(IDC_QUERYVAR, OnSomeChanged)
END_MESSAGE_MAP()

BOOL CVarsDlg::OnInitDialog() 
{
	CSetDialog::OnInitDialog();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CVarsDlg::LoadNames()
{
	POSITION pos=m_metainfo->m_ltypvar.GetHeadPosition();
	while(pos)
		m_ctypvarctrl.AddString(m_metainfo->m_ltypvar.GetNext(pos));

	pos=m_metainfo->m_ltypecntrl.GetHeadPosition();
	while(pos)
		m_ctypecntrlctrl.AddString(m_metainfo->m_ltypecntrl.GetNext(pos));

	m_queries->Reload();
	m_queries->MoveFirst();
	while(!m_queries->IsEOF())
	{
		m_cqueryvarctrl.AddString(m_queries->m_strName);
		m_queries->MoveNext();
	}

	if(m_scrqueries)			//дополнительно запросы из 14 базы если есть
	{
		m_scrqueries->Reload();
		m_scrqueries->MoveFirst();
		while(!m_scrqueries->IsEOF())
		{
			if(m_cqueryvarctrl.FindStringExact(-1, m_scrqueries->m_strName)  == CB_ERR)
			{
				m_cqueryvarctrl.AddString(m_scrqueries->m_strName);
			}
			m_scrqueries->MoveNext();
		}
	}

	if(m_queries->FindName(m_datasql))
	{
	}
}

void CVarsDlg::LoadData()
{
	CVarsSet *m_varsset=(CVarsSet *)m_set;

	m_numvar.Format(_T("%d"),m_varsset->m_NUMVAR);
	m_namevar=m_varsset->m_NAMEVAR;
	m_cformat=m_varsset->m_FORMAT;
	m_ccodvar=m_varsset->m_CODVAR;
	m_ctypvar=FindACC(m_metainfo->m_ACCtypvar,m_varsset->m_TYPVAR);
	m_ccondition=m_varsset->m_CONDITION;
	m_cdefval=m_varsset->m_DEFVAL;
	m_ctypecntrl=FindACC(m_metainfo->m_ACCtypctrl,m_varsset->m_TYPECNTRL);
	m_cnumcollist=m_varsset->m_NUMCOLLIST;
	m_cnumrowlist=m_varsset->m_NUMROWLIST;
	m_cwidthcntrl=m_varsset->m_WIDTHCNTRL;
	m_cncolquery=m_varsset->m_NCOLQUERY;

	m_cqueryvar=m_varsset->m_QUERYVAR;
	m_cqueryvar.TrimLeft();
	m_cqueryvar.TrimRight();

	m_cordervar=m_varsset->m_ORDERVAR;

	UpdateData(false);
	m_ischanged=FALSE;

	CSetDialog::LoadData();
}

BOOL CVarsDlg::SaveData()
{
	if(!VerifyData())
		return FALSE;
	CVarsSet *m_varsset=(CVarsSet *)m_set;

	if(m_ischanged)
	{
		UpdateData();
		m_varsset->Edit();

		m_varsset->m_NAMEVAR=m_namevar;
		m_varsset->m_FORMAT=m_cformat;
		m_varsset->m_CODVAR=m_ccodvar;
		m_varsset->m_TYPVAR=(BYTE)FindACCBack(m_metainfo->m_ACCtypvar,m_ctypvar);
		m_varsset->m_CONDITION=m_ccondition;
		m_varsset->m_DEFVAL=m_cdefval;
		m_varsset->m_TYPECNTRL=(BYTE)FindACCBack(m_metainfo->m_ACCtypctrl,m_ctypecntrl);
		m_varsset->m_NUMCOLLIST=m_cnumcollist;
		m_varsset->m_NUMROWLIST=m_cnumrowlist;
		m_varsset->m_WIDTHCNTRL=m_cwidthcntrl;
		m_varsset->m_NCOLQUERY=m_cncolquery;
		m_varsset->m_QUERYVAR=m_cqueryvar;
		m_varsset->m_ORDERVAR=m_cordervar;

		m_varsset->UpdateNet(0);

		m_ischanged=FALSE;
	}
	return TRUE;
}

void CVarsDlg::OnPrev() 
{
	CSetDialog::OnPrev();
}

void CVarsDlg::OnNext() 
{
	CSetDialog::OnNext();
}

void CVarsDlg::OnSomeChanged() 
{
	m_ischanged	= TRUE;
	ConformDataFields();
}

/*
void CVarsDlg::OnSave()
{
    SaveData();
}

void CVarsDlg::OnOK() 
{
	if(SaveData())	
		CDialog::OnOK();
}
*/

void CVarsDlg::ConformDataFields()
{
	UpdateData();
	CWnd *wnd=GetFocus();
	m_cnumcollistctrl.EnableWindow(false);
	m_cnumrowlistctrl.EnableWindow(false);
	m_cncolqueryctrl.EnableWindow(false);

	CString strtype;
	m_ctypecntrlctrl.GetWindowText(strtype);
	if(strtype=="Combo Box" || strtype == "Combo Box + search")
	{
		m_cnumrowlistctrl.EnableWindow(true);
		m_cncolqueryctrl.EnableWindow(true);
		if(!m_cqueryvarctrl.IsWindowEnabled())
			m_cqueryvarctrl.EnableWindow(true);
	}
	else if(strtype=="List Box")
	{
		m_cnumcollistctrl.EnableWindow(true);
		m_cnumrowlistctrl.EnableWindow(true);
		m_cncolqueryctrl.EnableWindow(true);
		if(!m_cqueryvarctrl.IsWindowEnabled())
			m_cqueryvarctrl.EnableWindow(true);
	}
	else
		m_cqueryvarctrl.EnableWindow(false);
	wnd->SetFocus();
}

void CVarsDlg::OnVerify() 
{
	CSetDialog::OnVerify();
}

BOOL CVarsDlg::VerifyData()
{
	BOOL ispass=TRUE;
	UpdateData();
	if(m_cnumcollistctrl.IsWindowEnabled() && m_cnumcollist=="")
	{
		if(!DoDataWarning(_T("Не заполнено поле \"колонок\".")))
			ispass=FALSE;
	}

	if(m_cnumrowlistctrl.IsWindowEnabled() && m_cnumrowlist=="")
	{
		if(!DoDataWarning(_T("Не заполнено поле \"строк\".")))
			ispass=FALSE;
	}

	if(m_cwidthcntrlctrl.IsWindowEnabled() && m_cwidthcntrl=="")
	{
		if(!DoDataWarning(_T("Не указана ширина.")))
			ispass=FALSE;
	}

	if(m_cncolqueryctrl.IsWindowEnabled() && m_cncolquery=="")
	{
		if(!DoDataWarning(_T("Не указан присоед. столбец.")))
			ispass=FALSE;
	}

	if(m_ctypvar == 2 && m_cformat=="")
	{
		DoDataError(_T("Формат для даты не заполнен."));
		ispass=FALSE;
	}

	return ispass;
}

void CVarsDlg::OnSelchangeTypVar() 
{
	UpdateData();
	if(FindACCBack(m_metainfo->m_ACCtypvar,m_ctypvar)==5)
	{
		m_ctypecntrl=FindACC(m_metainfo->m_ACCtypctrl,4);
		m_cnumrowlist="5";
		m_cncolquery="2";
		UpdateData(false);
	}
	OnSomeChanged();
}


/////////////////////////////////////////////////////////////////////////////
// CAgrsDlg dialog
CAgrsDlg::CAgrsDlg(SMetaInfo* metainfo,CWnd* pParent /*=NULL*/)
	: CSetDialog(CAgrsDlg::IDD, metainfo, pParent)
{
	m_ctypeagr = -1;
	m_ccalczero = FALSE;
	m_cncolkey = -1;
	m_cundertable = FALSE;
	m_levels = 0;
	m_noseeagrexists = TRUE;
}

void CAgrsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LEVELS, m_clevels);
	DDX_Control(pDX, IDC_UNDERTABLE, m_cundertablectrl);
	DDX_Control(pDX, IDC_NCOLKEY, m_cncolkeyctrl);
	DDX_Control(pDX, IDC_TYPEAGR, m_ctypeagrctrl);
	DDX_Text(pDX, IDC_DOCNAME, m_docname);
	DDX_Text(pDX, IDC_NAMEAGR, m_cnameagr);
	DDX_CBIndex(pDX, IDC_TYPEAGR, m_ctypeagr);
	DDX_Text(pDX, IDC_NROWLAST, m_cnrowlast);
	DDX_Text(pDX, IDC_NROWFIRST, m_cnrowfirst);
	DDX_Text(pDX, IDC_NUMAGR, m_numagr);
	DDX_Check(pDX, IDC_CALCZERO, m_ccalczero);
	DDX_CBIndex(pDX, IDC_NCOLKEY, m_cncolkey);
	DDX_Check(pDX, IDC_UNDERTABLE, m_cundertable);
	DDX_Text(pDX, IDC_LEVELS, m_levels);
}

BEGIN_MESSAGE_MAP(CAgrsDlg, CDialog)
	ON_EN_CHANGE(IDC_NAMEAGR, OnSomeChanged)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_VERIFY, OnVerify)
	ON_CBN_SELCHANGE(IDC_TYPEAGR, OnSomeChanged)
	ON_EN_CHANGE(IDC_NROWLAST, OnSomeChanged)
	ON_EN_CHANGE(IDC_NROWFIRST, OnSomeChanged)
	ON_BN_CLICKED(IDC_CALCZERO, OnSomeChanged)
	ON_CBN_SELCHANGE(IDC_NCOLKEY, OnSomeChanged)
	ON_BN_CLICKED(IDC_UNDERTABLE, OnSomeChanged)
	ON_EN_CHANGE(IDC_LEVELS, OnSomeChanged)
END_MESSAGE_MAP()

void CAgrsDlg::LoadNames()
{
	POSITION pos=m_metainfo->m_ltypeagr.GetHeadPosition();
	while(pos)
		m_ctypeagrctrl.AddString(m_metainfo->m_ltypeagr.GetNext(pos));

	CAgrsSet *m_agrsset=(CAgrsSet *)m_set;
	//вычитка значения ISNUMREC для текущего дока
	CDocsSet dset((CDatabNet *)m_set->m_pDatabase);
	dset.m_strFilter.Format(_T("CODDOC=%d"),m_agrsset->m_CODDOC);
	dset.Open();
	if(!dset.IsEOF())
		m_isnumrec=dset.m_ISNUMREC;
	dset.Close();

	//вычитка списка описанных столбцов
	CColsSet cset((CDatabNet *)m_set->m_pDatabase);
	cset.m_strFilter.Format(_T("CODDOC=%d"),m_agrsset->m_CODDOC);
	cset.Open();
	m_ACCcols.RemoveAll();

	m_cncolkeyctrl.AddString(_T(""));
	m_ACCcols.Add(SMI_NULLVALUE);
	
	m_cncolkeyctrl.AddString(_T("<По боковику>"));
	m_ACCcols.Add(-1);
	
	while(!cset.IsEOF())
	{
		m_cncolkeyctrl.AddString(cset.m_NAMSQLCOL);
		m_ACCcols.Add(cset.m_NUMCOL);
		cset.MoveNext();
	}
	cset.Close();
}

void CAgrsDlg::LoadData()
{
	CAgrsSet *m_agrsset=(CAgrsSet *)m_set;

	m_numagr.Format(_T("%d"),m_agrsset->m_NUMAGR);
	m_cnameagr=m_agrsset->m_NAMEAGR;
	m_ctypeagr=FindACC(m_metainfo->m_ACCtypeagr,m_agrsset->m_TYPEAGR);
	m_cnrowlast=m_agrsset->m_NROWLAST;
	m_cnrowfirst=m_agrsset->m_NROWFIRST;
	m_ccalczero=m_agrsset->m_CALCZERO;
	m_levels=m_agrsset->m_NCOL_HEAD;
	if (!m_agrsset->GetNoSeeAgr(m_cundertable))
	{
		m_cundertablectrl.EnableWindow(false);
		m_noseeagrexists = FALSE;
	}

	if(m_agrsset->m_NCOLKEY == -1)
		//по боковику
		m_cncolkey = 1;
	else if(m_agrsset->m_NCOLKEY == 0)
		m_cncolkey = 0;
	else if(m_isnumrec)
		m_cncolkey=FindACC(m_ACCcols,m_agrsset->m_NCOLKEY-1);
	else
		m_cncolkey=FindACC(m_ACCcols,m_agrsset->m_NCOLKEY);

	CRecordset set(m_BASEBase);
	CString SQL;
	SQL.Format(_T("SELECT NCOL_HEAD FROM DESCRDOC WHERE CODDOC=%d"), m_agrsset->m_CODDOC);
	set.Open(CRecordset::forwardOnly, SQL);
	CDBVariant var;
	set.GetFieldValue(_T("NCOL_HEAD"), var);
	set.Close();
	m_docNCOL_HEAD = var.m_chVal;

	UpdateData(false);
	m_ischanged=FALSE;

	CSetDialog::LoadData();
}

BOOL CAgrsDlg::SaveData()
{
	if(!VerifyData())
		return FALSE;
	CAgrsSet *m_agrsset=(CAgrsSet *)m_set;

	if(m_ischanged)
	{
		UpdateData();
		m_agrsset->Edit();

		m_agrsset->m_NAMEAGR=m_cnameagr;
		m_agrsset->m_TYPEAGR=(BYTE)FindACCBack(m_metainfo->m_ACCtypeagr,m_ctypeagr);
		m_agrsset->m_NROWLAST=m_cnrowlast;
		m_agrsset->m_NROWFIRST=m_cnrowfirst;
		m_agrsset->m_CALCZERO=m_ccalczero;
		m_agrsset->m_NCOL_HEAD=m_levels;
		if(m_cncolkey == 0 || m_cncolkey == 1)
			m_cundertable = FALSE;
		if (m_noseeagrexists)
			m_agrsset->SetNoSeeAgr(m_cundertable);
		
		if(m_cncolkey == 0) //отсутствует
			m_agrsset->SetFieldNull(&m_agrsset->m_NCOLKEY);
		else if(m_isnumrec && m_cncolkey != 1)
			    m_agrsset->m_NCOLKEY=FindACCBack(m_ACCcols,m_cncolkey)+1;
			else
				m_agrsset->m_NCOLKEY=FindACCBack(m_ACCcols,m_cncolkey);

		m_agrsset->UpdateNet(0);

		m_ischanged=FALSE;
	}
	return TRUE;
}

BOOL CAgrsDlg::OnInitDialog() 
{
	CSetDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAgrsDlg::OnSomeChanged() 
{
	ConformDataFields();
	m_ischanged=TRUE;	
}

void CAgrsDlg::OnPrev() 
{
	CSetDialog::OnPrev();
}

void CAgrsDlg::OnNext()
{
	CSetDialog::OnNext();
}

/*
void CAgrsDlg::OnSave()
{
    SaveData();
}

void CAgrsDlg::OnOK() 
{
	if(SaveData())
		CDialog::OnOK();
}
*/

void CAgrsDlg::OnVerify() 
{

	CSetDialog::OnVerify();	
}

BOOL CAgrsDlg::VerifyData()
{
	UpdateData();
	BOOL isPass=TRUE;
	if(isLevelsEnabled && (m_levels < 0 || m_levels > m_docNCOL_HEAD))
	{
		CString mes;
		mes.Format(_T("Неверное значение поля \"Уровней боковика\" (должно быть в диапазоне %d..%d)."), 0, m_docNCOL_HEAD);
		DoDataError(mes);
		isPass=FALSE;
	}

	return isPass;
}

void CAgrsDlg::ConformDataFields()
{
	UpdateData(); 
	if (m_cncolkey == 0 || m_cncolkey == 1 || !m_noseeagrexists)
		m_cundertablectrl.EnableWindow(FALSE);
	else
		m_cundertablectrl.EnableWindow(TRUE);

	if(m_set->IsColumnPresent(_T("NCOL_HEAD")))
		m_clevels.EnableWindow(isLevelsEnabled = TRUE);
	else
		m_clevels.EnableWindow(isLevelsEnabled = FALSE);

	CString name;
	m_cncolkeyctrl.GetWindowText(name);
	if(name != "<По боковику>")
		m_clevels.EnableWindow(isLevelsEnabled = FALSE);
}
