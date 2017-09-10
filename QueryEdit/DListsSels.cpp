#include "stdafx.h"

#include "QueryEditRes\resource.h"

#include "DQueryEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CListsDlg dialog
CListsDlg::CListsDlg(SMetaInfo* metainfo,CWnd* pParent /*=NULL*/)
	: CSetDialog(CListsDlg::IDD, metainfo,pParent)
{
	m_cnameclass = _T("");
	m_csameparam = FALSE;
	m_codclass = 0;
	m_cnosee = FALSE;
}

void CListsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_NOSEE, m_cnoseectrl);
	DDX_Control(pDX, IDC_DOCSLIST, m_doclistctrl);
	DDX_Text(pDX, IDC_NAMECLASS, m_cnameclass);
	DDX_Check(pDX, IDC_SAMEPARAM, m_csameparam);
	DDX_Text(pDX, IDC_CODCLASS, m_codclass);
	DDX_Check(pDX, IDC_NOSEE, m_cnosee);
}

BEGIN_MESSAGE_MAP(CListsDlg, CDialog)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_ADD, OnAddDoc)
	ON_BN_CLICKED(IDC_DELCUR, OnDelCurs)
	ON_EN_CHANGE(IDC_NAMECLASS, OnSomethingChanged)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_NOTIFY(LVN_KEYDOWN, IDC_DOCSLIST, OnKeydownDocslist)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ITEMUP, OnItemUp)
	ON_BN_CLICKED(IDC_ITEMDOWN, OnItemDown)
	ON_BN_CLICKED(IDC_SAMEPARAM, OnSomethingChanged)
	ON_EN_CHANGE(IDC_CODCLASS, OnSomethingChanged)
	ON_BN_CLICKED(IDC_NOSEE, OnSomethingChanged)
END_MESSAGE_MAP()

BOOL CListsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	InitListCtrl();
	LoadData();
	ConformDataFields();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CListsDlg::InitListCtrl()
{
	m_doclistctrl.InsertColumn(0,_T("CODDOC"),LVCFMT_LEFT,70,0);
	m_doclistctrl.InsertColumn(1,_T("Имя документа"),LVCFMT_LEFT,430,1);
	m_doclistctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

}

void CListsDlg::LoadData()
{
	CClassesSet *m_classesset=(CClassesSet *)m_set;

	m_codclass=m_classesset->m_LISTDOC;
	m_cnameclass=m_classesset->m_NAMELIST;
	m_cnosee=m_classesset->m_NOSEE;

	m_doclistctrl.DeleteAllItems();
	
	CListsSet lset((CDatabNet *)m_classesset->m_pDatabase);
	lset.m_strFilter.Format(_T("LISTDOC=%d AND listdocs.CODDOC=descrdoc.CODDOC"),m_classesset->m_LISTDOC);
	lset.m_strSort="NUMDOC";
	lset.Open();
	int i=0;
	CString iCode;
	while(!lset.IsEOF())
	{
		iCode.Format(_T("%d"),lset.m_CODDOC);
		m_doclistctrl.InsertItem(i,iCode);
		m_doclistctrl.SetItemText(i,1,lset.m_NAMEDOC);
		lset.MoveNext();
		i++;
	}
	lset.Close();
	m_csameparam=m_classesset->m_SAMEPARAM;

	UpdateData(false);
	m_ischanged=FALSE;
}

