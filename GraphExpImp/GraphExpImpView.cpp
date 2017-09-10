// GraphExpImpView.cpp : implementation of the CGraphExpImpView class
//

#include "stdafx.h"
#include "GraphExpImp.h"

#include "GraphExpImpDoc.h"
#include "GraphExpImpView.h"

#include "PlsizeRead.h"
#include "ItemMenuRead.h"
#include "ProfilesExpImpRead.h"
#include "FilesExpImpRead.h"

#include "AddProfileDlg.h"
#include "AddFilesExpDlg.h"
#include "AddFilesImpDlg.h"
#include "AddSampleProfileDlg.h"
#include "EditProfileExpDlg.h"
#include "EditProfileImpDlg.h"
#include "EditProfileTransDlg.h"
#include "EditProfileReorgDlg.h"
#include "EditFilesExpDlg.h"
#include "EditFilesImpDlg.h"
#include "AboutProgramDlg.h"
#include "NameNewTableDlg.h"

#pragma comment(lib, "OutGraf.lib")
#include "grafstr.h"

#pragma comment(lib, "expimp.lib")
#include "expimp.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpView

CString IniFile;
CTreeCtrl* m_Tree;
int TreeWidth = 40;
int TreeHeight = 40;
ProfilesExpImpRead ProfilesRS;
FilesExpImpRead FilesRS;
BOOL OperationsCreateFile;
BOOL CreateNewFile;
BOOL OperationsCreateSample;
BOOL CreateSample;
BOOL OperationsEdit;
BOOL Edit;
BOOL OperationsDelete;
BOOL Delete;
BOOL OperationsExecute;
BOOL Execute;
BOOL ExecuteEnable = false;
HTREEITEM ItemMenuElement;
vector <HTREEITEM> ExpImpElement;
vector <HTREEITEM> FileElement;

IMPLEMENT_DYNCREATE(CGraphExpImpView, CScrollView)

BEGIN_MESSAGE_MAP(CGraphExpImpView, CScrollView)
	//{{AFX_MSG_MAP(CGraphExpImpView)
	ON_WM_CREATE()
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TREE, OnItemexpandingTree)
	ON_NOTIFY(NM_RCLICK, IDC_TREE, OnRclickTree)
	ON_COMMAND(ID_OPERATIONS_CREATE_PROFILE, OnOperationsCreateProfile)
	ON_COMMAND(ID_CREATE_PROFILE, OnOperationsCreateProfile)
	ON_COMMAND(ID_POPUP_CREATE_PROFILE, OnPopupCreateProfile)
	ON_COMMAND(ID_OPERATIONS_CREATE_FILE, OnOperationsCreateFile)
	ON_COMMAND(ID_CREATE_FILE, OnOperationsCreateFile)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_CREATE_FILE, OnUpdateOperationsCreateFile)
	ON_UPDATE_COMMAND_UI(ID_CREATE_FILE, OnUpdateCreateFile)
	ON_COMMAND(ID_POPUP_CREATE_FILE, OnPopupCreateFile)
	ON_COMMAND(ID_OPERATIONS_CREATE_SAMPLE, OnOperationsCreateSample)
	ON_COMMAND(ID_CREATE_SAMPLE, OnOperationsCreateSample)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_CREATE_SAMPLE, OnUpdateOperationsCreateSample)
	ON_UPDATE_COMMAND_UI(ID_CREATE_SAMPLE, OnUpdateCreateSample)
	ON_COMMAND(ID_POPUP_CREATE_SAMPLE, OnPopupCreateSample)
	ON_COMMAND(ID_OPERATIONS_EDIT, OnOperationsEdit)
	ON_COMMAND(ID_EDIT, OnOperationsEdit)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_EDIT, OnUpdateOperationsEdit)
	ON_UPDATE_COMMAND_UI(ID_EDIT, OnUpdateEdit)
	ON_COMMAND(ID_POPUP_EDIT, OnPopupEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, OnDblclkTree)
	ON_COMMAND(ID_OPERATIONS_DELETE, OnOperationsDelete)
	ON_COMMAND(ID_DELETE, OnOperationsDelete)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_DELETE, OnUpdateOperationsDelete)
	ON_UPDATE_COMMAND_UI(ID_DELETE, OnUpdateDelete)
	ON_COMMAND(ID_POPUP_DELETE, OnPopupDelete)
	ON_COMMAND(ID_OPERATIONS_EXECUTE, OnOperationsExecute)
	ON_COMMAND(ID_EXECUTE, OnOperationsExecute)
	ON_UPDATE_COMMAND_UI(ID_OPERATIONS_EXECUTE, OnUpdateOperationsExecute)
	ON_UPDATE_COMMAND_UI(ID_EXECUTE, OnUpdateExecute)
	ON_COMMAND(ID_POPUP_EXECUTE, OnPopupExecute)
	ON_COMMAND(ID_EXIT, OnExit)
	ON_COMMAND(ID_PROGRAM_HELP, OnProgramHelp)
	ON_COMMAND(ID_OPEN_HELP, OnProgramHelp)
	ON_COMMAND(ID_PROGRAM_ABOUT, OnProgramAbout)
	ON_COMMAND(ID_OPEN_ABOUT, OnProgramAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpView construction/destruction

CGraphExpImpView::CGraphExpImpView()
{
	// TODO: add construction code here

}

CGraphExpImpView::~CGraphExpImpView()
{
}

BOOL CGraphExpImpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	char buffer[MAX_PATH];
	CString WorkFolder;
	GetCurrentDirectory(MAX_PATH, buffer);
	WorkFolder = buffer;
	if (access(WorkFolder + "\\Svisor.ini", 0))
	{
		CFileDialog fd(true);
		fd.m_ofn.lpstrFilter = "Svisor.ini\0Svisor.ini";
		if (fd.DoModal() == IDOK)
		{
			IniFile = fd.m_ofn.lpstrFile;
			return CScrollView::PreCreateWindow(cs);
		}
		else
		{
			PostQuitMessage(0);
			return FALSE;
		}
	}
	else
	{
		IniFile = WorkFolder + "\\Svisor.ini";
		return CScrollView::PreCreateWindow(cs);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpView drawing

void CGraphExpImpView::OnDraw(CDC* pDC)
{
	CGraphExpImpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CGraphExpImpView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = TreeWidth;
	sizeTotal.cy = TreeHeight;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpView diagnostics

#ifdef _DEBUG
void CGraphExpImpView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CGraphExpImpView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CGraphExpImpDoc* CGraphExpImpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphExpImpDoc)));
	return (CGraphExpImpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphExpImpView message handlers

int CGraphExpImpView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	try
	{
		char CommandLine[MAX_PATH];
		CString CommandLineStr = GetCommandLine();
		CFont* m_pFont = new CFont;
		CWindowDC winDC(this);
		CPaintDC paintDC(this);
		LOGFONT lf;
		CImageList* m_Image = new CImageList;
		CBitmap** m_Bitmap = new CBitmap*[8];
		strcpy(CommandLine, CommandLineStr);
		for (int j = CommandLineStr.GetLength() - 1; j >= 0; j--)
			if (CommandLine[j] == ' ')
			{
				CommandLineStr.Delete(0, j + 1);
				break;
			}
		if (CommandLineStr == "/execute")
			ExecuteEnable = true;
		for (j = 0; j < 7; j++)
			m_Bitmap[j] = new CBitmap;
		int i = 0;
		GetParentFrame()->SetWindowText("Операции экспорта/импорта ИГС \"CityCom\"");
		m_Tree = new CTreeCtrl();
		m_Tree->Create(WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS | TVS_DISABLEDRAGDROP, CRect(20, 20, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)), this, IDC_TREE);
		m_pFont = m_Tree->GetFont();
		m_pFont->GetLogFont(&lf);
		paintDC.SelectObject(m_pFont);
		m_Bitmap[0]->LoadBitmap(IDB_PICTURE_CITY);
		m_Bitmap[1]->LoadBitmap(IDB_PICTURE_PROFILE_EXP);
		m_Bitmap[2]->LoadBitmap(IDB_PICTURE_PROFILE_IMP);
		m_Bitmap[3]->LoadBitmap(IDB_PICTURE_PROFILE_TRANS);
		m_Bitmap[4]->LoadBitmap(IDB_PICTURE_PROFILE_REORG);
		m_Bitmap[5]->LoadBitmap(IDB_PICTURE_FILE_EXP);
		m_Bitmap[6]->LoadBitmap(IDB_PICTURE_FILE_IMP);
		m_Image->Create(16, 16, ILC_COLOR32 | ILC_MASK, 0, 1);
		for (j = 0; j < 7; j++)
			m_Image->Add(m_Bitmap[j], RGB(255, 255, 255));
		m_Tree->SetImageList(m_Image, TVSIL_NORMAL);
		ItemMenuRead itmrs;
		itmrs.IniFile = IniFile;
		ProfilesRS.IniFile = IniFile;
		FilesRS.IniFile = IniFile;
		itmrs.Open();
		ProfilesRS.Open();
		FilesRS.Open();
		if (!itmrs.IsBOF())
			itmrs.MoveFirst();
		while (!itmrs.IsEOF())
		{
			if (itmrs.m_CODITEM == 1)
			{
				ItemMenuElement = m_Tree->InsertItem(itmrs.m_NAMEITEM, 0, 0);
				if (paintDC.GetTextExtent(m_Tree->GetItemText(ItemMenuElement)).cx + 80 > TreeWidth)
					TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ItemMenuElement)).cx + 80;
				TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
				break;
			}
			itmrs.MoveNext();
		}
		if (!ProfilesRS.IsBOF())
			ProfilesRS.MoveFirst();
		while (!ProfilesRS.IsEOF())
		{
			if (ProfilesRS.m_Type_profile == 1)
				ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Экспорт)", 1, 1, ItemMenuElement));
			if (ProfilesRS.m_Type_profile == 2)
				ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Импорт)", 2, 2, ItemMenuElement));		
			if (ProfilesRS.m_Type_profile == 3)
				ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Преобразование координат)", 3, 3, ItemMenuElement));		
			if (ProfilesRS.m_Type_profile == 4)
				ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Реорганизация координат)", 4, 4, ItemMenuElement));		
			if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[i])).cx + 96 > TreeWidth)
				TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[i])).cx + 96;
			if (!FilesRS.IsBOF())
				FilesRS.MoveFirst();
			while (!FilesRS.IsEOF())
			{
				if (ProfilesRS.m_Id_profile == FilesRS.m_Id_profile)
				{
					if (ProfilesRS.m_Type_profile == 1)
						FileElement.push_back(m_Tree->InsertItem(FilesRS.m_Name_file, 5, 5, ExpImpElement[i]));
					if (ProfilesRS.m_Type_profile == 2)
						FileElement.push_back(m_Tree->InsertItem(FilesRS.m_Name_file, 6, 6, ExpImpElement[i]));
				}
				FilesRS.MoveNext();
			}
			ProfilesRS.MoveNext();
			i++;
		}
		itmrs.Close();
		ProfilesRS.Close();
		FilesRS.Close();
		m_Tree->SelectItem(ItemMenuElement);
		if (ExpImpElement.size() != 0)
			m_Tree->Expand(ItemMenuElement, TVE_EXPAND);
	}
	catch (...)
	{
		MessageBox("Источник данных не найден или отсутствуют соответствующие таблицы!", "Ошибка", MB_OK | MB_ICONERROR);
		PostQuitMessage(0);
	}

	return 0;
}

void CGraphExpImpView::OnItemexpandingTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CFont* m_pFont = new CFont;
	CWindowDC winDC(this);
	CPaintDC paintDC(this);
	LOGFONT lf;
	pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	m_pFont = m_Tree->GetFont();
	m_pFont->GetLogFont(&lf);
	paintDC.SelectObject(m_pFont);
	if (pNMTreeView->action == 1)
	{
		TreeWidth = 0;
		if (hItem == ItemMenuElement)
		{
			TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ItemMenuElement)).cx + 80;
			TreeHeight = 40 - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
		}
		else
		{
			for (int i = 0; i < ExpImpElement.size(); i++)
			{
				if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[i])).cx + 96 > TreeWidth)
					TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[i])).cx + 96;
				if ((m_Tree->GetItemState(ExpImpElement[i], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
					for (int j = 0; j < FileElement.size(); j++)
						if (m_Tree->GetParentItem(FileElement[j]) == ExpImpElement[i] && m_Tree->GetParentItem(FileElement[j]) != hItem)
							if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112 > TreeWidth)
								TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112;
			}
			for (i = 0; i < FileElement.size(); i++)
				if (hItem == m_Tree->GetParentItem(FileElement[i]))
					TreeHeight = TreeHeight + MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
		}
	}
	else
	{
		if (hItem == ItemMenuElement)
		{
			for (int i = 0; i < ExpImpElement.size(); i++)
			{
				if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[i])).cx + 96 > TreeWidth)
					TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[i])).cx + 96;
				TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
				if ((m_Tree->GetItemState(ExpImpElement[i], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
					for (int j = 0; j < FileElement.size(); j++)
						if (ExpImpElement[i] == m_Tree->GetParentItem(FileElement[j]))
							TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
			}
		}
		else
		{
			for (int i = 0; i < FileElement.size(); i++)
				if (hItem == m_Tree->GetParentItem(FileElement[i]))
				{
					if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[i])).cx + 112 > TreeWidth)
						TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[i])).cx + 112;
					TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
				}
		}
	}
	OnInitialUpdate();

	*pResult = 0;
}

