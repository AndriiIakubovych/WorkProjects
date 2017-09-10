// GraphOrderLibrary.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>

#include "GraphOrder.h"
#include "GraphOrderDoc.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "GraphOrderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static AFX_EXTENSION_MODULE GraphOrderLibraryDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("GRAPHORDERLIBRARY.DLL Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(GraphOrderLibraryDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(GraphOrderLibraryDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("GRAPHORDERLIBRARY.DLL Terminating!\n");
		// Terminate the library before destructors are called
		AfxTermExtensionModule(GraphOrderLibraryDLL);
	}
	return 1;   // ok
}

extern AFX_EXT_API void OpenGraphOrder()
{
	// Register the doc templates we provide to the app
	CGraphOrderApp* theApp = (CGraphOrderApp*)AfxGetApp();
	theApp->pDocTemplate = new CMultiDocTemplate(IDR_GraphOrderTYPE, RUNTIME_CLASS(CGraphOrderDoc), RUNTIME_CLASS(CChildFrame), RUNTIME_CLASS(CGraphOrderView));
	theApp->AddDocTemplate(theApp->pDocTemplate);
	theApp->pMainFrame = new CMainFrame;
	theApp->pMainFrame->LoadFrame(IDR_GraphOrderTYPE);
	theApp->pMainFrame->SetTitle("Заявки");
	theApp->Wnd = theApp->m_pMainWnd;
	theApp->m_pMainWnd = theApp->pMainFrame;
	CGraphOrderDoc* doc = (CGraphOrderDoc*)theApp->pDocTemplate->CreateNewDocument();
	CMainFrame* frm = (CMainFrame*)theApp->pDocTemplate->CreateNewFrame(doc, NULL);
	theApp->pDocTemplate->InitialUpdateFrame(frm, doc);
	theApp->m_pMainWnd = theApp->Wnd;
	theApp->pMainFrame->ShowWindow(theApp->m_nCmdShow);
	theApp->pMainFrame->UpdateWindow();
}