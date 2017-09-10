#ifndef _PARSE
#define _PARSE

#include <afxtempl.h>//CArray
//!!!!!!!
#include "i:\ciwin5\bibuni6\grafstr.h"
#include "i:\CIWIN5\bibuni6\RUniNew.h"
#include <i:\ciwin5\bibuni6\CodCod.h>
#include <i:\ciwin5\bibuni6\parse.h>

bool FormCopyFileAss(int NumHiper,CString NameFile, CString* CopyFileAss);//07.06.12
CString WritePoint(CString StrVal);
extern  AFX_EXT_API double WINAPI atofP(CString StrVal);
void PutMessNotCol(CString NAMSQLCOL,CString CurNameDoc);
extern  AFX_EXT_API void WINAPI PutMessNotAllCol(CString DescrcolFilter,CString NameDoc);//13.05.03

// CRECQDATA recordset
class  AFX_EXT_CLASS CRECQDATA : public CRUni
{
public:
	CString NameTabl,CodVar[10],CodVarDop[4];
	BYTE MTypVar[10],MNVARQ[10],ORDERVAR[10],NoData[10];
	int ValPar,ValParDop;	//BOOL FlSQXY,FlSelect...;

	//11.05.07
	//CRECQDATA(CDatabase* pDatabase = NULL,int ValParGlob = 0,CString NameTabl="");
	CRECQDATA(CDatabNet* pDatabase = NULL,int ValParGlob = 0,CString NameTabl="");

	 CTime m_DateParam[20];
	//26.08.03  not work in DoFieldExchange!!!   COleDateTime m_DateParam[20];
	CString m_StrParam[20],m_StrParamDop[10];
	//14.12.05
	TIMESTAMP_STRUCT CurStruct,MDateVal[10];


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRECQDATA)
	public:
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};
//***********************************************************
AFX_EXT_API BOOL ReadSelMeas(CString *SIGN,float *CTRMEAS);


//************************************************************
//YesInCom=1 процесс ввода
//RezData - есть записи в запросе на поиск или отсутствуют-убрать 
//RegSearch -использовать область поиска или нет 
//FileSQ,SectSQ - имя файла (<>.ini) и секции для чтения координат
//				 области поиска(Mov_ini,Razd.Format("Nreg_%d",theApp.GetRegCur());)
//FileSQ + "VARIABLE" - для записи значений параметров запросов
//StrList - класс поиска из gengen.ini

/********************************************************************/
extern  AFX_EXT_API BOOL WINAPI MultiParamSearch(
   CString FileSQ,CString SectSQ,CString StrList,BYTE *vidobj,
   CArray<long,long> *AMnumnode,
   CArray<CString,CString> *AMStrName,CArray<CString,CString> *AMStrNameObj,
   BOOL *RezData,BOOL RegSearch);
/********************************************************************/

extern  AFX_EXT_API BOOL WINAPI OrderSearchData(
   CString FileSQ,CString SectSQ,
   CString NAMEDOC,int CODDOC,CString QUERYDATA,CRECQDATA **rsQData);

struct DescrCol
{
	CString NAMSQLCOL;
	BOOL FindFieldCol;
	CString StrColVal;
	BOOL SEE;
	BYTE TYPDATA;
	CString FORMAT;
	CString NAMECOL;
	BYTE WIDTHCOL;
	int ClassID;
	BYTE FieldType;
};
typedef CArray<struct DescrCol,struct DescrCol> MARRDCol;
typedef CArray<struct Data,struct Data> MARRAY;
//12.11.04
struct SideHead
{
	int NumRow;
	int NumCol;
	int ValRow;
	CString Name;
};
//17.10.11
struct Search
{
   long StrNum;
   CString StrName;
   double StrX;
   double StrY;
   int NumReg;
   CString CtrlCol0;
   CString CtrlCol1;
   CString CtrlCol2;
   CString CtrlCol3;
};
typedef CArray<struct Search,struct Search> MArSearch;
//17.10.11
//// FlPrev   - Тип запроса: 1 - новый документ, 0 - раннее сформированный
extern AFX_EXT_API  BOOL WINAPI ViewDoc(BOOL FlPrev,
	int ValDoc,struct ListDoc *MListDoc,struct ParQ *MParQ,
	struct DCol *MDCol,struct RowHead *MRowHead,
	struct ColHead *MColHead,MARRAY *MData,struct SAgreg *MSAgreg,
	CStringArray *MTitle);
extern AFX_EXT_API BOOL WINAPI ViewDocNoView( BOOL FlPrev, int ValDoc, struct ListDoc *MListDoc,
					 struct ParQ *MParQ, struct DCol *MDCol, struct RowHead *MRowHead,
					 struct ColHead *MColHead,	MARRAY *MData, struct SAgreg *MSAgreg,
					 CStringArray *MTitle,	CStringArray *MFileDoc );
