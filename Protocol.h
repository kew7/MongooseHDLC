// Protocol.h : main header file for the PROTOCOL application
//

#if !defined(AFX_PROTOCOL_H__13C2F9AD_BE4A_11D5_9EDD_00A0C9C67EC7__INCLUDED_)
#define AFX_PROTOCOL_H__13C2F9AD_BE4A_11D5_9EDD_00A0C9C67EC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "ProtocolDlg.h"


/////////////////////////////////////////////////////////////////////////////
// CProtocolApp:
// See Protocol.cpp for the implementation of this class
//

class CProtocolApp : public CWinApp
{
public:
	CProtocolDlg* dlg;
	CProtocolApp();
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProtocolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CProtocolApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROTOCOL_H__13C2F9AD_BE4A_11D5_9EDD_00A0C9C67EC7__INCLUDED_)
