// ProtocolDlg.h : header file
//

#if !defined(AFX_PROTOCOLDLG_H__13C2F9AF_BE4A_11D5_9EDD_00A0C9C67EC7__INCLUDED_)
#define AFX_PROTOCOLDLG_H__13C2F9AF_BE4A_11D5_9EDD_00A0C9C67EC7__INCLUDED_

#include "TCP_IP.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OtborDlg.h"
#include "TempDirDlg.h"	// Added by ClassView

/////////////////////////////////////////////////////////////////////////////
// CProtocolDlg dialog

class CProtocolDlg : public CDialog
{
// Construction
public:
	void CloseThread();
	void SaveCfg(CString);
	void ZagrCfg(CString);
	BOOL ZagrHDR();
	BOOL ZagrOtbor();
	void QuickSort(CArray<UINT,UINT>*,int,int);
	COLORREF m_ColorSost;
	CTCP_IP m_TcpIp;
	void BufLoad();
	bool OnPlay();
	BOOL m_ThreadFlag;
	CWinThread* pThread;
	BOOL OpenThreadFunc();
	CString m_InDir,
			m_InFile,
			m_OutFile;

	CFile   m_FileInName,
			m_FileOutName;
			
	BOOL firstFlag;
    BYTE reg;
	COtborDlg m_OtbDlg;
	void  FirstFlag(BYTE*,int);
	CProtocolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProtocolDlg)
	enum { IDD = IDD_PROTOCOL_DIALOG };
	CEdit	m_EditSpin;
	CSpinButtonCtrl	m_Spin;
	CSliderCtrl	m_SliderK;
	CSliderCtrl	m_SliderD;
	CProgressCtrl	m_Progress;
	CButton	m_Rabota;
	int		m_Radio;
	CString	m_KData;
	CString	m_DData;
	BOOL	m_CheckDelMin;
	BOOL	m_CheckDelMax;
	CString	m_FileHDR;
	CString	m_FileSel;
	UINT	m_FirstNumFile;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtocolDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL


// Implementation
protected:
	HICON m_hIcon;
	UINT calcFiles;

	// Generated message map functions
	//{{AFX_MSG(CProtocolDlg)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInDir();
	afx_msg void OnInFile();
	afx_msg void OnOutDir();
	afx_msg void OnRabota();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnOtbor();
	afx_msg void OnCheckDelMax();
	afx_msg void OnCheckDelMin();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFileSel();
	afx_msg void OnNonSelDir();
	afx_msg void OnSelDir();
	afx_msg void OnHdrFile();
	afx_msg void OnClose();
	afx_msg void OnSaveCfg();
	afx_msg void OnZagrCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEditspin();
};

typedef CProtocolDlg*mClass;
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOLDLG_H__13C2F9AF_BE4A_11D5_9EDD_00A0C9C67EC7__INCLUDED_)
