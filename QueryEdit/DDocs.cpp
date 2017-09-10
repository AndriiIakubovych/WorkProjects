#include "stdafx.h"

#include "QueryEditRes\resource.h"

#include "DQueryEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDocsDlg dialog
CDocsDlg::CDocsDlg(SMetaInfo* metainfo, CDatabNet *bMSG, CDatabNet *bCN, CWnd* pParent /*=NULL*/)
	: CSetDialog(CDocsDlg::IDD, metainfo,pParent)
	, m_linkbas(false)
{
	m_ctrans = FALSE;
	m_cbreakepage = FALSE;
	m_ctypetopo = -1;
	m_ccodtech = -1;
	m_cvidobj = -1;
	m_cwhateq = -1;
	m_crefer = FALSE;
	m_creport = FALSE;
	m_csearch = FALSE;
	m_cselection = FALSE;
	m_cisnumrec = FALSE;
	m_cisgotosel = FALSE;
	m_pToolTip = NULL;
	m_MSGBase = bMSG;
	m_CNBase = bCN;
}

CDocsDlg::~CDocsDlg()
{
	delete m_pToolTip;
}

void CDocsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ISGOTOSEL, m_cisgotoselctrl);
	DDX_Control(pDX, IDC_ISNUMREC, m_cisnumrecctrl);
	DDX_Control(pDX, IDC_BREAKPAGE, m_cbreakpagectrl);
	DDX_Control(pDX, IDC_TRANSP, m_ctransctrl);
	DDX_Control(pDX, IDC_HFONT, m_chfontctrl);
	DDX_Control(pDX, IDC_MINWIDCOL, m_cminwidcolctrl);
	DDX_Control(pDX, IDC_NCOLHEAD, m_cncolheadctrl);

    DDX_Control (pDX, IDC_QUERYHEAD , m_cqueryheadctrl );
	DDX_Control (pDX, IDC_QUERYDATA , m_cquerydatactrl );
	DDX_Control (pDX, IDC_QUERYTITLE, m_cquerytitlectrl);
	DDX_Control (pDX, IDC_QUERYHEAD_4STATIC , m_cqueryheadctrl .m_st);
	DDX_Control (pDX, IDC_QUERYDATA_4STATIC , m_cquerydatactrl .m_st);
	DDX_Control (pDX, IDC_QUERYTITLE_4STATIC, m_cquerytitlectrl.m_st);
	DDX_CBString(pDX, IDC_QUERYDATA, m_cquerydata);
	DDX_CBString(pDX, IDC_QUERYHEAD, m_cqueryhead);
	DDX_CBString(pDX, IDC_QUERYTITLE, m_cquerytitle);

    DDX_Control(pDX, IDC_WHATEQ, m_cwhateqctrl);
	DDX_Control(pDX, IDC_VIDOBJ, m_cvidobjctrl);
	DDX_Control(pDX, IDC_CODTECH, m_ccodtechctrl);
	DDX_Control(pDX, IDC_TYPETOPO, m_ctypetopoctrl);
	DDX_Text(pDX, IDC_CODDOC, m_ccoddoc);
	DDX_Text(pDX, IDC_NAMEDOC, m_cnamedoc);
	DDX_Text(pDX, IDC_NCOLHEAD, m_cncolhead);
	DDX_Text(pDX, IDC_MINWIDCOL, m_cminwidcol);
	DDX_Check(pDX, IDC_TRANSP, m_ctrans);
	DDX_Check(pDX, IDC_BREAKPAGE, m_cbreakepage);
	DDX_Text(pDX, IDC_HFONT, m_chfont);
	DDX_CBIndex(pDX, IDC_TYPETOPO, m_ctypetopo);
	DDX_CBIndex(pDX, IDC_CODTECH, m_ccodtech);
	DDX_CBIndex(pDX, IDC_VIDOBJ, m_cvidobj);
	DDX_CBIndex(pDX, IDC_WHATEQ, m_cwhateq);
	DDX_Check(pDX, IDC_REFER, m_crefer);
	DDX_Check(pDX, IDC_REPORT, m_creport);
	DDX_Check(pDX, IDC_SEARCH, m_csearch);
	DDX_Check(pDX, IDC_SELECTION, m_cselection);
	DDX_Check(pDX, IDC_ISNUMREC, m_cisnumrec);
	DDX_Check(pDX, IDC_ISGOTOSEL, m_cisgotosel);
	DDX_Check(pDX, IDC_BREAK, m_cbreak);
	DDX_Control(pDX, IDC_BREAK, m_cbreakctrl);
	DDX_Control(pDX, IDC_CLASSES, m_classesctrl);
	DDX_Control(pDX, IDC_REPORTCOMP, m_clinkbas);
	DDX_Check(pDX, IDC_REPORTCOMP, m_linkbas);
	DDX_Control(pDX, IDC_TABLES, m_ctables);
	DDX_Control(pDX, IDC_PLACETITLE, m_cptitlectrl);
	DDX_Check(pDX, IDC_PLACETITLE, m_cptitle);
}

