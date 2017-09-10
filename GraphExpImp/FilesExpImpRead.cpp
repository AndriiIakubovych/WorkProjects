// FilesExpImpRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "FilesExpImpRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FilesExpImpRead

IMPLEMENT_DYNAMIC(FilesExpImpRead, CRecordset)

FilesExpImpRead::FilesExpImpRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(FilesExpImpRead)
	m_Id_file = 0;
	m_Id_profile = 0;
	m_Name_file = _T("");
	m_Type_graph_object = 0;
	m_Type_graph_obj = 0;
	m_Complement_areas_centers_knots = FALSE;
	m_Query_exp = _T("");
	m_Accepting_type_lines = 0;
	m_Level_lines = 0;
	m_Break_lines_segments = FALSE;
	m_Skip_superfluous_points = FALSE;
	m_Code_text = 0;
	m_Accepting_type_text = 0;
	m_Level_text = 0;
	m_Transform_denotations = 0;
	m_Type_transformed_denotations = 0;
	m_Level_denotations = 0;
	m_Size_denotations = 0.0;
	m_Import_charakteristics = FALSE;
	m_Number_field_charakteristics = 0;
	m_Accepting_type_charakteristics = 0;
	m_Level_charakteristics = 0;
	m_Height_charakteristics = 0.0;
	m_Delete_graph_object = 0;
	m_nFields = 24;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString FilesExpImpRead::GetDefaultConnect()
{
	char str[MAX_PATH], str_connection[MAX_PATH];
	GetPrivateProfileString("Supshort", "Sup", NULL, str_connection, sizeof(str_connection), IniFile);
	strcpy(str, "ODBC;DSN=");
	strcat(str, str_connection);
	return _T(str);
}

CString FilesExpImpRead::GetDefaultSQL()
{
	return _T("[FilesExpImp]");
}

void FilesExpImpRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(FilesExpImpRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Id_file]"), m_Id_file);
	RFX_Long(pFX, _T("[Id_profile]"), m_Id_profile);
	RFX_Text(pFX, _T("[Name_file]"), m_Name_file);
	RFX_Long(pFX, _T("[Type_graph_object]"), m_Type_graph_object);
	RFX_Long(pFX, _T("[Type_graph_obj]"), m_Type_graph_obj);
	RFX_Bool(pFX, _T("[Compl_areas_cent_kn]"), m_Complement_areas_centers_knots);
	RFX_Text(pFX, _T("[Query_exp]"), m_Query_exp);
	RFX_Long(pFX, _T("[Accepting_type_lines]"), m_Accepting_type_lines);
	RFX_Long(pFX, _T("[Level_lines]"), m_Level_lines);
	RFX_Bool(pFX, _T("[Break_lines_segments]"), m_Break_lines_segments);
	RFX_Bool(pFX, _T("[Skip_superfl_points]"), m_Skip_superfluous_points);
	RFX_Long(pFX, _T("[Code_text]"), m_Code_text);
	RFX_Long(pFX, _T("[Accepting_type_text]"), m_Accepting_type_text);
	RFX_Long(pFX, _T("[Level_text]"), m_Level_text);
	RFX_Long(pFX, _T("[Transform_denotation]"), m_Transform_denotations);
	RFX_Long(pFX, _T("[Type_trans_denot]"), m_Type_transformed_denotations);
	RFX_Long(pFX, _T("[Level_denotations]"), m_Level_denotations);
	RFX_Double(pFX, _T("[Size_denotations]"), m_Size_denotations);
	RFX_Bool(pFX, _T("[Import_charakter]"), m_Import_charakteristics);
	RFX_Long(pFX, _T("[Num_field_charakter]"), m_Number_field_charakteristics);
	RFX_Long(pFX, _T("[Accept_type_charakt]"), m_Accepting_type_charakteristics);
	RFX_Long(pFX, _T("[Level_charakt]"), m_Level_charakteristics);
	RFX_Double(pFX, _T("[Height_charakt]"), m_Height_charakteristics);
	RFX_Long(pFX, _T("[Delete_graph_object]"), m_Delete_graph_object);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// FilesExpImpRead diagnostics

#ifdef _DEBUG
void FilesExpImpRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void FilesExpImpRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
