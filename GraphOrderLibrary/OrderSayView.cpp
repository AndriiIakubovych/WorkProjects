// OrderSayView.cpp : implementation of the COrderSayView class
//

#include "stdafx.h"
#include "OrderSay.h"

#include "OrderSayDoc.h"
#include "OrderSayView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrderSayView

IMPLEMENT_DYNCREATE(COrderSayView, CHtmlView)

BEGIN_MESSAGE_MAP(COrderSayView, CHtmlView)
	//{{AFX_MSG_MAP(COrderSayView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrderSayView construction/destruction

COrderSayView::COrderSayView()
{
	// TODO: add construction code here

}

COrderSayView::~COrderSayView()
{
}

BOOL COrderSayView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COrderSayView drawing

void COrderSayView::OnDraw(CDC* pDC)
{
	COrderSayDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void COrderSayView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	char buffer[MAX_PATH];
	CString WorkFolder;
	GetCurrentDirectory(MAX_PATH, buffer);
	WorkFolder = buffer;
	if (_access(WorkFolder + "\\OrderSay.html", 0))
		Navigate2(WorkFolder + "\\OrderSay.htm", NULL, NULL);
	else
		Navigate2(WorkFolder + "\\OrderSay.html", NULL, NULL);
}

/////////////////////////////////////////////////////////////////////////////
// COrderSayView diagnostics

#ifdef _DEBUG
void COrderSayView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void COrderSayView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

COrderSayDoc* COrderSayView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COrderSayDoc)));
	return (COrderSayDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COrderSayView message handlers


int COrderSayView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CHtmlView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	GetParentFrame()->SetWindowText("Информация о заявке");
	
	return 0;
}
