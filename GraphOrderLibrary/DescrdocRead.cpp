// DescrdocRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "DescrdocRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DescrdocRead

IMPLEMENT_DYNAMIC(DescrdocRead, CRecordset)

DescrdocRead::DescrdocRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(DescrdocRead)
	m_CODDOC = 0;
	m_NAMEDOC = _T("");
	m_QUERYDATA = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString DescrdocRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString DescrdocRead::GetDefaultSQL()
{
	return _T("[descrdoc]");
}

void DescrdocRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(DescrdocRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[CODDOC]"), m_CODDOC);
	RFX_Text(pFX, _T("[NAMEDOC]"), m_NAMEDOC);
	RFX_Text(pFX, _T("[QUERYDATA]"), m_QUERYDATA);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// DescrdocRead diagnostics

#ifdef _DEBUG
void DescrdocRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void DescrdocRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