void CGraphExpImpView::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	char buffer[MAX_PATH];
	CString TypeProfile;
	int position;
	OperationsExecute = FALSE;
	Execute = FALSE;
	if (ExpImpElement.size() == 0 || m_Tree->GetSelectedItem() == ItemMenuElement)
	{
		OperationsCreateFile = FALSE;
		CreateNewFile = FALSE;
		OperationsCreateSample = FALSE;
		CreateSample = FALSE;
		OperationsEdit = FALSE;
		Edit = FALSE;
		OperationsDelete = FALSE;
		Delete = FALSE;
	}
	else
	{
		for (int i = 0; i < ExpImpElement.size(); i++)
			if (m_Tree->GetSelectedItem() == ExpImpElement[i])
			{
				strcpy(buffer, m_Tree->GetItemText(ExpImpElement[i]));
				TypeProfile = buffer;
				for (int j = TypeProfile.GetLength() - 1; j >= 0; j--)
					if (buffer[j] == '(')
					{
						position = j;
						break;
					}
				TypeProfile.Delete(0, position + 1);
				TypeProfile.Delete(TypeProfile.GetLength() - 1, 1);
				OperationsCreateSample = TRUE;
				CreateSample = TRUE;
				if (TypeProfile != "Преобразование координат" && TypeProfile != "Реорганизация координат")
				{
					OperationsCreateFile = TRUE;
					CreateNewFile = TRUE;
					for (j = 0; j < FileElement.size(); j++)
						if (ExpImpElement[i] == m_Tree->GetParentItem(FileElement[j]) && ExecuteEnable)
						{
							OperationsExecute = TRUE;
							Execute = TRUE;
							break;
						}
				}
				else
				{
					OperationsCreateFile = FALSE;
					CreateNewFile = FALSE;
					if (ExecuteEnable)
					{
						OperationsExecute = TRUE;
						Execute = TRUE;
					}
				}
				break;
			}
		for (i = 0; i < FileElement.size(); i++)
			if (m_Tree->GetSelectedItem() == FileElement[i])
			{
				OperationsCreateFile = TRUE;
				CreateNewFile = TRUE;
				OperationsCreateSample = FALSE;
				CreateSample = FALSE;
				if (ExecuteEnable)
				{
					OperationsExecute = TRUE;
					Execute = TRUE;
				}
				break;
			}
		OperationsEdit = TRUE;
		Edit = TRUE;
		OperationsDelete = TRUE;
		Delete = TRUE;
	}

	*pResult = 0;
}

void CGraphExpImpView::OnRclickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	char buffer[MAX_PATH];
	CString TypeProfile;
	int position;
	CPoint point;
	GetCursorPos(&point);
	m_Tree->ScreenToClient(&point);
	UINT uFlags;
	HTREEITEM hItem = m_Tree->HitTest(point, &uFlags);
	if ((hItem != NULL) && (TVHT_ONITEM & uFlags) && hItem != ItemMenuElement)
	{
		m_Tree->Select(hItem, TVGN_CARET);
		m_Tree->ClientToScreen(&point);
		CMenu* m_Menu = new CMenu;
		m_Menu->LoadMenu(IDR_POPUP_MENU);
		m_Menu->DeleteMenu(ID_POPUP_CREATE_PROFILE, MF_BYCOMMAND);
		for (int i = 0; i < ExpImpElement.size(); i++)
			if (hItem == ExpImpElement[i])
			{
				strcpy(buffer, m_Tree->GetItemText(ExpImpElement[i]));
				TypeProfile = buffer;
				for (int j = TypeProfile.GetLength() - 1; j >= 0; j--)
					if (buffer[j] == '(')
					{
						position = j;
						break;
					}
				TypeProfile.Delete(0, position + 1);
				TypeProfile.Delete(TypeProfile.GetLength() - 1, 1);
				if (TypeProfile == "Преобразование координат" || TypeProfile == "Реорганизация координат")
					m_Menu->DeleteMenu(ID_POPUP_CREATE_FILE, MF_BYCOMMAND);
				if ((TypeProfile == "Экспорт" || TypeProfile == "Импорт") && !m_Tree->ItemHasChildren(hItem))
					m_Menu->DeleteMenu(ID_POPUP_EXECUTE, MF_BYCOMMAND);
				break;
			}
		for (i = 0; i < FileElement.size(); i++)
			if (hItem == FileElement[i])
			{
				m_Menu->DeleteMenu(ID_POPUP_CREATE_FILE, MF_BYCOMMAND);
				m_Menu->DeleteMenu(ID_POPUP_CREATE_SAMPLE, MF_BYCOMMAND);
				break;
			}
		if (!ExecuteEnable)
			m_Menu->DeleteMenu(ID_POPUP_EXECUTE, MF_BYCOMMAND);
		m_Menu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else
	{
		m_Tree->ClientToScreen(&point);
		CMenu* m_Menu = new CMenu;
		m_Menu->LoadMenu(IDR_POPUP_MENU);
		m_Menu->DeleteMenu(ID_POPUP_CREATE_FILE, MF_BYCOMMAND);
		m_Menu->DeleteMenu(ID_POPUP_CREATE_SAMPLE, MF_BYCOMMAND);
		m_Menu->DeleteMenu(ID_POPUP_EDIT, MF_BYCOMMAND);
		m_Menu->DeleteMenu(ID_POPUP_DELETE, MF_BYCOMMAND);
		m_Menu->DeleteMenu(ID_POPUP_EXECUTE, MF_BYCOMMAND);
		m_Menu->GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	
	*pResult = 0;
}

void CGraphExpImpView::OnOperationsCreateProfile() 
{
	// TODO: Add your command handler code here
	CFont* m_pFont = new CFont;
	CWindowDC winDC(this);
	CPaintDC paintDC(this);
	LOGFONT lf;
	char buffer[MAX_PATH];
	CString buf, lpEXEName;
	ProfilesRS.Open();
	FilesRS.Open();
	AddProfileDlg dlg;
	dlg.IniFile = IniFile;
	if (dlg.DoModal() == IDOK)
	{
		ProfilesRS.AddNew();
		ProfilesRS.m_Name_profile = dlg.m_Name_profile_str;
		ProfilesRS.m_Number_section = dlg.NumberSection;
		ProfilesRS.m_Group_section = dlg.GroupSection;
		ProfilesRS.m_Path_section = dlg.PathSection;
		ProfilesRS.m_Type_source_data = dlg.TypeSourceData;
		ProfilesRS.m_Type_profile = dlg.TypeProfile;
		switch (dlg.m_Type_profile_int)
		{
			case 0:
			{
				ProfilesRS.m_Folder = dlg.m_Choosen_folder_str;
				ProfilesRS.m_Factor_x = atof(dlg.m_Factor_x_str);
				ProfilesRS.m_Factor_y = atof(dlg.m_Factor_y_str);
				ProfilesRS.m_Shift_x = atof(dlg.m_Shift_x_str);
				ProfilesRS.m_Shift_y = atof(dlg.m_Shift_y_str);
				ProfilesRS.m_Turn = atof(dlg.m_Turn_str);
				ProfilesRS.m_Size_x = 0;
				ProfilesRS.m_Size_y = 0;
				ProfilesRS.m_Initial_order_coordinates = -1;
				if (dlg.GraphAreaEnable)
					ProfilesRS.m_Graph_area = dlg.m_Graph_area_bool;
				if (dlg.m_Graph_area_bool && dlg.GraphAreaEnable)
					ProfilesRS.m_Graph_area_id = dlg.GraphAreaId;
				else
					ProfilesRS.m_Graph_area_id = -1;
				ProfilesRS.m_Unit = dlg.m_Metre_int;
				break;
			}
			case 1:
			{
				ProfilesRS.m_Folder = dlg.m_Choosen_folder_str;
				ProfilesRS.m_Factor_x = atof(dlg.m_Factor_x_str);
				ProfilesRS.m_Factor_y = atof(dlg.m_Factor_y_str);
				ProfilesRS.m_Shift_x = atof(dlg.m_Shift_x_str);
				ProfilesRS.m_Shift_y = atof(dlg.m_Shift_y_str);
				ProfilesRS.m_Turn = atof(dlg.m_Turn_str);
				ProfilesRS.m_Size_x = 0;
				ProfilesRS.m_Size_y = 0;
				ProfilesRS.m_Initial_order_coordinates = dlg.m_Usual_int;
				ProfilesRS.m_Graph_area_id = -1;
				ProfilesRS.m_Unit = -1;
				break;
			}
			case 2:
			{
				ProfilesRS.m_Folder = "НЕТ";
				ProfilesRS.m_Factor_x = atof(dlg.m_Factor_x_str);
				ProfilesRS.m_Factor_y = atof(dlg.m_Factor_y_str);
				ProfilesRS.m_Shift_x = atof(dlg.m_Shift_x_str);
				ProfilesRS.m_Shift_y = atof(dlg.m_Shift_y_str);
				ProfilesRS.m_Turn = atof(dlg.m_Turn_str);
				ProfilesRS.m_Size_x = atof(dlg.m_Size_x_str);
				ProfilesRS.m_Size_y = atof(dlg.m_Size_y_str);
				ProfilesRS.m_Initial_order_coordinates = -1;
				ProfilesRS.m_Graph_area_id = -1;
				ProfilesRS.m_Unit = -1;
				break;
			}
			case 3:
			{
				ProfilesRS.m_Folder = "НЕТ";
				ProfilesRS.m_Factor_x = 0;
				ProfilesRS.m_Factor_y = 0;
				ProfilesRS.m_Shift_x = 0;
				ProfilesRS.m_Shift_y = 0;
				ProfilesRS.m_Turn = 0;
				ProfilesRS.m_Size_x = 0;
				ProfilesRS.m_Size_y = 0;
				ProfilesRS.m_Initial_order_coordinates = -1;
				ProfilesRS.m_Graph_area_id = -1;
				ProfilesRS.m_Unit = -1;
				break;
			}
		}
		if (ProfilesRS.m_Type_profile == 1)
			ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Экспорт)", 1, 1, ItemMenuElement));
		if (ProfilesRS.m_Type_profile == 2)
			ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Импорт)", 2, 2, ItemMenuElement));		
		if (ProfilesRS.m_Type_profile == 3)
			ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Преобразование координат)", 3, 3, ItemMenuElement));		
		if (ProfilesRS.m_Type_profile == 4)
			ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Реорганизация координат)", 4, 4, ItemMenuElement));
		m_pFont = m_Tree->GetFont();
		m_pFont->GetLogFont(&lf);
		paintDC.SelectObject(m_pFont);
		if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[ExpImpElement.size() - 1])).cx + 96 > TreeWidth)
			TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[ExpImpElement.size() - 1])).cx + 96;
		TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
		OnInitialUpdate();
		ProfilesRS.Update();
		if (dlg.TypeProfile != 4)
		{
			sprintf(buffer, "%f", atof(dlg.m_Factor_x_str));
			buf = buffer;
			WritePrivateProfileString("IMPPAR_MIFDBF", "cxx", buf, dlg.m_Choosen_folder_str + "\\expimp.ini");
			sprintf(buffer, "%f", atof(dlg.m_Factor_y_str));
			buf = buffer;
			WritePrivateProfileString("IMPPAR_MIFDBF", "cyy", buf, dlg.m_Choosen_folder_str + "\\expimp.ini");
			sprintf(buffer, "%f", atof(dlg.m_Shift_x_str));
			buf = buffer;
			WritePrivateProfileString("IMPPAR_MIFDBF", "ax", buf, dlg.m_Choosen_folder_str + "\\expimp.ini");
			sprintf(buffer, "%f", atof(dlg.m_Shift_y_str));
			buf = buffer;
			WritePrivateProfileString("IMPPAR_MIFDBF", "ay", buf, dlg.m_Choosen_folder_str + "\\expimp.ini");
			sprintf(buffer, "%f", atof(dlg.m_Turn_str));
			buf = buffer;
			WritePrivateProfileString("IMPPAR", "angl", buf, dlg.m_Choosen_folder_str + "\\expimp.ini");
		}
		m_Tree->SelectItem(ExpImpElement[ExpImpElement.size() - 1]);
	}
	ProfilesRS.Close();
	FilesRS.Close();
}

void CGraphExpImpView::OnPopupCreateProfile() 
{
	// TODO: Add your command handler code here
	OnOperationsCreateProfile();
}

