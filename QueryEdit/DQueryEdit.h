#pragma once

#include "RQueryEdit.h"


/////////////////////////////////////////////////////////////////////////////
// CIListCtrl window
class CIListCtrl : public CListCtrl
{
public:
	CIListCtrl();

public:

	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	void AddColumn(LPCTSTR lpszName, int nWidth);
	virtual ~CIListCtrl();

protected:
	int m_count;
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CMTreeCtrl window
class CMTreeCtrl : public CTreeCtrl
{
public:
	CMTreeCtrl();

public:
	CPoint lPoint;
	virtual ~CMTreeCtrl();

protected:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()
};

/*
/////////////////////////////////////////////////////////////////////////////
// CAddNewDocDlg dialog
class CAddNewDocDlg : public CDialog
{
public:
	void SetDocsSet(CDocsSet *docsSet,int code);
	long m_doccode;
	CAddNewDocDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_DOCSLIST };
	CComboBox	m_docslist;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	int m_selcode;
	CDocsSet *m_docsset;

	virtual BOOL OnInitDialog();
	virtual void OnOK();

    DECLARE_MESSAGE_MAP()
};
*/


/////////////////////////////////////////////////////////////////////////////
// CImportDocsDlg dialog
class CImportDocsDlg : public CDialog
{
public:
	void SetDocsSet(CDocsSet *set);
	CImportDocsDlg(CWnd* pParent = NULL);
	CArray<int,int> m_doccodes;
	BOOL m_bImport;

	enum { IDD = IDD_IMPORT };
	CListBox	m_listdocsctrl;
	CButton m_OK;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	CDocsSet* m_docsset;

	virtual BOOL OnInitDialog();
	void OnOK();

    DECLARE_MESSAGE_MAP()
};


#define QE_VM_MESSAGEBOX	1
#define QE_VM_TOSTRING		2

typedef CArray<DWORD,DWORD > DWARRAY;

#define SMI_NULLVALUE	-1000

struct SMetaInfo
{
	//ƒŒ »
	CStringList m_ltypetopo;
	DWARRAY		m_ACCtypetopo;
	CStringList m_lcodtech;
	DWARRAY		m_ACCcodtech;
	CStringList m_lvidobj;
	DWARRAY		m_ACCvidobj;
	CStringList m_lwhateq;
	DWARRAY		m_ACCwhateq;
	// ŒÀŒÕ »
	CStringList m_ltypcentr;
	DWARRAY		m_ACCcentr;
	CStringList m_ltypdata;
	DWARRAY		m_ACCdat;
	CStringList m_ltyppar;
	DWARRAY		m_ACCpar;
	CStringList m_ltypobj;
	DWARRAY		m_ACCobj;
	CStringList m_ltypagrcol;
	DWARRAY		m_ACCagrcol;
	CStringList m_ldataformat;
    CStringList m_ltranstype;
    DWARRAY     m_ACCtrans;
	int			m_namewidth;
	//¿√≈√»–Œ¬¿Õ»≈
	CStringList m_ltypeagr;
	DWARRAY		m_ACCtypeagr;
	//œ≈–≈Ã≈ÕÕ€≈
	CStringList m_ltypvar;
	DWARRAY		m_ACCtypvar;
	CStringList m_ltypecntrl;
	DWARRAY		m_ACCtypctrl;
};

/////////////////////////////////////////////////////////////////////////////
// CSetDialog dialog
class CSetDialog : public CDialog
{
public:
    bool m_bNew; //15.05.17 Borys
	BOOL m_bCheckOnly;
	void OnVerify();
	CString m_verifydata;
	void SetQueries(CSQLAnalyzer *queries, CSQLAnalyzer *scrqueries = NULL);
	void SetBASEBase(CDatabNet *BASEBase);
	void SetSet(CQERecordset *set,DWORD ind);
	CSetDialog(UINT nIDTemplate, SMetaInfo* metainfo, CWnd* pParent = NULL);

