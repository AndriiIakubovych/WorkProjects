#include "stdafx.h"

#include "i:\CiWin5\bibuni6\MetaGlob.h"
#include "IQE2004.h"

#include "IQE2004Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////
// DELETE
void CIQE2004Dlg::OnDelete()
{
	BYTE selType;
	DWORD selOwner;
	DWORD selInd;
	if(!WhatSelected(&selType,&selOwner,&selInd))
		return;
	switch(selType)
	{
	//диалог с переменными
	case(TID_COLFIELD):
		{
			DeleteColumn(selOwner,selInd);
		};break;
	case(TID_VARFIELD):
		{
//			DeleteVar(selOwner,selInd);
		};break;
	case(TID_AGRFIELD):
		{
			DeleteAgr(selOwner,selInd);
		};break;
	case(TID_DOC):
		{
			DeleteDoc(selInd);
		};break;
	case(TID_CLASS):
		{
			DeleteClass(selInd);
		};break;
	case(TID_FSELFIELD):
		{
			DeleteSel(selOwner, selInd);
		};break;
	}
}

void CIQE2004Dlg::DeleteColumn(DWORD coddoc, DWORD numcol)
{
	if(AfxMessageBox(_T("Подтвердите удаление колонки"),MB_YESNO)==IDNO)
		return;

	CColsSet cset(m_CNBase);
	cset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);

	m_CNBase->BeginTrans();

	cset.Open();
	cset.MoveFirst();
	while(!cset.IsEOF())
	{
		if(cset.m_NUMCOL==numcol)
		{
			cset.DeleteNet();
			break;
		}
		cset.MoveNext();
	}


	cset.RequeryNet();

	cset.RemoveHoles();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&cset);

	cset.Close();

	//обновление nColKey в агрегировании
	CAgrsSet aset(m_CNBase);
	aset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	aset.Open();
	while(!aset.IsEOF())
	{
		if(!aset.IsFieldNull(&aset.m_NCOLKEY))
			if(aset.m_NCOLKEY == numcol)
			{
				aset.Edit();
				aset.m_NCOLKEY = 0;
				aset.UpdateNet(0);
			}
			else if(aset.m_NCOLKEY > numcol)
			{
				aset.Edit();
				aset.m_NCOLKEY--;
				aset.UpdateNet(0);
			}
		aset.MoveNext();
	}
	aset.Close();

	m_CNBase->CommitTrans();
}

void CIQE2004Dlg::DeleteVar(DWORD coddoc, DWORD numvar)
{
	if(AfxMessageBox(_T("Подтвердите удаление переменной"),MB_YESNO)==IDNO)
		return;

	CVarsSet vset(m_CNBase);
	vset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);

	m_CNBase->BeginTrans();

	vset.Open();
	vset.MoveFirst();
	while(!vset.IsEOF())
	{
		if(vset.m_NUMVAR==numvar)
		{
			vset.DeleteNet();
			break;
		}
		vset.MoveNext();
	}

	vset.RequeryNet();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&vset);

	vset.Close();

	m_CNBase->CommitTrans();
}

void CIQE2004Dlg::DeleteAgr(DWORD coddoc, DWORD numvar)
{
	if(AfxMessageBox(_T("Подтвердите удаление агрегирования"),MB_YESNO)==IDNO)
		return;

	CAgrsSet aset(m_CNBase);
	aset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);

	m_CNBase->BeginTrans();

	aset.Open();
	aset.MoveFirst();
	while(!aset.IsEOF())
	{
		if(aset.m_NUMAGR==(int)numvar)
		{
			aset.DeleteNet();
			break;
		}
		aset.MoveNext();
	}


	aset.RequeryNet();
	aset.RemoveHoles();

	if(aset.IsEOF() && aset.IsBOF())
	{
		CString SQL;
		SQL.Format(_T("UPDATE descrdoc SET existagr=0 WHERE coddoc=%d"),coddoc);
		m_CNBase->ExecuteSQL(SQL);
	}

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&aset);

	m_CNBase->CommitTrans();
}

