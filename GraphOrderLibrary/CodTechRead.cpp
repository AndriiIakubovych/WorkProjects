// CodTechRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "CodTechRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CodTechRead

IMPLEMENT_DYNAMIC(CodTechRead, CRecordset)

CodTechRead::CodTechRead(CDatabase* pdb)
: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CodTechRead)
	m_CODCLAS = 0;
	m_CODSCLAS = 0;
	m_NAME = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CodTechRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString CodTechRead::GetDefaultSQL()
{
	return _T("[codtech]");
}

void CodTechRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CodTechRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[CODCLAS]"), m_CODCLAS);
	RFX_Byte(pFX, _T("[CODSCLAS]"), m_CODSCLAS);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CodTechRead diagnostics

#ifdef _DEBUG
void CodTechRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void CodTechRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
