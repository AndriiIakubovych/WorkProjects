#include "stdafx.h"

#include "i:\CiWin5\bibuni6\MetaGlob.h"
#include "IQE2004.h"

#include "IQE2004Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIQE2004Dlg dialg
CIQE2004Dlg::CIQE2004Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIQE2004Dlg::IDD, pParent)
{
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_bSQLServer = false;
	m_queries = NULL,m_scrqueries = NULL;
}

void CIQE2004Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DELETE, m_deletebutton);
	DDX_Control(pDX, IDC_ADDNEW, m_addnewbutton);
	DDX_Control(pDX, IDC_FIELDPROPERTIES, m_fieldproperties);
	DDX_Control(pDX, IDC_MAINTREE, m_tree);
}

BEGIN_MESSAGE_MAP(CIQE2004Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FIELDPROPERTIES, OnFieldproperties)
	ON_NOTIFY(NM_DBLCLK, IDC_MAINTREE, OnDblclkMaintree)
	ON_WM_DESTROY()
	ON_NOTIFY(TVN_ITEMEXPANDED, IDC_MAINTREE, OnItemexpandedMaintree)
	ON_NOTIFY(NM_RCLICK, IDC_MAINTREE, OnRclickMaintree)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_ADDNEW, OnAddNew)
	ON_WM_SIZE()
	ON_NOTIFY(TVN_KEYDOWN, IDC_MAINTREE, OnKeydownMaintree)
	ON_NOTIFY(NM_RETURN, IDC_MAINTREE, OnEnterMaintree)
	ON_COMMAND(ID_REBUILDTREE, OnRebuildTree)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_MAINTREE, OnEndLabelEditMainTree)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_COMMAND(ID_IMPORT, OnImport)
	ON_MESSAGE(MES_DOCOPTIONSCHANGED,OnDocOptionsChanged)
	ON_COMMAND(IDC_MOVEDOWN, OnMoveDown)
	ON_COMMAND(IDC_MOVEUP, OnMoveUp)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_MAINTREE, OnBeginrdragMaintree)
	ON_COMMAND_RANGE(ID_CLASSES_STARTFROM,ID_CLASSES_ENDTO,OnAddDocToClass)
	ON_COMMAND(ID_BRANCHUPDATE, OnBranchupdate)
	ON_COMMAND(IDC_COPYDOC, OnCopyDoc)
	ON_COMMAND(IDS_VARSREBUILD, OnVarsRebuild)
	ON_COMMAND_RANGE(ID_SORTCODE, ID_SORTTYPE, OnSortDocs)
//	ON_COMMAND(ID_HEADERSCHEMA, OnHeaderSchema)
	ON_WM_TIMER()
	ON_WM_CANCELMODE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DOCS_VERIFY, &CIQE2004Dlg::OnDocsVerify)
END_MESSAGE_MAP()

BOOL CIQE2004Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	srand( (unsigned)time( NULL ) );

	if(!LoadBasesNames())
	{
		AfxMessageBox(IDS_CANTINITBASES);
		EndDialog(IDCANCEL);
		return FALSE;
	}

    bool bSplash = false;
    CWaiterDlg *waitDialog = NULL;
    if(bSplash)
    {
        waitDialog = new CWaiterDlg;
        waitDialog->Create(IDD_WAITER,this);
        waitDialog->ShowWindow(true);
        waitDialog->RedrawWindow();
    }

	BeginWaitCursor();

	CString title;
	title.Format(_T("Редактор документов - %s (%s)"),m_BASETitle,m_BASEDSN);
	SetWindowText(title);

	m_CNBase = GetCurDB(REGION_TYPE_CONST);
	m_MSGBase = GetCurDB(REGION_TYPE_MSG);
	m_BASEBase = GetCurDB(REGION_TYPE_BASE);
	m_SCRBase = GetCurDB(REGION_TYPE_SCR);
	m_SUPBase = GetCurDB(REGION_TYPE_SUP);

	//Checking is it SQL connection
	CString DBMSName;
	short size;
	SQLGetInfo(m_BASEBase->m_hdbc, SQL_DBMS_NAME, DBMSName.GetBuffer(100), 100, &size);
	DBMSName.ReleaseBuffer();
	if(DBMSName == "Microsoft SQL Server")
		m_bSQLServer = true;

	m_queries=new CSQLAnalyzer(m_BASEBase, m_bSQLServer?SQLMODE_SQL:SQLMODE_DAO);

	if(m_BASEBase != m_SCRBase)
		m_scrqueries = new CSQLAnalyzer(m_SCRBase);
	else
		m_scrqueries = NULL;

	popMenu.LoadMenu(IDR_RBMENU);
	
	InitImageList();
	InitTreeCtrl();

	m_sortby = ID_SORTCODE;
	LoadMetaData();
	BuildTree();
	
	m_fieldproperties.LoadBitmaps(IDB_PROP,IDB_PROPANTI);
	m_addnewbutton.LoadBitmaps(IDB_ADDNEW,IDB_ADDNEWANTI);
	m_deletebutton.LoadBitmaps(IDB_DELETE,IDB_DELETEANTI);

	m_classcount=0;

	EndWaitCursor();

    if(bSplash)
    {
        waitDialog->ShowWindow(false);
        waitDialog->DestroyWindow();
        delete waitDialog;
    }

	m_fDragging = FALSE;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CIQE2004Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
		CDialog::OnSysCommand(nID, lParam);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIQE2004Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIQE2004Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIQE2004Dlg::InitImageList()
{
	m_iconslist.Create(20,20,ILC_MASK,0,4);
	m_iconslist.Add(AfxGetApp()->LoadIcon(IDI_DOC));	//0
	m_iconslist.Add(AfxGetApp()->LoadIcon(IDI_COLUMN));	//1
	m_iconslist.Add(AfxGetApp()->LoadIcon(IDI_VAR));	//2
	m_iconslist.Add(AfxGetApp()->LoadIcon(IDI_AGR));	//3
	m_iconslist.Add(AfxGetApp()->LoadIcon(IDI_CLASS));	//4
	m_iconslist.Add(AfxGetApp()->LoadIcon(IDI_SEL));	//5
}

void CIQE2004Dlg::BuildTree()
{
	m_tree.DeleteAllItems();

	RedrawWindow();

	m_classesroot=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
			_T("Классы документов"), 4, 4, 0, 0, TREEID_CLASSESROOT, NULL, NULL);
	m_docsroot=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
			_T("Документы"), 0, 0, 0, 0, TREEID_DOCROOT, NULL, NULL);

	//сторим дерево классов
	CClassesSet clset(m_CNBase);
	clset.Open();
	m_isClassesUseOrder = FALSE;
	if(clset.FixUseOrder())
		clset.Requery();
	if(clset.isField("useorder") != -1)
		m_isClassesUseOrder = TRUE;
	while(!clset.IsEOF())
	{
		m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
			clset.GetCodeNameF(), 4, 4, 0, 0, clset.m_LISTDOC, m_classesroot, NULL);
		clset.MoveNext();
	}
	clset.Close();

	//строим дерево докуметов
	CDocsSet cds(m_CNBase);
	switch(m_sortby)
	{
		case(ID_SORTCODE):cds.m_mysort = "CODDOC";break;
		case(ID_SORTNAME):cds.m_mysort = "NAMEDOC";break;
		case(ID_SORTQUERY):cds.m_mysort = "QUERYDATA";break;
		case(ID_SORTTYPE):cds.m_mysort = "REPORT*8+SEARCH*4+REFER*2+DSELECT,CODDOC";break;
	}
	cds.m_strSort = cds.m_mysort;
	cds.Open();

	while(!cds.IsEOF())
	{
		HTREEITEM htdoc=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
			cds.GetCodeNameSorted(m_sortby), 0, 0, 0, 0, cds.m_CODDOC, m_docsroot, NULL);
		HTREEITEM htcols=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
			_T("Колонки"), 1, 1, 0, 0, DWORD(cds.m_CODDOC<<16)+TREEID_COL, htdoc,NULL);
		HTREEITEM htvars=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
			_T("Переменные"), 2, 2, 0, 0, DWORD(cds.m_CODDOC<<16)+TREEID_VAR, htdoc,NULL);
		HTREEITEM htagrs=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
			_T("Агрегирования"), 3, 3, 0, 0, DWORD(cds.m_CODDOC<<16)+TREEID_AGR, htdoc,NULL);

		cds.MoveNext();

	}
	cds.Close();


}

