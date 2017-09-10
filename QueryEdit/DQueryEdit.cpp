#include "stdafx.h"

#include "QueryEditRes\resource.h"

#include "DQueryEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CIListCtrl
CIListCtrl::CIListCtrl()
{
	m_count=0;
}

CIListCtrl::~CIListCtrl()
{
}

BEGIN_MESSAGE_MAP(CIListCtrl, CListCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()

void CIListCtrl::AddColumn(LPCTSTR lpszName, int nWidth)
{
	CString lpzWidth;
	if(nWidth<0)
		nWidth=0;
	lpzWidth.Format(_T("%d"),nWidth);
	InsertColumn(m_count,lpszName,LVCFMT_LEFT,nWidth);
	if(m_count==0)
		InsertItem(0,lpzWidth);
	else
		SetItemText(0,m_count,lpzWidth);
	m_count++;
}

BOOL CIListCtrl::PreTranslateMessage(MSG* pMsg) 
{
	for(int i=0;i<m_count;i++)
	{
		int width=GetColumnWidth(i);
		CString lpzWidth;
		lpzWidth.Format(_T("%d"),width/10);
		SetItemText(0,i,lpzWidth);
	}
	return CListCtrl::PreTranslateMessage(pMsg);
}

int CIListCtrl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMTreeCtrl
CMTreeCtrl::CMTreeCtrl()
{
}

CMTreeCtrl::~CMTreeCtrl()
{
}

BEGIN_MESSAGE_MAP(CMTreeCtrl, CTreeCtrl)
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CMTreeCtrl::OnRButtonDown(UINT nFlags, CPoint point) 
{
	HTREEITEM hItem=HitTest(point);
	if(hItem!=NULL)
		SelectItem(hItem);
	lPoint=point;
	CRect rect;
	GetWindowRect(rect);
	lPoint+=rect.TopLeft();

	CTreeCtrl::OnRButtonDown(nFlags, point);
}

void CMTreeCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	HTREEITEM hItem=HitTest(point);
	if(hItem!=NULL)
		SelectItem(hItem);
	lPoint=point;
	CRect rect;
	GetWindowRect(rect);
	lPoint+=rect.TopLeft();
	CTreeCtrl::OnLButtonDown(nFlags, point);
}


/* //03.01.17 Borys -- not used
/////////////////////////////////////////////////////////////////////////////
// CAddNewDocDlg dialog
CAddNewDocDlg::CAddNewDocDlg(CWnd* pParent)
	: CDialog(CAddNewDocDlg::IDD, pParent)
{
	m_docsset=NULL;
}

void CAddNewDocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DOCSLIST, m_docslist);
}

BEGIN_MESSAGE_MAP(CAddNewDocDlg, CDialog)
END_MESSAGE_MAP()

void CAddNewDocDlg::SetDocsSet(CDocsSet *docsSet,int code)
{
	m_docsset=docsSet;
	m_selcode=code;
}

BOOL CAddNewDocDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if(!m_docsset)
		return TRUE;

	m_docsset->MoveFirst();
	CString toadd;
	int ind=0,i=0;
	while(!m_docsset->IsEOF())
	{
		if(m_docsset->m_CODDOC==m_selcode)
			ind=i;
		toadd.Format(_T("%4d | %s"),m_docsset->m_CODDOC,m_docsset->m_NAMEDOC);
		m_docslist.AddString(toadd);
		m_docsset->MoveNext();
		i++;
	}
	m_docslist.SetCurSel(ind);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAddNewDocDlg::OnOK() 
{
	UINT ind=m_docslist.GetCurSel();
	m_docsset->MoveFirst();
	while(ind>0)
	{
		m_docsset->MoveNext();
		ind--;
	}

	if(m_docsset->IsEOF())
		m_doccode=-1;
	else
		m_doccode=m_docsset->m_CODDOC;

	CDialog::OnOK();
}
*/


