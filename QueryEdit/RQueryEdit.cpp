#include "stdafx.h"

#include "QueryEditRes\resource.h"

#include "RQueryEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CQERecordset
CQERecordset::CQERecordset(CDatabNet* pdb, CString tableName)
	: CRecordNet(pdb,tableName)
{
	m_isclloaded=FALSE;
}

CString CQERecordset::GetDefaultSQL()
{
	return _T("");
}

void CQERecordset::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
}

DWORD CQERecordset::GetCodeField()
{
	return 0;
}

int CQERecordset::FindFreeCode(int minVal, int maxVal)
{
	if(IsEOF())
		return minVal;
	MoveFirst();
	int i=minVal;
	while(!IsEOF())
	{
		if((int)GetCodeField()>i && ((int)GetCodeField()<=maxVal || maxVal==-1))
			return i;
		MoveNext();
		if(!IsEOF() && (int)GetCodeField()>i)
			i++;
	}
	return i+1;
}

CString& CQERecordset::GetNameField()
{
	return *(new CString(""));
}

const CString CQERecordset::GetCodeNameF()
{
	CString cn;
	cn.Format(_T("%d. %s"),GetCodeField(),GetNameField());
	return cn;
}

const CString CQERecordset::GetCodeNameSorted(UINT sorttype)
{
	return GetCodeNameF();
}

void CQERecordset::SetDefault()
{

}

void CQERecordset::SetFromOtherSet(CQERecordset *otherSet)
{
}

int CQERecordset::Open()
{
	return OpenNet(_T(""),m_nDefaultType,_T(""));
}

void CQERecordset::AddNew()
{
	CRecordset::AddNew();
}

BOOL CQERecordset::FreeCodeForMe(int code)
{
	if(!IsBOF())
		MoveFirst();
	while(!IsEOF() && code>GetCodeField())
		MoveNext();

	if(IsEOF() || code<GetCodeField())
		return TRUE;

	int toCode=FindFreeCode(code);
	MoveFirst();
	while(!IsEOF() && GetCodeField()<toCode)
		MoveNext();

	MovePrev();
	int curCode=toCode;

	for(int i=toCode;i>code;i--)
	{
		Edit();
		SetCodeField(i);
		UpdateNet(0);
		MovePrev();
	}

	Requery();

	return TRUE;
}

void CQERecordset::SetCodeField(int code)
{
}

BOOL CQERecordset::MoveToCode(int code)
{
	MoveFirst();
	while(!IsEOF() && GetCodeField()!=code)
		MoveNext();
	if(IsEOF())
		return FALSE;
	else
		return TRUE;
}

BOOL CQERecordset::IsColumnPresent(LPCTSTR strName)
{
	if(!m_isclloaded && !LoadColumnsList())
		return FALSE;

	for(int i=0;i<m_ciColumns.GetSize();i++)
		if(m_ciColumns[i].m_strName.CompareNoCase(strName)==0)
			return TRUE;

	return FALSE;
}

BOOL CQERecordset::LoadColumnsList()
{
	if(m_strTable=="")
		return FALSE;
	CRecordset rec(m_pDatabase);
	rec.Open(CRecordset::forwardOnly,"SELECT * from "+m_strTable);

	SColInfo ci;
	for(int i=0;i<rec.GetODBCFieldCount();i++)
	{
		ci.m_strName=rec.m_rgODBCFieldInfos[i].m_strName;
		m_ciColumns.Add(ci);
	}

	rec.Close();
	m_isclloaded=TRUE;
	return TRUE;
}

void CQERecordset::RemoveHoles()
{
	if(IsEOF() && IsBOF())
		return;
	MoveFirst();
	int curCode = 1;
	while(!IsEOF())
	{
		Edit();
		SetCodeField(curCode);
		UpdateNet(0);
		MoveNext();
		curCode++;
	}
	Requery();
}

BOOL CQERecordset::IsThereCode(int code)
{
	int curCode = GetCodeField();
	MoveFirst();
	while(!IsEOF() && GetCodeField()!=code)
		MoveNext();

	BOOL ret;

	if(IsEOF())
		ret=FALSE;
	else
		ret=TRUE;

	SetOnCode(curCode);

	return ret;
}

BOOL CQERecordset::SetOnCode(int code)
{
	MoveFirst();
	while(!IsEOF())
	{
		if(GetCodeField() == code)
			return TRUE;
		MoveNext();
	}
	return FALSE;
}


/////////////////////////////////////////////////////////////////////////////
// CAgrsSet
CAgrsSet::CAgrsSet(CDatabNet* pdb): CQERecordset(pdb,"descragr")
{
	m_CODDOC = 0;
	m_NUMAGR = 0;
	m_NAMEAGR = _T("");
	m_TYPEAGR = 0;
	m_NROWLAST = _T("");
	m_NROWFIRST = _T("");
	m_CALCZERO = FALSE;
	m_NCOLKEY=0;
	m_NCOL_HEAD=0;
	m_nFields = 8;

	m_strSort="NUMAGR";
	m_strTable = "[descragr]";

	if(IsColumnPresent(_T("NCOL_HEAD")))
        m_nFields++;
}

