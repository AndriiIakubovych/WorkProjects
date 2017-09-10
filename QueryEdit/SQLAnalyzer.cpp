// SQLAnalyzer.cpp: implementation of the CSQLAnalyzer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "..\outgraf\grafstr.h"

#include "iqe2004.h"
#include "SQLAnalyzer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

LPCTSTR StandNames[] = {_T("SQXL"),_T("SQXR"),_T("SQYL"),_T("SQYR"),_T("XCENTERL"),
							_T("XCENTERR"),_T("YCENTERL"),_T("YCENTERR"),_T("NUMF"),
							_T("NUML"),_T("SQXMIN"),_T("SQXMAX"),_T("SQYMIN"),_T("SQYMAX")};
const int StandNamesCount=14;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSQLAnalyzer::CSQLAnalyzer(CDatabNet* base, int mode)
	:m_mode(mode), m_base(base)
{
	if(!base || !base->IsOpen())
		return;
	
	if(mode == SQLMODE_SQL)
	{
		Init_SQL();
		return;
	}

	bname=base->GetDatabaseFileName();
	DWORD& nCurVer=AfxGetModuleState()->m_dwVersion;
	nCurVer=0x601;
	BOOL tryNew=false;
	try
	{
		m_daobase.Open(bname,FALSE,TRUE);
	}
	catch(CDaoException *e)
	{
		tryNew=true;
	}
	if(tryNew)
	{
		nCurVer=0x600;
		try
		{
			m_daobase.Open(bname,FALSE,TRUE);
		}
		catch(CDaoException *e)
		{
			e->ReportError();
		}

	}
	m_qcount = m_daobase.GetQueryDefCount();
	MoveFirst();
	m_curquery=NULL;
}

void CSQLAnalyzer::Init_SQL()
{
/*	m_SQLs.RemoveAll();
	CMStringInt map;
	GetTables(m_base->m_hdbc, map, INCLUDE_TABLES_QUERIES);
	m_SQLs.RemoveAll();
	int i;
	CString str;
	POSITION pos = map.GetStartPosition();
	while(pos)
	{
		map.GetNextAssoc(pos, str, i);
		m_SQLs.Add(str);
	}
	m_qcount = m_SQLs.GetSize();
	MoveFirst();*/
}

CSQLAnalyzer::~CSQLAnalyzer()
{
	if(m_curquery)
	{
		if(m_curquery->IsOpen())
			m_curquery->Close();
		delete m_curquery;
	}
	if(m_daobase.IsOpen())
		m_daobase.Close();
}

void CSQLAnalyzer::MoveFirst()
{
	m_index=0;
	LoadData();
}

void CSQLAnalyzer::MoveLast()
{
	m_index=m_qcount-1;
	LoadData();
}

void CSQLAnalyzer::MoveNext()
{
	if(m_index<m_qcount)
		m_index++;
	LoadData();
}

void CSQLAnalyzer::MovePrev()
{
	if(m_index>-1)
		m_index--;
	LoadData();
}

BOOL CSQLAnalyzer::IsEOF()
{
	if(m_index==m_qcount)
		return TRUE;
	else
		return FALSE;
}

BOOL CSQLAnalyzer::IsBOF()
{
	if(m_index==-1)
		return TRUE;
	else
		return FALSE;
}

void CSQLAnalyzer::MoveAt(UINT index)
{
	if(index>(UINT)m_qcount)
		m_index=m_daobase.GetQueryDefCount()-1;
	else
		m_index=index;
	LoadData();
}

void CSQLAnalyzer::LoadData()
{
	if(m_mode == SQLMODE_SQL)
	{
		LoadData_SQL();
		return;
	}
	CDaoQueryDefInfo info;
	if(!IsEOF() && !IsBOF())
	{
		m_daobase.GetQueryDefInfo(m_index,info);
		m_strName=info.m_strName;
		m_bcrosstab=(info.m_nType==dbQCrosstab);
	}
}