void CIQE2004Dlg::InitTreeCtrl()
{
	m_tree.SetImageList(&m_iconslist,TVSIL_NORMAL);
//	m_tree.SetBkColor(RGB(255,255,255));
}

BOOL CIQE2004Dlg::WhatSelected(BYTE *type,DWORD *owner, DWORD *code)
{
	HTREEITEM hPar,hItem=m_tree.GetSelectedItem();
	if(hItem==NULL)
		return FALSE;
	DWORD pdat,dat=m_tree.GetItemData(hItem);
	switch(dat&0xffff)
	{
	case(TREEID_DOCROOT):if(type)*type=TID_DOCROOT;return TRUE;
	case(TREEID_CLASSESROOT):if(type)*type=TID_CLASSESROOT;return TRUE;
	case(TREEID_COL):if(type)*type=TID_COL;if(owner)*owner=dat>>16;return TRUE;
	case(TREEID_VAR):if(type)*type=TID_VAR;if(owner)*owner=dat>>16;return TRUE;
	case(TREEID_AGR):if(type)*type=TID_AGR;if(owner)*owner=dat>>16;return TRUE;
	case(TREEID_FORSELECTION):if(type)*type=TID_FSEL;if(owner)*owner=dat>>16;return TRUE;
		
	default:
		hPar=m_tree.GetParentItem(hItem);
		if(hPar==NULL)
			return FALSE;
		pdat=m_tree.GetItemData(hPar);
		switch(pdat&0xffff)
		{
		case(TREEID_COL):if(type)*type=TID_COLFIELD;break;
		case(TREEID_VAR):if(type)*type=TID_VARFIELD;break;
		case(TREEID_AGR):if(type)*type=TID_AGRFIELD;break;
		case(TREEID_FORSELECTION):if(type)*type=TID_FSELFIELD;break;
		case(TREEID_DOCROOT):if(type)*type=TID_DOC;break;
		case(TREEID_CLASSESROOT):if(type)*type=TID_CLASS;break;
		}
		if(owner)*owner=pdat>>16;
		if(code)*code=dat&0xffff;
		return TRUE;
	}
	return FALSE;
}

void CIQE2004Dlg::OnDblclkMaintree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnFieldproperties();	
	*pResult = 0;
}

BOOL CIQE2004Dlg::GetNames(LPCSTR tablename, LPCSTR fieldname, CStringList *outList)
{
	return TRUE;
}

void CIQE2004Dlg::OnDestroy() 
{
	CDialog::OnDestroy();

	if(m_queries)
		delete m_queries;
	if(m_scrqueries)
		delete m_scrqueries;
	
	DoneCurBases();

}

void CIQE2004Dlg::OnItemexpandedMaintree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	if(pNMTreeView->action==2)
		if(WhatType(pNMTreeView->itemNew.hItem)==TID_DOC)
			SmartestUpdate(pNMTreeView->itemNew.hItem,true);
		else;
	else
		if(WhatType(pNMTreeView->itemNew.hItem)==TID_DOC)
			CleanDoc(pNMTreeView->itemNew.hItem);

	*pResult = 0;
}

void CIQE2004Dlg::OnRclickMaintree(NMHDR* pNMHDR, LRESULT* pResult)
{
	BYTE selType;
	DWORD selOwner,selCode;

	WhatSelected(&selType,&selOwner,&selCode);

	CMenu *menu=NULL;
	
	switch(selType)
	{
	case(TID_DOC):menu=popMenu.GetSubMenu(0);
		FillAddDocToClassMenu();
		break;
	case(TID_COLFIELD):		menu = popMenu.GetSubMenu(1 );break;
	case(TID_VARFIELD):		menu = popMenu.GetSubMenu(2 );break;
	case(TID_AGRFIELD):		menu = popMenu.GetSubMenu(3 );break;
	case(TID_FSELFIELD):	menu = popMenu.GetSubMenu(10);break;
	case(TID_FSEL):			menu = popMenu.GetSubMenu(11);break;
	case(TID_CLASS):		menu = popMenu.GetSubMenu(4 );break;
	case(TID_DOCROOT):		menu = popMenu.GetSubMenu(5 );break;
	case(TID_CLASSESROOT):	menu = popMenu.GetSubMenu(6 );break;
	case(TID_COL):			menu = popMenu.GetSubMenu(7 );break;
	case(TID_VAR):			menu = popMenu.GetSubMenu(8 );break;
	case(TID_AGR):			menu = popMenu.GetSubMenu(9 );break;
	}

	if(menu)
		menu->TrackPopupMenu(TPM_LEFTALIGN |TPM_RIGHTBUTTON, m_tree.lPoint.x, 
			m_tree.lPoint.y, this);

	*pResult = 0;
}

CPoint CIQE2004Dlg::GetItemPosition(HTREEITEM hItem)
{
	CPoint point;
	CRect rect;
	m_tree.GetItemRect(hItem,rect,TRUE);
	point=rect.TopLeft();

	return point;
}

void CIQE2004Dlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(m_fDragging)
	{
		m_pDragList->DragLeave(this);

		CPoint tvpoint = point;
		ClientToScreen(&tvpoint);
		m_tree.ScreenToClient(&tvpoint);

		BYTE type;
		DWORD code,owner;

        if ((m_hDropItem = m_tree.HitTest(tvpoint, &nFlags)) != NULL)
		{
			GetItemInfo(m_hDropItem,&type,&owner,&code);
			if(type == m_bDragType && owner == m_dwDragParentCode)
				m_tree.SelectDropTarget(m_hDropItem);
		}

		m_pDragList->DragEnter(this, point + CPoint(20,20));
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CIQE2004Dlg::OnOK()
{
	OnFieldproperties();
}

void CIQE2004Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(rect);
	if(IsWindowVisible())
		m_tree.SetWindowPos(&CWnd::wndBottom,0,0,rect.Width(),rect.Height(),SWP_NOZORDER);
}

void CIQE2004Dlg::OnKeydownMaintree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;

	switch(pTVKeyDown->wVKey)
	{
	case(32):m_tree.Expand(m_tree.GetSelectedItem(),TVE_TOGGLE);break;
	case(45):OnAddNew();break;
	case(46):OnDelete();break;
	}
	*pResult = 0;
}

