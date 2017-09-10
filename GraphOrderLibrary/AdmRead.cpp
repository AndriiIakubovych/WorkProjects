// AdmRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "AdmRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AdmRead

IMPLEMENT_DYNAMIC(AdmRead, CRecordset)

AdmRead::AdmRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(AdmRead)
	m_NREGADM = 0;
	m_NAMADM = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString AdmRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString AdmRead::GetDefaultSQL()
{
	return _T("[adm]");
}

void AdmRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(AdmRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[NREGADM]"), m_NREGADM);
	RFX_Text(pFX, _T("[NAMADM]"), m_NAMADM);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// AdmRead diagnostics

#ifdef _DEBUG
void AdmRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void AdmRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
