// OrderSayDoc.cpp : implementation of the COrderSayDoc class
//

#include "stdafx.h"
#include "OrderSay.h"

#include "OrderSayDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COrderSayDoc

IMPLEMENT_DYNCREATE(COrderSayDoc, CDocument)

BEGIN_MESSAGE_MAP(COrderSayDoc, CDocument)
	//{{AFX_MSG_MAP(COrderSayDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COrderSayDoc construction/destruction

COrderSayDoc::COrderSayDoc()
{
	// TODO: add one-time construction code here

}

COrderSayDoc::~COrderSayDoc()
{
}

BOOL COrderSayDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COrderSayDoc serialization

void COrderSayDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COrderSayDoc diagnostics

#ifdef _DEBUG
void COrderSayDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COrderSayDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COrderSayDoc commands
