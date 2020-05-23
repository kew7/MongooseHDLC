#if !defined(AFX_TEMPDIRDLG_H__5EC148C5_CEDC_11D5_AEBD_00A0CCD50301__INCLUDED_)
#define AFX_TEMPDIRDLG_H__5EC148C5_CEDC_11D5_AEBD_00A0CCD50301__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TempDirDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTempDirDlg dialog

class CTempDirDlg : public CDialog
{
// Construction
public:
	CTempDirDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTempDirDlg)
	enum { IDD = IDD_TmpDir };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTempDirDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTempDirDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEMPDIRDLG_H__5EC148C5_CEDC_11D5_AEBD_00A0CCD50301__INCLUDED_)