CAgrsSet::CAgrsSet(CString &defDSN,CDatabNet* pDatabase)
	:CQERecordset(pDatabase, "descragr")
{
	m_CODDOC = 0;
	m_NUMAGR = 0;
	m_NAMEAGR = _T("");
	m_TYPEAGR = 0;
	m_NROWLAST = _T("");
	m_NROWFIRST = _T("");
	m_CALCZERO = FALSE;
	m_NCOLKEY=0;
	m_NCOL_HEAD=0;
	m_nFields = 8;
	m_strSort="NUMAGR";
	m_strTable = "[descragr]";

	if(IsColumnPresent(_T("NCOL_HEAD")))
        m_nFields++;
}

void CAgrsSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[CODDOC]"), m_CODDOC);
	RFX_Int(pFX, _T("[NUMAGR]"), m_NUMAGR);
	RFX_Text(pFX, _T("[NAMEAGR]"), m_NAMEAGR);
	RFX_Byte(pFX, _T("[TYPEAGR]"), m_TYPEAGR);
	RFX_Text(pFX, _T("[NROWLAST]"), m_NROWLAST);
	RFX_Text(pFX, _T("[NROWFIRST]"), m_NROWFIRST);
	RFX_Bool(pFX, _T("[CALCZERO]"), m_CALCZERO);
	RFX_Int(pFX, _T("[NCOLKEY]"), m_NCOLKEY);
	if(IsColumnPresent(_T("NCOL_HEAD")))
	    RFX_Byte(pFX, _T("[NCOL_HEAD]"), m_NCOL_HEAD);
}

DWORD CAgrsSet::GetCodeField()
{
	return m_NUMAGR;
}

CString& CAgrsSet::GetNameField()
{
	return m_NAMEAGR;
}

void CAgrsSet::SetDefault()
{
	m_CODDOC = 0;
	m_NUMAGR = 0;
	m_NAMEAGR = _T("Новое агрегирование");
	m_TYPEAGR = 0;
	m_NROWLAST = _T("");
	m_NROWFIRST = _T("");
	m_CALCZERO = FALSE;
	m_NCOLKEY=0;
}

void CAgrsSet::SetFromOtherSet(CQERecordset *otherSet)
{
	CAgrsSet *aset=(CAgrsSet *)otherSet;
	m_CODDOC = aset->m_CODDOC;
	m_NUMAGR = aset->m_NUMAGR;
	m_NAMEAGR = aset->m_NAMEAGR;
	m_TYPEAGR = aset->m_TYPEAGR;
	m_NROWLAST = aset->m_NROWLAST;
	m_NROWFIRST = aset->m_NROWFIRST;
	m_CALCZERO = aset->m_CALCZERO;
	m_NCOLKEY = aset->m_NCOLKEY;
	m_NCOL_HEAD = aset->m_NCOL_HEAD;
}

void CAgrsSet::SetCodeField(int code)
{
	m_NUMAGR=code;
}

BOOL CAgrsSet::GetNoSeeAgr(BOOL& result)
{
	CRecordset set(m_pDatabase);
	CString SQL;
	if(m_NCOLKEY == 0 || m_NCOLKEY == 1 || IsFieldNull(&m_NCOLKEY) || m_NCOLKEY == -1)
		return FALSE;
	SQL.Format(_T("SELECT NOSEEAGR FROM DESCRCOL WHERE CODDOC=%d AND NUMCOL=%d"), m_CODDOC, m_NCOLKEY);
	set.Open(CRecordset::forwardOnly, SQL);
	if (!set.IsEOF())
	{
		CDBVariant var;
		set.GetFieldValue(_T("NOSEEAGR"), var);
		set.Close();
		result = var.m_chVal;
		return TRUE;
	}

	set.Close();
	result = false;
	return false;
}

void CAgrsSet::SetNoSeeAgr(BOOL nsa)
{
	CString SQL;
	if(m_NCOLKEY == 0 || m_NCOLKEY == 1 || IsFieldNull(&m_NCOLKEY) || m_NCOLKEY == -1)
		return;
	SQL.Format(_T("UPDATE DESCRCOL SET NOSEEAGR=%d WHERE CODDOC=%d AND NUMCOL=%d"), nsa, m_CODDOC, m_NCOLKEY);
	m_pDatabase->ExecuteSQL(SQL);
}


/////////////////////////////////////////////////////////////////////////////
// CClassesSet
CClassesSet::CClassesSet(CDatabNet* pdb): CQERecordset(pdb,"namlistd")
{
	m_LISTDOC = 0;
	m_NAMELIST = _T("");
	m_SAMEPARAM = FALSE;
	m_NOSEE = FALSE;
	m_nFields = 3;
	if (isField("USEORDER")!=-1)
		m_nFields++;
	if (isField("NOSEE")!=-1)
		m_nFields++;

    m_strTable = "[namlistd]";
	if (isField("USEORDER")!=-1)
		m_strSort = "USEORDER,LISTDOC";
	else
		m_strSort="LISTDOC";
}

CString CClassesSet::GetDefaultSQL()
{
	if (isField("USEORDER")!=-1)
		m_strSort = "USEORDER,LISTDOC";
	else
		m_strSort="LISTDOC";
	return _T("[namlistd]");
}

void CClassesSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[LISTDOC]"), m_LISTDOC);
	RFX_Text(pFX, _T("[NAMELIST]"), m_NAMELIST);
	RFX_Bool(pFX, _T("[SAMEPARAM]"), m_SAMEPARAM);
	if (isField("USEORDER")!=-1)
		RFX_Int(pFX, _T("[USEORDER]"), m_USEORDER);
	if (isField("NOSEE")!=-1)
		RFX_Bool(pFX, _T("[NOSEE]"), m_NOSEE);
}

DWORD CClassesSet::GetCodeField()
{
	return m_LISTDOC;
}

CString& CClassesSet::GetNameField()
{
	return m_NAMELIST;
}

void CClassesSet::SetDefault()
{
	m_NAMELIST = _T("Новый класс");
	m_SAMEPARAM = FALSE;
}

void CClassesSet::SetCodeField(int code)
{
	m_LISTDOC=code;
}

BOOL CClassesSet::FixUseOrder()
{
	if(1)
	//есть незаполненные поля - перенумерация
	{
		MoveFirst();
		int i = 1;
		while(!IsEOF())
		{
			Edit();
			m_USEORDER = i;
			Update();
			i++;
			MoveNext();
		}
	}
	MoveFirst();
	
	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CColsSet
CColsSet::CColsSet(CDatabNet* pdb): CQERecordset(pdb, "descrcol")
{
	m_CODDOC = 0;
	m_NUMCOL = 0;
	m_NAMSQLCOL = _T("");
	m_NAMECOL = _T("");
	m_WIDTHCOL = _T("");
	m_TYPDATA = 0;
	m_FORMAT = _T("");
	m_TYPCENTR = 0;
	m_SEE = FALSE;
	m_TOBJECT = 0;
	m_TYPPAR = 0;
	m_TYPEAGR = 0;
	m_CLASSID=_T("");
	m_FIELDTYPE=_T("");
    m_TYPEREFORM = 0;
	m_nFields = 15;

    m_strTable = "[descrcol]";
	m_strSort="NUMCOL";
    m_nFields = 0;
    if(IsColumnPresent(_T("CODDOC")))
        m_nFields++;
    if(IsColumnPresent(_T("NUMCOL")))
        m_nFields++;
    if(IsColumnPresent(_T("NAMSQLCOL")))
        m_nFields++;
    if(IsColumnPresent(_T("NAMECOL")))
        m_nFields++;
    if(IsColumnPresent(_T("WIDTHCOL")))
        m_nFields++;
    if(IsColumnPresent(_T("TYPDATA")))
        m_nFields++;
    if(IsColumnPresent(_T("FORMAT")))
        m_nFields++;
    if(IsColumnPresent(_T("TYPCENTR")))
        m_nFields++;
    if(IsColumnPresent(_T("SEE")))
        m_nFields++;
    if(IsColumnPresent(_T("TOBJECT")))
        m_nFields++;
    if(IsColumnPresent(_T("TYPPAR")))
        m_nFields++;
    if(IsColumnPresent(_T("TYPEAGR")))
        m_nFields++;
    if(IsColumnPresent(_T("CLASSID")))
        m_nFields++;
    if(IsColumnPresent(_T("FIELDTYPE")))
        m_nFields++;
    if(IsColumnPresent(_T("TYPEREFORM")))
        m_nFields++;
}

CColsSet::CColsSet(CString &defDSN,CDatabNet* pDatabase)
	:CQERecordset(pDatabase, "descrcol")
{
	m_CODDOC = 0;
	m_NUMCOL = 0;
	m_NAMSQLCOL = _T("");
	m_NAMECOL = _T("");
	m_WIDTHCOL = _T("");
	m_TYPDATA = 0;
	m_FORMAT = _T("");
	m_TYPCENTR = 0;
	m_SEE = FALSE;
	m_TOBJECT = 0;
	m_TYPPAR = 0;
	m_TYPEAGR = 0;
	m_CLASSID=_T("");
	m_FIELDTYPE=_T("");
	m_nFields = 14;
}

CString CColsSet::GetDefaultSQL()
{
	m_strSort="NUMCOL";
	return _T("[descrcol]");
}

void CColsSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
    if(IsColumnPresent(_T("CODDOC")))
	    RFX_Int(pFX, _T("[CODDOC]"), m_CODDOC);
    if(IsColumnPresent(_T("NUMCOL")))
	    RFX_Byte(pFX, _T("[NUMCOL]"), m_NUMCOL);
    if(IsColumnPresent(_T("NAMSQLCOL")))
	    RFX_Text(pFX, _T("[NAMSQLCOL]"), m_NAMSQLCOL);
    if(IsColumnPresent(_T("NAMECOL")))
	    RFX_Text(pFX, _T("[NAMECOL]"), m_NAMECOL);
    if(IsColumnPresent(_T("WIDTHCOL")))
	    RFX_Text(pFX, _T("[WIDTHCOL]"), m_WIDTHCOL);
    if(IsColumnPresent(_T("TYPDATA")))
	    RFX_Byte(pFX, _T("[TYPDATA]"), m_TYPDATA);
    if(IsColumnPresent(_T("FORMAT")))
	    RFX_Text(pFX, _T("[FORMAT]"), m_FORMAT);
    if(IsColumnPresent(_T("TYPCENTR")))
	    RFX_Byte(pFX, _T("[TYPCENTR]"), m_TYPCENTR);
    if(IsColumnPresent(_T("SEE")))
	    RFX_Bool(pFX, _T("[SEE]"), m_SEE);
    if(IsColumnPresent(_T("TOBJECT")))
	    RFX_Byte(pFX, _T("[TOBJECT]"), m_TOBJECT);
    if(IsColumnPresent(_T("TYPPAR")))
	    RFX_Int(pFX, _T("[TYPPAR]"), m_TYPPAR);
    if(IsColumnPresent(_T("TYPEAGR")))
	    RFX_Byte(pFX, _T("[TYPEAGR]"), m_TYPEAGR);
    if(IsColumnPresent(_T("CLASSID")))
	    RFX_Text(pFX, _T("[CLASSID]"),m_CLASSID);
    if(IsColumnPresent(_T("FIELDTYPE")))
	    RFX_Text(pFX, _T("[FIELDTYPE]"),m_FIELDTYPE);
    if(IsColumnPresent(_T("TYPEREFORM")))
	    RFX_Byte(pFX, _T("[TYPEREFORM]"),m_TYPEREFORM);
}

