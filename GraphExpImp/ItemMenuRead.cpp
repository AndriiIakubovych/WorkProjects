// ItemMenuRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "ItemMenuRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ItemMenuRead

IMPLEMENT_DYNAMIC(ItemMenuRead, CRecordset)

ItemMenuRead::ItemMenuRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(ItemMenuRead)
	m_CODMENU = 0;
	m_CODITEM = 0;
	m_NUMITEM = 0;
	m_NAMEITEM = _T("");
	m_CODCOMM = 0;
	m_CODICON = 0;
	m_HELPITEM = _T("");
	m_ACCESS = 0;
	m_WRJOURN = 0;
	m_nFields = 9;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString ItemMenuRead::GetDefaultConnect()
{
	char str[MAX_PATH], str_connection[MAX_PATH];
	GetPrivateProfileString("Supshort", "Sup", NULL, str_connection, sizeof(str_connection), IniFile);
	strcpy(str, "ODBC;DSN=");
	strcat(str, str_connection);
	return _T(str);
}

CString ItemMenuRead::GetDefaultSQL()
{
	return _T("[itemmenu]");
}

void ItemMenuRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(ItemMenuRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[CODMENU]"), m_CODMENU);
	RFX_Int(pFX, _T("[CODITEM]"), m_CODITEM);
	RFX_Int(pFX, _T("[NUMITEM]"), m_NUMITEM);
	RFX_Text(pFX, _T("[NAMEITEM]"), m_NAMEITEM);
	RFX_Int(pFX, _T("[CODCOMM]"), m_CODCOMM);
	RFX_Int(pFX, _T("[CODICON]"), m_CODICON);
	RFX_Text(pFX, _T("[HELPITEM]"), m_HELPITEM);
	RFX_Byte(pFX, _T("[ACCESS]"), m_ACCESS);
	RFX_Byte(pFX, _T("[WRJOURN]"), m_WRJOURN);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ItemMenuRead diagnostics

#ifdef _DEBUG
void ItemMenuRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void ItemMenuRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
