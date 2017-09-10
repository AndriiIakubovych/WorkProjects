#if !defined(AFX_PROFILESEXPIMPREAD_H__D4DBBBEA_0634_4B95_9B6C_12428E89AA46__INCLUDED_)
#define AFX_PROFILESEXPIMPREAD_H__D4DBBBEA_0634_4B95_9B6C_12428E89AA46__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ProfilesExpImpRead.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// ProfilesExpImpRead recordset

class ProfilesExpImpRead : public CRecordset
{
public:
	ProfilesExpImpRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(ProfilesExpImpRead)
	CString IniFile;

// Field/Param Data
	//{{AFX_FIELD(ProfilesExpImpRead, CRecordset)
	long	m_Id_profile;
	CString	m_Name_profile;
	long	m_Number_section;
	long	m_Group_section;
	CString	m_Path_section;
	long	m_Type_profile;
	long	m_Type_source_data;
	CString	m_Folder;
	double	m_Factor_x;
	double	m_Factor_y;
	double	m_Shift_x;
	double	m_Shift_y;
	double	m_Turn;
	long	m_Size_x;
	long	m_Size_y;
	long	m_Initial_order_coordinates;
	BOOL	m_Graph_area;
	long	m_Graph_area_id;
	CString m_Description_projection;
	long	m_Unit;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ProfilesExpImpRead)
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

#endif // !defined(AFX_PROFILESEXPIMPREAD_H__D4DBBBEA_0634_4B95_9B6C_12428E89AA46__INCLUDED_)