void CSQLAnalyzer::LoadData_SQL()
{
	/*if(!IsEOF() && !IsBOF())
	{
		m_strName = m_SQLs[m_index + 1];
		CLQueryCol listCols;
		GetColumns(m_base->m_hdbc, m_strName, listCols);
		int i = listCols.GetCount();
		POSITION pos = listCols.GetHeadPosition();
		QUERYCOL col = listCols.GetAt(pos);
	}*/
}

BOOL CSQLAnalyzer::FindName(LPCTSTR name)
{
	CString toFind(name);
	toFind.TrimLeft();
	toFind.TrimRight();
	CDaoQueryDefInfo info;
	for(int i=0;i<m_qcount;i++)
	{
		m_daobase.GetQueryDefInfo(i,info);
		if(info.m_strName.CompareNoCase(toFind)==0)
		{
			MoveAt(i);
			return TRUE;
		}
	}
	return FALSE;
}

void CSQLAnalyzer::TranslateSQL(BYTE whatNeed)
{
	LoadData();
	if(!m_curquery)
		m_curquery=new CDaoQueryDef(&m_daobase);
	if(m_curquery->IsOpen())
		m_curquery->Close();
	CDaoFieldInfo finfo;
	CDaoParameterInfo pinfo;

	m_curquery->Open(m_strName);

	SColInfo ci;

	m_ciCols.RemoveAll();
	if(whatNeed==QE_TRANS_NEEDALL || whatNeed==QE_TRANS_NEEDCOLS)
	{
		int len=m_curquery->GetFieldCount();
		for(int i=0;i<len;i++)
		{
			m_curquery->GetFieldInfo(i,finfo,AFX_DAO_PRIMARY_INFO);
			ci.m_strName=finfo.m_strName;
			ci.m_sType=TranslateTypeCol(finfo.m_nType);
			m_ciCols.Add(ci);
		}
	}
	SVarInfo vi;
	m_viVars.RemoveAll();
	if(1/*whatNeed==QE_TRANS_NEEDALL || whatNeed==QE_TRANS_NEEDVARS*/)
	{
		int len=m_curquery->GetParameterCount();
		for(int i=0;i<len;i++)
		{
			m_curquery->GetParameterInfo(i,pinfo);
			vi.m_strName=pinfo.m_strName;
			if(IsStandartName(vi.m_strName))
				continue;
			vi.m_sType=TranslateTypeCol(pinfo.m_nType);

			COleVariant var;
			var.ChangeType(VT_BSTR,pinfo.m_varValue);

			vi.m_strValue=var.bstrVal;
			
			vi.m_sTimes=CalcTimesSubstr(m_curquery->GetSQL(),"["+vi.m_strName+"]");

			m_viVars.Add(vi);
			
		}
	}
}

short CSQLAnalyzer::TranslateTypeCol(short type)
{
	switch(type)
	{
	case(dbBoolean):	return 4;
	case(dbByte):		return 2;
	case(dbInteger):	return 2;
	case(dbLong):		return 2;
	case(dbSingle):		return 2;
	case(dbDouble):		return 2;
	case(dbDate):		return 3;
	case(dbText):		return 1;
	case(dbMemo):		return 1;
	case(dbGUID):		return 6;
	default:			return 0;
	}
}

long CSQLAnalyzer::GetMetaField(LPCTSTR strTable,LPCTSTR strField,LPCTSTR strType)
{
	COleVariant var;
	if(GetMetaFieldVariant(strTable,strField,strType,&var))
		return var.iVal;
	else
		return -1;
}

BOOL CSQLAnalyzer::IsStandartName(CString &name)
{
	for(int i=0;i<StandNamesCount;i++)
		if(name.CompareNoCase(StandNames[i])==0)
			return TRUE;
	return FALSE;
}

CString CSQLAnalyzer::GetMetaFieldString(LPCTSTR strTable, LPCTSTR strField, LPCTSTR strType)
{
	COleVariant var;
	if(GetMetaFieldVariant(strTable,strField,strType,&var))
		return CString(var.pcVal);
	else
		return CString("");
}

