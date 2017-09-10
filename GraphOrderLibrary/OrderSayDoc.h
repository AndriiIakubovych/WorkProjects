// OrderSayDoc.h : interface of the COrderSayDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORDERSAYDOC_H__7A635DE0_4A0E_4EB2_9CD7_6AEEAED9A4A1__INCLUDED_)
#define AFX_ORDERSAYDOC_H__7A635DE0_4A0E_4EB2_9CD7_6AEEAED9A4A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COrderSayDoc : public CDocument
{
protected: // create from serialization only
	COrderSayDoc();
	DECLARE_DYNCREATE(COrderSayDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrderSayDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COrderSayDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COrderSayDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDERSAYDOC_H__7A635DE0_4A0E_4EB2_9CD7_6AEEAED9A4A1__INCLUDED_)
