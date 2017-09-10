#include "stdafx.h"

#include "QueryEditRes\resource.h"

#include "DQueryEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CColsDlg dialog
template<class InIt>
	bool ChangePlaces(InIt& A, InIt& B)
{
	InIt C = B;
	B = A;
	A = C;
	return true;
}

CColsDlg::CColsDlg(SMetaInfo* metainfo,CDocsSet *dset,CWnd* pParent /*=NULL*/)
	: CSetDialog(CColsDlg::IDD, metainfo, pParent)
{
	m_ctypcentr = -1;
	m_ctyppar = -1;
	m_ctypobj = -1;
	m_ctypdata = -1;
	m_ctypagr = -1;
	m_cvisible = FALSE;
	m_ctranstype = -1;
	m_numcol = 0;
	m_cvidobj = -1;
	m_datasql=dset->m_QUERYDATA;
	m_dset = dset;
	m_dontdodata=false;
}

void CColsDlg::DoDataExchange(CDataExchange* pDX)
{
	if(m_dontdodata)
		return;
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VIDOBJ, m_cvidobjctrl);
	DDX_Control(pDX, IDC_TRANSTYPE, m_ctranstypectrl);
	DDX_Control(pDX, IDC_DATAFORMAT, m_cdataformatctrl);
	DDX_Control(pDX, IDC_CLASSID, m_cclassidctrl);
	DDX_Control(pDX, IDC_FORMAT, m_cformatctrl);
	DDX_Control(pDX, IDC_WIDTH, m_cwidthctrl);
	DDX_Control(pDX, IDC_QUERYNAME, m_cquerynamectrl);
	DDX_Control(pDX, IDC_NAME, m_cnamectrl);
	DDX_Control(pDX, IDC_TYPEAGR, m_ctypagrctrl);
	DDX_Control(pDX, IDC_TYPOBJ, m_ctypobjctrl);
	DDX_Control(pDX, IDC_TYPPAR, m_ctypparctrl);
	DDX_Control(pDX, IDC_TYPEDATA, m_ctypdatactrl);
	DDX_Control(pDX, IDC_TYPECENTR, m_ctypcentrctrl);
	DDX_Text(pDX, IDC_NAME, m_cname);
	DDX_Text(pDX, IDC_WIDTH, m_cwidth);
	DDX_Text(pDX, IDC_FORMAT, m_cformat);
	DDX_CBIndex(pDX, IDC_TYPECENTR, m_ctypcentr);
	DDX_CBIndex(pDX, IDC_TYPPAR, m_ctyppar);
	DDX_CBIndex(pDX, IDC_TYPOBJ, m_ctypobj);
	DDX_CBIndex(pDX, IDC_TYPEDATA, m_ctypdata);
	DDX_CBIndex(pDX, IDC_TYPEAGR, m_ctypagr);
	DDX_Check(pDX, IDC_VISIBLE, m_cvisible);
	DDX_Text(pDX, IDC_DOCNAME, m_docname);
	DDX_CBString(pDX, IDC_QUERYNAME, m_queryname);
	DDX_Text(pDX, IDC_CLASSID, m_cclassid);
	DDX_Text(pDX, IDC_DATAFORMAT, m_cdataformat);
	DDX_CBIndex(pDX, IDC_TRANSTYPE, m_ctranstype);
	DDX_Text(pDX, IDC_NUMCOL, m_numcol);
	DDX_CBIndex(pDX, IDC_VIDOBJ, m_cvidobj);
}

