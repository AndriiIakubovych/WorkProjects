#pragma once

#include "..\outgraf\grafstr.h"

#include "sqlanalyzer.h"


/////////////////////////////////////////////////////////////////////////////
// CQERecordset recordset
class CQERecordset: public CRecordNet
{
public:
	BOOL SetOnCode(int code);
	BOOL IsThereCode(int);
	virtual const CString GetCodeNameSorted(UINT sorttype);
	void RemoveHoles();
	CArray<SColInfo,SColInfo > m_ciColumns;
	BOOL MoveToCode(int code);
	virtual void SetCodeField(int code);
	BOOL FreeCodeForMe(int code);
	void AddNew();
	int Open();
	virtual void SetFromOtherSet(CQERecordset *otherSet);
	virtual void SetDefault();
	virtual const CString GetCodeNameF();
	virtual CString& GetNameField();
	int FindFreeCode(int minVal,int maxVal=-1);
	virtual DWORD GetCodeField();
	CQERecordset(CDatabNet* pDatabase, CString tableName);
	BOOL IsColumnPresent(LPCTSTR strName);

public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support

protected:
	CString m_strTable;
	BOOL m_isclloaded;
	BOOL LoadColumnsList();
};


/////////////////////////////////////////////////////////////////////////////
// CAgrsSet recordset
class CAgrsSet: public CQERecordset
{
public:
	void SetCodeField(int code);
	void SetFromOtherSet(CQERecordset *otherSet);
	void SetDefault();
	CString& GetNameField();
	DWORD GetCodeField();
	CAgrsSet(CDatabNet* pdb = NULL);
	CAgrsSet(CString &defDSN, CDatabNet* pdb = NULL);
	void SetNoSeeAgr(BOOL nsa);
	BOOL GetNoSeeAgr(BOOL& result);

	int		m_CODDOC;
	int		m_NUMAGR;
	CString	m_NAMEAGR;
	BYTE	m_TYPEAGR;
	CString	m_NROWLAST;
	CString	m_NROWFIRST;
	BOOL	m_CALCZERO;
	int		m_NCOLKEY;
	BYTE	m_NCOL_HEAD;

public:
	virtual void DoFieldExchange(CFieldExchange* pFX);
};


/////////////////////////////////////////////////////////////////////////////
// CClassesSet recordset
class CClassesSet : public CQERecordset
{
public:
	void SetCodeField(int code);
	void SetDefault();
	BOOL FixUseOrder();
	CString& GetNameField();
	DWORD GetCodeField();
	CClassesSet(CDatabNet* pDatabase = NULL);

	int		m_LISTDOC;
	CString	m_NAMELIST;
	BOOL	m_SAMEPARAM;
	int		m_USEORDER;
	BOOL	m_NOSEE;


public:
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
};


/////////////////////////////////////////////////////////////////////////////
// CColsSet recordset
class CColsSet : public CQERecordset
{
public:
	void SetCodeField(int code);
	void SetFromOtherSet(CQERecordset *otherSet);
	CString& GetNameField();
	DWORD GetCodeField();
	void SetDefault();
	void SetFilter(BYTE ftype, DWORD param);
	CColsSet(CDatabNet* pdb);
	CColsSet(CString &defConnect, CDatabNet* pdb = NULL);

	int		m_CODDOC;
	BYTE	m_NUMCOL;
	CString	m_NAMSQLCOL;
	CString	m_NAMECOL;
	CString	m_WIDTHCOL;
	BYTE	m_TYPDATA;
	CString	m_FORMAT;
	BYTE	m_TYPCENTR;
	BOOL	m_SEE;
	BYTE	m_TOBJECT;
	int		m_TYPPAR;
	BYTE	m_TYPEAGR;
	CString m_CLASSID;
	CString	m_FIELDTYPE;
    BYTE    m_TYPEREFORM;

public:
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);

protected:
	CString defSQL;
};


/////////////////////////////////////////////////////////////////////////////
// CDocsSet recordset
class CDocsSet: public CQERecordset
{
public:
	void SetCodeField(int code);
	void SetFromOtherSet(CQERecordset *otherSet);
	void SetDefault();
	const CString GetCodeNameF();
	const CString GetCodeNameSorted(UINT sorttype);
	CString& GetNameField();
	DWORD GetCodeField();
	CDocsSet(CDatabNet* pDatabase);
	CDocsSet(CString &defConnect,CDatabNet* pDatabase = NULL);
	CString m_mysort;

