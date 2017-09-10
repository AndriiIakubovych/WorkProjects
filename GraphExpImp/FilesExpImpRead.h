#if !defined(AFX_FILESEXPIMPREAD_H__7B68DE72_54BF_41B8_A82F_83960CDE822A__INCLUDED_)
#define AFX_FILESEXPIMPREAD_H__7B68DE72_54BF_41B8_A82F_83960CDE822A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FilesExpImpRead.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// FilesExpImpRead recordset

class FilesExpImpRead : public CRecordset
{
public:
	FilesExpImpRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(FilesExpImpRead)
	CString IniFile;

// Field/Param Data
	//{{AFX_FIELD(FilesExpImpRead, CRecordset)
	long	m_Id_file;
	long	m_Id_profile;
	CString	m_Name_file;
	long	m_Type_graph_object;
	long	m_Type_graph_obj;
	BOOL	m_Complement_areas_centers_knots;
	CString	m_Query_exp;
	long	m_Accepting_type_lines;
	long	m_Level_lines;
	BOOL	m_Break_lines_segments;
	BOOL	m_Skip_superfluous_points;
	long	m_Code_text;
	long	m_Accepting_type_text;
	long	m_Level_text;
	long	m_Transform_denotations;
	long	m_Type_transformed_denotations;
	long	m_Level_denotations;
	double	m_Size_denotations;
	BOOL	m_Import_charakteristics;
	long	m_Number_field_charakteristics;
	long	m_Accepting_type_charakteristics;
	long	m_Level_charakteristics;
	double	m_Height_charakteristics;
	long	m_Delete_graph_object;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FilesExpImpRead)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESEXPIMPREAD_H__7B68DE72_54BF_41B8_A82F_83960CDE822A__INCLUDED_)