void CColsSet::SetDefault()
{
	m_NAMSQLCOL = _T("");
	m_NAMECOL = _T("Новая колонка");
	m_WIDTHCOL = _T("1");
	m_TYPDATA = 0;
	m_FORMAT = _T("");
	m_TYPCENTR = 0;
	m_SEE = TRUE;
	m_TOBJECT = 0;
	m_TYPPAR = 0;
	m_TYPEAGR = 0;
	m_CLASSID=_T("");
	m_FIELDTYPE=_T("");
}

DWORD CColsSet::GetCodeField()
{
	return m_NUMCOL;
}

CString& CColsSet::GetNameField()
{
	return m_NAMECOL;
}

void CColsSet::SetFromOtherSet(CQERecordset *otherSet)
{
	CColsSet *cset=(CColsSet *)otherSet;
	m_NUMCOL = cset->m_NUMCOL;
	m_NAMSQLCOL = cset->m_NAMSQLCOL;
	m_NAMECOL = cset->m_NAMECOL;
	m_WIDTHCOL = cset->m_WIDTHCOL;
	m_TYPDATA = cset->m_TYPDATA;
	m_FORMAT = cset->m_FORMAT;
	m_TYPCENTR = cset->m_TYPCENTR;
	m_SEE = cset->m_SEE;
	m_TOBJECT = cset->m_TOBJECT;
	m_TYPPAR = cset->m_TYPPAR;
	m_TYPEAGR = cset->m_TYPEAGR;
	m_CLASSID = cset->m_CLASSID;
	m_FIELDTYPE = cset->m_FIELDTYPE;
}

void CColsSet::SetCodeField(int code)
{
	m_NUMCOL=code;
}


/////////////////////////////////////////////////////////////////////////////
// CDocsSet
CDocsSet::CDocsSet(CDatabNet* pdb): CQERecordset(pdb,"descrdoc")
{
	m_CODDOC = 0;
	m_NAMEDOC = _T("");
	m_NCOL_HEAD = _T("");
	m_QUERYDATA = _T("");
	m_QUERYHEAD = _T("");
	m_QUERYTITLE = _T("");
	m_REPORT = FALSE;
	m_SEARCH = FALSE;
	m_REFER = FALSE;
	m_DSELECT = FALSE;
	m_VIDOBJ = 0;
	m_TYPETOPO = 0;
	m_CODTECH = 0;
	m_WHATEQ = 0;
	m_TRANS = FALSE;
	m_HFONT = _T("");
	m_MINWIDCOL = _T("");
	m_BREAKPAGE = FALSE;
	m_ISNUMREC=FALSE;
	m_CROSSTAB=FALSE;
	m_ISREFPARAM=FALSE;
	m_ISGOTOSEL=FALSE;
	m_LINKBAS = FALSE;
	m_BREAK = 0;
    m_PlaceTitle = 0;
	m_nFields = 21;

	m_strTable="[descrdoc]";
	m_nFields=0;
	if(IsColumnPresent(_T("CODDOC")))
		m_nFields++;
	if(IsColumnPresent(_T("NAMEDOC")))
		m_nFields++;
	if(IsColumnPresent(_T("NCOL_HEAD")))
		m_nFields++;
	if(IsColumnPresent(_T("QUERYDATA")))
		m_nFields++;
	if(IsColumnPresent(_T("QUERYHEAD")))
		m_nFields++;
	if(IsColumnPresent(_T("QUERYTITLE")))
		m_nFields++;
	if(IsColumnPresent(_T("REPORT")))
		m_nFields++;
	if(IsColumnPresent(_T("SEARCH")))
		m_nFields++;
	if(IsColumnPresent(_T("REFER")))
		m_nFields++;
	if(IsColumnPresent(_T("DSELECT")))
		m_nFields++;
	if(IsColumnPresent(_T("VIDOBJ")))
		m_nFields++;
	if(IsColumnPresent(_T("TYPETOPO")))
		m_nFields++;
	if(IsColumnPresent(_T("CODTECH")))
		m_nFields++;
	if(IsColumnPresent(_T("WHATEQ")))
		m_nFields++;
	if(IsColumnPresent(_T("TRANS")))
		m_nFields++;
	if(IsColumnPresent(_T("HFONT")))
		m_nFields++;
	if(IsColumnPresent(_T("MINWIDCOL")))
		m_nFields++;
	if(IsColumnPresent(_T("BREAKPAGE")))
		m_nFields++;
	if(IsColumnPresent(_T("ISNUMREC")))
		m_nFields++;
	if(IsColumnPresent(_T("CROSSTAB")))
		m_nFields++;
	if(IsColumnPresent(_T("ISREFPARAM")))
		m_nFields++;
	if(IsColumnPresent(_T("ISGOTOSEL")))
		m_nFields++;
	if(IsColumnPresent(_T("BREAK")))
		m_nFields++;
	if(IsColumnPresent(_T("LINKBAS")))
		m_nFields++;
	if(IsColumnPresent(_T("PlaceTitle")))
		m_nFields++;

/*	if(!IsColumnPresent(_T("ISNUMREC")))
		m_nFields--;*/
}

