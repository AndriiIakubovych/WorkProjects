
// GraphOrderDoc.cpp : реализация класса CGraphOrderDoc
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "GraphOrder.h"
#endif

#include "GraphOrderDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGraphOrderDoc

IMPLEMENT_DYNCREATE(CGraphOrderDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphOrderDoc, CDocument)
END_MESSAGE_MAP()


// создание/уничтожение CGraphOrderDoc

CGraphOrderDoc::CGraphOrderDoc()
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CGraphOrderDoc::~CGraphOrderDoc()
{
}

BOOL CGraphOrderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}

#ifdef SHARED_HANDLERS

#endif // SHARED_HANDLERS

// диагностика CGraphOrderDoc

#ifdef _DEBUG
void CGraphOrderDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphOrderDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// команды CGraphOrderDoc