void CGraphExpImpView::OnOperationsCreateFile() 
{
	// TODO: Add your command handler code here
	CFont* m_pFont = new CFont;
	CWindowDC winDC(this);
	CPaintDC paintDC(this);
	LOGFONT lf;
	bool file_element = true;
	char buffer[MAX_PATH];
	CString buf, NameProfile, lpEXEName;
	int position, Height = TreeHeight;
	m_pFont = m_Tree->GetFont();
	m_pFont->GetLogFont(&lf);
	paintDC.SelectObject(m_pFont);
	ProfilesRS.Open();
	FilesRS.Open();
	for (int i = 0; i < ExpImpElement.size(); i++)
		if (m_Tree->GetSelectedItem() == ExpImpElement[i])
		{
			strcpy(buffer, m_Tree->GetItemText(ExpImpElement[i]));
			NameProfile = buffer;
			for (int j = NameProfile.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == '(')
				{
					position = j - 1;
					break;
				}
			NameProfile.Delete(position, NameProfile.GetLength() - position);
			if (!ProfilesRS.IsBOF())
				ProfilesRS.MoveFirst();
			while (!ProfilesRS.IsEOF())
			{
				if (ProfilesRS.m_Name_profile == NameProfile)
				{
					if (ProfilesRS.m_Type_profile == 1)
					{
						AddFilesExpDlg dlg;
						dlg.IniFile = IniFile;
						dlg.StrConnection = ProfilesRS.m_Path_section;
						dlg.IdProfile = ProfilesRS.m_Id_profile;
						dlg.GROUPREG = ProfilesRS.m_Group_section;
						if (dlg.DoModal() == IDOK)
						{
							for (int j = 0; j < dlg.CountSelectedElements; j++)
							{
								FilesRS.AddNew();
								FilesRS.m_Id_profile = ProfilesRS.m_Id_profile;
								FilesRS.m_Name_file = dlg.NameFile[j];
								FilesRS.m_Type_graph_object = dlg.TypeGraphObject[j];
								FilesRS.m_Type_graph_obj = dlg.TypeGraphObj[j];
								FilesRS.m_Complement_areas_centers_knots = dlg.m_Complement_areas_centers_knots_bool;
								FilesRS.m_Query_exp = dlg.m_Query_exp_str;
								FilesRS.m_Accepting_type_lines = -1;
								FilesRS.m_Level_lines = -1;
								FilesRS.m_Code_text = -1;
								FilesRS.m_Accepting_type_text = -1;
								FilesRS.m_Level_text = -1;
								FilesRS.m_Transform_denotations = -1;
								FilesRS.m_Type_transformed_denotations = -1;
								FilesRS.m_Level_denotations = -1;
								FilesRS.m_Size_denotations = 0;
								FilesRS.m_Number_field_charakteristics = -1;
								FilesRS.m_Accepting_type_charakteristics = -1;
								FilesRS.m_Level_charakteristics = -1;
								FilesRS.m_Height_charakteristics = 0;
								FileElement.push_back(m_Tree->InsertItem(dlg.NameFile[j], 5, 5, ExpImpElement[i]));
								FilesRS.Update();
								m_Tree->SelectItem(FileElement[FileElement.size() - 1]);
								if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[FileElement.size() - 1])).cx + 112 > TreeWidth)
									TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[FileElement.size() - 1])).cx + 112;
								if ((TreeHeight == Height && j == 0) || j > 0)
									TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
								OnInitialUpdate();
							}
						}
					}
					if (ProfilesRS.m_Type_profile == 2)
					{
						AddFilesImpDlg dlg;
						dlg.IniFile = IniFile;
						dlg.StrConnection = ProfilesRS.m_Path_section;
						dlg.Folder = ProfilesRS.m_Folder;
						dlg.IdProfile = ProfilesRS.m_Id_profile;
						if (dlg.DoModal() == IDOK)
						{
							FilesRS.AddNew();
							FilesRS.m_Id_profile = ProfilesRS.m_Id_profile;
							FilesRS.m_Name_file = dlg.m_File_name_str;
							FilesRS.m_Type_graph_object = -1;
							FilesRS.m_Type_graph_obj = -1;
							if (dlg.ImportLinesEnable)
							{
								FilesRS.m_Accepting_type_lines = dlg.AcceptingTypeLines;
								FilesRS.m_Level_lines = dlg.LevelLines;
								FilesRS.m_Break_lines_segments = dlg.m_Break_lines_segments_bool;
								FilesRS.m_Skip_superfluous_points = dlg.m_Skip_superfluous_points_bool;
							}
							else
							{
								FilesRS.m_Accepting_type_lines = -1;
								FilesRS.m_Level_lines = -1;
							}
							FilesRS.m_Code_text = dlg.m_Windows_int;
							if (dlg.ImportTextEnable)
							{
								FilesRS.m_Accepting_type_text = dlg.AcceptingTypeText;
								FilesRS.m_Level_text = dlg.LevelText;
							}
							else
							{
								FilesRS.m_Accepting_type_text = -1;
								FilesRS.m_Level_text = -1;
							}
							if (dlg.ImportDenotationsEnable)
							{
								FilesRS.m_Transform_denotations = dlg.m_Circles_int;
								FilesRS.m_Type_transformed_denotations = dlg.TypeTransformedDenotations;
								FilesRS.m_Level_denotations = dlg.LevelDenotations;
								FilesRS.m_Size_denotations = atof(dlg.m_Size_denotations_str);
							}
							else
							{
								FilesRS.m_Transform_denotations = -1;
								FilesRS.m_Type_transformed_denotations = -1;
								FilesRS.m_Level_denotations = -1;
								FilesRS.m_Size_denotations = 0;
							}
							GetModuleFileName(NULL, buffer, MAX_PATH);
							lpEXEName = buffer;
							for (int j = lpEXEName.GetLength() - 1; j >= 0; j--)
								if (buffer[j] == '\\')
								{
									lpEXEName.Delete(j, lpEXEName.GetLength() - j);
									break;
								}
							sprintf(buffer, "%f", atof(dlg.m_Size_denotations_str));
							buf = buffer;
							WritePrivateProfileString("IMPPAR", "radp", buf, lpEXEName + "\\expimp.ini");
							if (dlg.ImportCharakteristicsEnable)
								FilesRS.m_Import_charakteristics = dlg.m_Import_charakteristics_bool;
							if (dlg.m_Import_charakteristics_bool && dlg.ImportCharakteristicsEnable)
							{
								FilesRS.m_Number_field_charakteristics = dlg.m_Name_field_charakteristics_int;
								FilesRS.m_Accepting_type_charakteristics = dlg.AcceptingTypeCharakteristics;
								FilesRS.m_Level_charakteristics = dlg.LevelCharakteristics;
								FilesRS.m_Height_charakteristics = atof(dlg.m_Height_charakteristics_str);
							}
							else
							{
								FilesRS.m_Number_field_charakteristics = -1;
								FilesRS.m_Accepting_type_charakteristics = -1;
								FilesRS.m_Level_charakteristics = -1;
								FilesRS.m_Height_charakteristics = 0;
							}
							if (dlg.m_Delete_graph_object_bool)
								FilesRS.m_Delete_graph_object = 1;
							else
								FilesRS.m_Delete_graph_object = 2;
							FileElement.push_back(m_Tree->InsertItem(dlg.m_File_name_str, 6, 6, ExpImpElement[i]));
							FilesRS.Update();
							m_Tree->SelectItem(FileElement[FileElement.size() - 1]);
							if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[FileElement.size() - 1])).cx + 112 > TreeWidth)
								TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[FileElement.size() - 1])).cx + 112;
							if (TreeHeight == Height)
								TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
							WritePrivateProfileString("IMPPAR", "radp", dlg.m_Size_denotations_str, ProfilesRS.m_Folder + "\\expimp.ini");
							OnInitialUpdate();
						}
					}
					file_element = false;
				}
				ProfilesRS.MoveNext();
			}
			break;
		}
	if (file_element)
		for (i = 0; i < FileElement.size(); i++)
			if (m_Tree->GetSelectedItem() == FileElement[i])
			{
				if (!FilesRS.IsBOF())
					FilesRS.MoveFirst();
				while (!FilesRS.IsEOF())
				{
					if (FilesRS.m_Name_file == m_Tree->GetItemText(FileElement[i]))
					{
						if (!ProfilesRS.IsBOF())
							ProfilesRS.MoveFirst();
						while (!ProfilesRS.IsEOF())
						{
							if (ProfilesRS.m_Id_profile == FilesRS.m_Id_profile)
							{
								if (ProfilesRS.m_Type_profile == 1)
								{
									AddFilesExpDlg dlg;
									dlg.IniFile = IniFile;
									dlg.StrConnection = ProfilesRS.m_Path_section;
									dlg.IdProfile = ProfilesRS.m_Id_profile;
									dlg.GROUPREG = ProfilesRS.m_Group_section;
									if (dlg.DoModal() == IDOK)
									{
										for (int j = 0; j < dlg.CountSelectedElements; j++)
										{
											FilesRS.AddNew();
											FilesRS.m_Id_profile = ProfilesRS.m_Id_profile;
											FilesRS.m_Name_file = dlg.NameFile[j];
											FilesRS.m_Type_graph_object = dlg.TypeGraphObject[j];
											FilesRS.m_Type_graph_obj = dlg.TypeGraphObj[j];
											FilesRS.m_Complement_areas_centers_knots = dlg.m_Complement_areas_centers_knots_bool;
											FilesRS.m_Query_exp = dlg.m_Query_exp_str;
											FilesRS.m_Accepting_type_lines = -1;
											FilesRS.m_Level_lines = -1;
											FilesRS.m_Code_text = -1;
											FilesRS.m_Accepting_type_text = -1;
											FilesRS.m_Level_text = -1;
											FilesRS.m_Transform_denotations = -1;
											FilesRS.m_Type_transformed_denotations = -1;
											FilesRS.m_Level_denotations = -1;
											FilesRS.m_Size_denotations = 0;
											FilesRS.m_Number_field_charakteristics = -1;
											FilesRS.m_Accepting_type_charakteristics = -1;
											FilesRS.m_Level_charakteristics = -1;
											FilesRS.m_Height_charakteristics = 0;
											FileElement.push_back(m_Tree->InsertItem(dlg.NameFile[j], 5, 5, m_Tree->GetParentItem(FileElement[i])));
											FilesRS.Update();
											m_Tree->SelectItem(FileElement[FileElement.size() - 1]);
											if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[FileElement.size() - 1])).cx + 112 > TreeWidth)
												TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[FileElement.size() - 1])).cx + 112;
											TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
											OnInitialUpdate();
										}
									}
								}
								if (ProfilesRS.m_Type_profile == 2)
								{
									AddFilesImpDlg dlg;
									dlg.IniFile = IniFile;
									dlg.StrConnection = ProfilesRS.m_Path_section;
									dlg.Folder = ProfilesRS.m_Folder;
									dlg.IdProfile = ProfilesRS.m_Id_profile;
									if (dlg.DoModal() == IDOK)
									{
										FilesRS.AddNew();
										FilesRS.m_Id_profile = ProfilesRS.m_Id_profile;
										FilesRS.m_Name_file = dlg.m_File_name_str;
										FilesRS.m_Type_graph_object = -1;
										FilesRS.m_Type_graph_obj = -1;
										if (dlg.ImportLinesEnable)
										{
											FilesRS.m_Accepting_type_lines = dlg.AcceptingTypeLines;
											FilesRS.m_Level_lines = dlg.LevelLines;
											FilesRS.m_Break_lines_segments = dlg.m_Break_lines_segments_bool;
											FilesRS.m_Skip_superfluous_points = dlg.m_Skip_superfluous_points_bool;
										}
										else
										{
											FilesRS.m_Accepting_type_lines = -1;
											FilesRS.m_Level_lines = -1;
										}
										FilesRS.m_Code_text = dlg.m_Windows_int;
										if (dlg.ImportTextEnable)
										{
											FilesRS.m_Accepting_type_text = dlg.AcceptingTypeText;
											FilesRS.m_Level_text = dlg.LevelText;
										}
										else
										{
											FilesRS.m_Accepting_type_text = -1;
											FilesRS.m_Level_text = -1;
										}
										if (dlg.ImportDenotationsEnable)
										{
											FilesRS.m_Transform_denotations = dlg.m_Circles_int;
											FilesRS.m_Type_transformed_denotations = dlg.TypeTransformedDenotations;
											FilesRS.m_Level_denotations = dlg.LevelDenotations;
											FilesRS.m_Size_denotations = atof(dlg.m_Size_denotations_str);
										}
										else
										{
											FilesRS.m_Transform_denotations = -1;
											FilesRS.m_Type_transformed_denotations = -1;
											FilesRS.m_Level_denotations = -1;
											FilesRS.m_Size_denotations = 0;
										}
										GetModuleFileName(NULL, buffer, MAX_PATH);
										lpEXEName = buffer;
										for (int j = lpEXEName.GetLength() - 1; j >= 0; j--)
											if (buffer[j] == '\\')
											{
												lpEXEName.Delete(j, lpEXEName.GetLength() - j);
												break;
											}
										sprintf(buffer, "%f", atof(dlg.m_Size_denotations_str));
										buf = buffer;
										WritePrivateProfileString("IMPPAR", "radp", buf, lpEXEName + "\\expimp.ini");
										if (dlg.ImportCharakteristicsEnable)
											FilesRS.m_Import_charakteristics = dlg.m_Import_charakteristics_bool;
										if (dlg.m_Import_charakteristics_bool && dlg.ImportCharakteristicsEnable)
										{
											FilesRS.m_Number_field_charakteristics = dlg.m_Name_field_charakteristics_int;
											FilesRS.m_Accepting_type_charakteristics = dlg.AcceptingTypeCharakteristics;
											FilesRS.m_Level_charakteristics = dlg.LevelCharakteristics;
											FilesRS.m_Height_charakteristics = atof(dlg.m_Height_charakteristics_str);
										}
										else
										{
											FilesRS.m_Number_field_charakteristics = -1;
											FilesRS.m_Accepting_type_charakteristics = -1;
											FilesRS.m_Level_charakteristics = -1;
											FilesRS.m_Height_charakteristics = 0;
										}
										if (dlg.m_Delete_graph_object_bool)
											FilesRS.m_Delete_graph_object = 1;
										else
											FilesRS.m_Delete_graph_object = 2;
										FileElement.push_back(m_Tree->InsertItem(dlg.m_File_name_str, 6, 6, m_Tree->GetParentItem(FileElement[i])));
										FilesRS.Update();
										m_Tree->SelectItem(FileElement[FileElement.size() - 1]);
										if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[FileElement.size() - 1])).cx + 112 > TreeWidth)
											TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[FileElement.size() - 1])).cx + 112;
										TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
										WritePrivateProfileString("IMPPAR", "radp", dlg.m_Size_denotations_str, ProfilesRS.m_Folder + "\\expimp.ini");
										OnInitialUpdate();
									}
								}
							}
							ProfilesRS.MoveNext();
						}
						break;
					}
					FilesRS.MoveNext();
				}
				break;
			}
	ProfilesRS.Close();
	FilesRS.Close();
}

