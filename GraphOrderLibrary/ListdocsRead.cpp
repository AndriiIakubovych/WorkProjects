// ListdocsRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "ListdocsRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ListdocsRead

IMPLEMENT_DYNAMIC(ListdocsRead, CRecordset)

ListdocsRead::ListdocsRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(ListdocsRead)
	m_LISTDOC = 0;
	m_NUMDOC = 0;
	m_CODDOC = 0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString ListdocsRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString ListdocsRead::GetDefaultSQL()
{
	return _T("[listdocs]");
}

void ListdocsRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(ListdocsRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[LISTDOC]"), m_LISTDOC);
	RFX_Byte(pFX, _T("[NUMDOC]"), m_NUMDOC);
	RFX_Int(pFX, _T("[CODDOC]"), m_CODDOC);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ListdocsRead diagnostics

#ifdef _DEBUG
void ListdocsRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void ListdocsRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
