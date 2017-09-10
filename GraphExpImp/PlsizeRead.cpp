// PlsizeRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "PlsizeRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PlsizeRead

IMPLEMENT_DYNAMIC(PlsizeRead, CRecordset)

PlsizeRead::PlsizeRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(PlsizeRead)
	m_NUMREG = 0;
	m_PLANSHET = 0;
	m_SIZX = 0.0f;
	m_SIZY = 0.0f;
	m_MASKSQLEN = 0;
	m_MASH = 0.0f;
	m_BSQX = 0;
	m_BSQY = 0;
	m_ESQX = 0;
	m_ESQY = 0;
	m_ABCD = _T("");
	m_NUMSQT = 0;
	m_PLANCOVER = 0;
	m_NUMSQ = 0;
	m_LENNAMPL = 0;
	m_XMIN = 0;
	m_YMIN = 0;
	m_XMAX = 0;
	m_YMAX = 0;
	m_KX = 0;
	m_KY = 0;
	m_MODEADRBLD = 0;
	m_LEVADR = 0;
	m_DRAWADR = 0;
	m_TYPNAMSTR = 0;
	m_TYPNAMREG = 0;
	m_ADM = FALSE;
	m_ADMSTR = FALSE;
	m_AREA = FALSE;
	m_BUILDING = FALSE;
	m_UPBASE = FALSE;
	m_BUILDPASP = FALSE;
	m_ICON = FALSE;
	m_desline = 0;
	m_desicon = 0;
	m_raster = 0;
	m_Digitizer = FALSE;
	m_ISEXPIMP = 0;
	m_NumSqlBl = 0;
	m_NumSqlLine = 0;
	m_bal = 0;
	m_nFields = 41;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString PlsizeRead::GetDefaultConnect()
{
	char str[MAX_PATH], str_connection[MAX_PATH];
	GetPrivateProfileString("Supshort", "Sup", NULL, str_connection, sizeof(str_connection), IniFile);
	strcpy(str, "ODBC;DSN=");
	strcat(str, str_connection);
	return _T(str);
}

CString PlsizeRead::GetDefaultSQL()
{
	return _T("[plsize]");
}

void PlsizeRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(PlsizeRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, _T("[NUMREG]"), m_NUMREG);
	RFX_Byte(pFX, _T("[PLANSHET]"), m_PLANSHET);
	RFX_Single(pFX, _T("[SIZX]"), m_SIZX);
	RFX_Single(pFX, _T("[SIZY]"), m_SIZY);
	RFX_Byte(pFX, _T("[MASKSQLEN]"), m_MASKSQLEN);
	RFX_Single(pFX, _T("[MASH]"), m_MASH);
	RFX_Int(pFX, _T("[BSQX]"), m_BSQX);
	RFX_Int(pFX, _T("[BSQY]"), m_BSQY);
	RFX_Int(pFX, _T("[ESQX]"), m_ESQX);
	RFX_Int(pFX, _T("[ESQY]"), m_ESQY);
	RFX_Text(pFX, _T("[ABCD]"), m_ABCD);
	RFX_Byte(pFX, _T("[NUMSQT]"), m_NUMSQT);
	RFX_Byte(pFX, _T("[PLANCOVER]"), m_PLANCOVER);
	RFX_Byte(pFX, _T("[NUMSQ]"), m_NUMSQ);
	RFX_Byte(pFX, _T("[LENNAMPL]"), m_LENNAMPL);
	RFX_Long(pFX, _T("[XMIN]"), m_XMIN);
	RFX_Long(pFX, _T("[YMIN]"), m_YMIN);
	RFX_Long(pFX, _T("[XMAX]"), m_XMAX);
	RFX_Long(pFX, _T("[YMAX]"), m_YMAX);
	RFX_Long(pFX, _T("[KX]"), m_KX);
	RFX_Long(pFX, _T("[KY]"), m_KY);
	RFX_Byte(pFX, _T("[MODEADRBLD]"), m_MODEADRBLD);
	RFX_Byte(pFX, _T("[LEVADR]"), m_LEVADR);
	RFX_Byte(pFX, _T("[DRAWADR]"), m_DRAWADR);
	RFX_Byte(pFX, _T("[TYPNAMSTR]"), m_TYPNAMSTR);
	RFX_Byte(pFX, _T("[TYPNAMREG]"), m_TYPNAMREG);
	RFX_Bool(pFX, _T("[ADM]"), m_ADM);
	RFX_Bool(pFX, _T("[ADMSTR]"), m_ADMSTR);
	RFX_Bool(pFX, _T("[AREA]"), m_AREA);
	RFX_Bool(pFX, _T("[BUILDING]"), m_BUILDING);
	RFX_Bool(pFX, _T("[UPBASE]"), m_UPBASE);
	RFX_Bool(pFX, _T("[BUILDPASP]"), m_BUILDPASP);
	RFX_Bool(pFX, _T("[ICON]"), m_ICON);
	RFX_Byte(pFX, _T("[desline]"), m_desline);
	RFX_Byte(pFX, _T("[desicon]"), m_desicon);
	RFX_Byte(pFX, _T("[raster]"), m_raster);
	RFX_Bool(pFX, _T("[Digitizer]"), m_Digitizer);
	RFX_Byte(pFX, _T("[ISEXPIMP]"), m_ISEXPIMP);
	RFX_Byte(pFX, _T("[NumSqlBl]"), m_NumSqlBl);
	RFX_Byte(pFX, _T("[NumSqlLine]"), m_NumSqlLine);
	RFX_Byte(pFX, _T("[bal]"), m_bal);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// PlsizeRead diagnostics

#ifdef _DEBUG
void PlsizeRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void PlsizeRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