void CGraphExpImpView::OnUpdateOperationsCreateFile(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(OperationsCreateFile);
}

void CGraphExpImpView::OnUpdateCreateFile(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CreateNewFile);
}

void CGraphExpImpView::OnPopupCreateFile() 
{
	// TODO: Add your command handler code here
	OnOperationsCreateFile();
}

void CGraphExpImpView::OnOperationsCreateSample() 
{
	// TODO: Add your command handler code here
	CFont* m_pFont = new CFont;
	CWindowDC winDC(this);
	CPaintDC paintDC(this);
	LOGFONT lf;
	char buffer[MAX_PATH];
	CString NameProfile, PathSection, Folder;
	int position, NumberSection, GroupSection, TypeSourceData, SizeX, SizeY, InitialOrderCoordinates, GraphAreaId, Unit;
	double FactorX, FactorY, ShiftX, ShiftY, Turn;
	bool GraphArea;
	m_pFont = m_Tree->GetFont();
	m_pFont->GetLogFont(&lf);
	paintDC.SelectObject(m_pFont);
	ProfilesRS.Open();
	for (int i = 0; i < ExpImpElement.size(); i++)
		if (m_Tree->GetSelectedItem() == ExpImpElement[i])
		{
			strcpy(buffer, m_Tree->GetItemText(ExpImpElement[i]));
			NameProfile = buffer;
			for (int j = NameProfile.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == '(')
				{
					position = j - 1;
					break;
				}
			NameProfile.Delete(position, NameProfile.GetLength() - position);
			if (!ProfilesRS.IsBOF())
				ProfilesRS.MoveFirst();
			while (!ProfilesRS.IsEOF())
			{
				if (ProfilesRS.m_Name_profile == NameProfile)
				{
					AddSampleProfileDlg dlg;
					dlg.IniFile = IniFile;
					dlg.TypeProfile = ProfilesRS.m_Type_profile;
					NumberSection = ProfilesRS.m_Number_section;
					GroupSection = ProfilesRS.m_Group_section;
					PathSection = ProfilesRS.m_Path_section;
					TypeSourceData = ProfilesRS.m_Type_source_data;
					Folder = ProfilesRS.m_Folder;
					FactorX = ProfilesRS.m_Factor_x;
					FactorY = ProfilesRS.m_Factor_y;
					ShiftX = ProfilesRS.m_Shift_x;
					ShiftY = ProfilesRS.m_Shift_y;
					Turn = ProfilesRS.m_Turn;
					SizeX = ProfilesRS.m_Size_x;
					SizeY = ProfilesRS.m_Size_y;
					InitialOrderCoordinates = ProfilesRS.m_Initial_order_coordinates;
					if (ProfilesRS.m_Graph_area)
						GraphArea = true;
					else
						GraphArea = false;
					GraphAreaId = ProfilesRS.m_Graph_area_id;
					Unit = ProfilesRS.m_Unit;
					if (dlg.DoModal() == IDOK)
					{
						ProfilesRS.AddNew();
						ProfilesRS.m_Name_profile = dlg.m_Name_profile_str;
						ProfilesRS.m_Number_section = NumberSection;
						ProfilesRS.m_Group_section = GroupSection;
						ProfilesRS.m_Path_section = PathSection;
						ProfilesRS.m_Type_profile = dlg.TypeProfile;
						ProfilesRS.m_Type_source_data = TypeSourceData;
						if (ProfilesRS.m_Type_profile == 1)
						{
							ProfilesRS.m_Folder = Folder;
							ProfilesRS.m_Factor_x = FactorX;
							ProfilesRS.m_Factor_y = FactorY;
							ProfilesRS.m_Shift_x = ShiftX;
							ProfilesRS.m_Shift_y = ShiftY;
							ProfilesRS.m_Turn = Turn;
							ProfilesRS.m_Size_x = 0;
							ProfilesRS.m_Size_y = 0;
							ProfilesRS.m_Initial_order_coordinates = -1;
							ProfilesRS.m_Graph_area = GraphArea;
							ProfilesRS.m_Graph_area_id = GraphAreaId;
							if (Unit > -1)
								ProfilesRS.m_Unit = Unit;
							else
								ProfilesRS.m_Unit = 0;
						}
						if (ProfilesRS.m_Type_profile == 2)
						{
							ProfilesRS.m_Folder = Folder;
							ProfilesRS.m_Factor_x = FactorX;
							ProfilesRS.m_Factor_y = FactorY;
							ProfilesRS.m_Shift_x = ShiftX;
							ProfilesRS.m_Shift_y = ShiftY;
							ProfilesRS.m_Turn = Turn;
							ProfilesRS.m_Size_x = 0;
							ProfilesRS.m_Size_y = 0;
							if (InitialOrderCoordinates > -1)
								ProfilesRS.m_Initial_order_coordinates = InitialOrderCoordinates;
							else
								ProfilesRS.m_Initial_order_coordinates = 0;
							ProfilesRS.m_Graph_area = false;
							ProfilesRS.m_Graph_area_id = -1;
							ProfilesRS.m_Unit = -1;
						}
						if (ProfilesRS.m_Type_profile == 3)
						{
							ProfilesRS.m_Folder = "НЕТ";
							ProfilesRS.m_Factor_x = FactorX;
							ProfilesRS.m_Factor_y = FactorY;
							ProfilesRS.m_Shift_x = ShiftX;
							ProfilesRS.m_Shift_y = ShiftY;
							ProfilesRS.m_Turn = Turn;
							ProfilesRS.m_Size_x = SizeX;
							ProfilesRS.m_Size_y = SizeY;
							ProfilesRS.m_Initial_order_coordinates = -1;
							ProfilesRS.m_Graph_area = false;
							ProfilesRS.m_Graph_area_id = -1;
							ProfilesRS.m_Unit = -1;
						}
						if (ProfilesRS.m_Type_profile == 4)
						{
							ProfilesRS.m_Folder = "НЕТ";
							ProfilesRS.m_Factor_x = 0;
							ProfilesRS.m_Factor_y = 0;
							ProfilesRS.m_Shift_x = 0;
							ProfilesRS.m_Shift_y = 0;
							ProfilesRS.m_Turn = 0;
							ProfilesRS.m_Size_x = 0;
							ProfilesRS.m_Size_y = 0;
							ProfilesRS.m_Initial_order_coordinates = -1;
							ProfilesRS.m_Graph_area = false;
							ProfilesRS.m_Graph_area_id = -1;
							ProfilesRS.m_Unit = -1;
						}
						if (ProfilesRS.m_Type_profile == 1)
							ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Экспорт)", 1, 1, ItemMenuElement));
						if (ProfilesRS.m_Type_profile == 2)
							ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Импорт)", 2, 2, ItemMenuElement));		
						if (ProfilesRS.m_Type_profile == 3)
							ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Преобразование координат)", 3, 3, ItemMenuElement));		
						if (ProfilesRS.m_Type_profile == 4)
							ExpImpElement.push_back(m_Tree->InsertItem(ProfilesRS.m_Name_profile + " (Реорганизация координат)", 4, 4, ItemMenuElement));
						if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[ExpImpElement.size() - 1])).cx + 96 > TreeWidth)
							TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[ExpImpElement.size() - 1])).cx + 96;
						TreeHeight = TreeHeight - MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
						OnInitialUpdate();
						ProfilesRS.Update();
						m_Tree->SelectItem(ExpImpElement[ExpImpElement.size() - 1]);
					}
				}
				ProfilesRS.MoveNext();
			}
			break;
		}
	ProfilesRS.Close();
}

void CGraphExpImpView::OnUpdateOperationsCreateSample(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(OperationsCreateSample);
}

void CGraphExpImpView::OnUpdateCreateSample(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(CreateSample);
}

void CGraphExpImpView::OnPopupCreateSample() 
{
	// TODO: Add your command handler code here
	OnOperationsCreateSample();
}