void CIQE2004Dlg::OnEnterMaintree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CIQE2004Dlg::OnRebuildTree() 
{
	CWaiterDlg *waitDialog=new CWaiterDlg;
	//запоминаем что было выбрано
	DWORD owner, code;
	WhatSelected(NULL, &owner, &code);

	waitDialog->Create(IDD_WAITER,this);
	waitDialog->ShowWindow(true);
	waitDialog->RedrawWindow();

	BeginWaitCursor();

	BuildTree();
	m_tree.Expand(m_docsroot, TVE_EXPAND);
	SelectDocByCode(owner?owner:code);

	EndWaitCursor();

	waitDialog->ShowWindow(false);
	waitDialog->DestroyWindow();
	delete waitDialog;
}

void CIQE2004Dlg::OnEndLabelEditMainTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	BYTE selType;
	DWORD selOwner,selCode;
	
	WhatSelected(&selType,&selOwner,&selCode);

	*pResult = 0;
}

BOOL CIQE2004Dlg::PreTranslateMessage(MSG* pMsg) 
{
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CIQE2004Dlg::LoadBasesNames()
{
	CDatabNet supBase;
/*	if(InitPath2(&supBase)!=1)
	{
		AfxMessageBox("Ошибка открытия sup");
		return FALSE;
	}*/
	if(InitCurBases()!=1)
	{
		AfxMessageBox(_T("Ошибка открытия sup"));
		return FALSE;
	}
	
	m_CNDSN=GetCurRegDSN(3);
	m_BASEDSN=GetCurRegDSN(4);
	m_BASETitle=GetCurRegName(4);
	m_MSGDSN=GetCurRegDSN(0);
	
//	supBase.Close();

	return TRUE;
}

BYTE CIQE2004Dlg::GetSelectedType()
{
	BYTE selType=-1;
	DWORD selOwner,selCode;
	WhatSelected(&selType,&selOwner,&selCode);
	return selType;
}

BYTE CIQE2004Dlg::GetImageFromType(BYTE type)
{
	return 0;
}

BYTE CIQE2004Dlg::WhatType(HTREEITEM hItem)
{
	HTREEITEM hPar;
	if(hItem==NULL)
		return FALSE;
	DWORD pdat,dat=m_tree.GetItemData(hItem);
	switch(dat&0xffff)
	{
	case(TREEID_DOCROOT):return TID_DOCROOT;
	case(TREEID_CLASSESROOT):return TID_CLASSESROOT;
	case(TREEID_COL):return TID_COL;
	case(TREEID_VAR):return TID_VAR;
	case(TREEID_AGR):return TID_AGR;
	case(TREEID_FORSELECTION):return TID_FSEL;
	default:
		hPar=m_tree.GetParentItem(hItem);
		if(hPar==NULL)
			return FALSE;
		pdat=m_tree.GetItemData(hPar);
		switch(pdat&0xffff)
		{
		case(TREEID_COL):return TID_COLFIELD;
		case(TREEID_VAR):return TID_VARFIELD;
		case(TREEID_AGR):return TID_AGRFIELD;
		case(TREEID_FORSELECTION): return TID_FSELFIELD;
		case(TREEID_DOCROOT):return TID_DOC;
		case(TREEID_CLASSESROOT):return TID_CLASS;
		}
	}
	return 0;
}

void CIQE2004Dlg::OnImport() 
{
	m_tree.SelectItem(m_docsroot);

	CDatabNet impBase;
	TRY
	{
	if(!impBase.Open(_T(""),FALSE,TRUE,_T("ODBC;"),FALSE))
		return;
	}
	CATCH(CDBException,e)
	{
		AfxMessageBox(_T("Ошибка открытия базы данных"));
		return;
	}
	END_CATCH

	CDocsSet dset(&impBase);
	dset.m_strSort="CODDOC";

	TRY
	{
	if(!dset.Open())
	{
		AfxMessageBox(_T("Ошибка открытия или в базе нет таблицы \"descrdoc\""));
		impBase.Close();
		return;
	}
	}
	CATCH(CDBException,e)
	{
		AfxMessageBox(_T("Ошибка открытия или в базе нет таблицы \"descrdoc\""));
		impBase.Close();
		return;
	}
	END_CATCH

	long localdoccode=-1;

	CImportDocsDlg impdlg;
	impdlg.SetDocsSet(&dset);
	impdlg.m_bImport = TRUE;
	if(impdlg.DoModal()==IDOK)
	{
		for(int dnom=0;dnom<impdlg.m_doccodes.GetSize();dnom++)
		{
			long doccode=impdlg.m_doccodes[dnom];
			dset.MoveToCode(doccode);
			CDocsSet dorset(m_CNBase);
			dorset.m_strFilter.Format(_T("CODDOC=%d"),doccode);
			//Проверка наличия документа с таким же кодом
			dorset.Open();

			if(!dorset.IsEOF())
				doccode=-1;

			dorset.Close();

			CString mes;
			mes.Format(_T("Документа с таким кодом %d уже существует. Разрешить подобрать свободный индекс?"),impdlg.m_doccodes[dnom]);

			if(doccode!=-1 ||
				(AfxMessageBox(mes,MB_YESNO)==IDYES))
				localdoccode=AddNewDoc(&dset,doccode);

			if(doccode==-1 && localdoccode!=-1)
			{
				CString mes;
				mes.Format(_T("Подобранный код - %d"),localdoccode);
				AfxMessageBox(mes);
			}

			if(localdoccode!=-1)
			{

				doccode=impdlg.m_doccodes[dnom];

				CColsSet cset(&impBase);
				cset.m_strFilter.Format(_T("CODDOC=%d"),doccode);
				cset.Open();
				while(!cset.IsEOF())
				{
					AddNewCol(localdoccode,&cset);
					cset.MoveNext();
				}

				cset.Close();
			
				CVarsSet vset(&impBase);
				vset.m_strFilter.Format(_T("CODDOC=%d"),doccode);
				vset.Open();
				while(!vset.IsEOF())
				{
					AddNewVar(localdoccode,&vset);
					vset.MoveNext();
				}

				vset.Close();

				CAgrsSet aset(&impBase);
				aset.m_strFilter.Format(_T("CODDOC=%d"),doccode);
				aset.Open();
				while(!aset.IsEOF())
				{
					AddNewAgr(localdoccode,&aset);
					aset.MoveNext();
				}

				aset.Close();

				CSelsSet sset(&impBase);
				sset.m_strFilter.Format(_T("CODDOC=%d"),doccode);
				sset.Open();
				while(!sset.IsEOF())
				{
					AddNewSel(localdoccode,&sset);
					sset.MoveNext();
				}

				sset.Close();

				SmartestUpdate(m_docsroot);

				HTREEITEM hDoc=FindCode(m_docsroot,localdoccode);

				SmartestUpdate(hDoc,TRUE);

				m_tree.SelectItem(hDoc);
			}
		}
	}

	dset.Close();

	impBase.Close();
}

LRESULT CIQE2004Dlg::OnDocOptionsChanged(WPARAM coddoc, LPARAM docopt)
{
	CDocsSet dset(m_CNBase);
	dset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	dset.Open();

	CString query=dset.m_QUERYDATA;
	BOOL isOnlySelection=((dset.m_DSELECT || dset.m_BREAK)&& !dset.m_REFER && !dset.m_REPORT && !dset.m_SEARCH);
	BOOL isNeedNum=(dset.m_REFER || dset.m_SEARCH);
	BOOL isNumRec=dset.m_ISNUMREC;

	dset.Close();

	CString SQL;

	if(docopt&DOCOPT_ISNUMREC)
	{		
		CString SQL;
		if(isNumRec)
			SQL.Format(_T("UPDATE descragr SET ncolkey=ncolkey+1 WHERE (coddoc=%d) AND (ncolkey is not null);"),coddoc);
		else
			SQL.Format(_T("UPDATE descragr SET ncolkey=ncolkey-1 WHERE (coddoc=%d) AND (ncolkey is not null);"),coddoc);
		m_CNBase->ExecuteSQL(SQL);
	}

	CSQLAnalyzer *curqueries;
	if(!m_queries->FindName(query) && m_scrqueries && m_scrqueries->FindName(query))
		curqueries = m_scrqueries;
	else
		curqueries = m_queries;

	if(docopt&DOCOPT_VARSREBUILD)
	{
		SQL.Format(_T("DELETE FROM variable WHERE CODDOC=%d"),coddoc);
		m_CNBase->ExecuteSQL(SQL);


		HTREEITEM varItem=m_tree.GetNextSiblingItem(m_tree.GetChildItem(FindCode(m_docsroot,coddoc)));
		
		SmartestUpdate(varItem);

		if(curqueries->FindName(query))
		{
			curqueries->TranslateSQL();
			for(int i=0;i<curqueries->m_viVars.GetSize();i++)
			{
				AddNewVar(coddoc,NULL,&curqueries->m_viVars[i]);
			}
			SmartestUpdate(varItem);

			if(curqueries->FindCol(_T("num"))==-1)
				isNeedNum = false;
		}
	}
	else
		//необходима проверка на необоходимость поля нум
	{
		if(curqueries->FindName(query))
		{
			curqueries->TranslateSQL();
			if(curqueries->FindCol(_T("num"))==-1)
				isNeedNum = false;
		}
	}

	//удаление всех колонок
	if(isOnlySelection)
	{
		SQL.Format(_T("DELETE FROM descrcol WHERE CODDOC=%d"),coddoc);
		m_CNBase->ExecuteSQL(SQL);

		HTREEITEM varItem=m_tree.GetChildItem(m_tree.GetSelectedItem());
		
		SmartestUpdate(varItem);

	}

	//необходио добавить поле num (если еще нет)
	if(isNeedNum)
	{
		CColsSet cset(m_CNBase);
		cset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
		cset.Open();

		while(!cset.IsEOF())
		{
			if(cset.m_NAMSQLCOL.CompareNoCase(_T("num"))==0)
				isNeedNum=false;
			cset.MoveNext();
		}

		if(isNeedNum)
		{
			SColInfo ci;
			ci.m_strName="num";
			ci.m_strDescr="Номер (добавлено автоматически)";
			ci.m_sType=2;
			AddNewCol(coddoc,NULL,&ci);

			HTREEITEM colItem=m_tree.GetChildItem(FindCode(m_docsroot,coddoc));
			cset.RequeryNet();
			SmartUpdateBranch(colItem,&cset);
		}

		cset.Close();
	}
	m_tree.RedrawWindow();

	return 0;
}

void CIQE2004Dlg::SwitchCols(DWORD coddoc, DWORD firstcol, DWORD lastcol)
{
	CColsSet cset(m_CNBase);
	cset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	cset.Open();

	while(!cset.IsEOF())
	{
		if(cset.m_NUMCOL==firstcol)
			break;
		cset.MoveNext();
	}

	if(!cset.IsEOF())
	{
		do{
			cset.MoveNext();
		}while(!cset.IsEOF() && lastcol != -1 && cset.m_NUMCOL != lastcol);
		if(!cset.IsEOF())
		{
			DWORD secondcol=cset.m_NUMCOL;
			do{
				cset.MovePrev();
			}while(cset.m_NUMCOL != firstcol);

			m_CNBase->BeginTrans();

			//редактируем первую
			cset.Edit();
			cset.m_NUMCOL=255;
			cset.UpdateNet(0);

			//вторую
			do{
				cset.MoveNext();
			}while(lastcol != -1 && cset.m_NUMCOL != lastcol);
			cset.Edit();
			cset.m_NUMCOL=(BYTE)firstcol;
			cset.UpdateNet(0);

			//снова первую
			do{
				cset.MovePrev();
			}while(cset.m_NUMCOL != 255);
			cset.Edit();
			cset.m_NUMCOL=(BYTE)secondcol;
			cset.UpdateNet(0);

			m_CNBase->CommitTrans();

			cset.RequeryNet();

			SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&cset);

		}
	}

	cset.Close();
}