BOOL CListsDlg::SaveData()
{
	if(!VerifyData())
		return FALSE;
	CClassesSet *m_classesset=(CClassesSet *)m_set;

	BOOL iscodechanged=FALSE;

	if(m_ischanged)
	{
		UpdateData();
		m_classesset->Edit();

		if(m_classesset->m_LISTDOC!=m_codclass)
		{
			m_classesset->m_LISTDOC=m_codclass;
			iscodechanged=TRUE;
		}
		m_classesset->m_NAMELIST=m_cnameclass;
		m_classesset->m_SAMEPARAM=m_csameparam;
		m_classesset->m_NOSEE=m_cnosee;

		m_classesset->UpdateNet(0);

		if(iscodechanged)
		{
			m_classesset->Requery();
			m_classesset->MoveToCode(m_codclass);
		}

		CDatabNet *m_CNBase=(CDatabNet *)m_classesset->m_pDatabase;
		m_CNBase->BeginTrans();

		CString SQL;
		SQL.Format(_T("DELETE FROM listdocs WHERE listdoc=%d"),m_classesset->m_LISTDOC);
		m_CNBase->ExecuteSQL(SQL);

		CListsDocOnlySet lset((CDatabNet *)m_classesset->m_pDatabase);

		lset.Open();

		int len=m_doclistctrl.GetItemCount();
		for(int i=0;i<len;i++)
		{
			lset.AddNew();
			
			lset.m_LISTDOC=m_classesset->m_LISTDOC;
			lset.m_NUMDOC=i+1;
			lset.m_CODDOC=_ttoi(m_doclistctrl.GetItemText(i,0));
			
			lset.UpdateNet(0);
		}
		lset.Close();

		m_CNBase->CommitTrans();
		m_ischanged=FALSE;
	}
	return TRUE;
}

void CListsDlg::OnPrev() 
{
	CSetDialog::OnPrev();
}

void CListsDlg::OnNext() 
{
	CSetDialog::OnNext();
}

void CListsDlg::OnAddDoc() 
{
	AddDoc(-1);
}

void CListsDlg::OnDelCurs() 
{
	POSITION pos=m_doclistctrl.GetFirstSelectedItemPosition();
	UINT *fordel=new UINT[m_doclistctrl.GetSelectedCount()],fi=0;
	while(pos)
	{
		fordel[fi++]=m_doclistctrl.GetNextSelectedItem(pos);
	}

	for(UINT i=0;i<fi;i++)
		m_doclistctrl.DeleteItem(fordel[i]-i);

	if(fi>0)
		m_ischanged=TRUE;

	delete[] fordel;
}

void CListsDlg::OnSomethingChanged() 
{
	ConformDataFields();
	m_ischanged=TRUE;
}

void CListsDlg::ConformDataFields()
{
	if(!m_set->IsColumnPresent(_T("NOSEE")))
		m_cnoseectrl.EnableWindow(false);
}

/*
void CListsDlg::OnSave()
{
    SaveData();
}

void CListsDlg::OnOK() 
{
	if(SaveData())
		CDialog::OnOK();
}
*/

void CListsDlg::OnKeydownDocslist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDown = (LV_KEYDOWN*)pNMHDR;

	switch(pLVKeyDown->wVKey)
	{
	case(45):OnAddDoc();break;
	case(46):OnDelCurs();break;
	}
		
	*pResult = 0;
}

int CListsDlg::DoModal(int flashaddcode)
{
	m_flashadd=flashaddcode;
	return CDialog::DoModal();
}

void CListsDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if(m_flashadd!=-1)
	{
		int flashaddtmp=m_flashadd;
		m_flashadd=-1;
//		AddDoc(flashaddtmp);
		CDocsSet dset((CDatabNet *)m_set->m_pDatabase);
		dset.m_strSort = "CODDOC";
		dset.Open();
		dset.MoveToCode(flashaddtmp);
		int el = m_doclistctrl.GetItemCount();
		CString at;
		at.Format(_T("%d"),dset.m_CODDOC);
		m_doclistctrl.InsertItem(el,at);
		m_doclistctrl.SetItemText(el,1,dset.m_NAMEDOC);
		m_doclistctrl.SetItemState(el, LVIS_SELECTED, LVIS_SELECTED);
		m_ischanged=TRUE;
	}
	
	// Do not call CDialog::OnPaint() for painting messages
}

