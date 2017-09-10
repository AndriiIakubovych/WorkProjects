
// GraphOrder.h : главный файл заголовка для приложения GraphOrder
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы
#include "MainFrm.h"


// CGraphOrderApp:
// О реализации данного класса см. GraphOrder.cpp
//

class CGraphOrderApp : public CWinApp
{
public:
	CMultiDocTemplate* pDocTemplate;
	CMainFrame* pMainFrame;
	CWnd* Wnd;

// Переопределение
public:

// Реализация
	DECLARE_MESSAGE_MAP()
};

extern CGraphOrderApp theApp;
