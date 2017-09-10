#pragma once

#include "..\outgraf\grafstr.h"
#include "..\outgraf\UniPath2.h"

#include "RQueryEdit.h"

#include "DQueryEdit.h"


/////////////////////////////////////////////////////////////////////////////
// CIQE2004Dlg dialog
#define TREEID_DOC			0xffff
#define TREEID_COL			0xffff-1
#define TREEID_VAR			0xffff-2
#define TREEID_AGR			0xffff-3
#define TREEID_DOCROOT		0xffff-4
#define TREEID_CLASSESROOT	0xffff-5
#define TREEID_CLASS		0xffff-6
#define TREEID_FORSELECTION 0xffff-7

#define TID_COL				1
#define TID_VAR				2
#define TID_AGR				3
#define TID_DOC				4
#define TID_CLASS			5
#define TID_COLFIELD		6
#define TID_VARFIELD		7
#define TID_AGRFIELD		8
#define TID_DOCROOT			9
#define TID_CLASSESROOT		10
#define TID_FSEL			11
#define TID_FSELFIELD		12


#define TOPER_UPDATED		1
#define TOPER_INSERTED		2
#define TOPER_DELETED		3
#define TOPER_SWITCHED		4

#define ID_CLASSES_STARTFROM	5000
#define ID_CLASSES_ENDTO		5200


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

protected:
	DECLARE_MESSAGE_MAP()
};

class CIQE2004Dlg : public CDialog
{
public:
	void MoveCol(DWORD coddoc, DWORD oldcode, DWORD newcode);
	void MoveClass(DWORD coddoc, DWORD oldcode, DWORD newcode);
	void DeleteSel(DWORD coddoc, DWORD numsel);
	void SmartestUpdate(HTREEITEM hPar,BOOL isSub=FALSE, BOOL bSubIfEll = FALSE);
	HTREEITEM SmartUpdateBranch(HTREEITEM hPar,CQERecordset *source);
	void SwitchCols(DWORD coddoc, DWORD firstcol, DWORD lastcol = -1);
	BYTE WhatType(HTREEITEM hItem);
	BYTE GetImageFromType(BYTE type);
	void ViewClassesProperties(DWORD ind);
	void ViewColsProperties(DWORD owner,DWORD ind);
	BOOL GetNames(LPCSTR tablename,LPCSTR fieldname,CStringList *outList);
	BOOL WhatSelected(BYTE *type,DWORD *owner,DWORD *code);
	CIQE2004Dlg(CWnd* pParent = NULL);	// standard constructor

	enum { IDD = IDD_IQE2004_DIALOG };
	CBitmapButton	m_deletebutton;
	CBitmapButton	m_addnewbutton;
	CBitmapButton	m_fieldproperties;
	CMTreeCtrl	m_tree;

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	BOOL SelectDocByCode(int code);
	UINT m_sortby;
	void MoveAgr(DWORD coddoc, DWORD oldcode, DWORD newcode);
	HTREEITEM m_hDropItem;
	BOOL GetItemInfo(HTREEITEM hItem, BYTE *type,DWORD *owner, DWORD *code);
	BOOL m_fDragging;
	DWORD m_dwDragParentCode;
	BYTE m_bDragType;
	DWORD m_dwDragSelCode;
	BOOL m_bSQLServer;
	CImageList* m_pDragList;
	void AddNewSel(DWORD coddoc,CSelsSet *propSet=NULL);
	void ViewSelsProperties(DWORD owner, DWORD ind);
	void SortMeta(CStringList& titles, DWARRAY& codes);
	SMetaInfo m_metainfo;
	void LoadMetaData();
	void RemoveAllChildren(HTREEITEM hPar);
	void CleanDoc(HTREEITEM hDoc);
	HTREEITEM FindCode(HTREEITEM hPar,DWORD code);
	void CopyDoc(int fromdoc);
	int m_classcount;
	void FillAddDocToClassMenu();
	CString m_BASETitle;
	void SwitchAgrs(DWORD coddoc,DWORD firstagr, DWORD lastagr = -1);
	CSQLAnalyzer* m_queries;
	CSQLAnalyzer* m_scrqueries; //дополнительные запросы из 14 баз
	CDatabNet *m_BASEBase;
	CString m_BASEDSN;
	void DeleteClass(DWORD numclass);
	void AddNewClass();
	void DeleteDoc(DWORD coddoc);
	long AddNewDoc(CDocsSet *propSet=NULL,long propCode=-1);
	void DeleteAgr(DWORD coddoc, DWORD numvar);
	void AddNewAgr(DWORD coddoc,CAgrsSet *propSet=NULL);
	void DeleteVar(DWORD coddoc, DWORD numvar);
	void AddNewVar(DWORD coddoc,CVarsSet *propSet=NULL,SVarInfo *varInfo=NULL);
	BYTE GetSelectedType();
	void DeleteColumn(DWORD coddoc,DWORD numcol);
	BOOL LoadBasesNames();
	void AddNewCol(DWORD coddoc,CColsSet *propSet=NULL, SColInfo *colInfo=NULL);
	void OnOK();
	HTREEITEM m_classesroot;
	HTREEITEM m_docsroot;
	void ViewDocsProperties(DWORD owner, DWORD ind, BOOL bCheckOnly = false);
	CPoint GetItemPosition(HTREEITEM hItem);
	CMenu popMenu;
	void ViewAgrsProperties(DWORD owner, DWORD ind);
	void ViewVarsProperties(DWORD owner, DWORD ind);
	CDatabNet *m_MSGBase;
	CDatabNet *m_CNBase;
	CDatabNet *m_SCRBase;
	CDatabNet *m_SUPBase;
	CString m_MSGDSN;
	CString m_CNDSN;
	int m_nregion;
	BOOL m_isClassesUseOrder;
	CToolBar m_toolbar;
	void InitTreeCtrl();
	void BuildTree();
	void InitImageList();
	CImageList m_iconslist;
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFieldproperties();
	afx_msg void OnDblclkMaintree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnItemexpandedMaintree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickMaintree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnAddNew();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeydownMaintree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnterMaintree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRebuildTree();
	afx_msg void OnEndLabelEditMainTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnImport();
	afx_msg LRESULT OnDocOptionsChanged(WPARAM, LPARAM);
	afx_msg void OnMoveDown();
	afx_msg void OnMoveUp();
	afx_msg void OnBeginrdragMaintree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAddDocToClass(UINT nID);
	afx_msg void OnBranchupdate();
	afx_msg void OnCopyDoc();
	afx_msg void OnVarsRebuild();
	afx_msg void OnHeaderSchema();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancelMode();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSortDocs(UINT nID);

    DECLARE_MESSAGE_MAP()
public:
	CString GenerateClassesListForDoc(int coddoc, int *count = NULL);
	afx_msg void OnDocsVerify();
};
