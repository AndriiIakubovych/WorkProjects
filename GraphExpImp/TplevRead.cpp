// TplevRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "TplevRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TplevRead

IMPLEMENT_DYNAMIC(TplevRead, CRecordset)

TplevRead::TplevRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TplevRead)
	m_vidobj = 0;
	m_type = 0;
	m_USEORDER = 0;
	m_dlevel = 0;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString TplevRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString TplevRead::GetDefaultSQL()
{
	return _T("[tplev]");
}

void TplevRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TplevRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[vidobj]"), m_vidobj);
	RFX_Int(pFX, _T("[type]"), m_type);
	RFX_Byte(pFX, _T("[USEORDER]"), m_USEORDER);
	RFX_Int(pFX, _T("[dlevel]"), m_dlevel);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TplevRead diagnostics

#ifdef _DEBUG
void TplevRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void TplevRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
