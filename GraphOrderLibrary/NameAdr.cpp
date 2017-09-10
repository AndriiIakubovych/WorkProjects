// NameAdr.cpp : implementation file
//

#include "stdafx.h"
#include "NameAdr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// NameAdr

NameAdr::NameAdr(CDatabNet* pdb,CString tblnam)
	: CRecordNet(pdb,tblnam)
{
	//{{AFX_FIELD_INIT(NameAdr)
	m_NUMAREA = 0;
	m_distr = _T("");
	m_street = _T("");
	m_ADDRESS = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString NameAdr::GetDefaultSQL()
{
	return _T("[NameAdrD]");
}

void NameAdr::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(NameAdr)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[NUMAREA]"), m_NUMAREA);
	RFX_Text(pFX, _T("[street]"), m_street);
	RFX_Text(pFX, _T("[ADDRESS]"), m_ADDRESS);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// NameAdr diagnostics

#ifdef _DEBUG
#endif //_DEBUG
