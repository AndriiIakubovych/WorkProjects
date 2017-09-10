// TplineRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "TplineRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TplineRead

IMPLEMENT_DYNAMIC(TplineRead, CRecordset)

TplineRead::TplineRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(TplineRead)
	m_VIDOBJ = 0;
	m_TYPBLINE = 0;
	m_USEORDER = 0;
	m_NAMTP = _T("");
	m_TYPLINE = 0;
	m_ICOLBOUM = 0;
	m_WIDTH = 0;
	m_CLOSE = 0;
	m_TYPSYS = 0;
	m_ICOLOUR = 0;
	m_ICOLDASH = 0;
	m_STYLDASH = 0;
	m_MODEADR = 0;
	m_SIZEVAL = 0.0f;
	m_NUMFIG = 0;
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString TplineRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString TplineRead::GetDefaultSQL()
{
	return _T("[tpline]");
}

void TplineRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(TplineRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Byte(pFX, _T("[VIDOBJ]"), m_VIDOBJ);
	RFX_Byte(pFX, _T("[TYPBLINE]"), m_TYPBLINE);
	RFX_Byte(pFX, _T("[USEORDER]"), m_USEORDER);
	RFX_Text(pFX, _T("[NAMTP]"), m_NAMTP);
	RFX_Byte(pFX, _T("[TYPLINE]"), m_TYPLINE);
	RFX_Long(pFX, _T("[ICOLBOUM]"), m_ICOLBOUM);
	RFX_Byte(pFX, _T("[WIDTH]"), m_WIDTH);
	RFX_Byte(pFX, _T("[CLOSE]"), m_CLOSE);
	RFX_Byte(pFX, _T("[TYPSYS]"), m_TYPSYS);
	RFX_Long(pFX, _T("[ICOLOUR]"), m_ICOLOUR);
	RFX_Long(pFX, _T("[ICOLDASH]"), m_ICOLDASH);
	RFX_Byte(pFX, _T("[STYLDASH]"), m_STYLDASH);
	RFX_Byte(pFX, _T("[MODEADR]"), m_MODEADR);
	RFX_Single(pFX, _T("[SIZEVAL]"), m_SIZEVAL);
	RFX_Int(pFX, _T("[NUMFIG]"), m_NUMFIG);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// TplineRead diagnostics

#ifdef _DEBUG
void TplineRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void TplineRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