BEGIN_MESSAGE_MAP(CDocsDlg, CDialog)
	ON_BN_CLICKED(IDC_PREV, OnPrev)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_EN_CHANGE(IDC_NAMEDOC, OnSomethingChanged)
	ON_CBN_EDITCHANGE(IDC_QUERYDATA, OnQueryDataChanged)
	ON_BN_CLICKED(IDC_VERIFY, OnVerify)
	ON_CBN_DROPDOWN(IDC_QUERYDATA, OnDropdownQuerydata)
	ON_CBN_EDITCHANGE(IDC_QUERYHEAD, OnSomethingChanged)
	ON_EN_CHANGE(IDC_NCOLHEAD, OnSomethingChanged)
	ON_EN_CHANGE(IDC_MINWIDCOL, OnSomethingChanged)
	ON_BN_CLICKED(IDC_TRANSP, OnSomethingChanged)
	ON_BN_CLICKED(IDC_BREAKPAGE, OnSomethingChanged)
	ON_EN_CHANGE(IDC_HFONT, OnSomethingChanged)
	ON_CBN_SELCHANGE(IDC_TYPETOPO, OnSomethingChanged)
	ON_CBN_SELCHANGE(IDC_CODTECH, OnSomethingChanged)
	ON_CBN_SELCHANGE(IDC_VIDOBJ, OnSomethingChanged)
	ON_CBN_SELCHANGE(IDC_WHATEQ, OnSomethingChanged)
	ON_BN_CLICKED(IDC_REFER, OnSomethingChanged)
	ON_BN_CLICKED(IDC_SEARCH, OnSomethingChanged)
	ON_BN_CLICKED(IDC_REPORT, OnSomethingChanged)
	ON_CBN_SELCHANGE(IDC_QUERYDATA, OnQueryDataChanged)
	ON_BN_CLICKED(IDC_SELECTION, OnSomethingChanged)
	ON_CBN_SELCHANGE(IDC_QUERYHEAD, OnSomethingChanged)
	ON_BN_CLICKED(IDC_ISNUMREC, OnSomethingChanged)
	ON_CBN_EDITCHANGE(IDC_QUERYTITLE, OnSomethingChanged)
	ON_CBN_SELCHANGE(IDC_QUERYTITLE, OnSomethingChanged)
	ON_BN_CLICKED(IDC_BREAK, OnSomethingChanged)
	ON_BN_CLICKED(IDC_ISGOTOSEL, OnSomethingChanged)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_TABLES, &CDocsDlg::OnBnClickedTables)
	ON_BN_CLICKED(IDC_REPORTCOMP, OnSomethingChanged)
	ON_BN_CLICKED(IDC_PLACETITLE, OnSomethingChanged)
END_MESSAGE_MAP()