	void SetMSGBase(CDatabNet *dbMSG);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	SMetaInfo *m_metainfo;
	BYTE m_verifymode;
	virtual BOOL VerifyData();
	void DoDataError(LPCTSTR mes);
	BOOL DoDataWarning(LPCTSTR mes);
	virtual void ConformDataFields();
	CSQLAnalyzer *m_queries;
	CSQLAnalyzer *m_scrqueries;
	CDatabNet* m_BASEBase;
	void OnNext();
	void OnPrev();
	CQERecordset *m_set;
	const CString FindACCBackS(DWARRAY &ar,long ind);
	long FindACC(DWARRAY &ar, LPCTSTR ind);
	BOOL m_ischanged;
	CDatabNet *m_dbMSG;
	virtual void LoadNames();
	virtual BOOL SaveData();
	virtual void LoadData();
            void OnSave(); //15.05.17 Borys
	virtual void OnOK();  //15.05.17 Borys
	virtual void OnCancel();

	long FindACCBack(DWARRAY &ar,long ind);
	long FindACC(DWARRAY &ar, long ind);

	virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CSelsDlg dialog
class CSelsDlg : public CSetDialog
{
public:
	CSelsDlg(SMetaInfo* metainfo, CWnd* pParent = NULL);

	enum { IDD = IDD_SELPROP };
	CString	m_docname;
	CString	m_namselect;
	CString	m_valselect;
	CString	m_dsel;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	BOOL SaveData();
	void LoadData();

	virtual BOOL OnInitDialog();
	afx_msg void OnNext();
	afx_msg void OnPrev();
	virtual void OnOK();
	afx_msg void OnVerify();
	afx_msg void OnSomeChanged();

    DECLARE_MESSAGE_MAP()
};


// CTablesDlg dialog
class CTablesDlg: public CDialog
{
public:
	CTablesDlg(CWnd* pParent = NULL);
	CTablesDlg(CDatabNet *MSGBase, CDatabNet *CNBase, int doccode);
	virtual ~CTablesDlg();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	CDatabNet *m_MSGBase;
	CDatabNet *m_CNBase;
	int m_nDoc;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
protected:
	void LoadMetaTables();
public:
	CListBox m_cmetatables;
protected:
	CListBox m_ctables;
public:
	afx_msg void OnBnClickedAddtable();
protected:
	void LoadTablesData();
public:
	bool IsTableAlready(int Table_ID);
	afx_msg void OnBnClickedRemovetable();
	afx_msg void OnBnClickedOk();
};


/////////////////////////////////////////////////////////////////////////////
// CListsDlg dialog
class CListsDlg : public CSetDialog
{
public:
	void AddDoc(int selcode);
	int DoModal(int flashaddcode=-1);
	CListsDlg(SMetaInfo* metainfo,CWnd* pParent = NULL);

	enum { IDD = IDD_CLASSLIST };
	CButton	m_cnoseectrl;
	CListCtrl	m_doclistctrl;
	CString	m_cnameclass;
	BOOL	m_csameparam;
	int		m_codclass;
	BOOL	m_cnosee;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	BOOL VerifyData();
	int m_flashadd;
	BOOL m_islistcreated;
	BOOL SaveData();
	void LoadData();
	void InitListCtrl();
	void ConformDataFields();

	virtual BOOL OnInitDialog();
	afx_msg void OnPrev();
	afx_msg void OnNext();
	afx_msg void OnAddDoc();
	afx_msg void OnDelCurs();
	afx_msg void OnSomethingChanged();
	//afx_msg void OnSave();
	//virtual void OnOK();
	afx_msg void OnKeydownDocslist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnItemUp();
	afx_msg void OnItemDown();

    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CAgrsDlg dialog
class CAgrsDlg : public CSetDialog
{
public:
	DWARRAY m_ACCcols;
	BOOL m_isnumrec;
	CAgrsDlg(SMetaInfo* metainfo,CWnd* pParent = NULL);   // standard constructor
	int m_docNCOL_HEAD;
	BOOL isLevelsEnabled;

	enum { IDD = IDD_AGRPROP };
	CEdit	m_clevels;
	CButton	m_cundertablectrl;
	CComboBox	m_cncolkeyctrl;
	CComboBox	m_ctypeagrctrl;
	CString	m_docname;
	CString	m_cnameagr;
	int		m_ctypeagr;
	CString	m_cnrowlast;
	CString	m_cnrowfirst;
	CString	m_numagr;
	BOOL	m_ccalczero;
	int		m_cncolkey;
	BOOL	m_cundertable;
	int		m_levels;
	BOOL	m_noseeagrexists;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	BOOL SaveData();
	void LoadNames();
	void LoadData();
	BOOL VerifyData();
	void ConformDataFields();

