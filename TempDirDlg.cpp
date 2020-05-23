// TempDirDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol.h"
#include "TempDirDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTempDirDlg dialog


CTempDirDlg::CTempDirDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTempDirDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTempDirDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTempDirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTempDirDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTempDirDlg, CDialog)
	//{{AFX_MSG_MAP(CTempDirDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTempDirDlg message handlers


