// SelectStateOrder.cpp : implementation file
//

#include "stdafx.h"
#include "GraphOrder.h"
#include "SelectStateOrder.h"

#include "CodTechRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectStateOrder


CSelectStateOrder::CSelectStateOrder()
{
}

CSelectStateOrder::~CSelectStateOrder()
{
}


BEGIN_MESSAGE_MAP(CSelectStateOrder, CComboBox)
	//{{AFX_MSG_MAP(CSelectStateOrder)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectStateOrder message handlers

void CSelectStateOrder::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your code to draw the specified item
	char buffer[MAX_PATH], buffer_str[MAX_PATH];
	CString IniWay, S;
	CDC dc;
	CRect Rect;
	CPen NoSelected(PS_SOLID, 1, RGB(255, 255, 255));
	CPen ColorRectangle(PS_SOLID, 1, RGB(0, 0, 0));
	CBrush ColorState;
	CBrush ColorList;
	ColorList.CreateSolidBrush(RGB(255, 255, 255));
	dc.Attach(lpDrawItemStruct->hDC);
	Rect = lpDrawItemStruct->rcItem;
	dc.SelectObject(ColorList);
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
		dc.Rectangle(Rect);
	else
	{
		dc.SelectObject(NoSelected);
		dc.Rectangle(Rect);
	}
	if (DrawItemNumber == 0)
	{
		CodTechRead CodTechRS;
		CodTechRS.StrConnection = StrConnection;
		CodTechRS.Open();
		if (!CodTechRS.IsBOF())
			CodTechRS.MoveFirst();
		while (!CodTechRS.IsEOF())
		{
			if (CodTechRS.m_CODCLAS == 51)
			{
				CodsClass.push_back(CodTechRS.m_CODSCLAS);
				if (CodTechRS.m_NAME == "нрясрярбсер")
					StateOrder.push_back("мюидеммше");
				else
					StateOrder.push_back(CodTechRS.m_NAME);
			}
			CodTechRS.MoveNext();
		}
		CodTechRS.Close();
		for (int i = 0; i < StateOrder.size(); i++)
		{
			S = "State";
			sprintf(buffer_str, "%i", CodsClass[i]);
			IniWay = IniFile;
			IniWay.Delete(IniWay.GetLength() - strlen("Svisor.ini"), strlen("Svisor.ini"));
			GetPrivateProfileString("ColorState", S + buffer_str, NULL, buffer, sizeof(buffer), IniWay + "GraphSettings.ini");
			S = buffer;
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer[j] == ',')
				{
					S.Delete(j, S.GetLength() - j);
					break;
				}
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer[j] == '(')
				{
					S.Delete(0, j + 1);
					break;
				}
			Red.push_back(atoi(S));
			S = buffer;
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer[j] == ',')
				{
					S.Delete(0, j + 1);
					if (buffer[j + 1] == ' ')
						S.Delete(0, 1);
					break;
				}
			strcpy(buffer_str, S);
			for (int j = 0; j < S.GetLength(); j++)
				if (buffer_str[j] == ',')
				{
					S.Delete(j, S.GetLength() - j);
					break;
				}
			Green.push_back(atoi(S));
			S = buffer;
			S.Delete(S.GetLength() - 1, 1);
			for (int j = S.GetLength() - 1; j >= 0; j--)
				if (buffer[j] == ',')
				{
					S.Delete(0, j + 1);
					if (buffer[j + 1] == ' ')
						S.Delete(0, 1);
					break;
				}
			Blue.push_back(atoi(S));
		}
	}
	dc.SelectObject(ColorRectangle);
	ColorState.CreateSolidBrush(RGB(Red[lpDrawItemStruct->itemID], Green[lpDrawItemStruct->itemID], Blue[lpDrawItemStruct->itemID]));
	dc.SelectObject(ColorState);
	dc.Rectangle(Rect.left + 2, Rect.top + 2, 30, Rect.bottom - 2);
	dc.TextOut(Rect.left + 35, Rect.top + 2, StateOrder[lpDrawItemStruct->itemID]);
	Color = RGB(Red[lpDrawItemStruct->itemID], Green[lpDrawItemStruct->itemID], Blue[lpDrawItemStruct->itemID]);
	SelectItem = lpDrawItemStruct->itemID;
	dc.DrawText((LPSTR)lpDrawItemStruct->itemData, Rect, DT_LEFT | DT_WORDBREAK);
	dc.Detach();
	DrawItemNumber++;
}

int CSelectStateOrder::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	// TODO: Add your code to determine the sorting order of the specified items

	return 0;
}
