// GraphExpImpDoc.h : interface of the CGraphExpImpDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHEXPIMPDOC_H__0FAFA2D1_F68D_489A_82A8_9279E740E50F__INCLUDED_)
#define AFX_GRAPHEXPIMPDOC_H__0FAFA2D1_F68D_489A_82A8_9279E740E50F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGraphExpImpDoc : public CDocument
{
protected: // create from serialization only
	CGraphExpImpDoc();
	DECLARE_DYNCREATE(CGraphExpImpDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphExpImpDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CGraphExpImpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphExpImpDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHEXPIMPDOC_H__0FAFA2D1_F68D_489A_82A8_9279E740E50F__INCLUDED_)
