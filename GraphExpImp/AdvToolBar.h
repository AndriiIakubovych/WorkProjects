#pragma once

#ifndef ADVTOOLBAR_H
#define ADVTOOLBAR_H

class CAdvToolBar : public CToolBar
{
	DECLARE_DYNAMIC(CAdvToolBar)

public:
	enum { ADVT_COLOR_256 = 0, ADVT_COLOR_TRUE };
	CAdvToolBar();
	virtual ~CAdvToolBar();
	bool CreateAdvToolBar(CWnd* pParentWnd, UINT nIDResource, const int nColorType = CAdvToolBar::ADVT_COLOR_256, DWORD dwCtrlStyle = TBSTYLE_FLAT, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP);
	CImageList* GetNormalImageList()
	{
		return reinterpret_cast<CImageList*>(&m_NormalImageList);
	}
	CImageList* DisabledImageList()
	{
		return reinterpret_cast<CImageList*>(&m_DisabledImageList);
	}

private:
	COLORREF LightenColor(COLORREF color, COLORREF color2);
	void GetDisabledBitmap(CBitmap &Bitmap);
	void ReplaceBackgroundColor(CBitmap& Bitmap);
	CImageList m_NormalImageList;
	CImageList m_DisabledImageList;
	DECLARE_MESSAGE_MAP()
};

#endif