BOOL CDocsDlg::OnInitDialog() 
{
	CSetDialog::OnInitDialog();

	//Set up the tooltip
	m_pToolTip = new CToolTipCtrl;
	if (!m_pToolTip->Create(this))
	{
		TRACE("Unable To create ToolTip\n");
		return TRUE;
	}

	if (m_pToolTip->AddTool(this, _T("About Box")))
	{
		TRACE("Unable to add Dialog to the tooltip\n");
	}

	if (m_pToolTip->AddTool(&m_classesctrl, m_classeslist))
	{
		TRACE("Unable to add OK button to the tooltip\n");
	}

	m_pToolTip->Activate(TRUE);

	CString cltext;
	cltext.Format(_T(" лассы: %d"), m_classescount);
	m_classesctrl.SetWindowText(cltext);

	if (m_bCheckOnly)
	{
		OnVerify();
		EndDialog(IDCANCEL);
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CQueryCombo::AddString(CString cQName, bool b14)
{
    int nIndex = CComboBox::AddString(cQName);
    SetItemData(nIndex,b14);
    return nIndex;
}

int CQueryCombo::SetStaticText()
{
	int querysel = GetCurSel();
	if(querysel == CB_ERR)
    {
        m_st.SetWindowText(_T(""));
        return -1;
    }

    DWORD data = GetItemData(querysel);
    m_st.SetWindowText((data == 0) ? _T("") : _T("14"));

    return (data == 1);
}

void CDocsDlg::LoadNames()
{
	POSITION pos=m_metainfo->m_ltypetopo.GetHeadPosition();
	while(pos)
		m_ctypetopoctrl.AddString(m_metainfo->m_ltypetopo.GetNext(pos));

	pos=m_metainfo->m_lcodtech.GetHeadPosition();
	while(pos)
		m_ccodtechctrl.AddString(m_metainfo->m_lcodtech.GetNext(pos));

	pos=m_metainfo->m_lvidobj.GetHeadPosition();
	while(pos)
		m_cvidobjctrl.AddString(m_metainfo->m_lvidobj.GetNext(pos));
	
	pos=m_metainfo->m_lwhateq.GetHeadPosition();
	while(pos)
		m_cwhateqctrl.AddString(m_metainfo->m_lwhateq.GetNext(pos));

    bool bscrqueries = (m_scrqueries != NULL);
    CString cQName;
	m_queries->Reload();
	m_queries->MoveFirst();
	while(!m_queries->IsEOF())
	{
        cQName = m_queries->m_strName;
        //if(m_scrqueries)
            //cQName += "    (4)";

		m_cquerydatactrl .AddString(cQName,false);
		m_cqueryheadctrl .AddString(cQName,false);
		m_cquerytitlectrl.AddString(cQName,false);
		m_queries->MoveNext(); 
	}

	if(m_scrqueries)			//дополнительно запросы из 14 базы если есть
	{
		m_scrqueries->Reload();
		m_scrqueries->MoveFirst();
		while(!m_scrqueries->IsEOF())
		{
			if(m_cquerydatactrl.FindStringExact(-1,m_scrqueries->m_strName) == CB_ERR)
			{
				m_cquerydatactrl .AddString(m_scrqueries->m_strName,true);
				m_cqueryheadctrl .AddString(m_scrqueries->m_strName,true);
				m_cquerytitlectrl.AddString(m_scrqueries->m_strName,true);
			}
			m_scrqueries->MoveNext();
		}
	}
}

void CDocsDlg::LoadData()
{
	CDocsSet *m_docsset=(CDocsSet *)m_set;

	m_ccoddoc.Format(_T("%d"),m_docsset->m_CODDOC);
	m_cnamedoc=m_docsset->m_NAMEDOC;

	m_cquerydata=m_docsset->m_QUERYDATA;
	m_cquerydata.TrimLeft();
	m_cquerydata.TrimRight();

	m_cqueryhead=m_docsset->m_QUERYHEAD;
	m_cqueryhead.TrimLeft();
	m_cqueryhead.TrimRight();

	m_cquerytitle = m_docsset->m_QUERYTITLE;
	m_cquerytitle.TrimRight();
	m_cquerytitle.TrimLeft();

	m_cncolhead=m_docsset->m_NCOL_HEAD;
	m_cminwidcol=m_docsset->m_MINWIDCOL;
	m_ctrans=m_docsset->m_TRANS;
	m_cbreakepage=m_docsset->m_BREAKPAGE;
	m_chfont=m_docsset->m_HFONT;

	if(m_docsset->IsFieldNull(&m_docsset->m_TYPETOPO))
		m_ctypetopo = 0;
	else
		m_ctypetopo=FindACC(m_metainfo->m_ACCtypetopo,m_docsset->m_TYPETOPO);
	if(m_docsset->IsFieldNull(&m_docsset->m_CODTECH))
		m_ccodtech = 0;
	else
		m_ccodtech=FindACC(m_metainfo->m_ACCcodtech,m_docsset->m_CODTECH);
	if(m_docsset->IsFieldNull(&m_docsset->m_VIDOBJ))
		m_cvidobj = 0;
	else
		m_cvidobj=FindACC(m_metainfo->m_ACCvidobj,m_docsset->m_VIDOBJ);
	if(m_docsset->IsFieldNull(&m_docsset->m_WHATEQ))
		m_cwhateq = 0;
	else
		m_cwhateq=FindACC(m_metainfo->m_ACCwhateq,m_docsset->m_WHATEQ);
	m_crefer=m_docsset->m_REFER;
	m_creport=m_docsset->m_REPORT;
	m_csearch=m_docsset->m_SEARCH;
	m_cselection=m_docsset->m_DSELECT;
	m_cisnumrec=m_docsset->m_ISNUMREC;
	m_ccrosstab=m_docsset->m_CROSSTAB;
	m_cisgotosel=m_docsset->m_ISGOTOSEL;
	m_cbreak = m_docsset->m_BREAK;
	m_linkbas = m_docsset->m_LINKBAS;
	if(m_docsset->IsColumnPresent(_T("PlaceTitle")))
    {
        if(m_docsset->IsFieldNull(&m_docsset->m_PlaceTitle))
            m_cptitle = 0;
        else
            m_cptitle = m_docsset->m_PlaceTitle;
    }

	UpdateData(false);
	if(m_cquerydata!="" && m_cquerydatactrl.FindStringExact(0, m_cquerydata) == -1)
	{
		AfxMessageBox(_T("«апрос на данные не существует."));
		m_cquerydatactrl.SetWindowText(m_cquerydata);
	}

    m_cqueryheadctrl .SetStaticText();
    m_cquerydatactrl .SetStaticText();
    m_cquerytitlectrl.SetStaticText();

	CSetDialog::LoadData();
	m_ischanged=FALSE;
}

BOOL CDocsDlg::SaveData()
{
	if(!VerifyData())
		return FALSE;
	CDocsSet *m_docsset=(CDocsSet *)m_set;

	DWORD docopt=0;

	if(m_ischanged)
	{
		UpdateData();
		m_docsset->Edit();

		if(m_docsset->m_QUERYDATA!=m_cquerydata)
			docopt|=DOCOPT_VARSREBUILD;

		if(m_docsset->m_ISNUMREC!=m_cisnumrec)
			docopt|=DOCOPT_ISNUMREC;

		m_docsset->m_NAMEDOC=m_cnamedoc;
		m_docsset->m_QUERYDATA=m_cquerydata;
		m_docsset->m_QUERYHEAD=m_cqueryhead;
		m_docsset->m_QUERYTITLE=m_cquerytitle;
		m_docsset->m_NCOL_HEAD=m_cncolhead;
		m_docsset->m_MINWIDCOL=m_cminwidcol;
		m_docsset->m_TRANS=m_ctrans;
		m_docsset->m_BREAKPAGE=m_cbreakepage;
		m_docsset->m_HFONT=m_chfont;
		m_docsset->m_BREAK = m_cbreak;
		m_docsset->m_LINKBAS = m_linkbas;
		if(m_ctypetopo == 0)
			m_docsset->SetFieldNull(&m_docsset->m_TYPETOPO);
		else
			m_docsset->m_TYPETOPO=(BYTE)FindACCBack(m_metainfo->m_ACCtypetopo,m_ctypetopo);
		if(m_ccodtech == 0)
			m_docsset->SetFieldNull(&m_docsset->m_CODTECH);
		else
			m_docsset->m_CODTECH=(BYTE)FindACCBack(m_metainfo->m_ACCcodtech,m_ccodtech);
		if(m_cvidobj == 0)
			m_docsset->SetFieldNull(&m_docsset->m_VIDOBJ);
		else
			m_docsset->m_VIDOBJ=(BYTE)FindACCBack(m_metainfo->m_ACCvidobj,m_cvidobj);
		if(m_cwhateq == 0)
			m_docsset->SetFieldNull(&m_docsset->m_WHATEQ);
		else
			m_docsset->m_WHATEQ=(BYTE)FindACCBack(m_metainfo->m_ACCwhateq,m_cwhateq);
		m_docsset->m_REFER=m_crefer;
		m_docsset->m_REPORT=m_creport;
		m_docsset->m_SEARCH=m_csearch;
		m_docsset->m_DSELECT=m_cselection;
		m_docsset->m_ISNUMREC=m_cisnumrec;
		m_docsset->m_CROSSTAB=m_ccrosstab;
		m_docsset->m_ISGOTOSEL=m_cisgotosel;
		m_docsset->m_PlaceTitle=m_cptitle;

		m_docsset->UpdateNet(0);

		GetOwner()->SendMessage(MES_DOCOPTIONSCHANGED,m_docsset->m_CODDOC,docopt);

		m_ischanged=FALSE;
	}
	return TRUE;
}

void CDocsDlg::OnPrev() 
{
	CSetDialog::OnPrev();
}

void CDocsDlg::OnNext() 
{
	CSetDialog::OnNext();
}

void CDocsDlg::OnSomethingChanged() 
{
	ConformDataFields();
	m_ischanged=TRUE;
	
}

void CDocsDlg::OnQueryDataChanged()
{
	CString query;
	int querysel = m_cquerydatactrl.GetCurSel();
	if(querysel!=-1)
	{
		m_cquerydatactrl.GetLBText(querysel,query);
		if(m_queries->FindName(query))
		{
			m_ccrosstab=m_queries->m_bcrosstab;
		}
		else if(m_scrqueries && m_scrqueries->FindName(query))
			//дл€ 14 баз
			m_ccrosstab=m_scrqueries->m_bcrosstab;

        m_cquerydatactrl.SetStaticText();
	}

	OnSomethingChanged();
}

void CDocsDlg::ConformDataFields()
{
	UpdateData();
	CWnd *wnd=GetFocus();
	m_cminwidcolctrl.EnableWindow(false);
	m_ctransctrl.EnableWindow(false);
	m_cbreakpagectrl.EnableWindow(false);
	m_chfontctrl.EnableWindow(false);
	m_ctypetopoctrl.EnableWindow(false);
	m_ccodtechctrl.EnableWindow(false);
	m_cvidobjctrl.EnableWindow(false);
	m_cwhateqctrl.EnableWindow(false);
	m_cncolheadctrl.EnableWindow(false);
	m_cbreakctrl.EnableWindow(false);
	m_cptitlectrl.ShowWindow(SW_HIDE);

	if(m_set->IsColumnPresent(_T("BREAK")))
		m_cbreakctrl.EnableWindow(true);

	if(m_set->IsColumnPresent(_T("PlaceTitle")))
		m_cptitlectrl.ShowWindow(SW_SHOW);

	if (m_creport)
		if (m_set->IsColumnPresent(_T("LINKBAS")))
		{
			m_clinkbas.EnableWindow(true);
			if (m_linkbas)
				m_ctables.EnableWindow(true);
			else
				m_ctables.EnableWindow(false);
		}
		else
		{
			m_clinkbas.EnableWindow(false);
			m_ctables.EnableWindow(false);
		}
	else
	{
		m_clinkbas.EnableWindow(false);
		m_ctables.EnableWindow(false);
	}


	if(m_cqueryheadctrl.IsWindowEnabled())
		if(m_cselection && !m_csearch && !m_creport && !m_crefer)
		{
			m_cqueryheadctrl.EnableWindow(false);
		}
		else;
	else
		if(m_csearch || m_creport || m_crefer)
		{
			m_cqueryheadctrl.EnableWindow(true);
		}

	if(m_set->IsColumnPresent(_T("QUERYTITLE")))
		m_cquerytitlectrl.EnableWindow(true);
	else
		m_cquerytitlectrl.EnableWindow(false);

	if(m_cselection)
		m_cvidobjctrl.EnableWindow();
	
	if(m_cselection && m_set->IsColumnPresent(_T("ISGOTOSEL")))
		m_cisgotoselctrl.EnableWindow();
	else
		m_cisgotoselctrl.EnableWindow(false);
	if(m_csearch)
	{
		m_cncolheadctrl.EnableWindow();
		m_cminwidcolctrl.EnableWindow();
		m_ctransctrl.EnableWindow();
		m_cbreakpagectrl.EnableWindow();
		m_chfontctrl.EnableWindow();
		m_cvidobjctrl.EnableWindow();
	}
	if(m_creport)
	{
		m_cncolheadctrl.EnableWindow();
		m_cminwidcolctrl.EnableWindow();
		m_ctransctrl.EnableWindow();
		m_cbreakpagectrl.EnableWindow();
		m_chfontctrl.EnableWindow();
	}
	if(m_crefer)
	{
		m_cncolheadctrl.EnableWindow();
		m_cminwidcolctrl.EnableWindow();
		m_ctransctrl.EnableWindow();
		m_cbreakpagectrl.EnableWindow();
		m_chfontctrl.EnableWindow();
		m_ctypetopoctrl.EnableWindow();
		m_ccodtechctrl.EnableWindow();
		m_cwhateqctrl.EnableWindow();
		m_cvidobjctrl.EnableWindow();
	}
	if(!m_ctrans)
		m_cminwidcolctrl.EnableWindow(false);

	if(m_creport && m_set->IsColumnPresent(_T("ISNUMREC")))
		m_cisnumrecctrl.EnableWindow();
	else
		m_cisnumrecctrl.EnableWindow(false);

    m_cqueryheadctrl .SetStaticText();
    m_cquerytitlectrl.SetStaticText();

	wnd->SetFocus();
//	m_cqueryheadctrl.SetEditSel(-1,-1);
}

BOOL CDocsDlg::VerifyData()
{
	CSQLAnalyzer *curqueries;
	if(!m_queries->FindName(m_cquerydata) && m_scrqueries && m_scrqueries->FindName(m_cquerydata))
		curqueries = m_scrqueries;
	else
		curqueries = m_queries;
	BeginWaitCursor();
	UpdateData();
	BOOL ispass=TRUE;
	if(m_csearch && m_cselection)
	{
		DoDataError(_T("ѕоиск и выделение не могут быть выбраны одновременно"));
		ispass=FALSE;
	}

	m_cquerydata.TrimLeft();
	m_cquerydata.TrimRight();

	if(m_cquerydata=="")
	{
		if(!DoDataWarning(_T("Ќе выбран запрос дл€ данных")))
			ispass=FALSE;
	}
	else
	{
		curqueries->Reload();
		if(!m_queries->FindName(m_cquerydata) && (!m_scrqueries || !m_scrqueries->FindName(m_cquerydata)))
		{
			DoDataError(_T("¬веденного запроса на данные не существует"));
			ispass=FALSE;
		}
		else
		{
			curqueries->TranslateSQL(QE_TRANS_NEEDCOLS);
			BOOL isNumPresent=(curqueries->FindCol(_T("num"))!=-1);
			if(((m_crefer || m_cselection) && !isNumPresent) ||
				(m_csearch && !isNumPresent &&
					AfxMessageBox(_T("ѕредназначен ли данный документ дл€ поиска графических объектов?"),MB_YESNO)==IDYES))
			{
				DoDataError(_T("¬ запросе нет колонки num"));
				ispass=FALSE;
			}
			//проверка на наличие лишних колонок
			BOOL superflous=FALSE;
			CColsSet cset((CDatabNet *)m_set->m_pDatabase);
			cset.m_strFilter.Format(_T("CODDOC=%d"),((CDocsSet *)m_set)->m_CODDOC);
			cset.Open();
			CString mess = "ѕрисутствуют описанные колонки, отсутствующие в запросе (";
			while(!cset.IsEOF())
			{
				if(curqueries->FindCol(cset.m_NAMSQLCOL)==-1)
				{
					if(superflous)
						mess += ", " + cset.m_NAMECOL;
					else
						mess += cset.m_NAMECOL;
					superflous=TRUE;
				}
				cset.MoveNext();
			}
			cset.Close();
			mess += ")";
			if(superflous)
			{
				if(!DoDataWarning(mess))
					ispass=FALSE;
			}
		}
	}

	m_cqueryhead.TrimRight();
	m_cqueryhead.TrimLeft();
	if(m_cqueryhead!="")
	{
		//проверка нет ли таких переменных, кот. есть в шанке, но нет в данных
		VARARRAY datvars;
		if(curqueries->FindName(m_cquerydata))
		{
			curqueries->TranslateSQL(QE_TRANS_NEEDVARS);
			datvars.Append(curqueries->m_viVars);
		}
		if(curqueries->FindName(m_cqueryhead))
		{
			curqueries->TranslateSQL(QE_TRANS_NEEDVARS);
			int pres=FALSE;
			for(int i=0;i<curqueries->m_viVars.GetSize();i++)
			{
				pres=FALSE;
				for(int j=0;j<datvars.GetSize();j++)
					if(datvars[j].m_strName.CompareNoCase(curqueries->m_viVars[i].m_strName)==0)
						pres=TRUE;
				if(!pres)
				{
					DoDataError(_T("¬ запросе на шапку присутствуют переменные, которых нет в запросе на данные"));
					ispass=FALSE;
					break;
				}
			}
		}
	}

	if((m_cselection || m_cbreak) && !m_csearch && !m_creport && !m_crefer)
	{
		if(!DoDataWarning(_T("ƒокумент представл€ет из себ€ выделение. ѕосле сохранени€ все колонки будут удалены")))
			ispass=FALSE;
	}

	if(!m_cbreak && !m_cselection && !m_csearch && !m_creport && !m_crefer)
	{
		DoDataError(_T("Ќе выбран тип документа"));
		ispass=FALSE;
	}
	
	EndWaitCursor();
	return ispass;
}

void CDocsDlg::OnVerify() 
{
	CSetDialog::OnVerify();
}

void CDocsDlg::OnDropdownQuerydata() 
{
	m_ischanged = TRUE;	
}

void CDocsDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CSetDialog::OnMouseMove(nFlags, point);
}

BOOL CDocsDlg::PreTranslateMessage(MSG* pMsg)
{
	if (NULL != m_pToolTip)
		m_pToolTip->RelayEvent(pMsg);

	return CSetDialog::PreTranslateMessage(pMsg);
}

void CDocsDlg::OnBnClickedTables()
{
	CTablesDlg tbl(m_MSGBase, m_CNBase, ((CDocsSet *) m_set)->m_CODDOC);
	tbl.DoModal();
}