void CListsDlg::AddDoc(int selcode)
{
	CDocsSet dset((CDatabNet *)m_set->m_pDatabase);
	dset.m_strSort = "CODDOC";
	dset.Open();

	CImportDocsDlg impdlg;
	impdlg.SetDocsSet(&dset);
	impdlg.m_bImport = FALSE;

	CString at;

	if(impdlg.DoModal()==IDOK)
	{
		POSITION pos=m_doclistctrl.GetFirstSelectedItemPosition();
		int el;
		if(pos)
			el=m_doclistctrl.GetNextSelectedItem(pos)+1;
		else
			el=m_doclistctrl.GetItemCount();
		for(int dnom=0;dnom<impdlg.m_doccodes.GetSize();dnom++)
		{
			long doccode=impdlg.m_doccodes[dnom];
			dset.MoveToCode(doccode);
			CString at;
			at.Format(_T("%d"),dset.m_CODDOC);
			m_doclistctrl.InsertItem(el,at);
			m_doclistctrl.SetItemText(el,1,dset.m_NAMEDOC);
			el++;
			m_ischanged=TRUE;
		}
	}

	dset.Close();
}

void CListsDlg::OnItemUp() 
{
	POSITION pos=m_doclistctrl.GetFirstSelectedItemPosition();
	int ind;
	CString A,B;
	int *sel=new int[m_doclistctrl.GetSelectedCount()],sind=0;
	while(pos)
	{
		ind=m_doclistctrl.GetNextSelectedItem(pos);
		if(ind==0)
			break;
		A=m_doclistctrl.GetItemText(ind-1,0);
		B=m_doclistctrl.GetItemText(ind,0);
		m_doclistctrl.SetItemText(ind-1,0,B);
		m_doclistctrl.SetItemText(ind,0,A);

		A=m_doclistctrl.GetItemText(ind-1,1);
		B=m_doclistctrl.GetItemText(ind,1);
		m_doclistctrl.SetItemText(ind-1,1,B);
		m_doclistctrl.SetItemText(ind,1,A);
		sel[sind++]=ind;
	}
	
	for(int i=0;i<sind;i++)
	{
		m_doclistctrl.SetItemState(sel[i],0, LVIS_SELECTED);
		m_doclistctrl.SetItemState(sel[i]-1,LVIS_SELECTED, LVIS_SELECTED);
	}
	
	delete[] sel;
	
	m_doclistctrl.SetFocus();

	m_ischanged=true;
}

void CListsDlg::OnItemDown() 
{
	POSITION pos=m_doclistctrl.GetFirstSelectedItemPosition();
	int ind;
	CString A,B;
	int *sel=new int[m_doclistctrl.GetSelectedCount()],sind=0;
	while(pos)
	{
		ind=m_doclistctrl.GetNextSelectedItem(pos);
		if(ind==m_doclistctrl.GetItemCount()-1)
		{
			sind=0;
			break;
		}
		sel[sind++]=ind;
	}
	for(int i=sind-1;i>=0;i--)
	{
		A=m_doclistctrl.GetItemText(sel[i]+1,0);
		B=m_doclistctrl.GetItemText(sel[i],0);
		m_doclistctrl.SetItemText(sel[i]+1,0,B);
		m_doclistctrl.SetItemText(sel[i],0,A);

		A=m_doclistctrl.GetItemText(sel[i]+1,1);
		B=m_doclistctrl.GetItemText(sel[i],1);
		m_doclistctrl.SetItemText(sel[i]+1,1,B);
		m_doclistctrl.SetItemText(sel[i],1,A);
	}

	for(int i=sind-1;i>=0;i--)
	{

		m_doclistctrl.SetItemState(sel[i],0, LVIS_SELECTED);
		m_doclistctrl.SetItemState(sel[i]+1,LVIS_SELECTED, LVIS_SELECTED);
	}

	delete[] sel;

	m_doclistctrl.SetFocus();	
	

	m_ischanged=true;
}

BOOL CListsDlg::VerifyData()
{
	BOOL ispass=TRUE;
	UpdateData();
	if(m_codclass!=m_set->GetCodeField())
	{
		int oldcode=m_set->GetCodeField();
		if(m_set->MoveToCode(m_codclass))
		{
			DoDataError(_T("Класса с таким кодом уже существует"));
			ispass=FALSE;
		}
		m_set->MoveToCode(oldcode);
	}
	return ispass;
}


