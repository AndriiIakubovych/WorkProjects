
// GraphOrderView.h : интерфейс класса CGraphOrderView
//

#pragma once


class CGraphOrderView : public CScrollView
{
protected: // создать только из сериализации
	CGraphOrderView();
	DECLARE_DYNCREATE(CGraphOrderView)

// Атрибуты
public:
	CGraphOrderDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void FindOrderResult();
protected:
	virtual void OnInitialUpdate(); // вызывается в первый раз после конструктора
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CGraphOrderView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnViewEnlarge();
	afx_msg void OnViewReduce();
	afx_msg void OnUpdateViewReduce(CCmdUI* pCmdUI);
	afx_msg void OnViewGeneralSettings();
	afx_msg void OnViewAdditionalSettings();
	afx_msg void OnViewNext();
	afx_msg void OnViewBack();
	afx_msg void OnPopupOpenOrder();
	afx_msg void OnPopupOperationOrder(UINT nID);
	afx_msg void OnPopupRegistrOrder();
	afx_msg void OnPopupSearchOrder(UINT nID);
	afx_msg void OnAppExit();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnOpenAbout();
	afx_msg void OnDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	DECLARE_MESSAGE_MAP()
public:
};

#ifndef _DEBUG  // отладочная версия в GraphOrderView.cpp
inline CGraphOrderDoc* CGraphOrderView::GetDocument() const
   { return reinterpret_cast<CGraphOrderDoc*>(m_pDocument); }
#endif