CDocsSet::CDocsSet(CString &defDSN,CDatabNet* pDatabase)
	:CQERecordset(pDatabase,"descrdoc")
{
	m_CODDOC = 0;
	m_NAMEDOC = _T("");
	m_NCOL_HEAD = _T("");
	m_QUERYDATA = _T("");
	m_QUERYHEAD = _T("");
	m_QUERYTITLE = _T("");
	m_REPORT = FALSE;
	m_SEARCH = FALSE;
	m_REFER = FALSE;
	m_DSELECT = FALSE;
	m_VIDOBJ = 0;
	m_TYPETOPO = 0;
	m_CODTECH = 0;
	m_WHATEQ = 0;
	m_TRANS = FALSE;
	m_HFONT = _T("");
	m_MINWIDCOL = _T("");
	m_BREAKPAGE = FALSE;
	m_ISNUMREC=FALSE;
	m_CROSSTAB=FALSE;
	m_ISREFPARAM=FALSE;
	m_nFields = 21;
}

CString CDocsSet::GetDefaultSQL()
{
	return m_strTable;
}

void CDocsSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if(IsColumnPresent(_T("CODDOC")))
		RFX_Int(pFX, _T("[CODDOC]"), m_CODDOC);
	if(IsColumnPresent(_T("NAMEDOC")))
		RFX_Text(pFX, _T("[NAMEDOC]"), m_NAMEDOC);
	if(IsColumnPresent(_T("NCOL_HEAD")))
		RFX_Text(pFX, _T("[NCOL_HEAD]"), m_NCOL_HEAD);
	if(IsColumnPresent(_T("QUERYDATA")))
		RFX_Text(pFX, _T("[QUERYDATA]"), m_QUERYDATA);
	if(IsColumnPresent(_T("QUERYHEAD")))
		RFX_Text(pFX, _T("[QUERYHEAD]"), m_QUERYHEAD);
	if(IsColumnPresent(_T("QUERYTITLE")))
		RFX_Text(pFX, _T("[QUERYTITLE]"), m_QUERYTITLE);
	if(IsColumnPresent(_T("REPORT")))
		RFX_Bool(pFX, _T("[REPORT]"), m_REPORT);
	if(IsColumnPresent(_T("SEARCH")))
		RFX_Bool(pFX, _T("[SEARCH]"), m_SEARCH);
	if(IsColumnPresent(_T("REFER")))
		RFX_Bool(pFX, _T("[REFER]"), m_REFER);
	if(IsColumnPresent(_T("DSELECT")))
		RFX_Bool(pFX, _T("[DSELECT]"), m_DSELECT);
	if(IsColumnPresent(_T("VIDOBJ")))
		RFX_Byte(pFX, _T("[VIDOBJ]"), m_VIDOBJ);
	if(IsColumnPresent(_T("TYPETOPO")))
		RFX_Byte(pFX, _T("[TYPETOPO]"), m_TYPETOPO);
	if(IsColumnPresent(_T("CODTECH")))
		RFX_Byte(pFX, _T("[CODTECH]"), m_CODTECH);
	if(IsColumnPresent(_T("WHATEQ")))
		RFX_Byte(pFX, _T("[WHATEQ]"), m_WHATEQ);
	if(IsColumnPresent(_T("TRANS")))
		RFX_Bool(pFX, _T("[TRANS]"), m_TRANS);
	if(IsColumnPresent(_T("HFONT")))
		RFX_Text(pFX, _T("[HFONT]"), m_HFONT);
	if(IsColumnPresent(_T("MINWIDCOL")))
		RFX_Text(pFX, _T("[MINWIDCOL]"), m_MINWIDCOL);
	if(IsColumnPresent(_T("BREAKPAGE")))
		RFX_Bool(pFX, _T("[BREAKPAGE]"), m_BREAKPAGE);
	if(IsColumnPresent(_T("CROSSTAB")))
		RFX_Bool(pFX, _T("[CROSSTAB]"), m_CROSSTAB);
	if(IsColumnPresent(_T("ISNUMREC")))
		RFX_Bool(pFX, _T("[ISNUMREC]"), m_ISNUMREC);
	if(IsColumnPresent(_T("ISREFPARAM")))
		RFX_Bool(pFX, _T("[ISREFPARAM]"), m_ISREFPARAM);
	if(IsColumnPresent(_T("ISGOTOSEL")))
		RFX_Bool(pFX, _T("[ISGOTOSEL]"), m_ISGOTOSEL);
	if(IsColumnPresent(_T("BREAK")))
		RFX_Bool(pFX, _T("[BREAK]"), m_BREAK);
	if (IsColumnPresent(_T("LINKBAS")))
		RFX_Bool(pFX, _T("[LINKBAS]"), m_LINKBAS);
	if (IsColumnPresent(_T("PlaceTitle")))
		RFX_Byte(pFX, _T("[PlaceTitle]"), m_PlaceTitle);
}

