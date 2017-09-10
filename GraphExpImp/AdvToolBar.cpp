// AdvToolBar.cpp : implementation file
//

#include "stdafx.h"
#include "GraphExpImp.h"
#include "AdvToolBar.h"
#include <AfxPriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AdvToolBar

IMPLEMENT_DYNAMIC(CAdvToolBar, CToolBar)

CAdvToolBar::CAdvToolBar() { }

CAdvToolBar::~CAdvToolBar() { }

BEGIN_MESSAGE_MAP(CAdvToolBar, CToolBar)
END_MESSAGE_MAP()

// CAdvToolBar message handlers

bool CAdvToolBar::CreateAdvToolBar(CWnd* pParentWnd, UINT nIDResource, const int nColorType, DWORD dwCtrlStyle, DWORD dwStyle)
{
	ASSERT(pParentWnd);
	ASSERT_VALID_IDR(nIDResource);
	if (!CToolBar::CreateEx(pParentWnd, dwCtrlStyle, dwStyle, CRect(0, 0, 0, 0), nIDResource))
		return false;
	if (!CToolBar::LoadToolBar(nIDResource))
		return false;
	SendMessage(TB_SETEXTENDEDSTYLE, 0, TBSTYLE_EX_DRAWDDARROWS);
	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(nIDResource), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);
	if (!hBitmap)
		return false;
	CBitmap BitmapNormal;
	CBitmap BitmapDisabled;
	if (!BitmapNormal.Attach(hBitmap))
		return false;
	if (!BitmapDisabled.Attach(hBitmap))
		return false;
	ReplaceBackgroundColor(BitmapNormal);
	ReplaceBackgroundColor(BitmapDisabled);
	UINT uImagesListsFlag = 0;
	switch(nColorType)
	{
		case 0:
			uImagesListsFlag |= ILC_COLOR8;
			break;
		case 1:
			uImagesListsFlag |= ILC_COLOR24;
			break;
		default:
			ASSERT(FALSE);
	}
	m_NormalImageList.DeleteImageList();
	if (!m_NormalImageList.Create(32, 32, uImagesListsFlag, 0, 0))
		return false;
	m_DisabledImageList.DeleteImageList();
	if (!m_DisabledImageList.Create(32, 32, uImagesListsFlag, 0, 0))
		return false;
	m_NormalImageList.Add(&BitmapNormal, (CBitmap*)NULL);
	GetToolBarCtrl().SetImageList(&m_NormalImageList);
	GetDisabledBitmap(BitmapDisabled);
	m_DisabledImageList.Add(&BitmapDisabled, (CBitmap*)NULL);
	GetToolBarCtrl().SetDisabledImageList(&m_DisabledImageList);
	SetSizes(CSize(39, 39), CSize(32, 32));
	CString strTitle;
	if (strTitle.LoadString(nIDResource))
		SetWindowText(strTitle);
	
    return true;
}

COLORREF CAdvToolBar::LightenColor(COLORREF color, COLORREF color2)
{
	BYTE r = 0, g = 0, b = 0;
	int avgcol = 0;
	double factor = 0;
	r = GetRValue(color2);
	g = GetGValue(color2);
	b = GetBValue(color2);
	avgcol = (r + g + b) / 3;
	factor = avgcol / 255.0;
	if (factor > 0.0 && factor <= 1.0)
	{
		BYTE red ,green, blue, lightred, lightgreen, lightblue;
		red = GetRValue(color);
		green = GetGValue(color);
		blue = GetBValue(color);
		lightred = (BYTE)((factor * (255 - red)) + red);
		lightgreen = (BYTE)((factor * (255 - green)) + green);
		lightblue = (BYTE)((factor * (255 - blue)) + blue);
		color = RGB(lightred, lightgreen, lightblue);
	}
	return color;
}

void CAdvToolBar::GetDisabledBitmap(CBitmap& Bitmap)
{
	CDC dc;
	COLORREF bgcolor, color, disabledcolor;
	BITMAP BitMap;
	Bitmap.GetBitmap(&BitMap);
	dc.CreateCompatibleDC(NULL);
	CBitmap * pdcOldBmp = dc.SelectObject(&Bitmap);
	CDC dcNew;
	CBrush brush;
	CBitmap BitmapNew;
	dcNew.CreateCompatibleDC(NULL);
	BitmapNew.CreateCompatibleBitmap(&dc, BitMap.bmWidth, BitMap.bmHeight);
	color = GetSysColor(COLOR_3DFACE);
	brush.CreateSolidBrush(color);
	CBitmap * pdcOldBmpNew = dcNew.SelectObject(&BitmapNew);
	CRect rect(0, 0, BitMap.bmWidth, BitMap.bmHeight);
	dcNew.FillRect(rect, &brush);
	bgcolor = dcNew.GetPixel(1, 1);
	brush.DeleteObject();
	dcNew.SelectObject(pdcOldBmpNew);
	disabledcolor = GetSysColor(COLOR_BTNSHADOW);
	for (int i = 0; i < BitMap.bmWidth; i++)
	{
		for(int j = 0; j < BitMap.bmHeight; j++)
		{
			color = dc.GetPixel(i, j);
			if(color != bgcolor)
				dc.SetPixel(i, j, LightenColor(disabledcolor, color));
		}
	}
	dc.SelectObject(pdcOldBmp);
}

void CAdvToolBar::ReplaceBackgroundColor (CBitmap& Bitmap) 
{ 
	CDC dc;
	COLORREF bgcolor, color, NormalColor;
	bgcolor = RGB(192, 192, 192);
	NormalColor = ::GetSysColor(COLOR_BTNFACE);
	BITMAP BitMap;
	Bitmap.GetBitmap(&BitMap);
	dc.CreateCompatibleDC(NULL);
	CBitmap * pdcOldBmp = dc.SelectObject(&Bitmap);
	for (int i = 0; i < BitMap.bmWidth; i++)
	{
		for (int j = 0; j < BitMap.bmHeight; j++)
		{
			color = dc.GetPixel(i, j);
			if(color == bgcolor)
				dc.SetPixel(i, j, NormalColor);
		}
	}
	dc.SelectObject(pdcOldBmp);
}
