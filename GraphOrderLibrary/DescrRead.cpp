// DescrRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "DescrRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DescrRead

IMPLEMENT_DYNAMIC(DescrRead, CRecordset)

DescrRead::DescrRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(DescrRead)
	m_CODDOC = 0;
	m_NUMCOL = 0;
	m_NAMSQLCOL = _T("");
	m_NAMECOL = _T("");
	m_WIDTHCOL = 0;
	m_TYPDATA = 0;
	m_FORMAT = _T("");
	m_TYPCENTR = 0;
	m_SEE = FALSE;
	m_NOSEEAGR = FALSE;
	m_TOBJECT = 0;
	m_TYPPAR = 0;
	m_TYPEAGR = 0;
	m_FIELDTYPE = 0;
	m_CLASSID = 0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString DescrRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString DescrRead::GetDefaultSQL()
{
	return _T("[descrcol]");
}

void DescrRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(DescrRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[CODDOC]"), m_CODDOC);
	RFX_Byte(pFX, _T("[NUMCOL]"), m_NUMCOL);
	RFX_Text(pFX, _T("[NAMSQLCOL]"), m_NAMSQLCOL);
	RFX_Text(pFX, _T("[NAMECOL]"), m_NAMECOL);
	RFX_Byte(pFX, _T("[WIDTHCOL]"), m_WIDTHCOL);
	RFX_Byte(pFX, _T("[TYPDATA]"), m_TYPDATA);
	RFX_Text(pFX, _T("[FORMAT]"), m_FORMAT);
	RFX_Byte(pFX, _T("[TYPCENTR]"), m_TYPCENTR);
	RFX_Bool(pFX, _T("[SEE]"), m_SEE);
	RFX_Bool(pFX, _T("[NOSEEAGR]"), m_NOSEEAGR);
	RFX_Byte(pFX, _T("[TOBJECT]"), m_TOBJECT);
	RFX_Int(pFX, _T("[TYPPAR]"), m_TYPPAR);
	RFX_Byte(pFX, _T("[TYPEAGR]"), m_TYPEAGR);
	RFX_Byte(pFX, _T("[FIELDTYPE]"), m_FIELDTYPE);
	RFX_Int(pFX, _T("[CLASSID]"), m_CLASSID);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// DescrRead diagnostics

#ifdef _DEBUG
void DescrRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void DescrRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
