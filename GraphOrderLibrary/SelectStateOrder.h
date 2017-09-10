#if !defined(AFX_SELECTSTATEORDER_H__9F85AC42_E061_4682_9D6B_D818AC0A31B3__INCLUDED_)
#define AFX_SELECTSTATEORDER_H__9F85AC42_E061_4682_9D6B_D818AC0A31B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelectStateOrder.h : header file
//

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CSelectStateOrder window

class CSelectStateOrder : public CComboBox
{
	// Construction
public:
	CSelectStateOrder();
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	CString IniFile;
	CString StrConnection;
	int DrawItemNumber;
	vector <int> CodsClass;
	vector <CString> StateOrder;
	vector <int> Red;
	vector <int> Green;
	vector <int> Blue;
	COLORREF Color;
	int SelectItem;

	// Attributes
public:

	// Operations
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectStateOrder)
	//}}AFX_VIRTUAL

	// Implementation
public:
	virtual ~CSelectStateOrder();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSelectStateOrder)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELECTSTATEORDER_H__9F85AC42_E061_4682_9D6B_D818AC0A31B3__INCLUDED_)
