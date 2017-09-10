// TpnameRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "TpnameRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TpnameRead

IMPLEMENT_DYNAMIC(TpnameRead, CRecordset)

TpnameRead::TpnameRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TpnameRead)
	m_VIDOBJ = 0;
	m_TYPNAM = 0;
	m_USEORDER = 0;
	m_NAMNAM = _T("");
	m_ICOLTEXT = 0;
	m_NUMFONT = 0;
	m_TYPSYS = 0;
	m_NUMEXPR = 0;
	m_STYLENAME = 0;
	m_NUMTPNAM = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString TpnameRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString TpnameRead::GetDefaultSQL()
{
	return _T("[tpname]");
}

void TpnameRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TpnameRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[VIDOBJ]"), m_VIDOBJ);
	RFX_Byte(pFX, _T("[TYPNAM]"), m_TYPNAM);
	RFX_Byte(pFX, _T("[USEORDER]"), m_USEORDER);
	RFX_Text(pFX, _T("[NAMNAM]"), m_NAMNAM);
	RFX_Long(pFX, _T("[ICOLTEXT]"), m_ICOLTEXT);
	RFX_Byte(pFX, _T("[NUMFONT]"), m_NUMFONT);
	RFX_Byte(pFX, _T("[TYPSYS]"), m_TYPSYS);
	RFX_Byte(pFX, _T("[NUMEXPR]"), m_NUMEXPR);
	RFX_Byte(pFX, _T("[STYLENAME]"), m_STYLENAME);
	RFX_Byte(pFX, _T("[NUMTPNAM]"), m_NUMTPNAM);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TpnameRead diagnostics

#ifdef _DEBUG
void TpnameRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void TpnameRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
