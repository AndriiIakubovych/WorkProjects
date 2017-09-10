// OrdAllRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "OrdAllRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// OrdAllRead

IMPLEMENT_DYNAMIC(OrdAllRead, CRecordset)

OrdAllRead::OrdAllRead(CDatabase* pdb)
: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(OrdAllRead)
	m_RegiServ = 0;
	m_NUMORD = 0;
	m_CODORD = 0;
	m_NREGSERV = 0;
	m_YY = 0;
	m_NREGADM = 0;
	m_NUMADRAM = 0;
	m_STATEORD = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString OrdAllRead::GetDefaultConnect()
{
	return _T("ODBC;DSN=" + StrConnection);
}

CString OrdAllRead::GetDefaultSQL()
{
	return _T(TableName);
}

void OrdAllRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(OrdAllRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	if (HasRegiServ)
		RFX_Byte(pFX, _T("[RegiServ]"), m_RegiServ);
	else
		RFX_Byte(pFX, _T("[NREGSERV]"), m_RegiServ);
	RFX_Long(pFX, _T("[NUMORD]"), m_NUMORD);
	RFX_Long(pFX, _T("[CODORD]"), m_CODORD);
	RFX_Byte(pFX, _T("[NREGSERV]"), m_NREGSERV);
	RFX_Long(pFX, _T("[YY]"), m_YY);
	RFX_Byte(pFX, _T("[NREGADM]"), m_NREGADM);
	//RFX_Long(pFX, _T("[NUMADRAM]"), m_NUMADRAM);
	RFX_Date(pFX, _T("[DATREC]"), m_DATREC);
	RFX_Byte(pFX, _T("[STATEORD]"), m_STATEORD);
	RFX_Date(pFX, _T("[DATENDF]"), m_DATENDF);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// OrdAllRead diagnostics

#ifdef _DEBUG
void OrdAllRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void OrdAllRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