void CIQE2004Dlg::OnMoveDown() 
{
	BYTE selType;
	DWORD selOwner;
	DWORD selInd;
	if(!WhatSelected(&selType,&selOwner,&selInd))
		return;
	switch(selType)
	{
	case(TID_COLFIELD):SwitchCols(selOwner,selInd);break;
	case(TID_AGRFIELD):SwitchAgrs(selOwner,selInd);break;
	}
	
	HTREEITEM nextItem=m_tree.GetNextSiblingItem(m_tree.GetSelectedItem());
	if(nextItem)
		m_tree.SelectItem(nextItem);
}

void CIQE2004Dlg::OnMoveUp()
{
	HTREEITEM prevItem=m_tree.GetPrevSiblingItem(m_tree.GetSelectedItem());
	if(prevItem==NULL)
		return;
	m_tree.SelectItem(prevItem);
	BYTE selType;
	DWORD selOwner;
	DWORD selInd;
	if(!WhatSelected(&selType,&selOwner,&selInd))
		return;
	
	switch(selType)
	{
	case(TID_COLFIELD):SwitchCols(selOwner,selInd);break;
	case(TID_AGRFIELD):SwitchAgrs(selOwner,selInd);break;
	}

};

void CIQE2004Dlg::SwitchAgrs(DWORD coddoc, DWORD firstagr, DWORD lastagr)
{
	CAgrsSet aset(m_CNBase);
	aset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	aset.Open();

	while(!aset.IsEOF())
	{
		if(aset.m_NUMAGR==firstagr)
			break;
		aset.MoveNext();
	}

	if(!aset.IsEOF())
	{
		do{
			aset.MoveNext();
		}while(!aset.IsEOF() && lastagr != -1 && aset.m_NUMAGR != lastagr);
		if(!aset.IsEOF())
		{
			DWORD secondagr=aset.m_NUMAGR;
			do{
				aset.MovePrev();
			}while(aset.m_NUMAGR != firstagr);

			m_CNBase->BeginTrans();

			//редактируем первую
			aset.Edit();
			aset.m_NUMAGR=255;
			aset.UpdateNet(0);

			//вторую
			do{
				aset.MoveNext();
			}while(lastagr != -1 && aset.m_NUMAGR != lastagr);
			aset.Edit();
			aset.m_NUMAGR=(BYTE)firstagr;
			aset.UpdateNet(0);

			//снова первую
			do{
				aset.MovePrev();
			}while(aset.m_NUMAGR != 255);
			aset.Edit();
			aset.m_NUMAGR=(BYTE)secondagr;
			aset.UpdateNet(0);

			m_CNBase->CommitTrans();

			aset.RequeryNet();

			SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&aset);

		}
	}

	aset.Close();
}

