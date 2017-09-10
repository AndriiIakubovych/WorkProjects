#pragma once


//25.07.07 Boris
const int MAX_SCR_NUMPOINT   = 5000;
const int SCRXY_POINT_BYTES  = 25;
const int SCRXYB_POINT_BYTES = 8;
const double SCR_XYB_PREC = 1000.;


/////////////////////////////////////////////////////////////////////////////
// BlokDial dialog
class BlokDial: public CDialog
{
public:
	BlokDial(CWnd* pParent = NULL);
    void InitBlokDial(class CDatabNet* pdb);

    //06.08.15 Borys -- cSQL (for empty CurTableName)
    //09.11.11 Boris -- CDatabNet* -- ������ ��������� � ������
    int ifBlock (CString cSQL, CDatabNet* pdb, int rg, CString SNOmsg, CString ERRmsg);
    int ifBlock (CString cSQL, CDatabNet* pdb, int rg, CDBException* e);
    int ifBlock0(CString cSQL, CDatabNet* pdb,         CDBException* e);

	CString	m_operation,m_resurs,m_error;
    CString m_DBName; //14.01.11 Boris

    int isInterupt;
    int isBlokMes;
    int ifStopDiag;
    long NumNext;
    CString state,native;
    CString m_strError;
    CString CurDBName; //14.01.11 Boris
    CString CurOperation;
    CString CurTableName;
    CString BlokState,DublState,DublNative;
    CArray<CString,CString> BlokNative;

protected:
    friend class CRecordNet;
    friend class CDatabNet;
    //static class CDatabNet* m_pdb; //22.07.08 Boris
    static //�� �������������� ����� �����
            int  drvtyp;

	virtual void DoDataExchange(CDataExchange* pDX);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel(); //31.06.07 Boris
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CDatabNet ����� ������ � ����������� ODBC � ��������������������� ������
class AFX_EXT_CLASS CDatabNet: public CDatabase
{
public:
    CDatabNet();
// �����������
    int OpenNet(CString,BOOL);
/* �������� ���������
���������
- ��� ���������
- ����� �������� - ������ 3-�� ��������� ������� Open ������ CDatabase
���� �������� - ��� � OpenNet ������ CRecordNet
*/
    int drvtyp; //23.05.07 Boris -- ��� ����
    void* m_pReserved;

    int ExecuteSQLNet(CString);
    // ���������� ��������� SQL, ��������� ������ � ������� ���������
    // ���� �������� - ��� � OpenNet ������ CRecordNet

    //18.06.07 Boris -- ��� ������������� � MSSQL
    int ExecuteJoinUpdate(CString cUpdateTable, CString cFROM, CString cSET, CString cWHERE = "");
    int ExecuteJoinDelete(CString cDeleteTable, CString cFROM,               CString cWHERE = "");

    int isTable(CString); // �������� ������� �������� �������
    int isQuery(CString); // � ��������� ODBC: �������, ������� ���
    int isLinked(CString);// ��������� �������. ���������� ����� �������
                        // ��� -1 ��� ���������� �������

    //17.12.13 Boris -- cWhere
    //11.10.11 Boris -- ���������� �� GydBib
    bool GetStatFuncTable(CString cFunc, CString cTable, CString cField, long& nL    , CString cWhere     );
    bool GetMaxTable     (               CString cTable, CString cField, long& nMax  , CString cWhere = "");
    bool GetCountTable   (               CString cTable, CString cField, long& nCount, CString cWhere = "");

public:
    BlokDial blkdlg;
    CString ErrState,ErrNative;

    CArray<CString,CString> TableTypeArray;
    CArray<CString,CString> TableNameArray;
};


/////////////////////////////////////////////////////////////////////////////
// CRecordNet recordset - ����� ��� ������ � ���������
// ���������� ODBC � ��������������������� �����
class AFX_EXT_CLASS CRecordNet: public CRecordset
{
public:
    CRecordNet();
    void InitRecordNet(CDatabNet* pdb, CString tblnam);
    CRecordNet(CDatabNet* pdb, CString tblnam);
//����������� ��������� ����� ��������� ��������� ODBC � ��� �������
    CDatabNet* GetDatabNet();
    enum fwonlyType //21.06.07 Boris -- ��� ������ � forwardOnly �� MSSQL
    {
        fwonlyYes   = 0, //�������� ������� ��� ������
        fwonlyNo    = 1, //�������� �� snapshot
        fwonlyNewDB = 2, //��������� forwardOnly �� ��������� �����������
        //fwonly = , //
    };

