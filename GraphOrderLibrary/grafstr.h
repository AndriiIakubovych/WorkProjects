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
    //09.11.11 Boris -- CDatabNet* -- нельзя запомнить в классе
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
    static //до перетрансляции всеми всего
            int  drvtyp;

	virtual void DoDataExchange(CDataExchange* pDX);

	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel(); //31.06.07 Boris
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
// CDatabNet класс работы с источниками ODBC в многопользовательском режиме
class AFX_EXT_CLASS CDatabNet: public CDatabase
{
public:
    CDatabNet();
// конструктор
    int OpenNet(CString,BOOL);
/* Открытие источника
принимает
- имя источника
- режим открытия - аналог 3-го параметра функции Open класса CDatabase
коды возврата - как у OpenNet класса CRecordNet
*/
    int drvtyp; //23.05.07 Boris -- тип СУБД
    void* m_pReserved;

    int ExecuteSQLNet(CString);
    // выполнение оператора SQL, принимает строку с текстом оператора
    // коды возврата - как у OpenNet класса CRecordNet

    //18.06.07 Boris -- для совместимости с MSSQL
    int ExecuteJoinUpdate(CString cUpdateTable, CString cFROM, CString cSET, CString cWHERE = "");
    int ExecuteJoinDelete(CString cDeleteTable, CString cFROM,               CString cWHERE = "");

    int isTable(CString); // Проверка наличия базового объекта
    int isQuery(CString); // в источнике ODBC: таблицы, запроса или
    int isLinked(CString);// связанной таблицы. Возвращают номер объекта
                        // или -1 при отсутствии объекта

    //17.12.13 Boris -- cWhere
    //11.10.11 Boris -- перенесено из GydBib
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
// CRecordNet recordset - класс для работы с таблицами
// средствами ODBC в многопользовательской среде
class AFX_EXT_CLASS CRecordNet: public CRecordset
{
public:
    CRecordNet();
    void InitRecordNet(CDatabNet* pdb, CString tblnam);
    CRecordNet(CDatabNet* pdb, CString tblnam);
//Конструктор принимает адрес открытого источника ODBC и имя таблицы
    CDatabNet* GetDatabNet();
    enum fwonlyType //21.06.07 Boris -- что делать с forwardOnly на MSSQL
    {
        fwonlyYes   = 0, //пытаться открыть как просят
        fwonlyNo    = 1, //заменять на snapshot
        fwonlyNewDB = 2, //открывать forwardOnly на отдельном подключении
        //fwonly = , //
    };

    int OpenNet(CString cSQL, DWORD dwOptions, CString cDescField,
        UINT nOpenType
        //21.06.07 Boris
        , UINT nFwOnlyType
        );
    int OpenNet(CString cSQL, DWORD dwOptions, CString cDescField,
        UINT nOpenType = AFX_DB_USE_DEFAULT_TYPE);
/* Открытие выборки
принимает
- текст оператора SELECT или пустая строка при выборке по имени таблицы
- режим работы с таблицей - аналог 3-го парвметра функции Open класса
  CRecordset
- пустая строка или имя поля, содержащего код, для случая вывода таблиц
  с автоматически кодируемым ключом
возвращает
 1 - нормальное завершение
 0 - сбой ODBC
-1 - прерванная блокировка
*/

    int RequeryNet();    // Коды возврата
    int DeleteNet();     // такие же, как
    int UpdateNet(int);  // у OpenNet
/* Изменение строки выборки
принимает режим работы
0-обычное обновление
1-обновление строки таблицы с автоматически кодируемым ключем,
  в поле ключа заносится автоматически присвоенное число
*/

    int isField(CString);
/* проверка наличия поля в таблице
принимает имя поля
возвращает номер поля в таблице или -1 при отсутствии поля
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
//открывает recordnet
// nMode = 0 -- с возможностью записи
// nMode = 1 -- только для чтения (readOnly + forwardOnly)
// nMode = 2 -- только для добавления (appendOnly)
int AFX_EXT_API sOpen(CRecordNet* prs, int nMode);
// В основном применяется для укорочения строки
// OpenNet("",CRecordset::readOnly,"",CRecordset::forwardOnly);
int AFX_EXT_API sOpen2(CRecordNet* prs, int nMode, CString cDescField);


class AFX_EXT_CLASS TablDescr: public CObject
{
public:
    TablDescr(CDatabase *,CString);
//конструктор принимает адрес открытого источника и имя таблицы
    int isField(CString );
// -1 - нет поля, >-1 - есть поле
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
Программа расчета сопротивления прижатой задвижки
принимает: 
- адрес источника с META таблицами
- код гидравлического типа задвижки (CODTV по VALVE)
- процент открытия задвижки
- условный диаметр задвижки
возвращает 
положительное число - сопротивление задвижки
-1 - неправильно заданы параметры (процент, диаметр)
-2 - ошибка чтения таблицы RESVALVE
-3 - тип задвижки не найден в таблице RESVALVE
-4 - ошибочные данные в таблице RESVALVE
*/