void CGraphExpImpView::OnOperationsEdit() 
{
	// TODO: Add your command handler code here
	CFont* m_pFont = new CFont;
	CWindowDC winDC(this);
	CPaintDC paintDC(this);
	LOGFONT lf;
	char buffer[MAX_PATH];
	CString NameProfile;
	int position;
	m_pFont = m_Tree->GetFont();
	m_pFont->GetLogFont(&lf);
	paintDC.SelectObject(m_pFont);
	ProfilesRS.Open();
	FilesRS.Open();
	for (int i = 0; i < ExpImpElement.size(); i++)
		if (m_Tree->GetSelectedItem() == ExpImpElement[i])
		{
			strcpy(buffer, m_Tree->GetItemText(ExpImpElement[i]));
			NameProfile = buffer;
			for (int j = NameProfile.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == '(')
				{
					position = j - 1;
					break;
				}
			NameProfile.Delete(position, NameProfile.GetLength() - position);
			if (!ProfilesRS.IsBOF())
				ProfilesRS.MoveFirst();
			while (!ProfilesRS.IsEOF())
			{
				if (ProfilesRS.m_Name_profile == NameProfile)
				{
					if (ProfilesRS.m_Type_profile == 1)
					{
						EditProfileExpDlg dlg;
						dlg.IniFile = IniFile;
						dlg.m_Name_profile_str = ProfilesRS.m_Name_profile;
						dlg.NumberSection = ProfilesRS.m_Number_section;
						dlg.GroupSection = ProfilesRS.m_Group_section;
						dlg.PathSection = ProfilesRS.m_Path_section;
						dlg.TypeSourceData = ProfilesRS.m_Type_source_data;
						dlg.m_Choosen_folder_str = ProfilesRS.m_Folder;
						sprintf(buffer, "%f", ProfilesRS.m_Factor_x);
						dlg.m_Factor_x_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Factor_y);
						dlg.m_Factor_y_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Shift_x);
						dlg.m_Shift_x_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Shift_y);
						dlg.m_Shift_y_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Turn);
						dlg.m_Turn_str = buffer;
						dlg.m_Metre_int = ProfilesRS.m_Unit;
						dlg.m_Graph_area_bool = ProfilesRS.m_Graph_area;
						dlg.GraphArea = ProfilesRS.m_Graph_area_id;
						if (dlg.DoModal() == IDOK)
						{
							ProfilesRS.Edit();
							ProfilesRS.m_Name_profile = dlg.m_Name_profile_str;
							ProfilesRS.m_Number_section = dlg.NumberSection;
							ProfilesRS.m_Group_section = dlg.GroupSection;
							ProfilesRS.m_Path_section = dlg.PathSection;
							ProfilesRS.m_Type_source_data = dlg.TypeSourceData;
							ProfilesRS.m_Folder = dlg.m_Choosen_folder_str;
							ProfilesRS.m_Factor_x = atof(dlg.m_Factor_x_str);
							ProfilesRS.m_Factor_y = atof(dlg.m_Factor_y_str);
							ProfilesRS.m_Shift_x = atof(dlg.m_Shift_x_str);
							ProfilesRS.m_Shift_y = atof(dlg.m_Shift_y_str);
							ProfilesRS.m_Turn = atof(dlg.m_Turn_str);
							if (dlg.GraphAreaEnable)
								ProfilesRS.m_Graph_area = dlg.m_Graph_area_bool;
							else
								ProfilesRS.m_Graph_area = false;
							if (dlg.m_Graph_area_bool && dlg.GraphAreaEnable)
								ProfilesRS.m_Graph_area_id = dlg.GraphArea;
							else
								ProfilesRS.m_Graph_area_id = -1;
							ProfilesRS.m_Unit = dlg.m_Metre_int;
							m_Tree->SetItemText(ExpImpElement[i], dlg.m_Name_profile_str + " (Экспорт)");
							ProfilesRS.Update();
							TreeWidth = 0;
							for (int k = 0; k < ExpImpElement.size(); k++)
							{
								if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96 > TreeWidth)
									TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96;
								if ((m_Tree->GetItemState(ExpImpElement[k], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
									for (int j = 0; j < FileElement.size(); j++)
									{
										if (m_Tree->GetParentItem(FileElement[j]) == ExpImpElement[k])
											if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112 > TreeWidth)
												TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112;
									}
							}
							OnInitialUpdate();
						}
					}
					if (ProfilesRS.m_Type_profile == 2)
					{
						EditProfileImpDlg dlg;
						dlg.IniFile = IniFile;
						dlg.m_Name_profile_str = ProfilesRS.m_Name_profile;
						dlg.NumberSection = ProfilesRS.m_Number_section;
						dlg.GroupSection = ProfilesRS.m_Group_section;
						dlg.PathSection = ProfilesRS.m_Path_section;
						dlg.TypeSourceData = ProfilesRS.m_Type_source_data;
						dlg.m_Choosen_folder_str = ProfilesRS.m_Folder;
						sprintf(buffer, "%f", ProfilesRS.m_Factor_x);
						dlg.m_Factor_x_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Factor_y);
						dlg.m_Factor_y_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Shift_x);
						dlg.m_Shift_x_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Shift_y);
						dlg.m_Shift_y_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Turn);
						dlg.m_Turn_str = buffer;
						dlg.m_Usual_int = ProfilesRS.m_Initial_order_coordinates;
						if (dlg.DoModal() == IDOK)
						{
							ProfilesRS.Edit();
							ProfilesRS.m_Name_profile = dlg.m_Name_profile_str;
							ProfilesRS.m_Number_section = dlg.NumberSection;
							ProfilesRS.m_Group_section = dlg.GroupSection;
							ProfilesRS.m_Path_section = dlg.PathSection;
							ProfilesRS.m_Type_source_data = dlg.TypeSourceData;
							ProfilesRS.m_Folder = dlg.m_Choosen_folder_str;
							ProfilesRS.m_Factor_x = atof(dlg.m_Factor_x_str);
							ProfilesRS.m_Factor_y = atof(dlg.m_Factor_y_str);
							ProfilesRS.m_Shift_x = atof(dlg.m_Shift_x_str);
							ProfilesRS.m_Shift_y = atof(dlg.m_Shift_y_str);
							ProfilesRS.m_Turn = atof(dlg.m_Turn_str);
							ProfilesRS.m_Initial_order_coordinates = dlg.m_Usual_int;
							m_Tree->SetItemText(ExpImpElement[i], dlg.m_Name_profile_str + " (Импорт)");
							ProfilesRS.Update();
							TreeWidth = 0;
							for (int k = 0; k < ExpImpElement.size(); k++)
							{
								if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96 > TreeWidth)
									TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96;
								if ((m_Tree->GetItemState(ExpImpElement[k], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
									for (int j = 0; j < FileElement.size(); j++)
									{
										if (m_Tree->GetParentItem(FileElement[j]) == ExpImpElement[k])
											if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112 > TreeWidth)
												TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112;
									}
							}
							OnInitialUpdate();
						}
					}
					if (ProfilesRS.m_Type_profile == 3)
					{
						EditProfileTransDlg dlg;
						dlg.IniFile = IniFile;
						dlg.m_Name_profile_str = ProfilesRS.m_Name_profile;
						dlg.NumberSection = ProfilesRS.m_Number_section;
						dlg.GroupSection = ProfilesRS.m_Group_section;
						dlg.PathSection = ProfilesRS.m_Path_section;
						dlg.TypeSourceData = ProfilesRS.m_Type_source_data;
						sprintf(buffer, "%f", ProfilesRS.m_Factor_x);
						dlg.m_Factor_x_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Factor_y);
						dlg.m_Factor_y_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Shift_x);
						dlg.m_Shift_x_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Shift_y);
						dlg.m_Shift_y_str = buffer;
						sprintf(buffer, "%f", ProfilesRS.m_Turn);
						dlg.m_Turn_str = buffer;
						sprintf(buffer, "%i", ProfilesRS.m_Size_x);
						dlg.m_Size_x_str = buffer;
						sprintf(buffer, "%i", ProfilesRS.m_Size_y);
						dlg.m_Size_y_str = buffer;
						if (dlg.DoModal() == IDOK)
						{
							ProfilesRS.Edit();
							ProfilesRS.m_Name_profile = dlg.m_Name_profile_str;
							ProfilesRS.m_Number_section = dlg.NumberSection;
							ProfilesRS.m_Group_section = dlg.GroupSection;
							ProfilesRS.m_Path_section = dlg.PathSection;
							ProfilesRS.m_Type_source_data = dlg.TypeSourceData;
							ProfilesRS.m_Factor_x = atof(dlg.m_Factor_x_str);
							ProfilesRS.m_Factor_y = atof(dlg.m_Factor_y_str);
							ProfilesRS.m_Shift_x = atof(dlg.m_Shift_x_str);
							ProfilesRS.m_Shift_y = atof(dlg.m_Shift_y_str);
							ProfilesRS.m_Turn = atof(dlg.m_Turn_str);
							m_Tree->SetItemText(ExpImpElement[i], dlg.m_Name_profile_str + " (Преобразование координат)");
							ProfilesRS.Update();
							TreeWidth = 0;
							for (int k = 0; k < ExpImpElement.size(); k++)
							{
								if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96 > TreeWidth)
									TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96;
								if ((m_Tree->GetItemState(ExpImpElement[k], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
									for (int j = 0; j < FileElement.size(); j++)
									{
										if (m_Tree->GetParentItem(FileElement[j]) == ExpImpElement[k])
											if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112 > TreeWidth)
												TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112;
									}
							}
							OnInitialUpdate();
						}
					}
					if (ProfilesRS.m_Type_profile == 4)
					{
						EditProfileReorgDlg dlg;
						dlg.IniFile = IniFile;
						dlg.m_Name_profile_str = ProfilesRS.m_Name_profile;
						dlg.NumberSection = ProfilesRS.m_Number_section;
						dlg.GroupSection = ProfilesRS.m_Group_section;
						dlg.PathSection = ProfilesRS.m_Path_section;
						dlg.TypeSourceData = ProfilesRS.m_Type_source_data;
						if (dlg.DoModal() == IDOK)
						{
							ProfilesRS.Edit();
							ProfilesRS.m_Name_profile = dlg.m_Name_profile_str;
							ProfilesRS.m_Number_section = dlg.NumberSection;
							ProfilesRS.m_Group_section = dlg.GroupSection;
							ProfilesRS.m_Path_section = dlg.PathSection;
							ProfilesRS.m_Type_source_data = dlg.TypeSourceData;
							m_Tree->SetItemText(ExpImpElement[i], dlg.m_Name_profile_str + " (Реорганизация координат)");
							ProfilesRS.Update();
							TreeWidth = 0;
							for (int k = 0; k < ExpImpElement.size(); k++)
							{
								if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96 > TreeWidth)
									TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96;
								if ((m_Tree->GetItemState(ExpImpElement[k], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
									for (int j = 0; j < FileElement.size(); j++)
									{
										if (m_Tree->GetParentItem(FileElement[j]) == ExpImpElement[k])
											if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112 > TreeWidth)
												TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112;
									}
							}
							OnInitialUpdate();
						}
					}
				}
				ProfilesRS.MoveNext();
			}
			break;
		}
	for (i = 0; i < FileElement.size(); i++)
		if (m_Tree->GetSelectedItem() == FileElement[i])
		{
			strcpy(buffer, m_Tree->GetItemText(m_Tree->GetParentItem(FileElement[i])));
			NameProfile = buffer;
			for (int j = NameProfile.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == '(')
				{
					position = j - 1;
					break;
				}
			NameProfile.Delete(position, NameProfile.GetLength() - position);
			if (!ProfilesRS.IsBOF())
				ProfilesRS.MoveFirst();
			while (!ProfilesRS.IsEOF())
			{
				if (ProfilesRS.m_Name_profile == NameProfile)
				{
					if (!FilesRS.IsBOF())
						FilesRS.MoveFirst();
					while (!FilesRS.IsEOF())
					{
						if (FilesRS.m_Name_file == m_Tree->GetItemText(FileElement[i]) && FilesRS.m_Id_profile == ProfilesRS.m_Id_profile)
						{
							if (ProfilesRS.m_Type_profile == 1)
							{
								EditFilesExpDlg dlg;
								dlg.IniFile = IniFile;
								dlg.IdProfile = ProfilesRS.m_Id_profile;
								dlg.NameFile_str = FilesRS.m_Name_file;
								dlg.TypeGraphObject_int = FilesRS.m_Type_graph_object;
								dlg.TypeGraphObj_int = FilesRS.m_Type_graph_obj;
								dlg.m_Complement_areas_centers_knots_bool = FilesRS.m_Complement_areas_centers_knots;
								dlg.m_Query_exp_str = FilesRS.m_Query_exp;
								dlg.StrConnection = ProfilesRS.m_Path_section;
								dlg.GROUPREG = ProfilesRS.m_Group_section;
								if (dlg.DoModal() == IDOK)
								{
									FilesRS.Edit();
									FilesRS.m_Name_file = dlg.NameFile_str;
									FilesRS.m_Type_graph_object = dlg.TypeGraphObject_int;
									FilesRS.m_Type_graph_obj = dlg.TypeGraphObj_int;
									if (ProfilesRS.m_Group_section != 2)
										FilesRS.m_Complement_areas_centers_knots = dlg.m_Complement_areas_centers_knots_bool;
									else
										FilesRS.m_Complement_areas_centers_knots = false;
									FilesRS.m_Query_exp = dlg.m_Query_exp_str;
									m_Tree->SetItemText(FileElement[i], dlg.NameFile_str);
									FilesRS.Update();
									TreeWidth = 0;
									for (int k = 0; k < ExpImpElement.size(); k++)
									{
										if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96 > TreeWidth)
											TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96;
										if ((m_Tree->GetItemState(ExpImpElement[k], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
											for (int j = 0; j < FileElement.size(); j++)
											{
												if (m_Tree->GetParentItem(FileElement[j]) == ExpImpElement[k])
													if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112 > TreeWidth)
														TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112;
											}
									}
									OnInitialUpdate();
								}
							}
							else
							{
								EditFilesImpDlg dlg;
								dlg.IniFile = IniFile;
								dlg.StrConnection = ProfilesRS.m_Path_section;
								dlg.IdProfile = ProfilesRS.m_Id_profile;
								dlg.m_File_name_str = FilesRS.m_Name_file;
								dlg.Folder = ProfilesRS.m_Folder;
								dlg.AcceptingTypeLines = FilesRS.m_Accepting_type_lines;
								dlg.LevelLines = FilesRS.m_Level_lines;
								dlg.m_Break_lines_segments_bool = FilesRS.m_Break_lines_segments;
								dlg.m_Skip_superfluous_points_bool = FilesRS.m_Skip_superfluous_points;
								dlg.m_Windows_int = FilesRS.m_Code_text;
								dlg.AcceptingTypeText = FilesRS.m_Accepting_type_text;
								dlg.LevelText = FilesRS.m_Level_text;
								dlg.TransformDenotations = FilesRS.m_Transform_denotations;
								dlg.TypeTransformedDenotations = FilesRS.m_Type_transformed_denotations;
								dlg.LevelDenotations = FilesRS.m_Level_denotations;
								sprintf(buffer, "%f", FilesRS.m_Size_denotations);
								dlg.m_Size_denotations_str = buffer;
								dlg.m_Import_charakteristics_bool = FilesRS.m_Import_charakteristics;
								dlg.NumberFieldCharakteristics = FilesRS.m_Number_field_charakteristics;
								dlg.AcceptingTypeCharakteristics = FilesRS.m_Accepting_type_charakteristics;
								dlg.LevelCharakteristics = FilesRS.m_Level_charakteristics;
								sprintf(buffer, "%.2f", FilesRS.m_Height_charakteristics);
								dlg.m_Height_charakteristics_str = buffer;
								if (FilesRS.m_Delete_graph_object == 1)
									dlg.m_Delete_graph_object_bool = true;
								else
									dlg.m_Delete_graph_object_bool = false;
								if (dlg.DoModal() == IDOK)
								{
									FilesRS.Edit();
									FilesRS.m_Id_profile = ProfilesRS.m_Id_profile;
									FilesRS.m_Name_file = dlg.m_File_name_str;
									FilesRS.m_Type_graph_object = -1;
									FilesRS.m_Type_graph_obj = -1;
									if (dlg.ImportLinesEnable)
									{
										FilesRS.m_Accepting_type_lines = dlg.AcceptingTypeLines;
										FilesRS.m_Level_lines = dlg.LevelLines;
										FilesRS.m_Break_lines_segments = dlg.m_Break_lines_segments_bool;
										FilesRS.m_Skip_superfluous_points = dlg.m_Skip_superfluous_points_bool;
									}
									else
									{
										FilesRS.m_Accepting_type_lines = -1;
										FilesRS.m_Level_lines = -1;
									}
									FilesRS.m_Code_text = dlg.m_Windows_int;
									if (dlg.ImportTextEnable)
									{
										FilesRS.m_Accepting_type_text = dlg.AcceptingTypeText;
										FilesRS.m_Level_text = dlg.LevelText;
									}
									else
									{
										FilesRS.m_Accepting_type_text = -1;
										FilesRS.m_Level_text = -1;
									}
									if (dlg.ImportDenotationsEnable)
									{
										FilesRS.m_Transform_denotations = dlg.m_Circles_int;
										FilesRS.m_Type_transformed_denotations = dlg.TypeTransformedDenotations;
										FilesRS.m_Level_denotations = dlg.LevelDenotations;
										FilesRS.m_Size_denotations = atof(dlg.m_Size_denotations_str);
									}
									else
									{
										FilesRS.m_Transform_denotations = -1;
										FilesRS.m_Type_transformed_denotations = -1;
										FilesRS.m_Level_denotations = -1;
										FilesRS.m_Size_denotations = 0;
									}
									if (dlg.ImportCharakteristicsEnable)
										FilesRS.m_Import_charakteristics = dlg.m_Import_charakteristics_bool;
									else
										FilesRS.m_Import_charakteristics = false;
									if (dlg.m_Import_charakteristics_bool && dlg.ImportCharakteristicsEnable)
									{
										FilesRS.m_Number_field_charakteristics = dlg.m_Name_field_charakteristics_int;
										FilesRS.m_Accepting_type_charakteristics = dlg.AcceptingTypeCharakteristics;
										FilesRS.m_Level_charakteristics = dlg.LevelCharakteristics;
										FilesRS.m_Height_charakteristics = atof(dlg.m_Height_charakteristics_str);
									}
									else
									{
										FilesRS.m_Number_field_charakteristics = -1;
										FilesRS.m_Accepting_type_charakteristics = -1;
										FilesRS.m_Level_charakteristics = -1;
										FilesRS.m_Height_charakteristics = 0;
									}
									if (dlg.m_Delete_graph_object_bool)
										FilesRS.m_Delete_graph_object = 1;
									else
										FilesRS.m_Delete_graph_object = 2;
									m_Tree->SetItemText(FileElement[i], dlg.m_File_name_str);
									FilesRS.Update();
									TreeWidth = 0;
									for (int k = 0; k < ExpImpElement.size(); k++)
									{
										if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96 > TreeWidth)
											TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[k])).cx + 96;
										if ((m_Tree->GetItemState(ExpImpElement[k], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
											for (int j = 0; j < FileElement.size(); j++)
											{
												if (m_Tree->GetParentItem(FileElement[j]) == ExpImpElement[k])
													if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112 > TreeWidth)
														TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112;
											}
									}
									OnInitialUpdate();
								}
							}
							break;
						}
						FilesRS.MoveNext();
					}
					break;
				}
				ProfilesRS.MoveNext();
			}
			m_Tree->SelectItem(FileElement[i]);
			break;
		}
	ProfilesRS.Close();
	FilesRS.Close();
}