void CIQE2004Dlg::DeleteDoc(DWORD coddoc)
{
	if(AfxMessageBox(_T("Подтвердите удаление документа"),MB_YESNO)==IDNO)
		return;

	CDocsSet dset(m_CNBase);
	switch(m_sortby)
	{
		case(ID_SORTCODE):	dset.m_mysort = "CODDOC";break;
		case(ID_SORTNAME):	dset.m_mysort = "NAMEDOC";break;
		case(ID_SORTQUERY):	dset.m_mysort = "QUERYDATA";break;
		case(ID_SORTTYPE):	dset.m_mysort = "REPORT*8+SEARCH*4+REFER*2+DSELECT,CODDOC";break;
	}
	dset.m_strSort = dset.m_mysort;

	m_CNBase->BeginTrans();

	dset.Open();
	dset.MoveFirst();
	while(!dset.IsEOF())
	{
		if(dset.m_CODDOC==(int)coddoc)
		{
			dset.DeleteNet();
			break;
		}
		dset.MoveNext();
	}

	dset.RequeryNet();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&dset);

	dset.Close();

	m_CNBase->CommitTrans();
}

void CIQE2004Dlg::DeleteClass(DWORD numclass)
{
	if(AfxMessageBox(_T("Подтвердите удаление класса"),MB_YESNO)==IDNO)
		return;

	CClassesSet clset(m_CNBase);

	m_CNBase->BeginTrans();

	clset.Open();
	clset.MoveFirst();
	int i = 0;
	while(!clset.IsEOF())
	{
		if(clset.m_LISTDOC==(int)numclass)
		{
			i = clset.m_USEORDER;
			clset.DeleteNet();
			break;
		}
		clset.MoveNext();
	}

	
	if(m_isClassesUseOrder)
	{
		if(!clset.IsEOF())
			clset.MoveNext();
		while(!clset.IsEOF())
		{
			clset.Edit();
			clset.m_USEORDER = i;
			clset.UpdateNet(0);
			i++;
			clset.MoveNext();
		}
	}

	clset.RequeryNet();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&clset);

	clset.Close();

	m_CNBase->CommitTrans();
}

void CIQE2004Dlg::DeleteSel(DWORD coddoc, DWORD numsel)
{
	if(AfxMessageBox(_T("Подтвердите удаление выделения"),MB_YESNO)==IDNO)
		return;

	CSelsSet sset(m_CNBase);
	sset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);

	m_CNBase->BeginTrans();

	sset.Open();
	sset.MoveFirst();
	while(!sset.IsEOF())
	{
		if(sset.m_DSELECT==(int)numsel)
		{
			sset.DeleteNet();
			break;
		}
		sset.MoveNext();
	}

	sset.RequeryNet();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&sset);

	sset.Close();

	m_CNBase->CommitTrans();
}


/////////////////////////////////////////////////////////////////////////
// ADDNEW
void CIQE2004Dlg::OnAddNew() 
{
	BYTE selType;
	DWORD selOwner;
	DWORD selInd;
	if(!WhatSelected(&selType,&selOwner,&selInd))
		return;
	switch(selType)
	{
	//диалог с переменными
	case(TID_COL):
	case(TID_COLFIELD):
		{
			AddNewCol(selOwner);
		};break;
	case(TID_VAR):
	case(TID_VARFIELD):
		{
//			AddNewVar(selOwner);
		};break;
	case(TID_AGR):
	case(TID_AGRFIELD):
		{
			AddNewAgr(selOwner);
		};break;
	case(TID_DOC):
	case(TID_DOCROOT):
		{
			AddNewDoc();
		};break;
	case(TID_CLASS):
	case(TID_CLASSESROOT):
		{
			AddNewClass();
		};break;
	case(TID_FSEL):
	case(TID_FSELFIELD):
		{
			AddNewSel(selOwner);
		};break;
	}
}

