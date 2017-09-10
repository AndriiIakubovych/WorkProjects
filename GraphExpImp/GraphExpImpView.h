// GraphExpImpView.h : interface of the CGraphExpImpView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHEXPIMPVIEW_H__8868322A_0D59_4CB7_9F20_05ECD244B039__INCLUDED_)
#define AFX_GRAPHEXPIMPVIEW_H__8868322A_0D59_4CB7_9F20_05ECD244B039__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphExpImpView : public CScrollView
{
protected: // create from serialization only
	CGraphExpImpView();
	DECLARE_DYNCREATE(CGraphExpImpView)

// Attributes
public:
	CGraphExpImpDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphExpImpView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphExpImpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphExpImpView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOperationsCreateProfile();
	afx_msg void OnPopupCreateProfile();
	afx_msg void OnOperationsCreateFile();
	afx_msg void OnPopupCreateFile();
	afx_msg void OnUpdateOperationsCreateFile(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateFile(CCmdUI* pCmdUI);
	afx_msg void OnOperationsCreateSample();
	afx_msg void OnPopupCreateSample();
	afx_msg void OnUpdateOperationsCreateSample(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCreateSample(CCmdUI* pCmdUI);
	afx_msg void OnOperationsEdit();
	afx_msg void OnPopupEdit();
	afx_msg void OnUpdateOperationsEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEdit(CCmdUI* pCmdUI);
	afx_msg void OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOperationsDelete();
	afx_msg void OnPopupDelete();
	afx_msg void OnUpdateOperationsDelete(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDelete(CCmdUI* pCmdUI);
	afx_msg void OnOperationsExecute();
	afx_msg void OnPopupExecute();
	afx_msg void OnUpdateOperationsExecute(CCmdUI* pCmdUI);
	afx_msg void OnUpdateExecute(CCmdUI* pCmdUI);
	afx_msg void OnExit();
	afx_msg void OnProgramHelp();
	afx_msg void OnProgramAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GraphExpImpView.cpp
inline CGraphExpImpDoc* CGraphExpImpView::GetDocument()
   { return (CGraphExpImpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHEXPIMPVIEW_H__8868322A_0D59_4CB7_9F20_05ECD244B039__INCLUDED_)