DWORD CDocsSet::GetCodeField()
{
	return m_CODDOC;
}

CString& CDocsSet::GetNameField()
{
	return m_NAMEDOC;
}

void CDocsSet::SetDefault()
{
	m_NAMEDOC = _T("Новый документ");
	m_NCOL_HEAD = _T("0");
	m_QUERYDATA = _T("");
	m_QUERYHEAD = _T("");
	m_QUERYTITLE = _T("");
	m_REPORT = TRUE;
	m_SEARCH = FALSE;
	m_REFER = FALSE;
	m_DSELECT = FALSE;
	m_VIDOBJ = 0;
	m_TYPETOPO = 0;
	m_CODTECH = 0;
	m_WHATEQ = 0;
	m_TRANS = FALSE;
	m_HFONT = _T("10");
	m_MINWIDCOL = _T("");
	m_BREAKPAGE = FALSE;
	m_ISNUMREC=FALSE;
	m_CROSSTAB=FALSE;
	m_ISREFPARAM=FALSE;
}

void CDocsSet::SetFromOtherSet(CQERecordset *otherSet)
{
	CDocsSet *dset=(CDocsSet *)otherSet;
	m_NAMEDOC = dset->m_NAMEDOC;
	m_NCOL_HEAD = dset->m_NCOL_HEAD;
	m_QUERYDATA = dset->m_QUERYDATA;
	m_QUERYHEAD = dset->m_QUERYHEAD;
	m_QUERYTITLE = dset->m_QUERYTITLE;
	m_REPORT = dset->m_REPORT;
	m_SEARCH = dset->m_SEARCH;
	m_REFER = dset->m_REFER;
	m_DSELECT = dset->m_DSELECT;
	m_VIDOBJ = dset->m_VIDOBJ;
	m_TYPETOPO = dset->m_TYPETOPO;
	m_CODTECH = dset->m_CODTECH;
	m_WHATEQ = dset->m_WHATEQ;
	m_TRANS = dset->m_TRANS;
	m_HFONT = dset->m_HFONT;
	m_MINWIDCOL = dset->m_MINWIDCOL;
	m_ISNUMREC = dset->m_ISNUMREC;
	m_CROSSTAB = dset->m_CROSSTAB;
	m_ISREFPARAM = dset->m_ISREFPARAM;
	m_BREAK = dset->m_BREAK;
	m_ISGOTOSEL = dset->m_ISGOTOSEL; //10.05.17 Borys
}

void CDocsSet::SetCodeField(int code)
{
	m_CODDOC=code;
}

const CString CDocsSet::GetCodeNameF()
{
	CString cn, trname = m_NAMEDOC, trquery = m_QUERYDATA;
	trname.TrimLeft();
	trname.TrimRight();
	trquery.TrimLeft();
	trquery.TrimRight();
	cn.Format(_T("%d. %s (%s/%s)"),m_CODDOC,trname, trquery,
			CString("")+(m_REFER?_T("Справка"):_T(""))+(m_REPORT?_T("Отчет"):_T(""))
			+(m_SEARCH?_T("Поиск"):_T(""))+((m_DSELECT || m_BREAK)?_T("Выделение"):_T("")));
	return cn;
}

const CString CDocsSet::GetCodeNameSorted(UINT sorttype)
{
	CString cn, trname = m_NAMEDOC, trquery = m_QUERYDATA, trtype;
	trname.TrimLeft();
	trname.TrimRight();
	trquery.TrimLeft();
	trquery.TrimRight();
	trtype = CString("")+(m_REPORT?_T(" Отчет"):_T(""))+(m_SEARCH?_T(" Поиск"):_T(""))+
		(m_REFER?_T(" Справка"):_T(""))+((m_DSELECT || m_BREAK)?_T(" Выделение"):_T("")); 

	switch(sorttype)
	{
	case(ID_SORTCODE):cn.Format(_T("%d. %s (%s, %s)"),m_CODDOC,trname, trquery, trtype);
		break;
	case(ID_SORTNAME):cn.Format(_T("%s [%d] (%s, %s)"),trname, m_CODDOC, trquery, trtype);
		break;
	case(ID_SORTQUERY):cn.Format(_T("%s: %d. %s (%s)"),trquery, m_CODDOC,trname, trtype);
		break;
	case(ID_SORTTYPE):cn.Format(_T("%s: %d. %s (%s)"),trtype, m_CODDOC,trname, trquery);
		break;
	}
	return cn;
}