void CIQE2004Dlg::OnBeginrdragMaintree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	GetItemInfo(pNMTreeView->itemNew.hItem,&m_bDragType,&m_dwDragParentCode,&m_dwDragSelCode);

	if(m_bDragType != TID_COLFIELD && m_bDragType != TID_AGRFIELD && (m_bDragType != TID_CLASS || !m_isClassesUseOrder))
	{
		*pResult = 0;
		return;
	}

	m_pDragList = m_tree.CreateDragImage(pNMTreeView->itemNew.hItem);

	CPoint point = pNMTreeView->ptDrag;

	DWORD dwLevel = pNMTreeView->itemNew.lParam; 
    DWORD dwIndent = (DWORD) m_tree.SendMessage(TVM_GETINDENT, 0, 0);

	m_pDragList->BeginDrag(0,CPoint(0,0));
	m_pDragList->DragEnter(this, point + CPoint(20,20));

	m_tree.SelectItem(NULL);

    SetCapture();
    m_fDragging = TRUE;
	
	*pResult = 0;
}

void CIQE2004Dlg::FillAddDocToClassMenu()
{
	CMenu *menu=popMenu.GetSubMenu(0);
	for(int i=ID_CLASSES_STARTFROM;i<ID_CLASSES_STARTFROM+m_classcount;i++)
	{
		menu->RemoveMenu(i,MF_BYCOMMAND);
	}

	CClassesSet cset(m_CNBase);
	cset.Open();
	m_classcount=0;
	cset.MoveFirst();

	while(!cset.IsEOF())
	{
		menu->InsertMenu(ID_DOCS_BLANKLAST,MF_BYCOMMAND,
			ID_CLASSES_STARTFROM+m_classcount,cset.m_NAMELIST);
		cset.MoveNext();
		m_classcount++;
	}
	cset.Close();
}

void CIQE2004Dlg::OnAddDocToClass(UINT nID)
{
	int coddoc=m_tree.GetItemData(m_tree.GetSelectedItem());
	CClassesSet clset(m_CNBase);
	clset.Open();
	clset.MoveFirst();
	for(int i=0;i<nID-ID_CLASSES_STARTFROM;i++)
		clset.MoveNext();

	CListsDlg ldlg(&m_metainfo);
	ldlg.SetSet(&clset,clset.GetCodeField());
	ldlg.SetMSGBase(m_MSGBase);
	ldlg.SetQueries(m_queries);
	ldlg.DoModal(coddoc);

	SmartUpdateBranch(m_classesroot,&clset);

	clset.Close();
}

HTREEITEM CIQE2004Dlg::SmartUpdateBranch(HTREEITEM hPar, CQERecordset *source)
{
	HTREEITEM hItem=m_tree.GetChildItem(hPar);
	CString __temp = m_tree.GetItemText(hItem);

	if(!(source->IsEOF() && source->IsBOF()))
		source->MoveFirst();
	int coditem,codsource;

	HTREEITEM hLastItem=TVI_FIRST,hRetItem=NULL;

	int imNom,imsNom;
	m_tree.GetItemImage(hPar,imNom,imsNom);

	while(hItem!=NULL || !source->IsEOF())
	{
		coditem=(hItem==NULL)?-1:m_tree.GetItemData(hItem);
		codsource=(source->IsEOF())?-1:source->GetCodeField();
		if(coditem==codsource)
		//if(coditem!=-1 && codsource!=-1 && source->GetCodeNameSorted(m_sortby).Compare(m_tree.GetItemText(hItem))==0)
		//равны, просто обновить надпись
		{
				m_tree.SetItemText(hItem,source->GetCodeNameSorted(m_sortby));
		}
		//else if(coditem==-1 || (coditem>codsource && codsource!=-1))
		//else if(coditem==-1 || (source->GetCodeNameSorted(m_sortby).Compare(m_tree.GetItemText(hItem))<0 && codsource!=-1))
		else if(coditem==-1 || (codsource!=-1 && source->IsThereCode(coditem)))
		//в соурсе есть элемент кот. надо добавить
		{
			if(WhatType(hPar)==TID_DOCROOT)
			{
				hRetItem=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
					source->GetCodeNameSorted(m_sortby), imNom, imsNom, 0, 0, source->GetCodeField(), hPar,hLastItem);
				HTREEITEM htcols=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
					_T("Колонки"), 1, 1, 0, 0, DWORD(source->GetCodeField()<<16)+TREEID_COL, hRetItem,NULL);
				HTREEITEM htvars=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
					_T("Переменные"), 2, 2, 0, 0, DWORD(source->GetCodeField()<<16)+TREEID_VAR, hRetItem,NULL);
				HTREEITEM htagrs=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
					_T("Агрегирования"), 3, 3, 0, 0, DWORD(source->GetCodeField()<<16)+TREEID_AGR, hRetItem,NULL);
			}		
			else
				hRetItem=m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
					source->GetCodeNameF(), imNom, imsNom, 0, 0, source->GetCodeField(), hPar,hLastItem);
			hItem=hRetItem;
		}
		//else if(codsource==-1 ||(codsource>coditem && coditem!=-1))
		//else if(codsource==-1 ||(source->GetCodeNameSorted(m_sortby).Compare(m_tree.GetItemText(hItem))>0 && coditem!=-1))
		else if(codsource==-1 || (coditem!=-1 && !source->IsThereCode(coditem)))
		//есть лишний элемент - удалить
		{
			m_tree.DeleteItem(hItem);
			hItem=hLastItem;
			if(!source->IsBOF())
				source->MovePrev();
		}
		if(hItem!=NULL)
		{
			hLastItem=hItem;
			if(hItem==TVI_FIRST)
				hItem=m_tree.GetChildItem(hPar);
			else
				hItem=m_tree.GetNextSiblingItem(hItem);
		}
		if(!source->IsEOF())
			source->MoveNext();
	}

	return hRetItem;
}

void CIQE2004Dlg::OnBranchupdate() 
{
	BeginWaitCursor();
	SmartestUpdate(m_tree.GetSelectedItem(),TRUE);
	EndWaitCursor();
}

void CIQE2004Dlg::OnCopyDoc()
{
	CopyDoc(m_tree.GetItemData(m_tree.GetSelectedItem()));
}

void CIQE2004Dlg::CopyDoc(int fromdoc)
{
	CDocsSet dset(m_CNBase);
	dset.m_strFilter.Format(_T("CODDOC=%d"),fromdoc);
	dset.Open();

	if(dset.IsEOF())
	{
		dset.Close();
		return;
	}

	int localdoccode=AddNewDoc(&dset);

	CColsSet cset(m_CNBase);
	cset.m_strFilter.Format(_T("CODDOC=%d"),fromdoc);
	cset.Open();
	while(!cset.IsEOF())
	{
		AddNewCol(localdoccode,&cset);
		cset.MoveNext();
	}
	cset.Close();

	CVarsSet vset(m_CNBase);
	vset.m_strFilter.Format(_T("CODDOC=%d"),fromdoc);
	vset.Open();
	while(!vset.IsEOF())
	{
		AddNewVar(localdoccode,&vset);
		vset.MoveNext();
	}
	vset.Close();

	CAgrsSet aset(m_CNBase);
	aset.m_strFilter.Format(_T("CODDOC=%d"),fromdoc);
	aset.Open();
	while(!aset.IsEOF())
	{
		AddNewAgr(localdoccode,&aset);
		aset.MoveNext();
	}
	aset.Close();

	CSelsSet sset(m_CNBase);
	sset.m_strFilter.Format(_T("CODDOC=%d"),fromdoc);
	sset.Open();
	while(!sset.IsEOF())
	{
		AddNewSel(localdoccode,&sset);
		sset.MoveNext();
	}
	sset.Close();

	CListsSet lset(m_CNBase);
	lset.m_strFilter.Format(_T("listdocs.CODDOC=%d AND listdocs.CODDOC=descrdoc.CODDOC"),fromdoc);
	lset.Open();
	CString SQL;
	DWARRAY ar;   //список списков :)
	DWARRAY arn;  //список позиций в списках
	while(!lset.IsEOF())
	{
		ar.Add(lset.m_LISTDOC);
		arn.Add(lset.m_NUMDOC);
		lset.MoveNext();
	}
	lset.Close();

	for(int i=0;i<ar.GetSize();i++)
	{
		lset.m_strFilter.Format(_T("LISTDOC=%d AND listdocs.CODDOC=descrdoc.CODDOC"),ar[i]);
		lset.Open();
		int newcode=lset.FindFreeCode(arn[i]);
		lset.Close();
		SQL.Format(_T("INSERT INTO listdocs VALUES (%d,%d,%d)"),ar[i],newcode,localdoccode);
		m_CNBase->ExecuteSQL(SQL);
	}

	SmartestUpdate(m_docsroot);
	HTREEITEM hDoc=FindCode(m_docsroot,localdoccode);
	SmartestUpdate(hDoc,TRUE);
	m_tree.SelectItem(hDoc);
}