/////////////////////////////////////////////////////////////////////////////
// CImportDocsDlg dialog
CImportDocsDlg::CImportDocsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportDocsDlg::IDD, pParent)
{
}

void CImportDocsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LISTDOCS, m_listdocsctrl);
	DDX_Control(pDX, IDOK, m_OK);
}

BEGIN_MESSAGE_MAP(CImportDocsDlg, CDialog)
END_MESSAGE_MAP()

void CImportDocsDlg::SetDocsSet(CDocsSet *set)
{
	m_docsset=set;
}

BOOL CImportDocsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int i=0;
	m_docsset->MoveFirst();
	while(!m_docsset->IsEOF())
	{
		m_listdocsctrl.AddString(m_docsset->GetCodeNameF());
		m_listdocsctrl.SetItemData(i,m_docsset->GetCodeField());
		m_docsset->MoveNext();
		i++;
	}

	if(!m_bImport)
		m_OK.SetWindowText(_T("Добавить"));
	
	return TRUE;  
}

void CImportDocsDlg::OnOK()
{
	CArray<int,int> inds;
	inds.SetSize(m_listdocsctrl.GetSelCount());
	m_listdocsctrl.GetSelItems(m_listdocsctrl.GetSelCount(),inds.GetData());

	for(int i=0;i<inds.GetSize();i++)
		m_doccodes.Add(m_listdocsctrl.GetItemData(inds[i]));

	CDialog::OnOK();
}


// CTablesDlg dialog
extern int SelRegionDoc(int CodDoc);
CTablesDlg::CTablesDlg(CWnd* pParent /*=NULL*/): CDialog(IDD_TABLES, pParent)
{
}

CTablesDlg::CTablesDlg(CDatabNet *MSGBase, CDatabNet *CNBase, int doccode)
	: CDialog(IDD_TABLES, NULL)
{
	m_MSGBase = MSGBase,m_CNBase = CNBase,m_nDoc = doccode;
}

CTablesDlg::~CTablesDlg()
{
}

void CTablesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSGTABLES, m_cmetatables);
	DDX_Control(pDX, IDC_CURDOCTABLES, m_ctables);
}