BOOL CSQLAnalyzer::GetMetaFieldVariant(LPCTSTR strTable, LPCTSTR strField, LPCTSTR strType, COleVariant *var)
{
	if(strTable[0]==0 || strField[0]==0)
		return FALSE;
	CDaoRecordset rec(&m_daobase);
	CString SQL;
	SQL.Format(_T("SELECT MetaField.%s \
		FROM MetaField, MetaTable \
		WHERE MetaTable.TableName='%s' AND MetaTable.Table_ID=MetaField.Table_ID AND \
		MetaField.FieldName='%s';"),strType,strTable,strField);
	rec.Open(dbOpenDynaset,SQL);
	BOOL ret;
	if(!rec.IsEOF())
	{
		rec.GetFieldValue(0,*var);
		ret=TRUE;
	}
	else
		ret=FALSE;
	rec.Close();

	return ret;
}

BOOL CSQLAnalyzer::LoadMetaForCol(LPCTSTR colname, int *ind)
{
	for(int i=0;i<m_ciCols.GetSize();i++)
	{
		if(m_ciCols[i].m_strName.CompareNoCase(colname) == 0)
		{
			*ind = i;
			return LoadMetaForCol(i);
		}
	}
	return FALSE;
}

BOOL CSQLAnalyzer::LoadMetaForCol(int colindex)
{
	if(colindex<0 || colindex>m_ciCols.GetSize())
		return FALSE;
	SColInfo ci=m_ciCols[colindex];
	CDaoFieldInfo finfo;
	m_curquery->GetFieldInfo(colindex,finfo,AFX_DAO_SECONDARY_INFO);
	ci.m_sMetaType=(short)GetMetaField(finfo.m_strSourceTable,finfo.m_strSourceField,_T("FieldType"));
	ci.m_sMetaClassID=(short)GetMetaField(finfo.m_strSourceTable,finfo.m_strSourceField,_T("ClassID"));
	ci.m_strDescr=GetMetaFieldString(finfo.m_strSourceTable,finfo.m_strSourceField,_T("FieldDescr"));
	ci.m_iSize=GetMetaField(finfo.m_strSourceTable,finfo.m_strSourceField,_T("FieldLen"));
	if(ci.m_sMetaType==4 || ci.m_sMetaType==8)
		ci.m_sType=5;
	m_ciCols.SetAt(colindex,ci);
	return TRUE;
}

short CSQLAnalyzer::CalcTimesSubstr(LPCTSTR str, LPCTSTR substr)
{
	CString _str=str;
	int startfrom=-1;
	int col=0;
	while((startfrom=_str.Find(substr,startfrom+1))!=-1)
	{
		col++;
	}
	return col;
}

void CSQLAnalyzer::Reload()
{
	if(m_curquery)
	{
		if(m_curquery->IsOpen())
			m_curquery->Close();
		delete m_curquery;
	}
	if(m_daobase.IsOpen())
		m_daobase.Close();

	m_daobase.Open(bname,FALSE,TRUE);
	m_qcount = m_daobase.GetQueryDefCount();
	MoveFirst();
	m_curquery=NULL;
}

int CSQLAnalyzer::FindCol(LPCTSTR colName)
{
	for(int i=0;i<m_ciCols.GetSize();i++)
		if(m_ciCols[i].m_strName.CompareNoCase(colName)==0)
			return i;
	return -1;
}

//DEL BOOL CSQLAnalyzer::IsCrossTab()
//DEL {
//DEL 	CDaoQueryDefInfo info;
//DEL 	m_daobase.GetQueryDefInfo(
//DEL 	if(m_curquery)
//DEL 	{
//DEL 		if(m_curquery->GetType()==dbQCrosstab)
//DEL 			return TRUE;
//DEL 		return FALSE;
//DEL 	}
//DEL 	return FALSE;
//DEL }

void CSQLAnalyzer::CloseBase()
{
	if(m_daobase.IsOpen())
		m_daobase.Close();
}