/////////////////////////////////////////////////////////////////////////////
// CListsDocOnlySet
CListsDocOnlySet::CListsDocOnlySet(CDatabNet* pdb): CQERecordset(pdb,"listdocs")
{
	m_LISTDOC = 0;
	m_NUMDOC = 0;
	m_CODDOC = 0;
	m_nFields = 3;
}

void CListsDocOnlySet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[LISTDOC]"), m_LISTDOC);
	RFX_Byte(pFX, _T("[NUMDOC]"), m_NUMDOC);
	RFX_Int(pFX, _T("[CODDOC]"), m_CODDOC);
}


/////////////////////////////////////////////////////////////////////////////
// CListsSet
CListsSet::CListsSet(CDatabNet* pdb): CQERecordset(pdb, _T(""))
{
	m_CODDOC = 0;
	m_NAMEDOC = _T("");
	m_LISTDOC = 0;
	m_NUMDOC = 0;
	m_CODDOC2 = 0;
	m_nFields = 5;

	m_isonlylistdocs=FALSE;
}

CString CListsSet::GetDefaultSQL()
{
	m_strSort="NUMDOC";
	return _T("[descrdoc],[listdocs]");
}

void CListsSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[descrdoc].[CODDOC]"), m_CODDOC);
	RFX_Text(pFX, _T("[NAMEDOC]"), m_NAMEDOC);
	RFX_Int(pFX, _T("[LISTDOC]"), m_LISTDOC);
	RFX_Byte(pFX, _T("[NUMDOC]"), m_NUMDOC);
	RFX_Int(pFX, _T("[listdocs].[CODDOC]"), m_CODDOC2);
}

DWORD CListsSet::GetCodeField()
{
	return m_NUMDOC;
}

CString& CListsSet::GetNameField()
{
	return m_NAMEDOC;
}


/////////////////////////////////////////////////////////////////////////////
// CMetaSet
CMetaSet::CMetaSet(CDatabNet* pdb): CRecordNet(pdb,"")
{
	m_ClassID = 0;
	m_ClassValueID = 0;
	m_ClassValue = _T("");
	m_nFields = 3;

	m_clID=-1;
}

CMetaSet::CMetaSet(LPCTSTR tableName, LPCTSTR fieldName, CDatabNet* pdb)
{
	m_tableName=tableName,m_fieldName=fieldName;
	m_ClassID = 0;
	m_ClassValueID = 0;
	m_ClassValue = _T("");
	m_nFields = 3;
	m_clID=-1;
}

CString CMetaSet::GetDefaultSQL()
{
	if(m_clID==-1)
	{
		m_strFilter.Format(_T("MetaField.FieldName='%s' AND MetaTable.TableName='%s' AND MetaField.Table_ID=MetaTable.Table_ID AND MetaGlobNam.ClassID=MetaField.ClassID"),m_fieldName,m_tableName);
		m_strSort="MetaGlobNam.ClassValueID";
		return _T("SELECT MetaGlobNam.ClassID,  MetaGlobNam.ClassValueID,  MetaGlobNam.ClassValue FROM MetaGlobNam,MetaField,MetaTable");
	}
	else if(m_clID==CLASSID_DATEFORM)
	{
		m_strFilter="Input=True";
		m_strSort="Code";
		return _T("SELECT 77777 AS ClassID,Code AS ClassValueID,(FormatW) AS ClassValue FROM dateform");
	}
	else
	{
		m_strFilter.Format(_T("ClassID=%d"),m_clID);
		m_strSort="ClassValueID";
		return _T("[MetaGlobNam]");
	}
}

void CMetaSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[ClassID]"), m_ClassID);
	RFX_Byte(pFX, _T("[ClassValueID]"), m_ClassValueID);
	RFX_Text(pFX, _T("[ClassValue]"), m_ClassValue);
}

void CMetaSet::SetTableField(LPCTSTR tableName, LPCTSTR fieldName)
{
	m_tableName=tableName;
	m_fieldName=fieldName;
	m_clID=-1;
}

void CMetaSet::SetClassID(long clID)
{
	m_clID=clID;
}


/////////////////////////////////////////////////////////////////////////////
// CSelsSet
CSelsSet::CSelsSet(CDatabNet* pdb): CQERecordset(pdb, "dessel")
{
	m_CODDOC = 0;
	m_DSELECT = 0;
	m_NAMSELECT = _T("");
	m_VALSELECT = _T("");
	m_nFields = 4;

	m_strTable="[dessel]";
}

CString CSelsSet::GetDefaultSQL()
{
	m_strSort="dselect";
	return m_strTable;
}

void CSelsSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[CODDOC]"), m_CODDOC);
	RFX_Byte(pFX, _T("[DSELECT]"), m_DSELECT);
	RFX_Text(pFX, _T("[NAMSELECT]"), m_NAMSELECT);
	RFX_Text(pFX, _T("[VALSELECT]"), m_VALSELECT);
}

void CSelsSet::SetCodeField(int code)
{
}

void CSelsSet::SetFromOtherSet(CQERecordset *otherSet)
{
	CSelsSet *sset=(CSelsSet *)otherSet;

	m_NAMSELECT = sset->m_NAMSELECT;
	m_VALSELECT = sset->m_VALSELECT;
}

void CSelsSet::SetDefault()
{
	m_NAMSELECT = _T("Новое");
	m_VALSELECT = _T("");
}

