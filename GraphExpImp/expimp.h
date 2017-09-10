struct ReorgParam {
  CString cdirb; //путь к DBF файлам;
  CString nmsrs; //имя источника ODBC для раздела, в который предполагается импорт;
  CString foldnm;//возвращаемое имя папки с MIF файлами;
  CString mfnm;  //возвращаемое имя MIF файла(включая расширение .MIF);
  CString crdsys;//строка с описанием проекции, пробел для 
                 //прямоугольных координат.
  CString quernm;//имя запроса для экспорта данных;
  int isys;      //значение SYS для выбранного раздела;
  int ig;        //группа раздела (2 или 4);
  int szx;       //размер квадрата по горизонтали (sizx);
  int szy;       //размер квадрата по вертикали (sizy);
  int rgrecr;    //режим изменения параметров преобразования в диалоге: 
                 //    1-параметры можно менять, 2-параметры не изменяются;
  int iswincd;   //исходная кодировка текстов (WINDOWS - 0,DOS - 1);
  int isugcrd;   //исходное расположение координат (обычное - 0, инверсное - 1);
  int iscirccd;  //исходный тип данных, к которым преобразются примитивы 
                 //    линии - 0, примитивы -1
  int issmoln;   //признак пропуска лишних точек на ломаной
  int lntp;      //тип линий;
  int lnlev;     //уровень линий;
  int txtp;      //тип надписей;
  int txlev;     //уровень надписей;
  int prtp;      //тип объектов для преобразования примитивов;
  int prlev;     //уровень объектов для преобразования примитивов;
  int codl;      //пункт меню типов линий;
  int codt;      //пункт меню типов надписей;
  int codp;      //пункт меню типов объектов для примитивов;
  int coddel;    //признак удаления данных того же типа(1-удалять,2-не удалять);
  int igrp;      //количество подготовленных ко вводу ломаных
  int iscp;      //количество подготовленных ко вводу текстовых строк
  int iicn;      //количество подготовленных ко вводу примитивов
//int iskhr;     //импорт характеристик ломаных 
  int codk;      //пункт меню типов надписей характеристик;
  int txtpk;     //тип надписей характеристик;
  int txlevk;    //уровень надписей характеристик;
  int numfld;    //номер поля характеристики;
  double xshift; //сдвиг вправо по оси абсцисс;
  double xkoef;  //коэффициент растяжения по оси абсцисс;
  double yshift; //сдвиг вверх по оси ординат;
  double ykoef;  //коэффициент растяжения по оси ординат;
  double rad;    //радиус точечных оъектов;
  double angrt;  //угол поворота против часовой стрелки.
  double hkhr;   //высота надписей характеристик;
  CArray<CString,CString> midfldn; //массив имен полей
  CArray<int,int> midfldl;         //массив длин полей/выбраных типов
};
typedef int (*tMifToDbf)
    (
     ReorgParam *
    );

int AFX_EXT_API MifToDbf(ReorgParam *);
/*
*/
typedef int (*tMifToDbfEx)
    (
     ReorgParam *
    );
int AFX_EXT_API MifToDbfEx(ReorgParam *);

/*
Процедура преобразования MIF/MID файлов в DBF файлы (без диалога).
принимает:
-путь к DBF файлам;
-имя источника ODBC для раздела, в который предполагается импорт;
-путь к MIF файлу;
-имя MIF файла (включая расширение .MIF);
-группа раздела (2 или 4);
-размер квадрата по горизонтали (sizx);
-размер квадрата по вертикали (sizy);
-исходная кодировка текстов (WINDOWS - 0,DOS - 1);
-исходное расположение координат (обычное - 0, инверсное - 1);
-текущий тип линий;
-текущий уровень линий;
-текущий тип надписей;
-текущий уровень надписей;
-возвращаемый признак того, были ли линии в MIF файле;
-возвращаемый признак того, были ли тексты в MIF файле;
-текущий сдвиг по оси абсцисс;
-текущий коэффициент растяжения по оси абсцисс;
-текущий сдвиг по оси ординат;
-текущий коэффициент растяжения по оси ординат;
-текущий радиус точечных оъектов.
*/

typedef int (*tDbfToMdb)
    (
      ReorgParam *
    );