void CIQE2004Dlg::AddNewCol(DWORD coddoc,CColsSet *propSet,SColInfo *colInfo)
{
	BeginWaitCursor();
	CColsSet cset(m_CNBase);
	cset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	cset.Open();

	long code;
	if(GetSelectedType()==TID_COL || propSet || colInfo)
		code=cset.FindFreeCode(1);
	else
	{
		int mcode=m_tree.GetItemData(m_tree.GetSelectedItem());
		cset.FreeCodeForMe(mcode+1);
		SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&cset);
		code=mcode+1;
		cset.RequeryNet();
	}

	m_CNBase->BeginTrans();

	cset.AddNew();
	if(propSet!=NULL)
		cset.SetFromOtherSet(propSet);
	else
		cset.SetDefault();

	if(colInfo!=NULL)
	{
		cset.m_NAMSQLCOL=colInfo->m_strName;
		cset.m_NAMECOL=colInfo->m_strDescr;
		cset.m_TYPDATA=(BYTE)colInfo->m_sType;
		if(cset.m_NAMSQLCOL=="num")
			cset.m_SEE=false;
	}

	cset.m_CODDOC=coddoc;
	cset.m_NUMCOL=(BYTE)code;
	cset.UpdateNet(0);

	m_CNBase->CommitTrans();

	cset.RequeryNet();

	if(!propSet && !colInfo)
	//значения задавались по умолчанию - необходимо редактирование
	{

		HTREEITEM hPar;
		if(GetSelectedType()==TID_COL)
			hPar=m_tree.GetSelectedItem();
		else
			hPar=m_tree.GetParentItem(m_tree.GetSelectedItem());

		SmartUpdateBranch(hPar,&cset);
		m_tree.SelectItem(FindCode(hPar,code));

		cset.Close();

		ViewColsProperties(coddoc,code);
	}

	//обновление nColKey в агрегировании
	CAgrsSet aset(m_CNBase);
	aset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	aset.Open();
	while(!aset.IsEOF())
	{
		if(!aset.IsFieldNull(&aset.m_NCOLKEY) && aset.m_NCOLKEY >= (BYTE)code)
		{
			aset.Edit();
			aset.m_NCOLKEY++;
			aset.UpdateNet(0);
		}
		aset.MoveNext();
	}
	aset.Close();

	EndWaitCursor();
}

void CIQE2004Dlg::AddNewVar(DWORD coddoc,CVarsSet *propSet,SVarInfo *varInfo)
{
	CVarsSet vset(m_CNBase);
	vset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	vset.Open();

	long code=vset.FindFreeCode(1);

	m_CNBase->BeginTrans();

	vset.AddNew();
	if(propSet!=NULL)
		vset.SetFromOtherSet(propSet);
	else
		vset.SetDefault();

	if(varInfo!=NULL)
	{
		vset.m_CODVAR=varInfo->m_strName;
		vset.m_TYPVAR=(BYTE)varInfo->m_sType;
		vset.m_DEFVAL=varInfo->m_strValue;
		vset.m_ORDERVAR=varInfo->m_sTimes;
	}
		
	vset.m_CODDOC=coddoc;
	vset.m_NUMVAR=(BYTE)code;
	vset.UpdateNet(0);

	m_CNBase->CommitTrans();

	vset.RequeryNet();

	if(!propSet && !varInfo)
	//значения задавались по умолчанию - необходимо редактирование
	{
		HTREEITEM hPar;
		if(GetSelectedType()==TID_VAR)
			hPar=m_tree.GetSelectedItem();
		else
			hPar=m_tree.GetParentItem(m_tree.GetSelectedItem());

		SmartUpdateBranch(hPar,&vset);
		m_tree.SelectItem(FindCode(hPar,code));

		vset.Close();

		ViewVarsProperties(coddoc,code);
	}
}

