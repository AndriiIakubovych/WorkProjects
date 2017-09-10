// GraphExpImp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "GraphExpImp.h"

#include "MainFrm.h"
#include "GraphExpImpDoc.h"
#include "GraphExpImpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpApp

BEGIN_MESSAGE_MAP(CGraphExpImpApp, CWinApp)
	//{{AFX_MSG_MAP(CGraphExpImpApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpApp construction

CGraphExpImpApp::CGraphExpImpApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGraphExpImpApp object

CGraphExpImpApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpApp initialization

BOOL CGraphExpImpApp::InitInstance()
{
	AfxEnableControlContainer();

	char cValue[128];
	GetPrivateProfileString("SupShort", "Lang", "rus", cValue, 127, ".\\svisor.ini");
	CString cLang = cValue;
	HMODULE hGraphExpImpRes = AfxLoadLibrary("GraphExpImp." + cLang);
	if (hGraphExpImpRes == NULL)
	{
		AfxMessageBox("Resource dll 'GraphExpImp." + cLang + "' was not found.");
		return false;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	#ifdef _AFXDLL
		Enable3dControls();			// Call this when using MFC in a shared DLL
	#else
		Enable3dControlsStatic();	// Call this when linking to MFC statically
	#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(IDR_MAINFRAME, RUNTIME_CLASS(CGraphExpImpDoc), RUNTIME_CLASS(CMainFrame), RUNTIME_CLASS(CGraphExpImpView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpApp message handlers