void CIQE2004Dlg::SmartestUpdate(HTREEITEM hPar, BOOL isSub, BOOL bSubIfEll)
{
	if(hPar==NULL)
		return;
	HTREEITEM hParPar=m_tree.GetParentItem(hPar);
	int coddoc=-1;
	if(hParPar!=NULL)
		coddoc=m_tree.GetItemData(hParPar);
	switch(WhatType(hPar))
	{
	case(TID_COL):
		{
			CColsSet cset(m_CNBase);
			cset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
			cset.Open();
			SmartUpdateBranch(hPar,&cset);
			cset.Close();
		}
		break;
	case(TID_COLFIELD):break;
	case(TID_VAR):
		{
			CVarsSet vset(m_CNBase);
			vset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
			vset.Open();
			SmartUpdateBranch(hPar,&vset);
			vset.Close();
		}
		break;
	case(TID_VARFIELD):break;
	case(TID_AGR):
		{
			CAgrsSet aset(m_CNBase);
			aset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
			aset.Open();
			SmartUpdateBranch(hPar,&aset);
			aset.Close();
		}
		break;
	case(TID_AGRFIELD):break;
	case(TID_DOC):
		{
			CDocsSet dset(m_CNBase);
			DWORD coddoc = m_tree.GetItemData(hPar);
			dset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
			dset.Open();
			if(dset.m_DSELECT || dset.m_BREAK)
			{
				if(!FindCode(hPar, DWORD(coddoc<<16) + TREEID_FORSELECTION))
				{
					HTREEITEM hItem = m_tree.InsertItem(TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_PARAM,
						_T("Условия выделения"), 5, 5, 0, 0, DWORD(coddoc<<16) + TREEID_FORSELECTION, hPar,NULL);
					SmartestUpdate(hItem);
				}
			}
			else
			{
				HTREEITEM hSel=FindCode(hPar,DWORD(coddoc<<16) + TREEID_FORSELECTION);
				if(hSel)
					m_tree.DeleteItem(hSel);
			}
			dset.Close();
		}
		break;
	case(TID_FSEL):
		{
			CSelsSet sset(m_CNBase);
			sset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
			sset.Open();
			SmartUpdateBranch(hPar,&sset);
			sset.Close();
		}
		break;
	case(TID_DOCROOT):
		{
			CDocsSet dset(m_CNBase);
			switch(m_sortby)
			{
				case(ID_SORTCODE):dset.m_mysort = "CODDOC";break;
				case(ID_SORTNAME):dset.m_mysort = "NAMEDOC";break;
				case(ID_SORTQUERY):dset.m_mysort = "QUERYDATA";break;
				case(ID_SORTTYPE):dset.m_mysort = "REPORT*8+SEARCH*4+REFER*2+DSELECT,CODDOC";break;
			}
			dset.m_strSort = dset.m_mysort;
			dset.Open();
			SmartUpdateBranch(hPar,&dset);
			dset.Close();
		}
		break;
	case(TID_CLASS):break;
	case(TID_CLASSESROOT):
		{
			CClassesSet clset(m_CNBase);
			clset.Open();
			SmartUpdateBranch(hPar,&clset);
			clset.Close();
		}
		break;
	}

	if(isSub)
	{
		HTREEITEM hChild=m_tree.GetChildItem(hPar);
		while(hChild)
		{
			if(!bSubIfEll || (m_tree.GetItemState(hChild,TVIS_EXPANDED)&&TVIS_EXPANDED))
			{
				SmartestUpdate(hChild,isSub,bSubIfEll);
			}
			hChild=m_tree.GetNextSiblingItem(hChild);
		}
	}
}

HTREEITEM CIQE2004Dlg::FindCode(HTREEITEM hPar, DWORD code)
{
	HTREEITEM hChild=m_tree.GetChildItem(hPar);
	while(hChild)
	{
		if(m_tree.GetItemData(hChild)==code)
			return hChild;
		hChild=m_tree.GetNextSiblingItem(hChild);
	}
	return NULL;
}

void CIQE2004Dlg::CleanDoc(HTREEITEM hDoc)
{
	HTREEITEM hMidRoot=m_tree.GetChildItem(hDoc);
	RemoveAllChildren(hMidRoot);
	hMidRoot=m_tree.GetNextSiblingItem(hMidRoot);
	RemoveAllChildren(hMidRoot);
	hMidRoot=m_tree.GetNextSiblingItem(hMidRoot);
	RemoveAllChildren(hMidRoot);
}

void CIQE2004Dlg::RemoveAllChildren(HTREEITEM hPar)
{
	HTREEITEM hChild=m_tree.GetChildItem(hPar),hNext;
	while(hChild)
	{
		hNext=m_tree.GetNextSiblingItem(hChild);
		m_tree.DeleteItem(hChild);
		hChild=hNext;
	}
}

