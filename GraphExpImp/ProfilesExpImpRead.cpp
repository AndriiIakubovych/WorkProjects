// ProfilesExpImpRead.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "ProfilesExpImpRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ProfilesExpImpRead

IMPLEMENT_DYNAMIC(ProfilesExpImpRead, CRecordset)

ProfilesExpImpRead::ProfilesExpImpRead(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(ProfilesExpImpRead)
	m_Id_profile = 0;
	m_Name_profile = _T("");
	m_Number_section = 0;
	m_Group_section = 0;
	m_Path_section = _T("");
	m_Type_profile = 0;
	m_Type_source_data = 0;
	m_Folder = _T("");
	m_Factor_x = 0.0;
	m_Factor_y = 0.0;
	m_Shift_x = 0.0;
	m_Shift_y = 0.0;
	m_Turn = 0.0;
	m_Size_x = 0;
	m_Size_y = 0;
	m_Initial_order_coordinates = 0;
	m_Graph_area = FALSE;
	m_Graph_area_id = 0;
	m_Description_projection = _T("");
	m_Unit = 0;
	m_nFields = 20;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString ProfilesExpImpRead::GetDefaultConnect()
{
	char str[MAX_PATH], str_connection[MAX_PATH];
	GetPrivateProfileString("Supshort", "Sup", NULL, str_connection, sizeof(str_connection), IniFile);
	strcpy(str, "ODBC;DSN=");
	strcat(str, str_connection);
	return _T(str);
}

CString ProfilesExpImpRead::GetDefaultSQL()
{
	return _T("[ProfilesExpImp]");
}

void ProfilesExpImpRead::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(ProfilesExpImpRead)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[Id_profile]"), m_Id_profile);
	RFX_Text(pFX, _T("[Name_profile]"), m_Name_profile);
	RFX_Long(pFX, _T("[Number_section]"), m_Number_section);
	RFX_Long(pFX, _T("[Group_section]"), m_Group_section);
	RFX_Text(pFX, _T("[Path_section]"), m_Path_section);
	RFX_Long(pFX, _T("[Type_profile]"), m_Type_profile);
	RFX_Long(pFX, _T("[Type_source_data]"), m_Type_source_data);
	RFX_Text(pFX, _T("[Folder]"), m_Folder);
	RFX_Double(pFX, _T("[Factor_x]"), m_Factor_x);
	RFX_Double(pFX, _T("[Factor_y]"), m_Factor_y);
	RFX_Double(pFX, _T("[Shift_x]"), m_Shift_x);
	RFX_Double(pFX, _T("[Shift_y]"), m_Shift_y);
	RFX_Double(pFX, _T("[Turn]"), m_Turn);
	RFX_Long(pFX, _T("[Size_x]"), m_Size_x);
	RFX_Long(pFX, _T("[Size_y]"), m_Size_y);
	RFX_Long(pFX, _T("[Initial_order_coor]"), m_Initial_order_coordinates);
	RFX_Bool(pFX, _T("[Graph_area]"), m_Graph_area);
	RFX_Long(pFX, _T("[Graph_area_id]"), m_Graph_area_id);
	RFX_Text(pFX, _T("[Description_project]"), m_Description_projection);
	RFX_Long(pFX, _T("[Unit]"), m_Unit);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// ProfilesExpImpRead diagnostics

#ifdef _DEBUG
void ProfilesExpImpRead::AssertValid() const
{
	CRecordset::AssertValid();
}

void ProfilesExpImpRead::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