void CGraphExpImpView::OnUpdateOperationsEdit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(OperationsEdit);
}

void CGraphExpImpView::OnUpdateEdit(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(Edit);
}

void CGraphExpImpView::OnPopupEdit() 
{
	// TODO: Add your command handler code here
	OnOperationsEdit();
}

void CGraphExpImpView::OnDblclkTree(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	OnOperationsEdit();
	*pResult = 0;
}

void CGraphExpImpView::OnOperationsDelete() 
{
	// TODO: Add your command handler code here
	CFont* m_pFont = new CFont;
	CWindowDC winDC(this);
	CPaintDC paintDC(this);
	LOGFONT lf;
	char buffer[MAX_PATH];
	vector <HTREEITEM>::iterator CurrentExpImpElement;
	vector <HTREEITEM>::iterator CurrentFileElement;
	CString NameProfile;
	int position;
	m_pFont = m_Tree->GetFont();
	m_pFont->GetLogFont(&lf);
	paintDC.SelectObject(m_pFont);
	ProfilesRS.Open();
	FilesRS.Open();
	CurrentExpImpElement = ExpImpElement.begin();
	for (int i = 0; i < ExpImpElement.size(); i++, CurrentExpImpElement++)
		if (m_Tree->GetSelectedItem() == ExpImpElement[i])
		{
			strcpy(buffer, m_Tree->GetItemText(ExpImpElement[i]));
			NameProfile = buffer;
			for (int j = NameProfile.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == '(')
				{
					position = j - 1;
					break;
				}
			NameProfile.Delete(position, NameProfile.GetLength() - position);
			if (!ProfilesRS.IsBOF())
				ProfilesRS.MoveFirst();
			while (!ProfilesRS.IsEOF())
			{
				if (ProfilesRS.m_Name_profile == NameProfile)
				{
					if (MessageBox("Вы действительно хотите удалить профиль?", "Сообщение", MB_YESNO | MB_ICONQUESTION) == IDYES)
					{
						if ((m_Tree->GetItemState(ExpImpElement[i], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
							for (j = 0; j < FileElement.size(); j++)
								if (ExpImpElement[i] == m_Tree->GetParentItem(FileElement[j]))
									TreeHeight = TreeHeight + MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
						TreeHeight = TreeHeight + MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
						ProfilesRS.Delete();
						m_Tree->DeleteItem(ExpImpElement[i]);
						ExpImpElement.erase(CurrentExpImpElement);
						OnInitialUpdate();
					}
				}
				ProfilesRS.MoveNext();
			}
			break;
		}
	CurrentFileElement = FileElement.begin();
	for (i = 0; i < FileElement.size(); i++, CurrentFileElement++)
		if (m_Tree->GetSelectedItem() == FileElement[i])
		{
			strcpy(buffer, m_Tree->GetItemText(m_Tree->GetParentItem(FileElement[i])));
			NameProfile = buffer;
			for (int j = NameProfile.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == '(')
				{
					position = j - 1;
					break;
				}
			NameProfile.Delete(position, NameProfile.GetLength() - position);
			if (!ProfilesRS.IsBOF())
				ProfilesRS.MoveFirst();
			while (!ProfilesRS.IsEOF())
			{
				if (ProfilesRS.m_Name_profile == NameProfile)
				{
					if (!FilesRS.IsBOF())
						FilesRS.MoveFirst();
					while (!FilesRS.IsEOF())
					{
						if (FilesRS.m_Name_file == m_Tree->GetItemText(FileElement[i]) && FilesRS.m_Id_profile == ProfilesRS.m_Id_profile)
						{
							if (MessageBox("Вы действительно хотите удалить файл?", "Сообщение", MB_YESNO | MB_ICONQUESTION) == IDYES)
							{
								FilesRS.Delete();
								m_Tree->DeleteItem(FileElement[i]);
								FileElement.erase(CurrentFileElement);
								TreeHeight = TreeHeight + MulDiv(lf.lfHeight, 72 * winDC.GetDeviceCaps(LOGPIXELSY) / 96, winDC.GetDeviceCaps(LOGPIXELSY)) * 2;
							}
							break;
						}
						FilesRS.MoveNext();
					}
					break;
				}
				ProfilesRS.MoveNext();
			}
			break;
		}
	TreeWidth = 0;
	for (i = 0; i < ExpImpElement.size(); i++)
	{
		if (paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[i])).cx + 96 > TreeWidth)
			TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(ExpImpElement[i])).cx + 96;
		if ((m_Tree->GetItemState(ExpImpElement[i], TVIS_EXPANDED) & TVIS_EXPANDED) == TVIS_EXPANDED)
			for (int j = 0; j < FileElement.size(); j++)
				if (m_Tree->GetParentItem(FileElement[j]) == ExpImpElement[i])
					if (paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112 > TreeWidth)
						TreeWidth = paintDC.GetTextExtent(m_Tree->GetItemText(FileElement[j])).cx + 112;
	}
	if (ExpImpElement.size() == 0)
	{
		OperationsCreateFile = FALSE;
		CreateNewFile = FALSE;
		OperationsCreateSample = FALSE;
		CreateSample = FALSE;
		OperationsEdit = FALSE;
		Edit = FALSE;
		OperationsDelete = FALSE;
		Delete = FALSE;
	}
	OnInitialUpdate();
	ProfilesRS.Close();
	FilesRS.Close();
}

void CGraphExpImpView::OnUpdateOperationsDelete(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(OperationsDelete);
}

void CGraphExpImpView::OnUpdateDelete(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(Delete);
}

void CGraphExpImpView::OnPopupDelete()
{
	// TODO: Add your command handler code here
	OnOperationsDelete();
}