BEGIN_MESSAGE_MAP(CColsDlg, CDialog)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_EN_CHANGE(IDC_NAME, OnSomeFieldChanged)
	ON_CBN_EDITCHANGE(IDC_QUERYNAME, OnQueryNameChange)
	ON_CBN_SELCHANGE(IDC_QUERYNAME, OnSelchangeQueryname)
	ON_BN_CLICKED(IDC_VISIBLE, OnVisibleChange)
	ON_BN_CLICKED(IDC_VERIFY, OnVerify)
	ON_CBN_SELCHANGE(IDC_TYPEDATA, OnChangeDataType)
	ON_CBN_DROPDOWN(IDC_QUERYNAME, OnDropDownQueryName)
	ON_EN_CHANGE(IDC_WIDTH, OnSomeFieldChanged)
	ON_EN_CHANGE(IDC_FORMAT, OnSomeFieldChanged)
	ON_CBN_SELCHANGE(IDC_TYPECENTR, OnSomeFieldChanged)
	ON_EN_CHANGE(IDC_QUERYNAME, OnSomeFieldChanged)
	ON_CBN_SELCHANGE(IDC_TYPEAGR, OnSomeFieldChanged)
	ON_CBN_SELCHANGE(IDC_TYPPAR, OnSomeFieldChanged)
	ON_CBN_SELCHANGE(IDC_TYPOBJ, OnSomeFieldChanged)
	ON_EN_CHANGE(IDC_CLASSID, OnSomeFieldChanged)
	ON_CBN_EDITCHANGE(IDC_DATAFORMAT, OnSomeFieldChanged)
	ON_CBN_SELCHANGE(IDC_DATAFORMAT, OnSomeFieldChanged)
	ON_CBN_SELCHANGE(IDC_TRANSTYPE, OnSomeFieldChanged)
	ON_EN_CHANGE(IDC_NUMCOL, OnSomeFieldChanged)
	ON_CBN_EDITCHANGE(IDC_VIDOBJ, OnSomeFieldChanged)
	ON_CBN_SELCHANGE(IDC_VIDOBJ, OnSomeFieldChanged)
END_MESSAGE_MAP()

BOOL CColsDlg::OnInitDialog() 
{
	CSetDialog::OnInitDialog();

	m_cnamectrl.SetLimitText(m_metainfo->m_namewidth);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CColsDlg::OnPrev()
{
	CSetDialog::OnPrev();
}

BOOL CColsDlg::SaveData()
{
	if(!VerifyData())
		return FALSE;
	CColsSet *m_cset=(CColsSet *)m_set;

	if(m_ischanged)
	{
		UpdateData();

		m_set->Edit();


		BOOL iscodechanged = FALSE;

		if(m_cset->m_NUMCOL!=m_numcol)
		{
			m_cset->m_NUMCOL=m_numcol;
			iscodechanged = TRUE;
/*			m_cset->UpdateNet(0);
			m_cset->Requery();
			m_cset->MoveToCode(m_numcol);*/
		}

		m_cset->m_NAMECOL=m_cname;
		
		m_cset->m_WIDTHCOL=m_cwidth;
		m_cset->m_TYPDATA=(BYTE)FindACCBack(m_metainfo->m_ACCdat,m_ctypdata);

		if(m_cdataformatctrl.IsWindowEnabled())
			m_cset->m_FORMAT=m_cdataformat;
		else
			m_cset->m_FORMAT=m_cformat;
		m_cset->m_TYPCENTR=(BYTE)FindACCBack(m_metainfo->m_ACCcentr,m_ctypcentr);
		m_queryname.TrimRight();
		m_cset->m_NAMSQLCOL=m_queryname;
		
		m_cset->m_TYPEAGR=(BYTE)FindACCBack(m_metainfo->m_ACCagrcol,m_ctypagr);

		if(m_ctyppar == 0 || m_ctyppar == -1)
			m_cset->SetFieldNull(&m_cset->m_TYPPAR);
		else
			m_cset->m_TYPPAR=FindACCBack(m_metainfo->m_ACCpar,m_ctyppar);
		m_cset->m_TOBJECT=(BYTE)FindACCBack(m_metainfo->m_ACCobj,m_ctypobj);
        m_cset->m_TYPEREFORM=FindACCBack(m_metainfo->m_ACCtrans,m_ctranstype);
		m_cset->m_SEE=m_cvisible;
		m_cset->m_CLASSID=m_cclassid;
		m_cset->m_FIELDTYPE=m_cfieldtype;
		if(m_cfieldtype == _T(""))
			m_cset->SetFieldNull(&m_cset->m_FIELDTYPE);
		else
			m_cset->m_FIELDTYPE=m_cfieldtype;

		m_cset->UpdateNet(0);
		if(iscodechanged)
		{
			m_cset->Requery();
			m_cset->MoveToCode(m_numcol);
		}
		m_ischanged=FALSE;

		//и вид объекта откорректировать, если тип - перейти к объекту
		if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==10)
		{
			m_dset->Edit();
			m_dset->m_VIDOBJ = (BYTE)FindACCBack(m_metainfo->m_ACCvidobj,m_cvidobj);
			m_dset->UpdateNet(0);
		}

	}
	return TRUE;
}