CString& CSelsSet::GetNameField()
{
	return m_NAMSELECT;
}

DWORD CSelsSet::GetCodeField()
{
	return m_DSELECT;
}


/////////////////////////////////////////////////////////////////////////////
// CVarsSet
CVarsSet::CVarsSet(CDatabNet* pdb): CQERecordset(pdb, "variable")
{
	m_CODDOC = 0;
	m_NUMVAR = 0;
	m_CODVAR = _T("");
	m_NAMEVAR = _T("");
	m_TYPVAR = 0;
	m_FORMAT = _T("");
	m_TYPECNTRL = 0;
	m_WIDTHCNTRL = _T("");
	m_NUMCOLLIST = _T("");
	m_NUMROWLIST = _T("");
	m_QUERYVAR = _T("");
	m_CONDITION = _T("");
	m_NCOLQUERY = _T("");
	m_DEFVAL = _T("");
	m_ORDERVAR=0;
	m_nFields = 15;

	m_strSort="NUMVAR";
}

CVarsSet::CVarsSet(CString &defDSN,CDatabNet* pDatabase)
	:CQERecordset(pDatabase, "variable")
{
	m_CODDOC = 0;
	m_NUMVAR = 0;
	m_CODVAR = _T("");
	m_NAMEVAR = _T("");
	m_TYPVAR = 0;
	m_FORMAT = _T("");
	m_TYPECNTRL = 0;
	m_WIDTHCNTRL = _T("");
	m_NUMCOLLIST = _T("");
	m_NUMROWLIST = _T("");
	m_QUERYVAR = _T("");
	m_CONDITION = _T("");
	m_NCOLQUERY = _T("");
	m_DEFVAL = _T("");
	m_ORDERVAR=0;
	m_nFields = 15;
	m_strSort="NUMVAR";
}

void CVarsSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[CODDOC]"), m_CODDOC);
	RFX_Byte(pFX, _T("[NUMVAR]"), m_NUMVAR);
	RFX_Text(pFX, _T("[CODVAR]"), m_CODVAR);
	RFX_Text(pFX, _T("[NAMEVAR]"), m_NAMEVAR);
	RFX_Byte(pFX, _T("[TYPVAR]"), m_TYPVAR);
	RFX_Text(pFX, _T("[FORMAT]"), m_FORMAT);
	RFX_Byte(pFX, _T("[TYPECNTRL]"), m_TYPECNTRL);
	RFX_Text(pFX, _T("[WIDTHCNTRL]"), m_WIDTHCNTRL);
	RFX_Text(pFX, _T("[NUMCOLLIST]"), m_NUMCOLLIST);
	RFX_Text(pFX, _T("[NUMROWLIST]"), m_NUMROWLIST);
	RFX_Text(pFX, _T("[QUERYVAR]"), m_QUERYVAR);
	RFX_Text(pFX, _T("[CONDITION]"), m_CONDITION);
	RFX_Text(pFX, _T("[NCOLQUERY]"), m_NCOLQUERY);
	RFX_Text(pFX, _T("[DEFVAL]"), m_DEFVAL);
	RFX_Byte(pFX, _T("[ORDERVAR]"),m_ORDERVAR);
}

DWORD CVarsSet::GetCodeField()
{
	return m_NUMVAR;
}

CString& CVarsSet::GetNameField()
{
	return m_NAMEVAR;
}

void CVarsSet::SetDefault()
{
	m_NAMEVAR = _T("Новая переменная");
	m_CODVAR = GenerateName();
	m_TYPVAR = 1;
	m_FORMAT = _T("");
	m_TYPECNTRL = 1;
	m_WIDTHCNTRL = _T("10");
	m_NUMCOLLIST = _T("");
	m_NUMROWLIST = _T("");
	m_QUERYVAR = _T("");
	m_CONDITION = _T("");
	m_NCOLQUERY = _T("");
	m_DEFVAL = _T("");
	m_ORDERVAR=0;
}

CString CVarsSet::GenerateName()
{
	return CString("RN")+CString(char('a'+rand()%22))+char('a'+rand()%22)
		+char('a'+rand()%22)+char('a'+rand()%22)+char('a'+rand()%22)+char('a'+rand()%22);
}

void CVarsSet::SetFromOtherSet(CQERecordset *otherSet)
{
	CVarsSet *vset=(CVarsSet *)otherSet;
	m_NAMEVAR = vset->m_NAMEVAR;
	m_CODVAR = vset->m_CODVAR;
	m_TYPVAR = vset->m_TYPVAR;
	m_FORMAT = vset->m_FORMAT;
	m_TYPECNTRL = vset->m_TYPECNTRL;
	m_WIDTHCNTRL = vset->m_WIDTHCNTRL;
	m_NUMCOLLIST = vset->m_NUMCOLLIST;
	m_NUMROWLIST = vset->m_NUMROWLIST;
	m_QUERYVAR = vset->m_QUERYVAR;
	m_CONDITION = vset->m_CONDITION;
	m_NCOLQUERY = vset->m_NCOLQUERY;
	m_DEFVAL = vset->m_DEFVAL;
	m_ORDERVAR = vset->m_ORDERVAR;
}

void CVarsSet::SetCodeField(int code)
{
	m_NUMVAR=code;
}
