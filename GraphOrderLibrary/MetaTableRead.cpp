// MetaTableRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "MetaTableRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MetaTableRead

IMPLEMENT_DYNAMIC(MetaTableRead, CRecordset)

MetaTableRead::MetaTableRead(CDatabase* pdb)
: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(MetaTableRead)
	m_NUMREG = 0;
	m_Table_ID = 0;
	m_TableName = _T("");
	m_TableDescr = _T("");
	m_IsTable = FALSE;
	m_TableType = 0;
	m_BaseType = 0;
	m_IsBlock = FALSE;
	m_Condition = _T("");
	m_ModeName = 0;
	m_nFields = 10;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString MetaTableRead::GetDefaultConnect()
{
	char str[MAX_PATH], str_connection[MAX_PATH];
	GetPrivateProfileString("Supshort", "Sup", NULL, str_connection, sizeof(str_connection), IniFile);
	strcpy(str, "ODBC;DSN=");
	strcat(str, str_connection);
	return _T(str);
}

CString MetaTableRead::GetDefaultSQL()
{
	return _T("[MetaTable]");
}

void MetaTableRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(MetaTableRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[NUMREG]"), m_NUMREG);
	RFX_Int(pFX, _T("[Table_ID]"), m_Table_ID);
	RFX_Text(pFX, _T("[TableName]"), m_TableName);
	RFX_Text(pFX, _T("[TableDescr]"), m_TableDescr);
	RFX_Bool(pFX, _T("[IsTable]"), m_IsTable);
	RFX_Byte(pFX, _T("[TableType]"), m_TableType);
	RFX_Byte(pFX, _T("[BaseType]"), m_BaseType);
	RFX_Bool(pFX, _T("[IsBlock]"), m_IsBlock);
	RFX_Text(pFX, _T("[Condition]"), m_Condition);
	RFX_Byte(pFX, _T("[ModeName]"), m_ModeName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// MetaTableRead diagnostics

#ifdef _DEBUG
void MetaTableRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void MetaTableRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
