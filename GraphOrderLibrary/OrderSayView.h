// OrderSayView.h : interface of the COrderSayView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_ORDERSAYVIEW_H__ED8F8EE0_ED54_4454_AEAE_976B30BC3DAD__INCLUDED_)
#define AFX_ORDERSAYVIEW_H__ED8F8EE0_ED54_4454_AEAE_976B30BC3DAD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COrderSayView : public CHtmlView
{
protected: // create from serialization only
	COrderSayView();
	DECLARE_DYNCREATE(COrderSayView)

// Attributes
public:
	COrderSayDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COrderSayView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COrderSayView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COrderSayView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OrderSayView.cpp
inline COrderSayDoc* COrderSayView::GetDocument()
   { return (COrderSayDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ORDERSAYVIEW_H__ED8F8EE0_ED54_4454_AEAE_976B30BC3DAD__INCLUDED_)