	virtual BOOL OnInitDialog();
	afx_msg void OnSomeChanged();
	afx_msg void OnPrev();
	afx_msg void OnNext();
	//afx_msg void OnSave();
	//virtual void OnOK();
	afx_msg void OnVerify();

    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CWaiterDlg dialog
class CWaiterDlg : public CDialog
{
public:
	CWaiterDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_WAITER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:

	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CVarsDlg dialog
class CVarsDlg : public CSetDialog
{
public:
	BOOL VerifyData();
	BYTE m_cordervar;
	CVarsDlg(SMetaInfo* metainfo, LPCTSTR datasql, CWnd* pParent = NULL);

	enum { IDD = IDD_VARPROP };
	CEdit	m_cwidthcntrlctrl;
	CEdit	m_cncolqueryctrl;
	CEdit	m_cnumrowlistctrl;
	CEdit	m_cnumcollistctrl;
	CComboBox	m_cqueryvarctrl;
	CComboBox	m_ctypecntrlctrl;
	CComboBox	m_ctypvarctrl;
	CString	m_docname;
	CString	m_numvar;
	CString	m_namevar;
	CString	m_cformat;
	CString	m_ccodvar;
	int		m_ctypvar;
	CString	m_ccondition;
	CString	m_cdefval;
	int		m_ctypecntrl;
	CString	m_cqueryvar;
	CString	m_cnumcollist;
	CString	m_cnumrowlist;
	CString	m_cwidthcntrl;
	CString	m_cncolquery;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	void ConformDataFields();
	CString m_datasql;
	BOOL SaveData();
	void LoadData();
	void LoadNames();

	virtual BOOL OnInitDialog();
	afx_msg void OnPrev();
	afx_msg void OnNext();
	afx_msg void OnSomeChanged();
	//afx_msg void OnSave();
	//virtual void OnOK();
	afx_msg void OnVerify();
	afx_msg void OnSelchangeTypVar();

    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CQuickSearchDlg dialog
class CQuickSearchDlg : public CDialog
{
public:
	CQuickSearchDlg(CTreeCtrl *tree, CWnd* pParent = NULL);

	CListCtrl	m_fulllistctrl;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	void FillListFromTreeBranch(HTREEITEM hFirst,int &curInd);
	void FillListFromTree();
	CTreeCtrl *m_tree;

	virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
};


struct SHeader
{
	CString m_lpzName;
	int		m_nWidth;
};

/////////////////////////////////////////////////////////////////////////////
// CHeaderSchemaDlg dialog
class CHeaderSchemaDlg : public CDialog
{
public:
	CHeaderSchemaDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_HEADERSCHEMA };
	CIListCtrl	m_header;

	CArray<SHeader,SHeader> m_columns;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CColsDlg dialog
class CColsDlg: public CSetDialog
{
public:
	int m_colindex;
	CString m_cfieldtype;
	CColsDlg(SMetaInfo* metainfo,CDocsSet *dset,CWnd* pParent = NULL);

	enum { IDD = IDD_COLPROP };
	CComboBox	m_cvidobjctrl;
	CComboBox	m_ctranstypectrl;
	CComboBox	m_cdataformatctrl;
	CEdit	m_cclassidctrl;
	CEdit	m_cformatctrl;
	CEdit	m_cwidthctrl;
	CComboBox	m_cquerynamectrl;
	CEdit	m_cnamectrl;
	CComboBox	m_ctypagrctrl;
	CComboBox	m_ctypobjctrl;
	CComboBox	m_ctypparctrl;
	CComboBox	m_ctypdatactrl;
	CComboBox	m_ctypcentrctrl;
	CString	m_cname;
	CString	m_cwidth;
	CString	m_cformat;
	int		m_ctypcentr;
	int		m_ctyppar;
	int		m_ctypobj;
	int		m_ctypdata;
	int		m_ctypagr;
	BOOL	m_cvisible;
	CString	m_docname;
	CString	m_queryname;
	CString	m_cclassid;
	CString	m_cdataformat;
	int		m_ctranstype;
	int		m_numcol;
	BOOL	m_isreport;		//ÂÒÎË ˝ÚÓ ÓÚ˜ÂÚ ÚÓ ÌÓ‚˚È ÚËÔ ÍÓÎÓÌÍË "ÔÂÂıÓ‰ Í Ó·˙ÂÍÚÛ" = 10
	int		m_cvidobj;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	BOOL m_dontdodata;
	BOOL m_isisnumrecpres;
	CDocsSet *m_dset;
	BOOL VerifyData();
	void ConformDataFields();
	CString m_datasql;
	void LoadNames();
	BOOL SaveData();
	void LoadData();

