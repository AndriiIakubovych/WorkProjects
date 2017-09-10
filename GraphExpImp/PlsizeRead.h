#if !defined(AFX_PLSIZEREAD_H__782FE33B_1B37_4C98_8E04_2AB3571A47D7__INCLUDED_)
#define AFX_PLSIZEREAD_H__782FE33B_1B37_4C98_8E04_2AB3571A47D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PlsizeRead.h : header file
//

#include "stdafx.h"

/////////////////////////////////////////////////////////////////////////////
// PlsizeRead recordset

class PlsizeRead : public CRecordset
{
public:
	PlsizeRead(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(PlsizeRead)
	CString IniFile;

// Field/Param Data
	//{{AFX_FIELD(PlsizeRead, CRecordset)
	int		m_NUMREG;
	BYTE	m_PLANSHET;
	float	m_SIZX;
	float	m_SIZY;
	BYTE	m_MASKSQLEN;
	float	m_MASH;
	int		m_BSQX;
	int		m_BSQY;
	int		m_ESQX;
	int		m_ESQY;
	CString	m_ABCD;
	BYTE	m_NUMSQT;
	BYTE	m_PLANCOVER;
	BYTE	m_NUMSQ;
	BYTE	m_LENNAMPL;
	long	m_XMIN;
	long	m_YMIN;
	long	m_XMAX;
	long	m_YMAX;
	long	m_KX;
	long	m_KY;
	BYTE	m_MODEADRBLD;
	BYTE	m_LEVADR;
	BYTE	m_DRAWADR;
	BYTE	m_TYPNAMSTR;
	BYTE	m_TYPNAMREG;
	BOOL	m_ADM;
	BOOL	m_ADMSTR;
	BOOL	m_AREA;
	BOOL	m_BUILDING;
	BOOL	m_UPBASE;
	BOOL	m_BUILDPASP;
	BOOL	m_ICON;
	BYTE	m_desline;
	BYTE	m_desicon;
	BYTE	m_raster;
	BOOL	m_Digitizer;
	BYTE	m_ISEXPIMP;
	BYTE	m_NumSqlBl;
	BYTE	m_NumSqlLine;
	BYTE	m_bal;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PlsizeRead)
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

#endif // !defined(AFX_PLSIZEREAD_H__782FE33B_1B37_4C98_8E04_2AB3571A47D7__INCLUDED_)