//------------------------------------------------------
//		NameZag  - заголовок документа HTML
//		NameHtml -  полное имя файла с документом HTML
//03.12.02 extern  AFX_EXT_API void WINAPI ViewDocHtml(CString NameZag,CString NameHtml);
//		   extern AFX_EXT_API void WINAPI InitHtmlDoc();

//*************************************************************
//************  CUnivDoc  *******************

class  AFX_EXT_CLASS CUnivDoc: public CObject
{
   DECLARE_DYNAMIC(CUnivDoc)
public:
	CUnivDoc();
	~CUnivDoc();
//-------- INPUT
//CDatabase *m_BASE, *m_CN;
CDatabNet *m_BASE, *m_CN;
CString FileSQ,SectSQ,StrList,/*PathCn,PathCnPl,*/MEntNamKey[10],
 MStrEnt[200],StrPar[10],StrNamobj;
CString FileWrRe;//12.12.07
BOOL RegSearch,AddSELSEA,KzNSDL;
BYTE ValEntKey,ValEntNum,COUNTFIRST,SelCODTECH;
int RecDialSea,ValPar,NumListCtr;
bool GroupRead,YesCancSelsean,YesBackSelsean,YesBackDialsea,TreeSearch,YesConsStruct;

CString StrDopNum,StrDopNumF;//is not necessary,default = ""

//--------- OUTPUT
//18.02.99  BYTE vidobj;
long StrNum,MEntNum[200];
CString StrName;
CStringList ListValCol,*UListValCol,ListNamCol, *UListNamCol;
//CString FileSQ,SectSQ;
//CDatabase *m_CN;
CString QUERYDATA,NAMEDOC,MNameDoc[2];
CRECQDATA *rsQData;
//double STRX,STRY;
BOOL FlGraf;
CNameSqPl *rNameSqPl;
bool NotShowOneRec; // Not schow  dialog search with one record(item)
//-------- INPUT+OUTPUT
int CODDOC,ValData;
//CArray<CString,CString> MStrNamObj1,*AMStrNamObj1,MStrNamObj2,*AMStrNamObj2;
CArray<CString,CString> *AMStrNamObj1,*AMStrNamObj2;


BOOL CallSearch();
BOOL CallSearchNext();

BOOL CallSearchTree();//09.11.09


private:

#ifdef _DEBUG
    void Dump(CDumpContext& dc) const;
#endif
	
};
//*************************************************************
 void FormHiperJava(FILE *SysOut,int RefNumHiper, CString *MPath);
 bool FormHtmlRef(struct OBJ *MasObj,int ValObj,struct ListDoc *MListDoc,
		struct DCol *MDCol,MARRAY *MData,int ValDoc,int TypSprav,int &NumHtml,
		int RefNumHiper,CString *MPath);//,CArray<double,double> *MSumAgr);
 BOOL FormRefer(
	BYTE vidobj,struct OBJ *MasObj,int ValObj,
	int *ValDoc,struct ListDoc *MListDoc,struct ParQ *MParQ,
	struct DCol *MDCol,struct RowHead *MRowHead,
	struct ColHead *MColHead,MARRAY *MData,int *RefNumHiper,CString *MPath,
	struct SAgreg *MSAgreg);
  int FormDoc(
	CString StrList,BOOL *FlPrev,BOOL ReDrow,
	int *ValDoc,struct ListDoc *MListDoc,struct ParQ *MParQ,
	struct DCol *MDCol,struct RowHead *MRowHead,
	struct ColHead *MColHead,MARRAY *MData,
	struct SAgreg *MSAgreg,CStringArray *MTitle);

//23.03.04
AFX_EXT_API CString PutData(CString strdate,CString FORMAT);

void GetMax(int *MaxDoc,int *MaxPar,int *MaxRow,int *MaxCol,
			int *MaxRowName,int *MaxColName,int *MaxRowAgr);
/* 22.10.15
BOOL ParSearchRez(
   CString FileSQ,CString SectSQ,CString StrList,
   BYTE *vidobj,long *StrNum,CString *StrName,double *StrX,double *StrY,
   BOOL FlMark,BYTE *NumGR,BOOL RegSearch,int &NumReg,bool SearchMultiBase);//07.10.11 add int &NumReg
*/
BOOL ParSearchRez(CString FileSQ, CString SectSQ, CString StrList,
	BYTE *vidobj, long *StrNum, CString *StrName, double *StrX, double *StrY,
	BOOL FlMark, BYTE *NumGR, BOOL RegSearch, int &NumReg,
	bool SearchMultiBase, bool &NotDimCurBuf);//22.10.15

#endif _PARSE