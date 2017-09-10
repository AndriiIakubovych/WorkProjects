struct ReorgParam {
  CString cdirb; //���� � DBF ������;
  CString nmsrs; //��� ��������� ODBC ��� �������, � ������� �������������� ������;
  CString foldnm;//������������ ��� ����� � MIF �������;
  CString mfnm;  //������������ ��� MIF �����(������� ���������� .MIF);
  CString crdsys;//������ � ��������� ��������, ������ ��� 
                 //������������� ���������.
  CString quernm;//��� ������� ��� �������� ������;
  int isys;      //�������� SYS ��� ���������� �������;
  int ig;        //������ ������� (2 ��� 4);
  int szx;       //������ �������� �� ����������� (sizx);
  int szy;       //������ �������� �� ��������� (sizy);
  int rgrecr;    //����� ��������� ���������� �������������� � �������: 
                 //    1-��������� ����� ������, 2-��������� �� ����������;
  int iswincd;   //�������� ��������� ������� (WINDOWS - 0,DOS - 1);
  int isugcrd;   //�������� ������������ ��������� (������� - 0, ��������� - 1);
  int iscirccd;  //�������� ��� ������, � ������� ������������ ��������� 
                 //    ����� - 0, ��������� -1
  int issmoln;   //������� �������� ������ ����� �� �������
  int lntp;      //��� �����;
  int lnlev;     //������� �����;
  int txtp;      //��� ��������;
  int txlev;     //������� ��������;
  int prtp;      //��� �������� ��� �������������� ����������;
  int prlev;     //������� �������� ��� �������������� ����������;
  int codl;      //����� ���� ����� �����;
  int codt;      //����� ���� ����� ��������;
  int codp;      //����� ���� ����� �������� ��� ����������;
  int coddel;    //������� �������� ������ ���� �� ����(1-�������,2-�� �������);
  int igrp;      //���������� �������������� �� ����� �������
  int iscp;      //���������� �������������� �� ����� ��������� �����
  int iicn;      //���������� �������������� �� ����� ����������
//int iskhr;     //������ ������������� ������� 
  int codk;      //����� ���� ����� �������� �������������;
  int txtpk;     //��� �������� �������������;
  int txlevk;    //������� �������� �������������;
  int numfld;    //����� ���� ��������������;
  double xshift; //����� ������ �� ��� �������;
  double xkoef;  //����������� ���������� �� ��� �������;
  double yshift; //����� ����� �� ��� �������;
  double ykoef;  //����������� ���������� �� ��� �������;
  double rad;    //������ �������� �������;
  double angrt;  //���� �������� ������ ������� �������.
  double hkhr;   //������ �������� �������������;
  CArray<CString,CString> midfldn; //������ ���� �����
  CArray<int,int> midfldl;         //������ ���� �����/�������� �����
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
��������� �������������� MIF/MID ������ � DBF ����� (��� �������).
���������:
-���� � DBF ������;
-��� ��������� ODBC ��� �������, � ������� �������������� ������;
-���� � MIF �����;
-��� MIF ����� (������� ���������� .MIF);
-������ ������� (2 ��� 4);
-������ �������� �� ����������� (sizx);
-������ �������� �� ��������� (sizy);
-�������� ��������� ������� (WINDOWS - 0,DOS - 1);
-�������� ������������ ��������� (������� - 0, ��������� - 1);
-������� ��� �����;
-������� ������� �����;
-������� ��� ��������;
-������� ������� ��������;
-������������ ������� ����, ���� �� ����� � MIF �����;
-������������ ������� ����, ���� �� ������ � MIF �����;
-������� ����� �� ��� �������;
-������� ����������� ���������� �� ��� �������;
-������� ����� �� ��� �������;
-������� ����������� ���������� �� ��� �������;
-������� ������ �������� �������.
*/

typedef int (*tDbfToMdb)
    (
      ReorgParam *
    );
int AFX_EXT_API DbfToMdb(ReorgParam *);
/*
int AFX_EXT_API DbfToMdb(CString ,CString ,int ,int ,int , int ,int ,int);
��������� �������� DBF ������ � ����.
���������:
-���� � DBF ������;
-��� ��������� ODBC ��� �������, � ������� �������������� ������;
-������ ������� (2 ��� 4);
-������� ��� �����;
-������� ��� ��������;
-������� ������� ����� � ������������� ������ (-1 - �����������);
-������� ������� ������� � ������������� ������ (-1 - �����������);
-������� �������� ����� �������������� ������ ������� �����;
*/
int AFX_EXT_API ScrToMif(ReorgParam *);
/*
int AFX_EXT_API ScrToMif(CString ,int ,int ,int ,HWND ,CString *,
  int *,double *,double *,double *,double *,double *);
��������� �������� � MIF/MID ����� (� ��������).
���������:
-��� ��������� ODBC ��� �������, �� �������� �������������� �������;
-������ ������� (2 ��� 4);
-����� ��������� ���������� �������������� � �������: 
     1-��������� ����� ������, 2-��������� �� ����������;
-��� ������������ (PERSON) ���� codk;
-����;
-������������ ���� � MIF ������;
-����������� ������� ��������� ����� � �������� ����� (� - 0,�� - 1)
   ���� iswincd;
-������������ ������� ������� ������� SCR?XY ���� isugcrd;
-������� ����� ����� �� ��� �������;
-������� ����������� ������ �� ��� �������;
-������� ����� ����� �� ��� �������;
-������� ����������� ������ �� ��� �������;
-������� ������� �� ������� ������� � ��������;
CString AFX_EXT_API ScrToMifEx(CString ,CString ,int ,int ,int ,int ,int ,
  double ,double ,double ,double ,double ,int ,int ,
  CArray<CString,CString> *,CString );
*/
CString AFX_EXT_API ScrToMifEx(ReorgParam *);
/*
��������� �������� � MIF/MID �����(��� �������).
���������:
-��� ��������� ODBC ��� �������, �� �������� �������������� �������;
-���� � MIF �����;
-������ ������� (2 ��� 4);
-��� �������� ������ (0-����������,1-����������,2-�������) iscirccd;
-VIDOVJ ���� lnlev;
-��� ���� ������� ���� lntp;
-����������� ������� ��������� ����� � �������� ����� (� - 0,�� - 1);
-����� ����� �� ��� �������;
-����������� ������ �� ��� �������;
-����� ����� �� ��� �������;
-����������� ������ �� ��� �������;
-������� �� ������� ������� � ��������;
-���� >0 -��� ���������� �������, <0 - ��� ����������� ������� ���� txtp;
-��� ������������ - ����� �������� ��� ����������� �������
-������ ���������� ���������� ����� ��� MIF ����� midfldn;
-������ �� ������ ������ - mfnm;
-������ � ��������� ��������, ������ ��� ������������� ���������.
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
��������� �������� ��������� � DBF �����.
���������:
-���� � DBF ������;
-��� ��������� ODBC ��� �������, ���������� �������� �����������;
-������ ����� SCR(C) ��� ������ ������- ���� mfnm; 
-������ ������� (2 ��� 4);
-������ �������� �� ����������� (sizx);
-������ �������� �� ��������� (sizy);
-������� ������� ������� SCR(C)XY;
   ���� iswincd;
-������� ����� ����� �� ��� �������;
-������� ����������� ������ �� ��� �������;
-������� ����� ����� �� ��� �������;
-������� ����������� ������ �� ��� �������;
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
