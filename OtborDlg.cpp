// OtborDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol.h"
#include "OtborDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COtborDlg dialog


COtborDlg::COtborDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COtborDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COtborDlg)
	m_RADIO = 3;
	m_NonSave = FALSE;
	//}}AFX_DATA_INIT
}


void COtborDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COtborDlg)
	DDX_Radio(pDX, IDC_RADIO_IP, m_RADIO);
	DDX_Check(pDX, IDC_SaveNonSel, m_NonSave);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COtborDlg, CDialog)
	//{{AFX_MSG_MAP(COtborDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COtborDlg message handlers