void CGraphExpImpView::OnOperationsExecute()
{
	// TODO: Add your command handler code here
	string s;
	ifstream *in;
	char buffer[MAX_PATH], igrp_str[MAX_PATH],  iscp_str[MAX_PATH], iicn_str[MAX_PATH], message[MAX_PATH];
	CString NameProfile, WayDBF, S;
	int z = 0, k = 0, position, PERSON, szx, szy, start = 0, end = 0;
	bool file_element = true, type_char = false;
	ProfilesRS.Open();
	FilesRS.Open();
	GetPrivateProfileString("Supshort", "PERSON", NULL, buffer, sizeof(buffer), IniFile);
	PERSON = atoi(buffer);
	WayDBF = IniFile;
	for (int i = WayDBF.GetLength() - 1; i >= 0; i--)
		if (IniFile[i] == '\\')
		{
			WayDBF.Delete(i, WayDBF.GetLength() - i);
			break;
		}
	PlsizeRead rspls;
	rspls.IniFile = IniFile;
	rspls.Open();
	szx = rspls.m_SIZX;
	szy = rspls.m_SIZY;
	for (i = 0; i < ExpImpElement.size(); i++)
		if (m_Tree->GetSelectedItem() == ExpImpElement[i])
		{
			strcpy(buffer, m_Tree->GetItemText(ExpImpElement[i]));
			NameProfile = buffer;
			for (int j = NameProfile.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == '(')
				{
					position = j - 1;
					break;
				}
			NameProfile.Delete(position, NameProfile.GetLength() - position);
			if (!ProfilesRS.IsBOF())
				ProfilesRS.MoveFirst();
			while (!ProfilesRS.IsEOF())
			{
				if (ProfilesRS.m_Name_profile == NameProfile)
				{
					if (ProfilesRS.m_Type_profile == 1)
					{
						if (!FilesRS.IsBOF())
							FilesRS.MoveFirst();
						while (!FilesRS.IsEOF())
						{
							if (FilesRS.m_Id_profile == ProfilesRS.m_Id_profile)
							{
								ReorgParam* rgpm = new ReorgParam;
								rgpm->nmsrs = ProfilesRS.m_Path_section;
								rgpm->foldnm = ProfilesRS.m_Folder;
								rgpm->mfnm = FilesRS.m_Name_file;
								rgpm->ig = ProfilesRS.m_Group_section;
								rgpm->iscirccd = ProfilesRS.m_Type_source_data;
								rgpm->lnlev = FilesRS.m_Type_graph_obj;
								rgpm->lntp = FilesRS.m_Type_graph_object;
								rgpm->iswincd = ProfilesRS.m_Unit;
								rgpm->xshift = ProfilesRS.m_Shift_x;
								rgpm->xkoef = ProfilesRS.m_Factor_x;
								rgpm->yshift = ProfilesRS.m_Shift_x;
								rgpm->ykoef = ProfilesRS.m_Factor_y;
								rgpm->angrt = ProfilesRS.m_Turn;
								rgpm->txtp = ProfilesRS.m_Graph_area_id;
								rgpm->codk = PERSON;
								if (FilesRS.m_Complement_areas_centers_knots)
									rgpm->numfld = 1;
								else
									rgpm->numfld = 0;
								rgpm->quernm = FilesRS.m_Query_exp;
								rgpm->crdsys = " ";
								ScrToMifEx(rgpm);
							}
							FilesRS.MoveNext();
						}
						MessageBox("Экспорт завершён!", "Сообщение", MB_OK | MB_ICONINFORMATION);
					}
					if (ProfilesRS.m_Type_profile == 2)
					{
						if (!FilesRS.IsBOF())
							FilesRS.MoveFirst();
						while (!FilesRS.IsEOF())
						{
							if (FilesRS.m_Id_profile == ProfilesRS.m_Id_profile)
								k++;
							FilesRS.MoveNext();
						}
						if (!FilesRS.IsBOF())
							FilesRS.MoveFirst();
						while (!FilesRS.IsEOF())
						{
							if (FilesRS.m_Id_profile == ProfilesRS.m_Id_profile)
							{
								in = new ifstream[k];
								in[z].open(ProfilesRS.m_Folder + "\\" + FilesRS.m_Name_file + ".mif");
								if (in[z].is_open())
								{
									end = 0;
									start = 0;
									ReorgParam* rgpm = new ReorgParam;
									rgpm->cdirb = WayDBF;
									rgpm->nmsrs = ProfilesRS.m_Path_section;
									rgpm->foldnm = ProfilesRS.m_Folder;
									rgpm->mfnm = FilesRS.m_Name_file + ".mif";
									rgpm->ig = ProfilesRS.m_Group_section;
									rgpm->szx = szx;
									rgpm->szy = szy;
									rgpm->rgrecr = 1;
									rgpm->iswincd = FilesRS.m_Code_text;
									rgpm->isugcrd = ProfilesRS.m_Initial_order_coordinates;
									rgpm->iscirccd = FilesRS.m_Transform_denotations;
									rgpm->issmoln = FilesRS.m_Skip_superfluous_points;
									rgpm->lntp = FilesRS.m_Accepting_type_lines;
									rgpm->lnlev = FilesRS.m_Level_lines;
									rgpm->txtp = FilesRS.m_Accepting_type_text;
									rgpm->txlev = FilesRS.m_Level_text;
									rgpm->prtp = FilesRS.m_Type_transformed_denotations;
									rgpm->prlev = FilesRS.m_Level_denotations;
									rgpm->coddel = FilesRS.m_Break_lines_segments;
									if (FilesRS.m_Import_charakteristics)
										rgpm->codk = 0;
									else
										rgpm->codk = -1;
									rgpm->txtpk = FilesRS.m_Accepting_type_charakteristics;
									rgpm->txlevk = FilesRS.m_Level_charakteristics;
									rgpm->numfld = FilesRS.m_Number_field_charakteristics;
									rgpm->xshift = ProfilesRS.m_Shift_x;
									rgpm->xkoef = ProfilesRS.m_Factor_x;
									rgpm->yshift = ProfilesRS.m_Shift_y;
									rgpm->ykoef = ProfilesRS.m_Factor_y;
									rgpm->rad = FilesRS.m_Size_denotations;
									rgpm->angrt = ProfilesRS.m_Turn;
									rgpm->hkhr = FilesRS.m_Height_charakteristics;
									while (!in[z].eof())
									{
										getline(in[z], s);
										S = s.c_str();
										if (start == 1)
											start++;
										if (S.Left(7).CompareNoCase("columns") == 0)
											start++;
										if (S.Left(4).CompareNoCase("data") == 0)
											end++;
										if (start > 1 && end == 0 && S.GetLength() > 0)
										{
											strcpy(buffer, S);
											for (int j = 0; buffer[j] == ' '; j++)
												S.Delete(0, 1);
											strcpy(buffer, S);
											for (j = 0; j < S.GetLength(); j++)
												if (buffer[j] == ' ')
												{
													S.Delete(j, S.GetLength() - j);
													break;
												}
											rgpm->midfldn.Add(S);
										}
										S = s.c_str();
										if (start > 1 && end == 0 && S.GetLength() > 0)
										{
											type_char = false;
											strcpy(buffer, S);
											for (int j = 0; j < S.GetLength(); j++)
												if (buffer[j] == '(')
													type_char = true;
											if (type_char)
											{
												for (int j = 0; j < S.GetLength(); j++)
													if (buffer[j] == '(')
													{
														S.Delete(0, j + 1);
														S.Delete(S.GetLength() - 1, 1);
													}
											}
											else
												S = "20";
											rgpm->midfldl.Add(atoi(S));
										}
									}
									MifToDbfEx(rgpm);
									sprintf(igrp_str, "%i", rgpm->igrp);
									sprintf(iscp_str, "%i", rgpm->iscp);
									sprintf(iicn_str, "%i", rgpm->iicn);
									strcpy(message, "Подготовлено ко вводу:\nломанных: ");
									strcat(message, igrp_str);
									strcat(message, "\nтекстовых строк: ");
									strcat(message, iscp_str);
									strcat(message, "\nобозначений: ");
									strcat(message, iicn_str);
									strcat(message, "\nЗаносить новые данные в базу данных?");
									if (MessageBox(message, "Сообщение", MB_YESNO | MB_ICONWARNING) == IDYES)
									{
										ReorgParam* rgpm_imp = new ReorgParam;
										rgpm_imp->cdirb = rgpm->cdirb;
										rgpm_imp->nmsrs = rgpm->nmsrs;
										rgpm_imp->ig = rgpm->ig;
										rgpm_imp->lntp = rgpm->lntp;
										rgpm_imp->txtp = rgpm->txtp;
										rgpm_imp->igrp = rgpm->igrp;
										rgpm_imp->iscp = rgpm->iscp;
										rgpm_imp->iicn = rgpm->iicn;
										rgpm_imp->codl = 0;
										rgpm_imp->codt = 0;
										rgpm_imp->codp = 0;
										rgpm_imp->coddel = FilesRS.m_Delete_graph_object;
										DbfToMdb(rgpm_imp);
										HKEY rKey;
										unsigned char Reget[MAX_PATH];
										DWORD RegetPath = sizeof(Reget);
										RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\ODBC\\ODBC.INI\\" + ProfilesRS.m_Path_section, 0, KEY_QUERY_VALUE, &rKey);
										RegQueryValueEx(rKey, "DBQ", NULL, NULL, Reget, &RegetPath);
										RegCloseKey(rKey);
										CString WaySource = Reget;
										for (int j = WaySource.GetLength() - 1; j >= 0; j--)
											if (Reget[j] == '\\')
											{
												WaySource.Delete(j, WaySource.GetLength() - j);
												break;
											}
										SQLConfigDataSource(NULL, ODBC_ADD_DSN, "Microsoft Access Driver (*.mdb)", "CREATE_DB=" + WaySource + "\\Save_dbf.mdb General\0");
										CDatabNet* db = new CDatabNet;
										frmdbsrc("Microsoft dBase Driver (*.dbf)", "tmp_dbf_source", "Temporary source for dbf bases", WayDBF, ODBC_ADD_DSN);
										db->OpenNet("tmp_dbf_source", FALSE);
										CString NameTable;
										NameTable = FilesRS.m_Name_file;
										if (NameTable.GetLength() > 8)
											NameTable.Delete(8, NameTable.GetLength() - 8);
										if (db->isTable(NameTable) > -1)
										{
											CDatabNet* dn = new CDatabNet;
											CRecordNet rn;
											CString SQL_str;
											dn->OpenNet("ODBC;DSN=MS Access Database;DBQ=" + WaySource + "\\Save_dbf.mdb", FALSE);
											rn.InitRecordNet(db, NameTable);
											if (dn->isTable(NameTable) == -1)
											{
												SQL_str = "CREATE TABLE " + NameTable + " (";
												for (int j = 0; j < rn.FieldNameArray.GetSize(); j++)
													if (j < rn.FieldNameArray.GetSize() - 1)
														SQL_str = SQL_str + rn.FieldNameArray[j] + " CHAR(50), ";
													else
														SQL_str = SQL_str + rn.FieldNameArray[j] + " CHAR(50)";
												SQL_str = SQL_str + ")";
												dn->ExecuteSQLNet(SQL_str);
											}
											else
											{
												if (MessageBox("Таблица " + NameTable + " уже существует! Удалить имеющиеся данные?", "Сообщение", MB_YESNO | MB_ICONWARNING) == IDYES)
													dn->ExecuteSQLNet("DELETE * FROM " + NameTable);
												else
													if (MessageBox("Создать новую таблицу для добавления данных (в случае отказа данные будут добавлены в существующую таблицу)?", "Сообщение", MB_YESNO | MB_ICONWARNING) == IDYES)
													{
														NameNewTableDlg dlg;
														if (dlg.DoModal() == IDOK)
														{
															SQL_str = "CREATE TABLE " + dlg.m_Name_table_str + " (";
															for (int j = 0; j < rn.FieldNameArray.GetSize(); j++)
																if (j < rn.FieldNameArray.GetSize() - 1)
																	SQL_str = SQL_str + rn.FieldNameArray[j] + " CHAR(50), ";
																else
																	SQL_str = SQL_str + rn.FieldNameArray[j] + " CHAR(50)";
															SQL_str = SQL_str + ")";
															dn->ExecuteSQLNet(SQL_str);
															NameTable = dlg.m_Name_table_str;
														}
													}
											}
											SQL_str = "INSERT INTO " + NameTable + " (";
											for (int j = 0; j < rn.FieldNameArray.GetSize(); j++)
												if (j < rn.FieldNameArray.GetSize() - 1)
													SQL_str = SQL_str + rn.FieldNameArray[j] + ", ";
												else
													SQL_str = SQL_str + rn.FieldNameArray[j];
											SQL_str = SQL_str + ") SELECT ";
											for (j = 0; j < rn.FieldNameArray.GetSize(); j++)
												if (j < rn.FieldNameArray.GetSize() - 1)
													SQL_str = SQL_str + rn.FieldNameArray[j] + ", ";
												else
													SQL_str = SQL_str + rn.FieldNameArray[j];
											NameTable = FilesRS.m_Name_file;
											if (NameTable.GetLength() > 8)
												NameTable.Delete(8, NameTable.GetLength() - 8);
											SQL_str = SQL_str + " FROM [dBase III; database=" + WayDBF + "]." + NameTable + ".DBF";
											dn->ExecuteSQLNet(SQL_str);
											rn.Close();
											dn->Close();
										}
										db->Close();
										frmdbsrc("Microsoft dBase Driver (*.dbf)", "tmp_dbf_source", "Temporary source for dbf bases", "", ODBC_REMOVE_DSN);
									}
								}
								else
									MessageBox("Файл " + FilesRS.m_Name_file + ".mif в папке " + ProfilesRS.m_Folder + " не найден!", "Сообщение", MB_OK | MB_ICONERROR);
								z++;
							}
							FilesRS.MoveNext();
						}
						MessageBox("Импорт завершён!", "Сообщение", MB_OK | MB_ICONINFORMATION);
					}
					if (ProfilesRS.m_Type_profile == 3)
					{
						ReorgParam* rgpm = new ReorgParam;
						rgpm->cdirb = WayDBF;
						rgpm->nmsrs = ProfilesRS.m_Path_section;
						rgpm->ig = ProfilesRS.m_Group_section;
						rgpm->rgrecr = 1;
						rgpm->xshift = ProfilesRS.m_Shift_x;
						rgpm->xkoef = ProfilesRS.m_Factor_x;
						rgpm->yshift = ProfilesRS.m_Shift_x;
						rgpm->ykoef = ProfilesRS.m_Factor_y;
						rgpm->angrt = ProfilesRS.m_Turn;
						rgpm->szx = szx;
						rgpm->szy = szy;
						rgpm->iscirccd = ProfilesRS.m_Type_source_data;
						ScrToDbf(rgpm);
						if (MessageBox("Выполнять изменение координат объектов?", "Сообщение", MB_YESNO | MB_ICONWARNING) == IDYES)
						{	
							CDatabNet* dn = new CDatabNet;
							int rtcd, iscrxy = -2, isnode, k = 0;
							CString scnmbuf, sbuf, sbuf1, crebuf;
							if ((rtcd = dn->OpenNet(rgpm->nmsrs, FALSE)) == 1)
							{
								scnmbuf = (rgpm->ig == 2)? "SCRC": "SCR";
								sbuf1 = scnmbuf + "XY";
								sbuf = (rgpm->ig == 2)? "DELETE FROM SCRCSQ;": "DELETE FROM SCRSQ;";
								if ((j = dn->ExecuteSQLNet(sbuf)) != 1)
									rtcd = k;
								iscrxy = dn->isTable(sbuf1);
								if (iscrxy >- 1)
								{
									sbuf = (rgpm->ig == 2)? "DELETE FROM SCRCXY;": "DELETE FROM SCRXY;";
									if ((k = dn->ExecuteSQLNet(sbuf)) != 1)
										rtcd = k;
								}
								sbuf = (rgpm->ig == 2)? "DELETE FROM SCRC;": "DELETE FROM SCR;";
								if ((k = dn->ExecuteSQLNet(sbuf)) != 1)
									rtcd = k;
								if ((isnode = dn->isTable("NODE")) >- 1)
								{ 
									if (dn->isTable("NODET") >- 1)
										if ((k = dn->ExecuteSQLNet("DROP TABLE NODET;")) != 1)
											rtcd = k;
									if (rtcd == 1)
									{
										crebuf = "CREATE TABLE NODET (NUMNODE LONG, SQX INT, SQY INT);";
										if ((k = dn->ExecuteSQLNet(crebuf)) != 1)
											rtcd = k;
									}
								}
								InsDbfCoor(WayDBF, scnmbuf, "NODET", "", dn, 1, iscrxy, isnode);
								dn->Close();
								if (rtcd > -1)
								{
									if (dn->OpenNet(rgpm->nmsrs, FALSE) == 1)
									{
										Reorgcr(scnmbuf, dn, rgpm->nmsrs);
										if ((iscrxy < 0) && (dn->isTable(sbuf1)) > -1)
										{
											crebuf = "DROP TABLE " + scnmbuf + "XY;";
											dn->ExecuteSQLNet(crebuf);
										}
										dn->Close();
									}
								}
								MessageBox("Преобразование координат завершено!", "Сообщение", MB_OK | MB_ICONINFORMATION);
							}
						}
					}
					if (ProfilesRS.m_Type_profile == 4)
					{
						CString grplbuf;
						CDatabNet* dn = new CDatabNet;
						dn->OpenNet("ODBC;DSN=" + ProfilesRS.m_Path_section, false);
						if (dn->isTable("scr") > -1)
							grplbuf = "scr";
						else
							grplbuf = "scrc";
						Reorgcr(grplbuf, dn, ProfilesRS.m_Path_section);
						dn->Close();
						MessageBox("Реорганизация координат завершена!", "Сообщение", MB_OK | MB_ICONINFORMATION);
					}
					file_element = false;
				}
				ProfilesRS.MoveNext();
			}
			break;
		}
	if (file_element)
		for (i = 0; i < FileElement.size(); i++)
			if (m_Tree->GetSelectedItem() == FileElement[i])
			{
				if (!FilesRS.IsBOF())
					FilesRS.MoveFirst();
				while (!FilesRS.IsEOF())
				{
					if (FilesRS.m_Name_file == m_Tree->GetItemText(FileElement[i]))
					{
						if (!ProfilesRS.IsBOF())
							ProfilesRS.MoveFirst();
						while (!ProfilesRS.IsEOF())
						{
							if (ProfilesRS.m_Id_profile == FilesRS.m_Id_profile)
							{
								if (ProfilesRS.m_Type_profile == 1)
								{
									ReorgParam* rgpm = new ReorgParam;
									rgpm->nmsrs = ProfilesRS.m_Path_section;
									rgpm->foldnm = ProfilesRS.m_Folder;
									rgpm->mfnm = FilesRS.m_Name_file;
									rgpm->ig = ProfilesRS.m_Group_section;
									rgpm->iscirccd = ProfilesRS.m_Type_source_data;
									rgpm->lnlev = FilesRS.m_Type_graph_obj;
									rgpm->lntp = FilesRS.m_Type_graph_object;
									rgpm->iswincd = ProfilesRS.m_Unit;
									rgpm->xshift = ProfilesRS.m_Shift_x;
									rgpm->xkoef = ProfilesRS.m_Factor_x;
									rgpm->yshift = ProfilesRS.m_Shift_x;
									rgpm->ykoef = ProfilesRS.m_Factor_y;
									rgpm->angrt = ProfilesRS.m_Turn;
									rgpm->txtp = ProfilesRS.m_Graph_area_id;
									rgpm->codk = PERSON;
									if (FilesRS.m_Complement_areas_centers_knots)
										rgpm->numfld = 1;
									else
										rgpm->numfld = 0;
									rgpm->crdsys = " ";
									rgpm->quernm = FilesRS.m_Query_exp;
									ScrToMifEx(rgpm);
									MessageBox("Экспорт завершён!", "Сообщение", MB_OK | MB_ICONINFORMATION);
								}
								if (ProfilesRS.m_Type_profile == 2)
								{
									in = new ifstream[1];
									in[0].open(ProfilesRS.m_Folder + "\\" + FilesRS.m_Name_file + ".mif");
									if (in[0].is_open())
									{
										ReorgParam* rgpm = new ReorgParam;
										rgpm->cdirb = WayDBF;
										rgpm->nmsrs = ProfilesRS.m_Path_section;
										rgpm->foldnm = ProfilesRS.m_Folder;
										rgpm->mfnm = FilesRS.m_Name_file + ".mif";
										rgpm->ig = ProfilesRS.m_Group_section;
										rgpm->szx = szx;
										rgpm->szy = szy;
										rgpm->rgrecr = 1;
										rgpm->iswincd = FilesRS.m_Code_text;
										rgpm->isugcrd = ProfilesRS.m_Initial_order_coordinates;
										rgpm->iscirccd = FilesRS.m_Transform_denotations;
										rgpm->issmoln = FilesRS.m_Skip_superfluous_points;
										rgpm->lntp = FilesRS.m_Accepting_type_lines;
										rgpm->lnlev = FilesRS.m_Level_lines;
										rgpm->txtp = FilesRS.m_Accepting_type_text;
										rgpm->txlev = FilesRS.m_Level_text;
										rgpm->prtp = FilesRS.m_Type_transformed_denotations;
										rgpm->prlev = FilesRS.m_Level_denotations;
										rgpm->coddel = FilesRS.m_Break_lines_segments;
										if (FilesRS.m_Import_charakteristics)
											rgpm->codk = 0;
										else
											rgpm->codk = -1;
										rgpm->txtpk = FilesRS.m_Accepting_type_charakteristics;
										rgpm->txlevk = FilesRS.m_Level_charakteristics;
										rgpm->numfld = FilesRS.m_Number_field_charakteristics;
										rgpm->xshift = ProfilesRS.m_Shift_x;
										rgpm->xkoef = ProfilesRS.m_Factor_x;
										rgpm->yshift = ProfilesRS.m_Shift_y;
										rgpm->ykoef = ProfilesRS.m_Factor_y;
										rgpm->rad = FilesRS.m_Size_denotations;
										rgpm->angrt = ProfilesRS.m_Turn;
										rgpm->hkhr = FilesRS.m_Height_charakteristics;
										while (!in[0].eof())
										{
											getline(in[0], s);
											S = s.c_str();
											if (start == 1)
												start++;
											if (S.Left(7).CompareNoCase("columns") == 0)
												start++;
											if (S.Left(4).CompareNoCase("data") == 0)
												end++;
											if (start > 1 && end == 0 && S.GetLength() > 0)
											{
												strcpy(buffer, S);
												for (int j = 0; buffer[j] == ' '; j++)
													S.Delete(0, 1);
												strcpy(buffer, S);
												for (j = 0; j < S.GetLength(); j++)
													if (buffer[j] == ' ')
													{
														S.Delete(j, S.GetLength() - j);
														break;
													}
												rgpm->midfldn.Add(S);
											}
											S = s.c_str();
											if (start > 1 && end == 0 && S.GetLength() > 0)
											{
												type_char = false;
												strcpy(buffer, S);
												for (int j = 0; j < S.GetLength(); j++)
													if (buffer[j] == '(')
														type_char = true;
												if (type_char)
												{
													for (int j = 0; j < S.GetLength(); j++)
														if (buffer[j] == '(')
														{
															S.Delete(0, j + 1);
															S.Delete(S.GetLength() - 1, 1);
														}
												}
												else
													S = "20";
												rgpm->midfldl.Add(atoi(S));
											}
										}
										MifToDbfEx(rgpm);
										sprintf(igrp_str, "%i", rgpm->igrp);
										sprintf(iscp_str, "%i", rgpm->iscp);
										sprintf(iicn_str, "%i", rgpm->iicn);
										strcpy(message, "Подготовлено ко вводу:\nломанных: ");
										strcat(message, igrp_str);
										strcat(message, "\nтекстовых строк: ");
										strcat(message, iscp_str);
										strcat(message, "\nобозначений: ");
										strcat(message, iicn_str);
										strcat(message, "\nЗаносить новые данные в базу данных?");
										if (MessageBox(message, "Сообщение", MB_YESNO | MB_ICONWARNING) == IDYES)
										{
											ReorgParam* rgpm_imp = new ReorgParam;
											rgpm_imp->cdirb = rgpm->cdirb;
											rgpm_imp->nmsrs = rgpm->nmsrs;
											rgpm_imp->ig = rgpm->ig;
											rgpm_imp->lntp = rgpm->lntp;
											rgpm_imp->txtp = rgpm->txtp;
											rgpm_imp->igrp = rgpm->igrp;
											rgpm_imp->iscp = rgpm->iscp;
											rgpm_imp->iicn = rgpm->iicn;
											rgpm_imp->codl = 0;
											rgpm_imp->codt = 0;
											rgpm_imp->codp = 0;
											rgpm_imp->coddel = FilesRS.m_Delete_graph_object;
											DbfToMdb(rgpm_imp);
											HKEY rKey;
											unsigned char Reget[MAX_PATH];
											DWORD RegetPath = sizeof(Reget);
											RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\ODBC\\ODBC.INI\\" + ProfilesRS.m_Path_section, 0, KEY_QUERY_VALUE, &rKey);
											RegQueryValueEx(rKey, "DBQ", NULL, NULL, Reget, &RegetPath);
											RegCloseKey(rKey);
											CString WaySource = Reget;
											for (int j = WaySource.GetLength() - 1; j >= 0; j--)
												if (Reget[j] == '\\')
												{
													WaySource.Delete(j, WaySource.GetLength() - j);
													break;
												}
											SQLConfigDataSource(NULL, ODBC_ADD_DSN, "Microsoft Access Driver (*.mdb)", "CREATE_DB=" + WaySource + "\\Save_dbf.mdb General\0");
											CDatabNet* db = new CDatabNet;
											frmdbsrc("Microsoft dBase Driver (*.dbf)", "tmp_dbf_source", "Temporary source for dbf bases", WayDBF, ODBC_ADD_DSN);
											db->OpenNet("tmp_dbf_source", FALSE);
											CString NameTable;
											NameTable = FilesRS.m_Name_file;
											if (NameTable.GetLength() > 8)
												NameTable.Delete(8, NameTable.GetLength() - 8);
											if (db->isTable(NameTable) > -1)
											{
												CDatabNet* dn = new CDatabNet;
												CRecordNet rn;
												CString SQL_str;
												dn->OpenNet("ODBC;DSN=MS Access Database;DBQ=" + WaySource + "\\Save_dbf.mdb", FALSE);
												rn.InitRecordNet(db, NameTable);
												if (dn->isTable(NameTable) == -1)
												{
													SQL_str = "CREATE TABLE " + NameTable + " (";
													for (int j = 0; j < rn.FieldNameArray.GetSize(); j++)
														if (j < rn.FieldNameArray.GetSize() - 1)
															SQL_str = SQL_str + rn.FieldNameArray[j] + " CHAR(50), ";
														else
															SQL_str = SQL_str + rn.FieldNameArray[j] + " CHAR(50)";
													SQL_str = SQL_str + ")";
													dn->ExecuteSQLNet(SQL_str);
												}
												else
												{
													if (MessageBox("Таблица " + NameTable + " уже существует! Удалить имеющиеся данные?", "Сообщение", MB_YESNO | MB_ICONWARNING) == IDYES)
														dn->ExecuteSQLNet("DELETE * FROM " + NameTable);
													else
														if (MessageBox("Создать новую таблицу для добавления данных (в случае отказа данные будут добавлены в существующую таблицу)?", "Сообщение", MB_YESNO | MB_ICONWARNING) == IDYES)
														{
															NameNewTableDlg dlg;
															if (dlg.DoModal() == IDOK)
															{
																SQL_str = "CREATE TABLE " + dlg.m_Name_table_str + " (";
																for (int j = 0; j < rn.FieldNameArray.GetSize(); j++)
																	if (j < rn.FieldNameArray.GetSize() - 1)
																		SQL_str = SQL_str + rn.FieldNameArray[j] + " CHAR(50), ";
																	else
																		SQL_str = SQL_str + rn.FieldNameArray[j] + " CHAR(50)";
																SQL_str = SQL_str + ")";
																dn->ExecuteSQLNet(SQL_str);
																NameTable = dlg.m_Name_table_str;
															}
														}
												}
												SQL_str = "INSERT INTO " + NameTable + " (";
												for (int j = 0; j < rn.FieldNameArray.GetSize(); j++)
													if (j < rn.FieldNameArray.GetSize() - 1)
														SQL_str = SQL_str + rn.FieldNameArray[j] + ", ";
													else
														SQL_str = SQL_str + rn.FieldNameArray[j];
												SQL_str = SQL_str + ") SELECT ";
												for (j = 0; j < rn.FieldNameArray.GetSize(); j++)
													if (j < rn.FieldNameArray.GetSize() - 1)
														SQL_str = SQL_str + rn.FieldNameArray[j] + ", ";
													else
														SQL_str = SQL_str + rn.FieldNameArray[j];
												NameTable = FilesRS.m_Name_file;
												if (NameTable.GetLength() > 8)
													NameTable.Delete(8, NameTable.GetLength() - 8);
												SQL_str = SQL_str + " FROM [dBase III; database=" + WayDBF + "]." + NameTable + ".DBF";
												dn->ExecuteSQLNet(SQL_str);
												rn.Close();
												dn->Close();
											}
											db->Close();
											frmdbsrc("Microsoft dBase Driver (*.dbf)", "tmp_dbf_source", "Temporary source for dbf bases", "", ODBC_REMOVE_DSN);
											MessageBox("Импорт завершён!", "Сообщение", MB_OK | MB_ICONINFORMATION);
										}
									}
									else
										MessageBox("Файл " + FilesRS.m_Name_file + ".mif в папке " + ProfilesRS.m_Folder + " не найден!", "Сообщение", MB_OK | MB_ICONERROR);
								}
							}
							ProfilesRS.MoveNext();
						}
					}
					FilesRS.MoveNext();
				}
				break;
			}
	ProfilesRS.Close();
	FilesRS.Close();
	rspls.Close();
}

void CGraphExpImpView::OnUpdateOperationsExecute(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(OperationsExecute);
}

void CGraphExpImpView::OnUpdateExecute(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable(Execute);
}

void CGraphExpImpView::OnPopupExecute()
{
	// TODO: Add your command handler code here
	OnOperationsExecute();
}

void CGraphExpImpView::OnExit()
{
	// TODO: Add your command handler code here
	PostQuitMessage(0);
}

void CGraphExpImpView::OnProgramHelp()
{
	// TODO: Add your command handler code here
	char buffer[MAX_PATH];
	CString lpEXEName;
	GetModuleFileName(NULL, buffer, MAX_PATH);
	lpEXEName = buffer;
	for (int i = lpEXEName.GetLength() - 1; i >= 0; i--)
		if (buffer[i] == '\\')
		{
			lpEXEName.Delete(i, lpEXEName.GetLength() - i);
			break;
		}
	ShellExecute(NULL, NULL, lpEXEName + "\\GraphExpImpHelp.chm", NULL, NULL, SW_SHOWDEFAULT);
}

void CGraphExpImpView::OnProgramAbout() 
{
	// TODO: Add your command handler code here
	AboutProgramDlg dlg;
	dlg.DoModal();
}
