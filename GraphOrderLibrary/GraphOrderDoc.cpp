
// GraphOrderDoc.cpp : ���������� ������ CGraphOrderDoc
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
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


// ��������/����������� CGraphOrderDoc

CGraphOrderDoc::CGraphOrderDoc()
{
	// TODO: �������� ��� ��� ������������ ������ ������������

}

CGraphOrderDoc::~CGraphOrderDoc()
{
}

BOOL CGraphOrderDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)

	return TRUE;
}

#ifdef SHARED_HANDLERS

#endif // SHARED_HANDLERS

// ����������� CGraphOrderDoc

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


// ������� CGraphOrderDoc