void CIQE2004Dlg::AddNewAgr(DWORD coddoc,CAgrsSet *propSet)
{
	CAgrsSet aset(m_CNBase);
	aset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	aset.Open();

	long code;

	if(GetSelectedType()==TID_AGR || propSet)
		code=aset.FindFreeCode(1);
	else
	{
		int mcode=m_tree.GetItemData(m_tree.GetSelectedItem());
		aset.FreeCodeForMe(mcode+1);
		SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&aset);
		code=mcode+1;
		aset.RequeryNet();
	}

	m_CNBase->BeginTrans();

	aset.AddNew();
	if(propSet!=NULL)
		aset.SetFromOtherSet(propSet);
	else
		aset.SetDefault();
	aset.m_CODDOC=coddoc;
	aset.m_NUMAGR=code;
	aset.UpdateNet(0);
	m_CNBase->CommitTrans();

	aset.RequeryNet();

	aset.SetFieldNull(&aset.m_NCOLKEY);

	CString SQL;
	SQL.Format(_T("UPDATE descrdoc SET existagr=-1 WHERE coddoc=%d"),coddoc);
	m_CNBase->ExecuteSQL(SQL);

	if(!propSet)
	//значения задавались по умолчанию - необходимо редактирование
	{

		HTREEITEM hPar;
		if(GetSelectedType()==TID_AGR)
			hPar=m_tree.GetSelectedItem();
		else
			hPar=m_tree.GetParentItem(m_tree.GetSelectedItem());

		SmartUpdateBranch(hPar,&aset);
		m_tree.SelectItem(FindCode(hPar,code));

		aset.Close();

		ViewAgrsProperties(coddoc,code);
	}
}

long CIQE2004Dlg::AddNewDoc(CDocsSet *propSet,long propCode)
{
	CDocsSet dset(m_CNBase);
	dset.m_strSort = "CODDOC";

	dset.Open();

	long code;

	if(propCode==-1)
		code=dset.FindFreeCode(1);
	else
		code=propCode;

	m_CNBase->BeginTrans();

	dset.AddNew();
	
	if(propSet!=NULL)
		dset.SetFromOtherSet(propSet);
	else
		dset.SetDefault();
	dset.m_CODDOC=code;

	dset.UpdateNet(0);

	m_CNBase->CommitTrans();

	switch(m_sortby)
	{
		case(ID_SORTCODE):dset.m_mysort = "CODDOC";break;
		case(ID_SORTNAME):dset.m_mysort = "NAMEDOC";break;
		case(ID_SORTQUERY):dset.m_mysort = "QUERYDATA";break;
		case(ID_SORTTYPE):dset.m_mysort = "REPORT*8+SEARCH*4+REFER*2+DSELECT,CODDOC";break;
	}

	dset.RequeryNet();

	if(!propSet) //значения задавались по умолчанию - необходимо редактирование
	{
		HTREEITEM hPar;
		if(GetSelectedType()==TID_DOCROOT)
			hPar=m_tree.GetSelectedItem();
		else
			hPar=m_tree.GetParentItem(m_tree.GetSelectedItem());

		SmartUpdateBranch(hPar,&dset);
		m_tree.SelectItem(FindCode(hPar,code));
	
		dset.Close();

		ViewDocsProperties(code,code);
	}
	return code;
}

void CIQE2004Dlg::AddNewClass()
{
	CClassesSet clset(m_CNBase);
	clset.m_strSort = "LISTDOC";
	clset.Open();

	long code=clset.FindFreeCode(1);

	if (clset.isField("USEORDER")!=-1)
		clset.m_strSort = "USEORDER,LISTDOC";
	else
		clset.m_strSort="LISTDOC";

	clset.Requery();

	m_CNBase->BeginTrans();

	int useorder = 0;
	if(m_isClassesUseOrder)
	{
		clset.MoveLast();
		useorder = clset.m_USEORDER + 1;
	}

	clset.AddNew();
	clset.SetDefault();
	clset.m_LISTDOC=code;
	clset.m_USEORDER = useorder;
	clset.UpdateNet(0);

	m_CNBase->CommitTrans();

	clset.RequeryNet();

	HTREEITEM hPar;
	if(GetSelectedType()==TID_CLASSESROOT)
		hPar=m_tree.GetSelectedItem();
	else
		hPar=m_tree.GetParentItem(m_tree.GetSelectedItem());

	SmartUpdateBranch(hPar,&clset);
	m_tree.SelectItem(FindCode(hPar,code));

	clset.Close();

	ViewClassesProperties(code);
}