void CColsDlg::LoadData()
{
	CColsSet *m_cset=(CColsSet *)m_set;

	m_cname=m_cset->m_NAMECOL;
	m_cwidth=m_cset->m_WIDTHCOL;
	m_numcol = m_cset->m_NUMCOL;
	m_cformat=m_cset->m_FORMAT;
	m_cdataformat=m_cset->m_FORMAT;
	m_ctypcentr=FindACC(m_metainfo->m_ACCcentr,m_cset->m_TYPCENTR);
	m_queryname=m_cset->m_NAMSQLCOL + _T(" ");

	m_ctypdata=FindACC(m_metainfo->m_ACCdat,m_cset->m_TYPDATA);
	m_ctypagr=FindACC(m_metainfo->m_ACCagrcol,m_cset->m_TYPEAGR);
	m_ctyppar=FindACC(m_metainfo->m_ACCpar,m_cset->m_TYPPAR);
	m_ctypobj=FindACC(m_metainfo->m_ACCobj,m_cset->m_TOBJECT);
    m_ctranstype=FindACC(m_metainfo->m_ACCtrans,m_cset->m_TYPEREFORM);

	m_cvidobj=FindACC(m_metainfo->m_ACCvidobj,m_dset->m_VIDOBJ);

    if(m_ctranstype==-1)
        m_ctranstype=0;
	m_cvisible=m_cset->m_SEE;
	m_cclassid=m_cset->m_CLASSID;
	m_cfieldtype=m_cset->m_FIELDTYPE;

/*	int ind = m_cquerynamectrl.FindStringExact(0,m_queryname);
	if( ind != -1 )
		m_cquerynamectrl.SetCurSel(ind);*/
	UpdateData(false);
//	m_cquerynamectrl.SetWindowText(m_queryname);
	m_ischanged=FALSE;

	CSetDialog::LoadData();
}

void CColsDlg::OnNext() 
{
	CSetDialog::OnNext();
}

/*
void CColsDlg::OnSave()
{
    SaveData();
}

void CColsDlg::OnOK()
{
	if(SaveData())
		CDialog::OnOK();
}
*/