/////////////////////////////////////////////////////////////////////////////
// CSelsDlg dialog
CSelsDlg::CSelsDlg(SMetaInfo* metainfo, CWnd* pParent /*=NULL*/)
	: CSetDialog(CSelsDlg::IDD, metainfo, pParent)
{
}

void CSelsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DOCNAME, m_docname);
	DDX_Text(pDX, IDC_NAMSELECT, m_namselect);
	DDX_Text(pDX, IDC_VALSELECT, m_valselect);
	DDX_Text(pDX, IDC_DSEL, m_dsel);
}

BEGIN_MESSAGE_MAP(CSelsDlg, CDialog)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_VERIFY, OnVerify)
	ON_EN_CHANGE(IDC_NAMSELECT, OnSomeChanged)
	ON_EN_CHANGE(IDC_VALSELECT, OnSomeChanged)
END_MESSAGE_MAP()

void CSelsDlg::LoadData()
{
	CSelsSet *sset=(CSelsSet *)m_set;

	m_dsel.Format(_T("%d"),sset->m_DSELECT);
	m_namselect = sset->m_NAMSELECT;
	m_valselect = sset->m_VALSELECT;

	CSetDialog::LoadData();

	UpdateData(false);
	m_ischanged=FALSE;
}

BOOL CSelsDlg::SaveData()
{
	if(!VerifyData())
		return FALSE;
	CSelsSet *sset=(CSelsSet *)m_set;

	if(m_ischanged)
	{
		UpdateData();
		sset->Edit();

		sset->m_NAMSELECT = m_namselect;
		sset->m_VALSELECT = m_valselect;

		sset->UpdateNet(0);
		m_ischanged=FALSE;
	}
	return TRUE;
}

