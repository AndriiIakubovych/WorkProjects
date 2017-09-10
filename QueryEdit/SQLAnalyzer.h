// SQLAnalyzer.h: interface for the CSQLAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "i:\CiWin5\bibuni6\sqlx.h"

#define QE_TRANS_NEEDALL	1
#define QE_TRANS_NEEDCOLS	2
#define QE_TRANS_NEEDVARS	3

#define SQLMODE_DAO 0
#define SQLMODE_SQL 1

struct SColInfo
{
	CString m_strName;
	int		m_iSize;
	short   m_sType;
	short	m_sMetaType;
	short	m_sMetaClassID;
	CString m_strDescr;
};

struct SVarInfo
{
	CString m_strName;
	short m_sType;
	CString m_strValue;
	short m_sTimes;
};

typedef CArray<SColInfo,SColInfo > COLARRAY;
typedef CArray<SVarInfo,SVarInfo > VARARRAY;

class CSQLAnalyzer
{
public:
	void CloseBase();
	int FindCol(LPCTSTR colName);
	void Reload();
	short CalcTimesSubstr(LPCTSTR str, LPCTSTR substr);
	BOOL LoadMetaForCol(int colindex);
	BOOL LoadMetaForCol(LPCTSTR colname, int *ind = NULL);
	CString GetMetaFieldString(LPCTSTR strTable,LPCTSTR strField,LPCTSTR strType);
	BOOL IsStandartName(CString &name);
	void TranslateSQL(BYTE whatNeed=QE_TRANS_NEEDALL);
	BOOL FindName(LPCTSTR name);
	CString m_strName;
	BOOL	m_bcrosstab;
	COLARRAY m_ciCols;
	VARARRAY m_viVars;
	void MoveAt(UINT index);
	BOOL IsBOF();
	BOOL IsEOF();
	void MovePrev();
	void MoveNext();
	void MoveLast();
	void MoveFirst();
	CSQLAnalyzer(CDatabNet *base, int mode = SQLMODE_DAO);
	virtual ~CSQLAnalyzer();

protected:
	int m_mode;
	//SQL variants
	void Init_SQL();

protected:
	CString bname;
	CDaoQueryDef *m_curquery;
	BOOL GetMetaFieldVariant(LPCTSTR strTable, LPCTSTR strField, LPCTSTR strType, COleVariant *var);
	long GetMetaField(LPCTSTR strTable,LPCTSTR strField,LPCTSTR strType);
	short TranslateTypeCol(short type);
	void LoadData();
	void LoadData_SQL();
	int m_index;
	int m_qcount;
	CStringArray m_SQLs;
	CDaoDatabase m_daobase;
	CDatabNet *m_base;
};