void CColsDlg::LoadNames()
{
	POSITION pos=m_metainfo->m_ltypcentr.GetHeadPosition();
	while(pos)
		m_ctypcentrctrl.AddString(m_metainfo->m_ltypcentr.GetNext(pos));

	pos=m_metainfo->m_ltypdata.GetHeadPosition();
	while(pos)
		m_ctypdatactrl.AddString(m_metainfo->m_ltypdata.GetNext(pos));

	pos=m_metainfo->m_lvidobj.GetHeadPosition();
	while(pos)
		m_cvidobjctrl.AddString(m_metainfo->m_lvidobj.GetNext(pos));

	pos=m_metainfo->m_ltyppar.GetHeadPosition();
	while(pos)
		m_ctypparctrl.AddString(m_metainfo->m_ltyppar.GetNext(pos));

	pos=m_metainfo->m_ltypobj.GetHeadPosition();
	while(pos)
		m_ctypobjctrl.AddString(m_metainfo->m_ltypobj.GetNext(pos));

	pos=m_metainfo->m_ltypagrcol.GetHeadPosition();
	while(pos)
		m_ctypagrctrl.AddString(m_metainfo->m_ltypagrcol.GetNext(pos));

	pos=m_metainfo->m_ldataformat.GetHeadPosition();
	while(pos)
		m_cdataformatctrl.AddString(m_metainfo->m_ldataformat.GetNext(pos));

    pos=m_metainfo->m_ltranstype.GetHeadPosition();
	while(pos)
		m_ctranstypectrl.AddString(m_metainfo->m_ltranstype.GetNext(pos));

	m_queries->Reload();
	if(m_queries->FindName(m_datasql))
	{
		m_queries->TranslateSQL(QE_TRANS_NEEDCOLS);
		for(int i=0;i<m_queries->m_ciCols.GetSize();i++)
			m_cquerynamectrl.AddString(m_queries->m_ciCols[i].m_strName + _T(" "));
	}

	//для 14 баз
	if(m_scrqueries && m_scrqueries->FindName(m_datasql))
	{
		m_scrqueries->TranslateSQL(QE_TRANS_NEEDCOLS);
		for(int i=0;i<m_scrqueries->m_ciCols.GetSize();i++)
			m_cquerynamectrl.AddString(m_scrqueries->m_ciCols[i].m_strName + _T(" "));
	}
}

void CColsDlg::OnSomeFieldChanged()
{
	ConformDataFields();
	m_ischanged=TRUE;
}

void CColsDlg::OnQueryNameChange()
{
	CString str;
	int ind = m_cquerynamectrl.GetCurSel();
	if( ind == -1)
		return;
	m_cquerynamectrl.GetLBText(ind,str);
	m_queryname=str;
	m_queryname.TrimRight();

	for(int i=0;i<m_queries->m_ciCols.GetSize();i++)
		if(m_queryname.CompareNoCase(m_queries->m_ciCols[i].m_strName)==0)
		{
			m_queries->LoadMetaForCol(i);
			m_ctypdata=FindACC(m_metainfo->m_ACCdat,m_queries->m_ciCols[i].m_sType);
			m_cname=m_queries->m_ciCols[i].m_strDescr;
			if(m_queries->m_ciCols[i].m_sType!=1)		//если не текст...
			if(m_queries->m_ciCols[i].m_sType==2)		//...и число
				m_ctyppar=FindACC(m_metainfo->m_ACCpar,m_queries->m_ciCols[i].m_sMetaClassID);
			else										//...и не число
				m_cclassid.Format(_T("%d"),m_queries->m_ciCols[i].m_sMetaClassID);
			if(m_queries->m_ciCols[i].m_sType==5)
				m_cfieldtype.Format(_T("%d"),m_queries->m_ciCols[i].m_sMetaType);
			else
				m_cfieldtype=_T("");
			break;
		}

	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==1)
		m_ctypcentr=FindACC(m_metainfo->m_ACCcentr,2);
	else
		m_ctypcentr=FindACC(m_metainfo->m_ACCcentr,3);

	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==2)
		m_ctypagr=FindACC(m_metainfo->m_ACCtypeagr,int(7));
	else
		m_ctypagr=FindACC(m_metainfo->m_ACCtypeagr,77);

	CString s;
	m_dontdodata=true;
	m_ctypdatactrl.SetCurSel(m_ctypdata);
	m_ctypparctrl.SetCurSel(m_ctyppar);
	m_cclassidctrl.SetWindowText(m_cclassid);
	m_ctypcentrctrl.SetCurSel(m_ctypcentr);
	m_ctypagrctrl.SetCurSel(m_ctypagr);
	m_cnamectrl.SetWindowText(m_cname);
	m_dontdodata=false;

	m_ischanged=TRUE;
}

void CColsDlg::OnSelchangeQueryname()
{
	OnQueryNameChange();
}