void CIQE2004Dlg::AddNewSel(DWORD coddoc, CSelsSet *propSet)
{
	CSelsSet sset(m_CNBase);
	sset.m_strFilter.Format(_T("CODDOC=%d"),coddoc);
	sset.Open();

	long code=sset.FindFreeCode(1);

	m_CNBase->BeginTrans();

	sset.AddNew();
	if(propSet!=NULL)
		sset.SetFromOtherSet(propSet);
	else
		sset.SetDefault();
	sset.m_CODDOC=coddoc;
	sset.m_DSELECT=code;
	sset.UpdateNet(0);

	m_CNBase->CommitTrans();

	sset.RequeryNet();

	if(!propSet)
	//значения задавались по умолчанию - необходимо редактирование
	{

		HTREEITEM hPar;
		if(GetSelectedType()==TID_FSEL)
			hPar=m_tree.GetSelectedItem();
		else
			hPar=m_tree.GetParentItem(m_tree.GetSelectedItem());

		SmartUpdateBranch(hPar,&sset);
		m_tree.SelectItem(FindCode(hPar,code));

		sset.Close();

		ViewSelsProperties(coddoc,code);
	}
}

/////////////////////////////////////////////////////////////////////////
// PROPERTIES
void CIQE2004Dlg::OnFieldproperties() 
{
	BYTE selType;
	DWORD selOwner;
	DWORD selInd;
	if(!WhatSelected(&selType,&selOwner,&selInd))
		return;
	switch(selType)
	{
	//диалог с переменными
	case(TID_COLFIELD):
		{
			ViewColsProperties(selOwner,selInd);
		};break;
	case(TID_VARFIELD):
		{
			ViewVarsProperties(selOwner,selInd);
		};break;
	case(TID_AGRFIELD):
		{
			ViewAgrsProperties(selOwner,selInd);
		};break;
	case(TID_DOC):
		{
			ViewDocsProperties(selOwner,selInd);
		};break;
	case(TID_CLASS):
		{
			ViewClassesProperties(selInd);
		};break;
	case(TID_FSELFIELD):
		{
			ViewSelsProperties(selOwner,selInd);
		};break;
	}
}

void CIQE2004Dlg::ViewColsProperties(DWORD owner, DWORD ind)
{
	BeginWaitCursor();
	//Определение имени документа и запроса
	CDocsSet dset(m_CNBase);
	dset.m_strFilter.Format(_T("CODDOC=%d"),owner);
	dset.Open();

	CColsDlg ccd(&m_metainfo,&dset);

	CString sqdata; //запрос на документ
	
	if(!dset.IsEOF())
	{
		ccd.m_docname.Format(_T("[%d] %s"),dset.m_CODDOC,dset.m_NAMEDOC);
		ccd.m_isreport = dset.m_REPORT;
		sqdata = dset.m_QUERYDATA;
	}
	else
		ccd.m_docname="Can't detect doc name!";

	CColsSet ccs(m_CNBase);
	ccs.m_strFilter.Format(_T("CODDOC=%d"),owner);
	ccs.Open();

	ccd.SetSet(&ccs,ind);
	ccd.SetMSGBase(m_MSGBase);
	if(!m_queries->FindName(sqdata) && m_scrqueries && m_scrqueries->FindName(sqdata))
		ccd.SetQueries(m_scrqueries);
	else
		ccd.SetQueries(m_queries);
	ccd.DoModal();
	dset.Close();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&ccs);

	ccs.Close();
}

void CIQE2004Dlg::ViewVarsProperties(DWORD owner, DWORD ind)
{
	BeginWaitCursor();
	//Определение имени документа
	CDocsSet dset(m_CNBase);
	dset.m_strFilter.Format(_T("CODDOC=%d"),owner);
	dset.Open();

	CVarsSet vset(m_CNBase);
	vset.m_strFilter.Format(_T("CODDOC=%d"),owner);
	vset.Open();

	CVarsDlg vdlg(&m_metainfo,dset.m_QUERYDATA);
	
	if(!dset.IsEOF())
		vdlg.m_docname.Format(_T("[%d] %s"),dset.m_CODDOC,dset.m_NAMEDOC);
	else
		vdlg.m_docname="Can't detect doc name!";
	dset.Close();

	vdlg.SetSet(&vset,ind);
	vdlg.SetMSGBase(m_MSGBase);
	vdlg.SetQueries(m_queries,m_scrqueries);
	vdlg.DoModal();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&vset);

	vset.Close();
}