    int		m_CODDOC;
	CString	m_NAMEDOC;
	CString	m_NCOL_HEAD;
	CString	m_QUERYDATA;
	CString	m_QUERYHEAD;
	CString m_QUERYTITLE;
	BOOL	m_REPORT;
	BOOL	m_SEARCH;
	BOOL	m_REFER;
	BOOL	m_DSELECT;
	BYTE	m_VIDOBJ;
	BYTE	m_TYPETOPO;
	BYTE	m_CODTECH;
	BYTE	m_WHATEQ;
	BOOL	m_TRANS;
	CString	m_HFONT;
	CString	m_MINWIDCOL;
	BOOL	m_BREAKPAGE;
	BOOL	m_BREAK;
	BOOL	m_ISNUMREC;
	BOOL	m_ISREFPARAM;
	BOOL	m_CROSSTAB;
	BOOL	m_ISGOTOSEL;
	BOOL	m_LINKBAS;
    BYTE    m_PlaceTitle;

public:
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
};


/////////////////////////////////////////////////////////////////////////////
// CListsDocOnlySet recordset
class CListsDocOnlySet : public CQERecordset
{
public:
	CListsDocOnlySet(CDatabNet* pdb);

	int		m_LISTDOC;
	BYTE	m_NUMDOC;
	int		m_CODDOC;

public:
	virtual void DoFieldExchange(CFieldExchange* pFX);
};


/////////////////////////////////////////////////////////////////////////////
// CListsSet recordset
class CListsSet: public CQERecordset
{
public:
	CString& GetNameField();
	DWORD GetCodeField();
	BOOL m_isonlylistdocs;
	CListsSet(CDatabNet* pDatabase);

	int		m_CODDOC;
	CString	m_NAMEDOC;
	int		m_LISTDOC;
	BYTE	m_NUMDOC;
	int		m_CODDOC2;

public:
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
};


/////////////////////////////////////////////////////////////////////////////
// CMetaSet recordset
#define CLASSID_DOC_TYPETOPO	42
#define CLASSID_DOC_CODTECH		8
#define CLASSID_DOC_VIDOBJ		57
#define CLASSID_DOC_WHATEQ		58

#define CLASSID_COL_TYPDATA		2306
#define CLASSID_COL_TYPCENTR	2309
#define CLASSID_COL_TYPPAR		50
#define CLASSID_COL_TYPAGR		38
#define CLASSID_COL_TOBJECT		2302
#define CLASSID_COL_TRANSTYPE   3421

#define CLASSID_VAR_TYPVAR		2306
#define CLASSID_VAR_TYPECNTRL	2300

#define CLASSID_AGR_TYPEAGR		38

#define CLASSID_DATEFORM		77777

class CMetaSet: public CRecordNet
{
public:
	void SetTableField(LPCTSTR tableName, LPCTSTR fieldName);
	void SetClassID(long clID);
	CMetaSet(CDatabNet* pdb = NULL);
	CMetaSet(LPCTSTR tableName, LPCTSTR fieldName, CDatabNet* pdb = NULL);

	int		m_ClassID;
	BYTE	m_ClassValueID;
	CString	m_ClassValue;

public:
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);

protected:
	long m_clID;
	CString m_fieldName,m_tableName;
};


/////////////////////////////////////////////////////////////////////////////
// CSelsSet recordset
class CSelsSet: public CQERecordset
{
public:
	DWORD GetCodeField();
	CString& GetNameField();
	void SetDefault();
	void SetFromOtherSet(CQERecordset *otherSet);
	void SetCodeField(int code);
	CSelsSet(CDatabNet* pDatabase = NULL);

	int		m_CODDOC;
	BYTE	m_DSELECT;
	CString	m_NAMSELECT;
	CString	m_VALSELECT;

public:
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
};


/////////////////////////////////////////////////////////////////////////////
// CVarsSet recordset
class CVarsSet : public CQERecordset
{
public:
	void SetCodeField(int code);
	void SetFromOtherSet(CQERecordset *otherSet);
	CString GenerateName();
	void SetDefault();
	CString& GetNameField();
	DWORD GetCodeField();
	CVarsSet(CDatabNet* pdb = NULL);
	CVarsSet(CString &defConnect, CDatabNet* pdb = NULL);

	int		m_CODDOC;
	BYTE	m_NUMVAR;
	CString	m_CODVAR;
	CString	m_NAMEVAR;
	BYTE	m_TYPVAR;
	CString	m_FORMAT;
	BYTE	m_TYPECNTRL;
	CString	m_WIDTHCNTRL;
	CString	m_NUMCOLLIST;
	CString	m_NUMROWLIST;
	CString	m_QUERYVAR;
	CString	m_CONDITION;
	CString m_NCOLQUERY;
	CString	m_DEFVAL;
	BYTE	m_ORDERVAR;

public:
	virtual void DoFieldExchange(CFieldExchange* pFX);
};