void CColsDlg::ConformDataFields()
{
	UpdateData();
	CWnd *wnd=GetFocus();
	m_cwidthctrl.EnableWindow(false);
	m_cformatctrl.EnableWindow(false);
	m_ctypcentrctrl.EnableWindow(false);
	m_cdataformatctrl.EnableWindow(false);
	m_cclassidctrl.EnableWindow(false);
	m_ctypagrctrl.EnableWindow(false);
	m_ctypparctrl.EnableWindow(false);
	m_cvidobjctrl.EnableWindow(false);
	if(m_cvisible)
	{
		m_cwidthctrl.EnableWindow();
		m_ctypcentrctrl.EnableWindow();
		if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==2)
			m_cformatctrl.EnableWindow();
		if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==3)
			m_cdataformatctrl.EnableWindow();
	}
	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==5)
		m_cclassidctrl.EnableWindow();
	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==2)
		m_ctypagrctrl.EnableWindow();
	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==2)
		m_ctypparctrl.EnableWindow();

	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==10)
		m_cvidobjctrl.EnableWindow();

	if(m_set->IsColumnPresent(_T("TYPEREFORM")))
		m_ctranstypectrl.EnableWindow();
	else
		m_ctranstypectrl.EnableWindow(false);


	if(!m_set->IsColumnPresent(_T("CLASSID")))
		m_cclassidctrl.EnableWindow(false);

	wnd->SetFocus();
	m_cdataformatctrl.SetEditSel(-1,-1);
}

void CColsDlg::OnVisibleChange() 
{
	OnSomeFieldChanged();
}

void CColsDlg::OnVerify()
{
	CSetDialog::OnVerify();
}

BOOL CColsDlg::VerifyData()
{
	BeginWaitCursor();
	UpdateData();
	BOOL isPass=TRUE;
	m_queryname.TrimRight();
	if(m_queries->FindCol(m_queryname)==-1)
	{
		DoDataError(_T("Колонка с таким именем не существует."));
		isPass=FALSE;
	}
	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==2)
	{
		if(m_cformat=="" && m_cvisible)
		{
			DoDataError(_T("Не введен формат для числа"));
			isPass=FALSE;
		}
	}

	//проверка формата числа
	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==2)
	{
		const CString alphabet = "0123456789.";
		for( int i = 0; i < m_cformat.GetLength(); i++ )
			if( alphabet.Find(m_cformat[i], 0) == -1 )
			{
				if(!DoDataWarning(_T("Формат числа неверный")))
					isPass = FALSE;
				break;
			}
	}

	//проверка что введена дата
	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==3)
	{
		if(m_cdataformat == "")
		{
			DoDataError(_T("Не введен формат даты"));
			isPass = FALSE;
		}
	}

	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==10 && m_cvidobj == 0)
	{
		DoDataError(_T("Не выбран вид объекта"));
		isPass = FALSE;
	}

	if(m_numcol!=m_set->GetCodeField())
	{
		int oldcode=m_set->GetCodeField();
		if(m_set->MoveToCode(m_numcol))
		{
			DoDataError(_T("Колонка с таким кодом уже существует"));
			isPass=FALSE;
		}
		m_set->MoveToCode(oldcode);
	}

	EndWaitCursor();
	return isPass;

}

void CColsDlg::OnChangeDataType()
{
	UpdateData();
	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==1)
	{
		m_ctypcentr=FindACC(m_metainfo->m_ACCcentr,2);
		m_ctypagr=FindACC(m_metainfo->m_ACCtypeagr,77);
	}
	else
		m_ctypcentr=FindACC(m_metainfo->m_ACCcentr,3);

	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==2)
		m_ctypagr=FindACC(m_metainfo->m_ACCtypeagr,long(0));
	else
		m_ctypagr=FindACC(m_metainfo->m_ACCtypeagr,77);

	if(FindACCBack(m_metainfo->m_ACCdat,m_ctypdata)==10)
	{
		m_cwidth = _T("10");
		m_cvisible = TRUE;
	}

	UpdateData(false);
	m_cquerynamectrl.SetWindowText(m_queryname);
	OnSomeFieldChanged();
}

void CColsDlg::OnDropDownQueryName() 
{
}
