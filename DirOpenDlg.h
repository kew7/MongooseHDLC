#if !defined(AFX_DIROPENDIALOG_H__C8A12872_EBE3_11D1_BAB6_9053A1D6CE2A__INCLUDED_)
#define AFX_DIROPENDIALOG_H__C8A12872_EBE3_11D1_BAB6_9053A1D6CE2A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DirOpenDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDirOpenDialog dialog

class CDirOpenDialog : public CDialog
{
// Construction
public:
	CString GetPath();
	CDirOpenDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
protected:
	CImageList m_ImageList;
	TV_INSERTSTRUCT tvinsert;
	CString Path;
	//{{AFX_DATA(CDirOpenDialog)
	enum { IDD = IDD_DIrOpenDialog };
	CTreeCtrl*	pFolderTree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDirOpenDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDirOpenDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemexpandingTreeDir(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangedTreeDir(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIROPENDIALOG_H__C8A12872_EBE3_11D1_BAB6_9053A1D6CE2A__INCLUDED_)
