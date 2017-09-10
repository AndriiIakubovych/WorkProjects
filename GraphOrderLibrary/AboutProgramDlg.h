#pragma once


// AboutProgramDlg dialog

class AboutProgramDlg : public CDialog
{
	DECLARE_DYNAMIC(AboutProgramDlg)

public:
	AboutProgramDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AboutProgramDlg();

// Dialog Data
	enum { IDD = IDD_ABOUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
