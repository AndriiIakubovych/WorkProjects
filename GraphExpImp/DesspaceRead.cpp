// DesspaceRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "DesspaceRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DesspaceRead

IMPLEMENT_DYNAMIC(DesspaceRead, CRecordset)

DesspaceRead::DesspaceRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(DesspaceRead)
	m_PERSON = 0;
	m_NUMSPACE = 0;
	m_NAMESPACE = _T("");
	m_TYPSPACE = 0;
	//m_CRIT = 0;
	m_NUMPOINT = 0;
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString DesspaceRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString DesspaceRead::GetDefaultSQL()
{
	return _T("[desspace]");
}

void DesspaceRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(DesspaceRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[PERSON]"), m_PERSON);
	RFX_Int(pFX, _T("[NUMSPACE]"), m_NUMSPACE);
	RFX_Text(pFX, _T("[NAMESPACE]"), m_NAMESPACE);
	RFX_Byte(pFX, _T("[TYPSPACE]"), m_TYPSPACE);
	//RFX_Byte(pFX, _T("[CRIT]"), m_CRIT);
	RFX_Int(pFX, _T("[NUMPOINT]"), m_NUMPOINT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// DesspaceRead diagnostics

#ifdef _DEBUG
void DesspaceRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void DesspaceRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