BOOL CSelsDlg::OnInitDialog() 
{
	CSetDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelsDlg::OnNext() 
{
	CSetDialog::OnNext();	
}

void CSelsDlg::OnPrev() 
{
	CSetDialog::OnPrev();	
}

void CSelsDlg::OnOK() 
{
	if(SaveData())
		CDialog::OnOK();
}

void CSelsDlg::OnVerify() 
{
	CSetDialog::OnVerify();
}

void CSelsDlg::OnSomeChanged() 
{
	m_ischanged=TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CSetDialog dialog
CSetDialog::CSetDialog(UINT nIDTemplate, SMetaInfo* metainfo, CWnd* pParent /*=NULL*/)
	: CDialog(nIDTemplate, pParent)
{
    m_bNew = false;
	m_verifymode=QE_VM_MESSAGEBOX;
	m_verifydata="";
	m_metainfo=metainfo;
	m_bCheckOnly = false;
	ASSERT(m_metainfo);
}

void CSetDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetDialog, CDialog)
END_MESSAGE_MAP()

long CSetDialog::FindACC(DWARRAY &ar, long ind)
{
	if(ind<0)
		return -1;
	long i=ar.GetSize()-1;
	if(i>ar.GetSize()-1)
		i=ar.GetSize()-1;
	while(i>=0 && (long)ar[i]!=ind)
		i--;
	if(i<0)
		return -1;
	return i;
}

long CSetDialog::FindACCBack(DWARRAY &ar, long ind)
{
	if(ind<0)
		return 0;
	if(ind>ar.GetSize()-1)
		return 0;
	return ar[ind];
}

void CSetDialog::LoadNames()
{
}

void CSetDialog::LoadData()
{
	ConformDataFields();
}

BOOL CSetDialog::SaveData()
{
	return FALSE;	
}

BOOL CSetDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadNames();
	LoadData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSetDialog::SetMSGBase(CDatabNet *dbMSG)
{
	m_dbMSG=dbMSG;
}

long CSetDialog::FindACC(DWARRAY &ar, LPCTSTR ind)
{
	CString _buf(ind);
	_buf.TrimLeft();
	_buf.TrimRight();
	if(_buf.GetLength()==0)
		return -1;
	int iind=_ttoi(_buf);
	return FindACC(ar,iind);
}

const CString CSetDialog::FindACCBackS(DWARRAY &ar, long ind)
{
	CString snull;
	if(ar[0]==0)
		snull="";
	else
		snull="0";
	if(ind<0)
		return snull;
	if(ind>ar.GetSize()-1)
		return snull;
	CString sret;
	sret.Format(_T("%d"),ar[ind]);
	return sret;
}

void CSetDialog::SetSet(CQERecordset *set,DWORD ind)
{
	m_set=set;
	m_set->MoveFirst();
	while(!m_set->IsEOF() && m_set->GetCodeField()!=ind)
		m_set->MoveNext();
	if(m_set->GetCodeField()!=ind)
		m_set->MoveFirst();
}

void CSetDialog::OnPrev()
{
	if(m_ischanged)
	{
		if(AfxMessageBox(_T("Сохранить изменения в текущей записи?"),MB_YESNO)==IDYES)
			if(!SaveData())
				return;
	}
	m_set->MovePrev();
	if(m_set->IsBOF())
		m_set->MoveNext();
	else
		LoadData();
}

void CSetDialog::OnNext()
{
	if(m_ischanged)
	{
		if(AfxMessageBox(_T("Сохранить изменения в текущей записи?"),MB_YESNO)==IDYES)
			if(!SaveData())
				return;
	}
	m_set->MoveNext();
	if(m_set->IsEOF())
		m_set->MovePrev();
	else
		LoadData();
}

void CSetDialog::SetBASEBase(CDatabNet *BASEBase)
{
	m_BASEBase=BASEBase;
}

void CSetDialog::SetQueries(CSQLAnalyzer *queries, CSQLAnalyzer *scrqueries)
{
	m_queries=queries;
	m_scrqueries = scrqueries;
}

void CSetDialog::ConformDataFields()
{

}

BOOL CSetDialog::DoDataWarning(LPCTSTR mes)
{
	CString warning;
	if(m_verifymode==QE_VM_MESSAGEBOX)
	{
		warning.Format(_T("ПРЕДУПРЕЖДЕНИЕ: %s Все равно продолжить?"),mes);
		if(AfxMessageBox(warning,MB_YESNO)==IDYES)
			return TRUE;
		else
			return FALSE;
	}
	else if(m_verifymode==QE_VM_TOSTRING)
	{
		warning=mes;
		m_verifydata+=warning+"\n";
        return true;
	}
    else
        return true;
}

void CSetDialog::DoDataError(LPCTSTR mes)
{
	CString error;
	if(m_verifymode==QE_VM_MESSAGEBOX)
	{
		error.Format(_T("ОШИБКА: %s Невозможно продолжить, необходимо изменение данных."),mes);
		AfxMessageBox(error);
	}
	else if(m_verifymode==QE_VM_TOSTRING)
	{
		error=mes;
		m_verifydata+=error+"\n";
	}
}

void CSetDialog::OnSave()
{
	if(SaveData())
        m_bNew = false;
}

void CSetDialog::OnOK() 
{
	if(SaveData())
		CDialog::OnOK();
}

BOOL CSetDialog::VerifyData()
{
	return TRUE;
}

void CSetDialog::OnVerify()
{
	m_verifymode=QE_VM_TOSTRING;
	m_verifydata="";
	VerifyData();
	m_verifymode=QE_VM_MESSAGEBOX;
	if(m_verifydata=="")
		AfxMessageBox(_T("Замечаний нет"), MB_ICONINFORMATION);
	else
		AfxMessageBox(m_verifydata);
}

void CSetDialog::OnCancel()
{
	if(!m_ischanged ||
			AfxMessageBox(_T("Данные были изменены. Сохранить?"),MB_YESNO)==IDNO ||
			SaveData())
		CDialog::OnCancel();
}