void CIQE2004Dlg::LoadMetaData()
{
	//ДЛЯ ДОКУМЕНТОВ

	CMetaSet cms(m_MSGBase);
	cms.SetClassID(CLASSID_DOC_TYPETOPO);
	sOpen(&cms,1);
	m_metainfo.m_ltypetopo.RemoveAll();
	m_metainfo.m_ltypetopo.AddTail(_T(""));
	m_metainfo.m_ACCtypetopo.Add(SMI_NULLVALUE);
	while(!cms.IsEOF())
	{
		m_metainfo.m_ltypetopo.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCtypetopo.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	cms.SetClassID(CLASSID_DOC_CODTECH);
	cms.Open();
	m_metainfo.m_lcodtech.RemoveAll();
	m_metainfo.m_lcodtech.AddTail(_T(""));
	m_metainfo.m_ACCcodtech.Add(SMI_NULLVALUE);
	while(!cms.IsEOF())
	{
		m_metainfo.m_lcodtech.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCcodtech.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	cms.SetClassID(CLASSID_DOC_VIDOBJ);
	cms.Open();
	m_metainfo.m_lvidobj.RemoveAll();
	m_metainfo.m_lvidobj.AddTail(_T(""));
	m_metainfo.m_ACCvidobj.Add(SMI_NULLVALUE);
	while(!cms.IsEOF())
	{
		m_metainfo.m_lvidobj.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCvidobj.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	cms.SetClassID(CLASSID_DOC_WHATEQ);
	cms.Open();
	m_metainfo.m_lwhateq.RemoveAll();
	m_metainfo.m_lwhateq.AddTail(_T(""));
	m_metainfo.m_ACCwhateq.Add(SMI_NULLVALUE);
	while(!cms.IsEOF())
	{
		m_metainfo.m_lwhateq.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCwhateq.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	SortMeta(m_metainfo.m_lwhateq,m_metainfo.m_ACCwhateq);

	//ДЛЯ КОЛОНОК

	cms.SetClassID(CLASSID_COL_TYPCENTR);
	cms.Open();
	m_metainfo.m_ltypcentr.RemoveAll();
	while(!cms.IsEOF())
	{
		m_metainfo.m_ltypcentr.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCcentr.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	cms.SetClassID(CLASSID_COL_TYPDATA);
	cms.Open();
	m_metainfo.m_ltypdata.RemoveAll();
	while(!cms.IsEOF())
	{
		m_metainfo.m_ltypdata.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCdat.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	cms.SetClassID(CLASSID_COL_TYPPAR);
	cms.Open();
	m_metainfo.m_ltyppar.RemoveAll();
	m_metainfo.m_ltyppar.AddTail(_T(""));
	m_metainfo.m_ACCpar.Add(SMI_NULLVALUE);
	while(!cms.IsEOF())
	{
		m_metainfo.m_ltyppar.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCpar.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	cms.SetClassID(CLASSID_COL_TOBJECT);
	cms.Open();
	m_metainfo.m_ltypobj.RemoveAll();
	while(!cms.IsEOF())
	{
		m_metainfo.m_ltypobj.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCobj.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	cms.SetClassID(CLASSID_COL_TYPAGR);
	cms.Open();
	m_metainfo.m_ltypagrcol.RemoveAll();
	while(!cms.IsEOF())
	{
		//замечание Задачина от 16.07.2007 - не включать пункт "индивидуальное по колонкам"
		//в дальнейшем потребовать заведения отдельного классивикатора для этого
		//комбо-бокса
		if(cms.m_ClassValueID == 0)
		{
			cms.MoveNext();
			continue;
		}

		m_metainfo.m_ltypagrcol.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCagrcol.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	cms.SetClassID(CLASSID_DATEFORM);
	cms.Open();
	m_metainfo.m_ldataformat.RemoveAll();
	while(!cms.IsEOF())
	{
		m_metainfo.m_ldataformat.AddTail(cms.m_ClassValue);
		cms.MoveNext();
	}
	cms.Close();

    cms.SetClassID(CLASSID_COL_TRANSTYPE);
    cms.Open();
	m_metainfo.m_ltranstype.RemoveAll();
    while(!cms.IsEOF())
	{
		m_metainfo.m_ltranstype.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCtrans.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
    cms.Close();

	//загрузка дополнительной информации о колонке
	CRecordset set(m_SUPBase);
	CDBVariant var;
	CString SQL;
	SQL.Format(_T("SELECT FieldLen FROM MetaField WHERE Table_ID=28 AND Field_ID=4 AND NUMREG=%d"), GetCurRegNum(3));
	set.Open(CRecordset::forwardOnly, SQL);
	
	if(!set.IsEOF())
	{
		set.GetFieldValue(_T("FieldLen"), var);
		m_metainfo.m_namewidth = var.m_chVal;
	}
	else
		m_metainfo.m_namewidth = -1;

	//ДЛЯ АГРЕГИРОВАНИЙ

	cms.SetClassID(CLASSID_AGR_TYPEAGR);
	cms.Open();
	while(!cms.IsEOF())
	{
		m_metainfo.m_ltypeagr.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCtypeagr.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	//ДЛЯ ПЕРЕМЕННЫХ

	cms.SetClassID(CLASSID_VAR_TYPVAR);
	cms.Open();
	while(!cms.IsEOF())
	{
		m_metainfo.m_ltypvar.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCtypvar.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();

	cms.SetClassID(CLASSID_VAR_TYPECNTRL);
	cms.Open();
	while(!cms.IsEOF())
	{
		m_metainfo.m_ltypecntrl.AddTail(cms.m_ClassValue);
		m_metainfo.m_ACCtypctrl.Add(cms.m_ClassValueID);
		cms.MoveNext();
	}
	cms.Close();
}

void CIQE2004Dlg::OnVarsRebuild() 
{
	BeginWaitCursor();
	DWORD coddoc;
	WhatSelected(NULL,&coddoc,NULL);
	OnDocOptionsChanged(coddoc,DOCOPT_VARSREBUILD);
	EndWaitCursor();
}

void CIQE2004Dlg::OnHeaderSchema() 
{
	BYTE selType;
	DWORD selOwner;
	DWORD selInd;
	if(!WhatSelected(&selType,&selOwner,&selInd))
		return;

	CColsSet ccs(m_CNBase);
	ccs.m_strFilter.Format(_T("CODDOC=%d"),selOwner);
	ccs.Open();

	CHeaderSchemaDlg sdlg;

	SHeader sh;
	while(!ccs.IsEOF())
	{
		if(ccs.m_SEE)
		{
			sh.m_lpzName=ccs.m_NAMECOL;
			sh.m_nWidth=_ttoi(ccs.m_WIDTHCOL);
			sdlg.m_columns.Add(sh);
		}
		ccs.MoveNext();
	}

	ccs.Close();

	if(sdlg.DoModal()==IDOK)
	{
	}
}

void CIQE2004Dlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==ID_UPDATEONCETIMER)
	{
		SmartestUpdate(m_classesroot);
		KillTimer(nIDEvent);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CIQE2004Dlg::OnCancelMode() 
{
	CDialog::OnCancelMode();
}

void CIQE2004Dlg::SortMeta(CStringList &titles, DWARRAY &codes)
{
	BOOL modify=TRUE;
	int ind;
	while(modify)
	{
		modify=FALSE;
		CString sA,sB;
		DWORD dC;
		ind=0;
		for(POSITION pos=titles.GetHeadPosition();pos!=NULL;)
		{
			POSITION posnext=pos;
			sA=titles.GetNext(posnext);
			if(posnext==NULL)
				break;
			sB=titles.GetAt(posnext);
			if(sA.CompareNoCase(sB)>0)
				//начать процесс обмена
			{
				titles.SetAt(pos,sB);
				titles.SetAt(posnext,sA);

				dC=codes[ind+1];
				codes[ind+1]=codes[ind];
				codes[ind]=dC;

				modify=TRUE;
			}
			ind++;
			pos=posnext;
		}
	}
}	

void CIQE2004Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_fDragging)
	{
		m_pDragList->DragLeave(this);
		m_pDragList->EndDrag();
        ReleaseCapture();
        m_fDragging = FALSE; 
		delete m_pDragList;

		m_tree.SelectDropTarget(NULL);
		m_tree.SelectItem(m_hDropItem);
		m_tree.RedrawWindow();
		

		BYTE selType;
		DWORD selOwner;
		DWORD selInd;
		if(WhatSelected(&selType,&selOwner,&selInd))
		{
			if(selInd != m_dwDragSelCode)
			{
				switch(selType)
				{
				case(TID_COLFIELD):	MoveCol(m_dwDragParentCode,m_dwDragSelCode,selInd+1);break;
				case(TID_AGRFIELD):	MoveAgr(m_dwDragParentCode,m_dwDragSelCode,selInd+1);break;
				case(TID_CLASS):	MoveClass(m_dwDragParentCode,m_dwDragSelCode,selInd);break;
				}	
			}
		}

	}	
	CDialog::OnLButtonUp(nFlags, point);
}

BOOL CIQE2004Dlg::GetItemInfo(HTREEITEM hItem, BYTE *type, DWORD *owner, DWORD *code)
{
	HTREEITEM hPar;
	if(hItem==NULL)
		return FALSE;
	DWORD pdat,dat=m_tree.GetItemData(hItem);
	switch(dat&0xffff)
	{
	case(TREEID_DOCROOT):if(type)*type=TID_DOCROOT;return TRUE;
	case(TREEID_CLASSESROOT):if(type)*type=TID_CLASSESROOT;return TRUE;
	case(TREEID_COL):if(type)*type=TID_COL;if(owner)*owner=dat>>16;return TRUE;
	case(TREEID_VAR):if(type)*type=TID_VAR;if(owner)*owner=dat>>16;return TRUE;
	case(TREEID_AGR):if(type)*type=TID_AGR;if(owner)*owner=dat>>16;return TRUE;
	case(TREEID_FORSELECTION):if(type)*type=TID_FSEL;if(owner)*owner=dat>>16;return TRUE;
		
	default:
		hPar=m_tree.GetParentItem(hItem);
		if(hPar==NULL)
			return FALSE;
		pdat=m_tree.GetItemData(hPar);
		switch(pdat&0xffff)
		{
		case(TREEID_COL):if(type)*type=TID_COLFIELD;break;
		case(TREEID_VAR):if(type)*type=TID_VARFIELD;break;
		case(TREEID_AGR):if(type)*type=TID_AGRFIELD;break;
		case(TREEID_FORSELECTION):if(type)*type=TID_FSELFIELD;break;
		case(TREEID_DOCROOT):if(type)*type=TID_DOC;break;
		case(TREEID_CLASSESROOT):if(type)*type=TID_CLASS;break;
		}
		if(owner)*owner=pdat>>16;
		if(code)*code=dat&0xffff;
		return TRUE;
	}
	return FALSE;
}

void CIQE2004Dlg::MoveCol(DWORD coddoc, DWORD oldcode, DWORD newcode)
{
	CColsSet cset(m_CNBase);
	cset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	cset.Open();

	m_CNBase->BeginTrans();

	if(!cset.MoveToCode(oldcode))
	{
		cset.Close();
		return;
	}

	cset.Edit();
	cset.m_NUMCOL = 255;
	cset.UpdateNet(0);
	cset.Requery();

	if(!cset.FreeCodeForMe(newcode))
	{
		cset.Close();
		return;
	}

	cset.MoveToCode(255);


	cset.Edit();
	cset.m_NUMCOL = newcode;

	cset.UpdateNet(0);

	m_CNBase->CommitTrans();

	cset.Requery();

	cset.RemoveHoles();
	

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&cset);

	cset.Close();
}

void CIQE2004Dlg::MoveAgr(DWORD coddoc, DWORD oldcode, DWORD newcode)
{
	CAgrsSet aset(m_CNBase);
	aset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	aset.Open();

	m_CNBase->BeginTrans();

	if(!aset.MoveToCode(oldcode))
	{
		aset.Close();
		return;
	}

	aset.Edit();
	aset.m_NUMAGR = 255;
	aset.UpdateNet(0);
	aset.Requery();

	if(!aset.FreeCodeForMe(newcode))
	{
		aset.Close();
		return;
	}

	aset.MoveToCode(255);


	aset.Edit();
	aset.m_NUMAGR = newcode;

	aset.UpdateNet(0);

	m_CNBase->CommitTrans();

	aset.Requery();

	aset.RemoveHoles();
	

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&aset);

	aset.Close();
}

void CIQE2004Dlg::MoveClass(DWORD coddoc, DWORD oldcode, DWORD newcode)
{
	CClassesSet cset(m_CNBase);
	cset.Open();
	BOOL b;

	cset.MoveToCode(oldcode);
	int firstuseorder = cset.m_USEORDER;

	cset.MoveToCode(newcode);
	cset.MoveNext();
	int seconduseorder = cset.m_USEORDER;

	if(firstuseorder > seconduseorder)
	{

		b = cset.MoveToCode(newcode);
		cset.MoveNext();

		int i = seconduseorder + 1;

		while(!cset.IsEOF())
		{
			cset.Edit();
			cset.m_USEORDER = i;
			cset.UpdateNet(0);
			i++;
			cset.MoveNext();
		}

		b = cset.MoveToCode(oldcode);
		cset.Edit();
		cset.m_USEORDER = seconduseorder;
		cset.UpdateNet(0);
	}
	else
	{
		b = cset.MoveToCode(oldcode);
		cset.MoveNext();

		int i = firstuseorder, last= -1;

		while(!cset.IsEOF() && last != newcode)
		{
			cset.Edit();
			cset.m_USEORDER = i;
			cset.UpdateNet(0);
			i++;
			last = cset.m_LISTDOC;
			cset.MoveNext();
		}

		b = cset.MoveToCode(oldcode);
		cset.Edit();
		cset.m_USEORDER = i;
		cset.UpdateNet(0);
	}
	

	cset.Requery();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&cset);

	cset.Close();

}

void CIQE2004Dlg::OnSortDocs(UINT nID)
{
	CMenu *menu = GetMenu();
	menu->CheckMenuItem(nID, MF_BYCOMMAND | MF_CHECKED);

	for( UINT iID = ID_SORTCODE; iID <= ID_SORTTYPE; iID++)
	{
		if (iID != nID)
			menu->CheckMenuItem(iID, MF_BYCOMMAND | MF_UNCHECKED);
	}

	m_sortby = nID;
	OnRebuildTree();
}

BOOL CIQE2004Dlg::SelectDocByCode(int code)
{
	HTREEITEM hItem = m_tree.GetChildItem(m_docsroot);
	while (hItem != NULL)
	{
		if((m_tree.GetItemData(hItem)&0xffff) == code)
		{
			m_tree.SelectItem(hItem);
			return TRUE;
		}
		hItem = m_tree.GetNextSiblingItem(hItem);
	}
	return FALSE;
}

CString CIQE2004Dlg::GenerateClassesListForDoc(int coddoc, int *count)
{
	CString result, SQL, name;
	int i = 0;

	CRecordset set(m_CNBase);
	SQL.Format(_T("SELECT namelist FROM listdocs, namlistd WHERE listdocs.listdoc = namlistd.listdoc AND listdocs.coddoc = %d"), coddoc);
	set.Open(CRecordset::forwardOnly, SQL);

	while (!set.IsEOF())
	{
		set.GetFieldValue(_T("namelist"), name);
		if ("" == result)
			result = name;
		else
			result += ", " + name;
		i++;
		set.MoveNext();
	}

	if (NULL != count)
		*count = i;

	set.Close();

	return result;
}

void CIQE2004Dlg::OnDocsVerify()
{
	BYTE selType;
	DWORD selOwner;
	DWORD selInd;
	if (!WhatSelected(&selType, &selOwner, &selInd))
		return;
	ViewDocsProperties(selOwner, selInd, true);
}
