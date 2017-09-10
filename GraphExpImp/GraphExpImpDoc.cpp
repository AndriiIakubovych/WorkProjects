// GraphExpImpDoc.cpp : implementation of the CGraphExpImpDoc class
//

#include "stdafx.h"
#include "GraphExpImp.h"

#include "GraphExpImpDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpDoc

IMPLEMENT_DYNCREATE(CGraphExpImpDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphExpImpDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphExpImpDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpDoc construction/destruction

CGraphExpImpDoc::CGraphExpImpDoc()
{
	// TODO: add one-time construction code here

}

CGraphExpImpDoc::~CGraphExpImpDoc()
{
}

BOOL CGraphExpImpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpDoc serialization

void CGraphExpImpDoc::Serialize(CArchive& ar)
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
// CGraphExpImpDoc diagnostics

#ifdef _DEBUG
void CGraphExpImpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphExpImpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpDoc commands