    int OpenNet(CString cSQL, DWORD dwOptions, CString cDescField,
        UINT nOpenType
        //21.06.07 Boris
        , UINT nFwOnlyType
        );
    int OpenNet(CString cSQL, DWORD dwOptions, CString cDescField,
        UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE);
/* �������� �������
���������
- ����� ��������� SELECT ��� ������ ������ ��� ������� �� ����� �������
- ����� ������ � �������� - ������ 3-�� ��������� ������� Open ������
  CRecordset
- ������ ������ ��� ��� ����, ����������� ���, ��� ������ ������ ������
  � ������������� ���������� ������
����������
 1 - ���������� ����������
 0 - ���� ODBC
-1 - ���������� ����������
*/

    int RequeryNet();    // ���� ��������
    int DeleteNet();     // ����� ��, ���
    int UpdateNet(int);  // � OpenNet
/* ��������� ������ �������
��������� ����� ������
0-������� ����������
1-���������� ������ ������� � ������������� ���������� ������,
  � ���� ����� ��������� ������������� ����������� �����
*/

    int isField(CString);
/* �������� ������� ���� � �������
��������� ��� ����
���������� ����� ���� � ������� ��� -1 ��� ���������� ����
*/

    //24.04.09 Boris
    int GetFieldValueNet(LPCTSTR lpszName, CString& strValue);
    int GetFieldValueNet(short   nIndex  , CString& strValue);

    void AddAND(CString c); //23.05.11 Boris
protected:
    int GetNumNext(CString cField); //24.04.09 Boris
    bool RemoveForwardOnlyIf(UINT nFwOnlyType, UINT& nOpenType); //13.06.07 Boris
    CDatabNet* m_pdb2;
public:
    BlokDial blkdlg;

    long NumNext;

    CString ErrState,ErrNative;
    CString CurTableName;
    CArray<CString,CString> FieldNameArray;

    virtual void Close();
};

//13.11.13 Boris
bool AFX_EXT_API IsDynasets();
//13.03.01 Boris
//��������� recordnet
// nMode = 0 -- � ������������ ������
// nMode = 1 -- ������ ��� ������ (readOnly + forwardOnly)
// nMode = 2 -- ������ ��� ���������� (appendOnly)
int AFX_EXT_API sOpen(CRecordNet* prs, int nMode);
// � �������� ����������� ��� ���������� ������
// OpenNet("",CRecordset::readOnly,"",CRecordset::forwardOnly);
int AFX_EXT_API sOpen2(CRecordNet* prs, int nMode, CString cDescField);


class AFX_EXT_CLASS TablDescr: public CObject
{
public:
    TablDescr(CDatabase *,CString);
//����������� ��������� ����� ��������� ��������� � ��� �������
    int isField(CString );
// -1 - ��� ����, >-1 - ���� ����
    CArray<CString,CString> FieldNameArray;
};

class AFX_EXT_CLASS SrcDescr
{
public:
    SrcDescr(CDatabase *);
    int isTable(CString );
    CArray<CString,CString> TableTypeArray;
    CArray<CString,CString> TableNameArray;
};


//-----------------------------------------------------------------
int   AFX_EXT_API propen(int ,int );
float AFX_EXT_API ResPtClv(CDatabNet *,int ,int ,float );

/*
��������� ������� ������������� �������� ��������
���������: 
- ����� ��������� � META ���������
- ��� ��������������� ���� �������� (CODTV �� VALVE)
- ������� �������� ��������
- �������� ������� ��������
���������� 
������������� ����� - ������������� ��������
-1 - ����������� ������ ��������� (�������, �������)
-2 - ������ ������ ������� RESVALVE
-3 - ��� �������� �� ������ � ������� RESVALVE
-4 - ��������� ������ � ������� RESVALVE
*/