BEGIN_MESSAGE_MAP(CTablesDlg, CDialog)
	ON_BN_CLICKED(IDC_ADDTABLE, &CTablesDlg::OnBnClickedAddtable)
	ON_BN_CLICKED(IDC_REMOVETABLE, &CTablesDlg::OnBnClickedRemovetable)
	ON_BN_CLICKED(IDOK, &CTablesDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CTablesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadTablesData();
	LoadMetaTables();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTablesDlg::LoadMetaTables()
{
	m_cmetatables.ResetContent();
	CRecordset tbls(m_MSGBase);
	tbls.Open(CRecordset::forwardOnly, _T("SELECT Table_ID, BaseType, TableName FROM MetaTable WHERE (BaseType = 4 OR BaseType = 14 OR BaseType = 16) AND IsTable = -1"));
	CDBVariant var, varID;
	int ind;
	BYTE grreg;
	while (!tbls.IsEOF())
	{
		tbls.GetFieldValue(_T("Table_ID"), varID);
		tbls.GetFieldValue(_T("BaseType"), var);
		grreg = var.m_iVal;
		if (!IsTableAlready(10000 * grreg + varID.m_iVal))
		{
			tbls.GetFieldValue(_T("TableName"), var);
			ind = m_cmetatables.AddString(*var.m_pstring);
			m_cmetatables.SetItemData(ind, 10000 * grreg + varID.m_iVal);
		}
		tbls.MoveNext();
	}
	tbls.Close();
}

void CTablesDlg::OnBnClickedAddtable()
{
	CArray<int, int> inds;
	inds.SetSize(m_cmetatables.GetSelCount());
	m_cmetatables.GetSelItems(m_cmetatables.GetSelCount(), inds.GetData());
	CString buf;
	int ind;
	for (int i = 0; i < inds.GetSize(); i++)
	{
		m_cmetatables.GetText(inds[i]-i, buf);
		ind = m_ctables.AddString(buf);
		m_ctables.SetItemData(ind, m_cmetatables.GetItemData(inds[i]-i));
		m_cmetatables.DeleteString(inds[i]-i);
	}
}

void CTablesDlg::LoadTablesData()
{
	m_ctables.ResetContent();
	CRecordset tbls(m_CNBase);
	CString SQL;
	CDBVariant var;
	int ind;
	BYTE grreg;
	SQL.Format(_T("SELECT Table_ID, GRUPREG, TableName FROM DescrTabl WHERE CODDOC = %d"), m_nDoc);
	tbls.Open(CRecordset::forwardOnly, SQL);
	while (!tbls.IsEOF())
	{
		tbls.GetFieldValue(_T("TableName"), var);
		ind = m_ctables.AddString(*var.m_pstring);
		tbls.GetFieldValue(_T("GRUPREG"), var);
		grreg = var.m_iVal;
		tbls.GetFieldValue(_T("Table_ID"), var);
		m_ctables.SetItemData(ind, grreg*10000 + var.m_iVal);
		tbls.MoveNext();
	}
	tbls.Close();
}

bool CTablesDlg::IsTableAlready(int Table_ID)
{
	for (int i = 0; i < m_ctables.GetCount(); i++)
	{
		if (m_ctables.GetItemData(i) == Table_ID)
			return true;
	}
	return false;
}

void CTablesDlg::OnBnClickedRemovetable()
{
	CArray<int, int> inds;
	inds.SetSize(m_ctables.GetSelCount());
	m_ctables.GetSelItems(m_ctables.GetSelCount(), inds.GetData());
	CString buf;
	int ind;
	for (int i = 0; i < inds.GetSize(); i++)
	{
		m_ctables.GetText(inds[i] - i, buf);
		ind = m_cmetatables.AddString(buf);
		m_cmetatables.SetItemData(ind, m_ctables.GetItemData(inds[i] - i));
		m_ctables.DeleteString(inds[i] - i);
	}
}

void CTablesDlg::OnBnClickedOk()
{
	CString SQL, TableName;
	SQL.Format(_T("DELETE FROM DescrTabl WHERE CODDOC = %d"), m_nDoc);
	m_CNBase->ExecuteSQL(SQL);
	CRecordset tbls(m_CNBase);
	BYTE grreg;
	int tblID;
	for (int i = 0; i < m_ctables.GetCount(); i++)
	{
		m_ctables.GetText(i, TableName);
		grreg = m_ctables.GetItemData(i) / 10000;
		tblID = m_ctables.GetItemData(i) % 10000;
		SQL.Format(_T("INSERT INTO DescrTabl (CODDOC, GRUPREG, Table_ID, TableName) VALUES (%d, %d, %d, '%s')"),
			m_nDoc, grreg, tblID, TableName);
		m_CNBase->ExecuteSQL(SQL);
	}

	SelRegionDoc(m_nDoc);
	
	CDialog::OnOK();
}


/////////////////////////////////////////////////////////////////////////////
// CWaiterDlg dialog
CWaiterDlg::CWaiterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaiterDlg::IDD, pParent)
{
}

void CWaiterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWaiterDlg, CDialog)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CHeaderSchemaDlg dialog
CHeaderSchemaDlg::CHeaderSchemaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHeaderSchemaDlg::IDD, pParent)
{
}

void CHeaderSchemaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HEADER, m_header);
}

BEGIN_MESSAGE_MAP(CHeaderSchemaDlg, CDialog)
END_MESSAGE_MAP()

BOOL CHeaderSchemaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	for(int i=0;i<m_columns.GetSize();i++)
	{
		m_header.AddColumn(m_columns[i].m_lpzName,m_columns[i].m_nWidth*10);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