	virtual BOOL OnInitDialog();
	afx_msg void OnPrev();
	afx_msg void OnNext();
	//afx_msg void OnSave();
	//afx_msg void OnOK();
	afx_msg void OnSomeFieldChanged();
	afx_msg void OnQueryNameChange();
	afx_msg void OnSelchangeQueryname();
	afx_msg void OnVisibleChange();
	afx_msg void OnVerify();
	afx_msg void OnChangeDataType();
	afx_msg void OnDropDownQueryName();

    DECLARE_MESSAGE_MAP()
};


#define DOCOPT_VARSREBUILD	1
#define DOCOPT_ISNUMREC		2

/////////////////////////////////////////////////////////////////////////////
// CDocsDlg dialog
//05.05.17 Borys
class CQueryCombo: public CComboBox
{
public:
    int AddString(CString cQName, bool b14);

    CStatic m_st;

    int SetStaticText();
};

class CDocsDlg : public CSetDialog
{
public:
	CDocsDlg(SMetaInfo* metainfo, CDatabNet *bMSG, CDatabNet *bCN, CWnd* pParent = NULL);
   ~CDocsDlg();

	enum { IDD = IDD_DOCPROP };
	CButton	m_cisgotoselctrl;
	CButton	m_cisnumrecctrl;
	CButton	m_cbreakpagectrl;
	CButton	m_ctransctrl;
	CButton	m_cbreakctrl;
	CEdit	m_chfontctrl;
	CEdit	m_cminwidcolctrl;
	CEdit	m_cncolheadctrl;

    CQueryCombo	m_cqueryheadctrl;
	CQueryCombo	m_cquerydatactrl;
	CQueryCombo	m_cquerytitlectrl;
	CButton	m_cptitlectrl;

    CComboBox	m_cwhateqctrl;
	CComboBox	m_cvidobjctrl;
	CComboBox	m_ccodtechctrl;
	CComboBox	m_ctypetopoctrl;
	CToolTipCtrl *m_pToolTip;
	CString	m_ccoddoc;
	CString	m_cnamedoc;
	CString	m_cquerydata;
	CString	m_cqueryhead;
	CString	m_cncolhead;
	CString	m_cminwidcol;
	CString m_classeslist;
	int		m_classescount;
	BOOL	m_ctrans;
	BOOL	m_cbreakepage;
	CString	m_chfont;
	int		m_ctypetopo;
	int		m_ccodtech;
	int		m_cvidobj;
	int		m_cwhateq;
	BOOL	m_crefer;
	BOOL	m_creport;
	BOOL	m_csearch;
	BOOL	m_cselection;
	BOOL	m_cisnumrec;
	BOOL	m_cbreak;
	BOOL	m_linkbas;
	CString	m_cquerytitle;
	BOOL	m_cisgotosel;
    BOOL    m_cptitle;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	BOOL m_ccrosstab;
	BOOL VerifyData();
	void ConformDataFields();
	BOOL SaveData();
	void LoadData();
	void LoadNames();
	CDatabNet *m_MSGBase;
	CDatabNet *m_CNBase;

	virtual BOOL OnInitDialog();
	afx_msg void OnPrev();
	afx_msg void OnNext();
	//afx_msg void OnSave();
	//virtual void OnOK();
	afx_msg void OnSomethingChanged();
	afx_msg void OnQueryDataChanged();
	afx_msg void OnVerify();
	afx_msg void OnDropdownQuerydata();

    DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_classesctrl;
	afx_msg void OnBnClickedTables();
	CButton m_clinkbas;
	CButton m_ctables;
};


