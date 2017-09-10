// NregionRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "NregionRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// NregionRead

IMPLEMENT_DYNAMIC(NregionRead, CRecordset)

NregionRead::NregionRead(CDatabase* pdb)
: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(NregionRead)
	m_NUMREG = 0;
	m_GRUPREG = 0;
	m_NAMREG = _T("");
	m_PATH = _T("");
	m_TYPBASE = 0;
	m_PARENT = 0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString NregionRead::GetDefaultConnect()
{
	char str[MAX_PATH], str_connection[MAX_PATH];
	GetPrivateProfileString("Supshort", "Sup", NULL, str_connection, sizeof(str_connection), IniFile);
	strcpy(str, "ODBC;DSN=");
	strcat(str, str_connection);
	return _T(str);
}

CString NregionRead::GetDefaultSQL()
{
	return _T("[nregion]");
}

void NregionRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(NregionRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[NUMREG]"), m_NUMREG);
	RFX_Byte(pFX, _T("[GRUPREG]"), m_GRUPREG);
	RFX_Text(pFX, _T("[NAMREG]"), m_NAMREG);
	RFX_Text(pFX, _T("[PATH]"), m_PATH);
	RFX_Byte(pFX, _T("[TYPBASE]"), m_TYPBASE);
	RFX_Int(pFX, _T("[PARENT]"), m_PARENT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// NregionRead diagnostics

#ifdef _DEBUG
void NregionRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void NregionRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