void CIQE2004Dlg::ViewAgrsProperties(DWORD owner, DWORD ind)
{
	BeginWaitCursor();
	CAgrsSet aset(m_CNBase);
	aset.m_strFilter.Format(_T("CODDOC=%d"),owner);
	aset.Open();
	CAgrsDlg adlg(&m_metainfo);
	adlg.SetBASEBase(m_CNBase);
	
	//Определение имени документа
	CDocsSet dset(m_CNBase);
	dset.m_strFilter.Format(_T("CODDOC=%d"),owner);
	dset.Open();
	if(!dset.IsEOF())
		adlg.m_docname.Format(_T("[%d] %s"),dset.m_CODDOC,dset.m_NAMEDOC);
	else
		adlg.m_docname="Can't detect doc name!";
	dset.Close();

	adlg.SetSet(&aset,ind);
	adlg.SetMSGBase(m_MSGBase);
	adlg.SetQueries(m_queries);
	adlg.DoModal();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&aset);

	aset.Close();
}

void CIQE2004Dlg::ViewDocsProperties(DWORD owner, DWORD ind, BOOL bCheckOnly)
{
	BeginWaitCursor();
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
	CDocsDlg vdlg(&m_metainfo, m_MSGBase, m_CNBase);
	
	vdlg.SetSet(&dset,ind);
	vdlg.SetMSGBase(m_MSGBase);
	vdlg.SetBASEBase(m_CNBase);
	vdlg.SetQueries(m_queries, m_scrqueries);
	int count;
	vdlg.m_classeslist = GenerateClassesListForDoc(ind, &count);
	vdlg.m_classescount = count;
	
	vdlg.m_bCheckOnly = bCheckOnly;

	vdlg.DoModal();

	dset.Close();

	SmartestUpdate(m_docsroot, TRUE, TRUE);
	
	SelectDocByCode(ind);

}

void CIQE2004Dlg::ViewClassesProperties(DWORD ind)
{
	BeginWaitCursor();
	CClassesSet clset(m_CNBase);

	clset.Open();
	CListsDlg ldlg(&m_metainfo);
	ldlg.SetSet(&clset,ind);
	ldlg.SetMSGBase(m_MSGBase);
	ldlg.SetQueries(m_queries);
	ldlg.DoModal();

	clset.Close();

/*	m_tree.SelectItem(m_classesroot);*/
	SetTimer(ID_UPDATEONCETIMER,500,NULL);

//	SmartestUpdate(m_classesroot);
}

void CIQE2004Dlg::ViewSelsProperties(DWORD owner, DWORD ind)
{
	BeginWaitCursor();
	CSelsSet sset(m_CNBase);
	sset.m_strFilter.Format(_T("CODDOC=%d"),owner);
	sset.Open();
	CSelsDlg sdlg(&m_metainfo);
	
	//Определение имени документа
	CDocsSet dset(m_CNBase);
	dset.m_strFilter.Format(_T("CODDOC=%d"),owner);
	dset.Open();
	if(!dset.IsEOF())
		sdlg.m_docname.Format(_T("[%d] %s"),dset.m_CODDOC,dset.m_NAMEDOC);
	else
		sdlg.m_docname="Can't detect doc name!";
	dset.Close();

	sdlg.SetSet(&sset,ind);
	sdlg.SetMSGBase(m_MSGBase);
	sdlg.SetQueries(m_queries);
	sdlg.DoModal();

	SmartUpdateBranch(m_tree.GetParentItem(m_tree.GetSelectedItem()),&sset);

	sset.Close();
}
