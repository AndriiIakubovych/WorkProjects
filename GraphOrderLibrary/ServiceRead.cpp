// ServiceRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "ServiceRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ServiceRead

IMPLEMENT_DYNAMIC(ServiceRead, CRecordset)

ServiceRead::ServiceRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(ServiceRead)
	m_NREGSERV = 0;
	m_NAMSERV = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString ServiceRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString ServiceRead::GetDefaultSQL()
{
	return _T("[service]");
}

void ServiceRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(ServiceRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[NREGSERV]"), m_NREGSERV);
	RFX_Text(pFX, _T("[NAMSERV]"), m_NAMSERV);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ServiceRead diagnostics

#ifdef _DEBUG
void ServiceRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void ServiceRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