int AFX_EXT_API DbfToMdb(ReorgParam *);
/*
int AFX_EXT_API DbfToMdb(CString ,CString ,int ,int ,int , int ,int ,int);
Процедура загрузки DBF файлов в базу.
принимает:
-путь к DBF файлам;
-имя источника ODBC для раздела, в который предполагается импорт;
-группа раздела (2 или 4);
-текущий тип линий;
-текущий тип надписей;
-признак наличия линий в преобразуемых данных (-1 - отсутствуют);
-признак наличия текстов в преобразуемых данных (-1 - отсутствуют);
-признак удаления ранее существовавших данных текущих типов;
*/
int AFX_EXT_API ScrToMif(ReorgParam *);
/*
int AFX_EXT_API ScrToMif(CString ,int ,int ,int ,HWND ,CString *,
  int *,double *,double *,double *,double *,double *);
Процедура выгрузки в MIF/MID файлы (с диалогом).
принимает:
-имя источника ODBC для раздела, из которого предполагается экспорт;
-группа раздела (2 или 4);
-режим изменения параметров преобразования в диалоге: 
     1-параметры можно менять, 2-параметры не изменяются;
-код пользователя (PERSON) поле codk;
-окно;
-возвращаемый путь к MIF файлам;
-номинальная единица измерения длины в выходном файле (м - 0,мм - 1)
   поле iswincd;
-возвращаемый признак наличия таблицы SCR?XY поле isugcrd;
-текущий сдвиг влево по оси абсцисс;
-текущий коэффициент сжатия по оси абсцисс;
-текущий сдвиг влево по оси ординат;
-текущий коэффициент сжатия по оси ординат;
-текущий поворот по часовой стрелке в градусах;
CString AFX_EXT_API ScrToMifEx(CString ,CString ,int ,int ,int ,int ,int ,
  double ,double ,double ,double ,double ,int ,int ,
  CArray<CString,CString> *,CString );
*/
CString AFX_EXT_API ScrToMifEx(ReorgParam *);
/*
Процедура выгрузки в MIF/MID файлы(без диалога).
принимает:
-имя источника ODBC для раздела, из которого предполагается экспорт;
-путь к MIF файлу;
-группа раздела (2 или 4);
-тип исходных данных (0-поточечные,1-символьные,2-битовые) iscirccd;
-VIDOVJ поле lnlev;
-код вида объекта поле lntp;
-номинальная единица измерения длины в выходном файле (м - 0,мм - 1);
-сдвиг влево по оси абсцисс;
-коэффициент сжатия по оси абсцисс;
-сдвиг влево по оси ординат;
-коэффициент сжатия по оси ординат;
-поворот по часовой стрелке в градусах;
-Если >0 -код графичекой области, <0 - без графической области поле txtp;
-код пользователя - имеет значение для графической области
-массив символьных описателей полей для MIF файла midfldn;
-фильтр на выбрку данных - mfnm;
-строка с описанием проекции, пробел для прямоугольных координат.
*/
typedef int (*tScrToDbf)
    (
     ReorgParam *
/*
    CString ,CString ,CString ,CString ,
    int ,int *,int *,int *,double *,double *,double *,double *,double *
*/
    );
int AFX_EXT_API ScrToDbf(ReorgParam *);
/*
int AFX_EXT_API ScrToDbf(CString ,CString ,CString ,CString ,
  int ,int *,int *,int *,double *,double *,double *,double *,double *);
Процедура выгрузки координат в DBF файлы.
принимает:
-путь к DBF файлам;
-имя источника ODBC для раздела, координаты которого выгружаются;
-фильтр файла SCR(C) для отбора данных- поле mfnm; 
-группа раздела (2 или 4);
-размер квадрата по горизонтали (sizx);
-размер квадрата по вертикали (sizy);
-признак наличия таблицы SCR(C)XY;
   поле iswincd;
-текущий сдвиг влево по оси абсцисс;
-текущий коэффициент сжатия по оси абсцисс;
-текущий сдвиг влево по оси ординат;
-текущий коэффициент сжатия по оси ординат;
*/
void AFX_EXT_API NamCopn(CDatabNet *,CString );
void AFX_EXT_API CreaProc(CString ,CString );
int AFX_EXT_API Reorgcr(CString ,CDatabNet *,CString );
int AFX_EXT_API addpnt(CString ,CArray<double,double> *,CArray<double,double> *);
int AFX_EXT_API addpntb(CByteArray *,CArray<double,double> *,
  CArray<double,double> *);
void AFX_EXT_API WrRecno(CString ,char *,long *);
int AFX_EXT_API CreDbf(CDatabNet *,CString ,CString ,CString ,FILE **);
int AFX_EXT_API InsDbfCoor(CString ,CString ,CString ,CString ,
  CDatabNet *,int ,int ,int );
int AFX_EXT_API frmdbsrc(CString ,CString ,CString ,CString ,WORD );
HKEY AFX_EXT_API ODBCRgOp();
int AFX_EXT_API PthDesYn(HKEY ,CString ,CString *,CString *);

/////////////////////////////////////////////////////////////////////////////
// Tb_reg recordset

class AFX_EXT_API Tb_reg : public CRecordNet
{
public:
	Tb_reg(CDatabNet* ,CString);
//  DECLARE_DYNAMIC(Tb_reg)

// Field/Param Data
	//{{AFX_FIELD(Tb_reg, CRecordset)
	int		m_NUMREG;
	int		m_NUMCNREG;
	int		m_NUMTWREG;
	int		m_NUMARCHREG;
	BYTE	m_TYPSYS;
	//}}AFX_FIELD
    int isarh;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Tb_reg)
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

class AFX_EXT_API Tb_city : public CRecordNet
{
public:
	Tb_city(CDatabNet* ,CString);
//  DECLARE_DYNAMIC(Tb_city)

// Field/Param Data
	//{{AFX_FIELD(Tb_city, CRecordset)
	int		m_NUMREG;
	int		m_NUMCNREG;
	int		m_NUMGRREG;
	BYTE	m_TYPSYS;
	//}}AFX_FIELD

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Tb_city)
	public:
//	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

/////////////////////////////////////////////////////////////////////////////
// Tb_layer recordset

class AFX_EXT_API Tb_layer : public CRecordNet
{
public:
	Tb_layer(CDatabNet* ,CString);
//	DECLARE_DYNAMIC(Tb_layer)

// Field/Param Data
	//{{AFX_FIELD(Tb_layer, CRecordset)
	BYTE	m_CODLAY;
	CString	m_NAMELAY;
	BYTE	m_TYPSYS;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Tb_layer)
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
