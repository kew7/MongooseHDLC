// ProtocolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol.h"
#include "ProtocolDlg.h"
#include "DirOpenDlg.h"
#include "OtborDlg.h"
//#include <D:\My Proects\Visual C++\!!! ПРИМЕРЫ\USB\libpcap-master\pcap\pcap.h>
//#include "afxwin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT

}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtocolDlg dialog

UINT ThreadFunc(void*CCC)
{
 // struct _finddata_t  Info;
  WIN32_FIND_DATA Info;
  CString FileName,strTemp; 
  HANDLE hF;
  UINT k;

  mClass md=(mClass)CCC;
  md->firstFlag=0;
  k=md->m_FirstNumFile;

  while(md->m_ThreadFlag==TRUE)
  {
        Sleep(50);   
	    strTemp.Format("%u",(k++)%1000);
        switch(strTemp.GetLength())
		{
         case 1: {strTemp="00"+strTemp; break;}
         case 2: {strTemp="0"+strTemp;  break;}
		// case 3: {strTemp="00"+strTemp;   break;}
        // case 4: {strTemp="0"+strTemp;    break;}
		}

		//ВНИМАНИЕ!!! Изменено имя выходных файлов !!!!!!! 
		
      FileName=md->m_InDir+"\\"+"demux"+strTemp+".dat";

	  if((hF=::FindFirstFile(FileName,&Info))!=INVALID_HANDLE_VALUE)
	  {
		md->m_InFile=md->m_InDir+"\\"+Info.cFileName;
        if(!md->OnPlay()) {
			k--;
			md->m_ColorSost=RGB(128,32,32);
			md->SetDlgItemText(IDC_SOST,"Ожидание...");
		}
	   else
		  ::DeleteFile(md->m_InFile);  
       if(!FindClose(hF)) exit(0);
	  }
	  else{
		  k--;
		  md->m_ColorSost=RGB(128,32,32);
		  md->SetDlgItemText(IDC_SOST,"Ожидание...");
	  }
  }
 md->CloseThread();
 return 0;
}

CProtocolDlg::CProtocolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProtocolDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProtocolDlg)
	m_Radio = 1;
	m_KData = _T("0 Byte");
	m_DData = _T("100 K");
	m_CheckDelMin = FALSE;
	m_CheckDelMax = FALSE;
	m_FileHDR = _T("");
	m_FileSel = _T("");
	m_FirstNumFile = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProtocolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProtocolDlg)
	DDX_Control(pDX, IDC_EditSpin, m_EditSpin);
	DDX_Control(pDX, IDC_SPIN, m_Spin);
	DDX_Control(pDX, IDC_SLIDER_K, m_SliderK);
	DDX_Control(pDX, IDC_SLIDER_D, m_SliderD);
	DDX_Control(pDX, IDC_PROGRESS2, m_Progress);
	DDX_Control(pDX, IDC_RABOTA, m_Rabota);
	DDX_Radio(pDX, IDC_RADIO1, m_Radio);
	DDX_Text(pDX, IDC_STATIC_KD, m_KData);
	DDX_Text(pDX, IDC_STATIC_DD, m_DData);
	DDX_Check(pDX, IDC_CheckDelMin, m_CheckDelMin);
	DDX_Check(pDX, IDC_CheckDelMax, m_CheckDelMax);
	DDX_Text(pDX, IDC_STATIC_HDR, m_FileHDR);
	DDX_Text(pDX, IDC_STATIC_FileSel, m_FileSel);
	DDX_Text(pDX, IDC_EditFirstNumFile, m_FirstNumFile);
	DDV_MinMaxUInt(pDX, m_FirstNumFile, 0, 99999);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProtocolDlg, CDialog)
	//{{AFX_MSG_MAP(CProtocolDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_IN_DIR, OnInDir)
	ON_COMMAND(ID_IN_FILE, OnInFile)
	ON_COMMAND(ID_OUT_DIR, OnOutDir)
	ON_BN_CLICKED(IDC_RABOTA, OnRabota)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_WM_HSCROLL()
	ON_WM_CTLCOLOR()
	ON_COMMAND(ID_OTBOR, OnOtbor)
	ON_BN_CLICKED(IDC_CheckDelMax, OnCheckDelMax)
	ON_BN_CLICKED(IDC_CheckDelMin, OnCheckDelMin)
	ON_WM_TIMER()
	ON_COMMAND(ID_FileOtbor, OnFileSel)
	ON_COMMAND(ID_NonSelDir, OnNonSelDir)
	ON_COMMAND(ID_SelDir, OnSelDir)
	ON_COMMAND(ID_HDR_FILE, OnHdrFile)
	ON_WM_CLOSE()
	ON_COMMAND(ID_SaveCfg, OnSaveCfg)
	ON_COMMAND(ID_ZagrCfg, OnZagrCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProtocolDlg message handlers

BOOL CProtocolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	GetMenu()->EnableMenuItem(ID_IN_FILE,MF_GRAYED);

	SetDlgItemText(IDC_STATIC_KD,m_KData);
	SetDlgItemText(IDC_STATIC_DD,m_DData);
	m_SliderK.SetRange(0,10000);
	m_SliderD.SetRange(100,10000);

	GetDlgItem(IDC_SLIDER_K)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_D)->EnableWindow(FALSE);

	m_TcpIp.strHDR.Empty();
	m_TcpIp.pBufPORT=new CArray<unsigned short,unsigned short>;
	m_TcpIp.pBufIP_2=new CArray<unsigned short,unsigned short>;
	m_TcpIp.pBufIP_3=new CArray<UINT,UINT>;
	m_TcpIp.pBufIP_4=new CArray<UINT,UINT>;
	m_TcpIp.nCountData=0;
 
	WIN32_FIND_DATA Info;
	if(::FindFirstFile("*.cnf",&Info)!=INVALID_HANDLE_VALUE)
	{
		ZagrCfg(Info.cFileName);
	}
	m_Spin.SetBuddy(&m_EditSpin);
	m_Spin.SetRange(0,100);
	m_Spin.SetPos(4);
	
	SetWindowPos(NULL,0,0,0,0,SWP_SHOWWINDOW|SWP_NOSIZE);
	CenterWindow();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CProtocolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

void CProtocolDlg::OnCancel() 
{
  	// TODO: Add your message handler code here and/or call default
 	SendMessage(WM_SYSCOMMAND,SC_ICON);
 	return;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CProtocolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CProtocolDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CProtocolDlg::OnInDir() 
{
	// TODO: Add your command handler code here
	CDirOpenDialog m_DirDlg;
	if(m_DirDlg.DoModal())
	{
		m_InDir=m_DirDlg.GetPath();
		SetDlgItemText(IDC_STATIC_IN,m_InDir);
	}
	else
	{
      m_InDir="C:\\";
	  SetDlgItemText(IDC_STATIC_IN,m_InDir);
	}

}

void CProtocolDlg::OnInFile() 
{
	// TODO: Add your command handler code here
	CFileDialog dlgOpen(TRUE,0,0,OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,0,this);
	if(IDCANCEL==dlgOpen.DoModal()) return;
	m_InFile=dlgOpen.GetPathName();
}

void CProtocolDlg::OnOutDir() 
{
	// TODO: Add your command handler code here
	CDirOpenDialog m_DirDlg;
	if(m_DirDlg.DoModal())
	{
		m_TcpIp.strTempDir=m_DirDlg.GetPath();
		SetDlgItemText(IDC_STATIC_TEMP,m_TcpIp.strTempDir);
	}
	else 
	{
		m_TcpIp.strTempDir="C:\\";
		SetDlgItemText(IDC_STATIC_TEMP,m_TcpIp.strTempDir);
	}
}

void CProtocolDlg::OnRabota() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_TcpIp.nBegin=m_Spin.GetPos();
	CString strMir="\\Mirage1";
	if(m_Rabota.GetCheck()==1)		// кнопка "Работа" 
	{
		m_TcpIp.nCalcFiles=0;
		m_TcpIp.nCountData=0;
		m_TcpIp.nDirInSel=0;
		m_TcpIp.nDirInNonSel=0;
		m_TcpIp.nFilesInDirNONSEL=0;
		m_TcpIp.nFilesInDirSEL=0;
		m_TcpIp.nData.RemoveAll();
		calcFiles=0;
		m_TcpIp.strSelDir+=strMir;
		CreateDirectory(m_TcpIp.strSelDir,NULL);

		UpdateData(TRUE);

		if(m_Radio==0)				// если обрабатываем один файл
		{
			if(!OnPlay()) return;
		}
		else
		{							// если обрабатываем каталог
			if(!OpenThreadFunc())	
			{
				MessageBox("Не могу открыть поток!!!",NULL,MB_ICONERROR);
				m_ThreadFlag=FALSE;
				m_Rabota.SetCheck(0);
				return;
			}
		}
	}
	else
	{
		m_ThreadFlag=FALSE;
		m_TcpIp.strSelDir=m_TcpIp.strSelDir.Left(m_TcpIp.strSelDir.GetLength()-strMir.GetLength());
		m_Rabota.SetCheck(0);
	 return;
 }
 return;
}

void CProtocolDlg::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	GetMenu()->EnableMenuItem(ID_IN_DIR,MF_GRAYED);
	GetMenu()->EnableMenuItem(ID_IN_FILE,MF_ENABLED);
	GetDlgItem(IDC_STATIC_INT)->EnableWindow(FALSE);

}

void CProtocolDlg::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	GetMenu()->EnableMenuItem(ID_IN_DIR,MF_ENABLED);
	GetDlgItem(IDC_STATIC_INT)->EnableWindow(TRUE);
}

BOOL CProtocolDlg::OpenThreadFunc()
{
	m_ThreadFlag=TRUE;
	if((pThread=AfxBeginThread(ThreadFunc,(void*)this,THREAD_PRIORITY_NORMAL-2,0,0,NULL))==NULL)
		return FALSE;
	else
		return TRUE;
}

bool CProtocolDlg::OnPlay()
{
	CString strTemp;

		if(m_InFile!="")
		{
			if(!m_FileInName.Open(m_InFile, CFile::modeRead | CFile::typeBinary))
			{
				if(m_Radio==0)
				{
				 MessageBox("Такого файла не существует!!!",0,MB_ICONERROR);
				 m_Rabota.SetCheck(0);
				}
    			return FALSE;
			}
			else
			{
             //обработка одного файла
				m_ColorSost=RGB(32,128,32);
                SetDlgItemText(IDC_SOST,"Обработка...");
				BufLoad();
				strTemp.Format("%u",++calcFiles);
				SetDlgItemText(IDC_STATIC_O,strTemp);
				strTemp.Format("%u",m_TcpIp.nCountData);
				SetDlgItemText(IDC_STATIC_C,strTemp);
				m_Progress.SetPos(0);
				return TRUE;
			}
		}
		else
		{
			MessageBox("Выберите входной файл!!!",0,MB_ICONERROR);
			m_Rabota.SetCheck(0);
			return FALSE;
		}
}

void CProtocolDlg::BufLoad()
{
	 UINT nCount;
	 BYTE BufIN[16384]; 
	 m_Progress.SetRange(0,(int)(m_FileInName.GetLength()/1024));
	 while(nCount=m_FileInName.Read(BufIN,sizeof(BufIN))) 
	 {
         FirstFlag(BufIN,nCount);
	 }
	 m_FileInName.Close();
}

void CProtocolDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_KData.Format("%d Byte",m_SliderK.GetPos());
    SetDlgItemText(IDC_STATIC_KD,m_KData);	

	m_DData.Format("%d K",m_SliderD.GetPos());
    SetDlgItemText(IDC_STATIC_DD,m_DData);	
 	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CProtocolDlg::FirstFlag(BYTE*BufIN,int lenb)	// функция снятия протокола HDLC
{  
   int i=0,j=0;
   static BYTE
	      NN,ed_5,sum_ed,
	      flag=0,
		  buf_save[5000],
		  FlagPCAP=1;  
   static UINT l;

   // ==================== блок для PCAP ======================
   //firstFlag = TRUE;		// для режима PCAP
   //flag = 1;				// для режима PCAP
   //m_TcpIp.DePakets(buf_save, lenb);


	//*************** БЛОК для снятия и отслеживания протокола HDLC *********
  // if (!FlagPCAP)
   {
	   if (firstFlag) i = 0;	// если есть синхронизация по флагу HDLC
	   else						// если нет - снимаем протокол HDLC
	   {
		   NN = 0;
		   l = 0;
		   sum_ed = 0;
		   flag = 0;
		   for (i = 0;i < lenb;i++)
		   {
			   for (j = 0;j < 8;j++)
			   {
				   (BufIN[i] & (1 << j)) ? (reg = ((reg >> 1) | 0x80)) : (reg >>= 1);

				   if (reg == 0x7E)
				   {
					   firstFlag = TRUE;
					   for (reg = 0;j < 8;j++)
					   {
						   (BufIN[i] & (1 << j)) ? (reg = (reg >> 1) | 0x80) : (reg >>= 1);
						   if (reg & 0x80) sum_ed++; else sum_ed = 0;
						   ++NN;
					   }
					   i++;
					   break;
				   }
			   }
			   if (firstFlag) break;
		   }
	   }

	   for (;i < lenb;i++)
		   for (j = 0;j < 8;j++)
		   {
			   (BufIN[i] & (1 << j)) ? (reg = (reg >> 1) | 0x80) : (reg >>= 1);

			   if (flag)
			   {
				   reg = 0; flag = 0;

				   if (l > 40)
				   {
					   m_TcpIp.DePakets(buf_save, l);
				   }
				   l = 0; continue;
			   }


			   if (sum_ed == 5)
			   {
				   if (reg & 0x80) { flag = 1; NN = 0; }
				   else reg <<= 1;
				   sum_ed = 0;
				   continue;
			   }

			   if (reg & 0x80) sum_ed++; else sum_ed = 0;
			   ++NN;

			   if (NN == 8)
				   if (!flag)
				   {
					   buf_save[l] = reg;
					   l++;
					   NN = 0;
				   }
		   }
   }
 m_Progress.SetPos(m_FileInName.GetPosition()/1024);	
 return;
}

HBRUSH CProtocolDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
		int TargetControl=pWnd->GetDlgCtrlID();
	switch(TargetControl){
	case IDC_SOST:	    pDC->SetTextColor(m_ColorSost);		    break;
	}	
	
	// TODO: Return a different brush if the default is not desired
	return hbr;
}

void CProtocolDlg::OnOtbor() 
{
	// TODO: Add your command handler code here

	if(m_OtbDlg.DoModal()==IDOK)
	{
      return;
	}
	else
	{
         m_OtbDlg.m_RADIO=3;
	}
	return;
}


void CProtocolDlg::OnCheckDelMax() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_CheckDelMax)
	{
      	GetDlgItem(IDC_SLIDER_D)->EnableWindow(TRUE);
	}
	else
	{
      GetDlgItem(IDC_SLIDER_D)->EnableWindow(FALSE);
	  m_SliderD.SetPos(100);
      SetDlgItemText(IDC_STATIC_DD,"100 K");	
	}
	return;

}

void CProtocolDlg::OnCheckDelMin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_CheckDelMin)
	{
      	GetDlgItem(IDC_SLIDER_K)->EnableWindow(TRUE);
		
	}
	else
	{
      GetDlgItem(IDC_SLIDER_K)->EnableWindow(FALSE);
	  m_SliderK.SetPos(0);
      SetDlgItemText(IDC_STATIC_KD,"0 Byte");	
	}
	return;
}

void CProtocolDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	m_TcpIp.FormatData(nIDEvent);
	CDialog::OnTimer(nIDEvent);
}


     // для загрузки IP-адресов используется три массива, в первом содержатся  
     //  2-х байтные IP-адреса, во втором - 3-х байтные IP-адреса , в третьем - 
     //  полные IP-адреса  (МАКСИМАЛЬНОЕ КОЛИЧЕСТВО АДРЕСОВ = 32768)
       
BOOL CProtocolDlg::ZagrOtbor()
{
  CStdioFile m_FOtbor;
  CString Str;
  UINT FindFlag=0,i,NewElem=0;
 
  // Обнуляем массивы перед загрузкой

  m_TcpIp.pBufPORT->RemoveAll();
  m_TcpIp.pBufIP_2->RemoveAll();
  m_TcpIp.pBufIP_3->RemoveAll();
  m_TcpIp.pBufIP_4->RemoveAll();

  if(m_FileSel!="")
  {
	  if(!m_FOtbor.Open(m_FileSel,CFile::modeReadWrite))
	  {
	    MessageBox("Hе могу найти файл отбора - "+m_FileSel,NULL,MB_ICONERROR);
	    m_FileSel.Empty();
	    return FALSE;
	  }
  }
  else return FALSE;
  
  while(m_FOtbor.ReadString(Str))
  {
	  if((FindFlag=Str.Find("порт"))!=-1) break;  //находим строку "//порт"
  }

  if(FindFlag==-1) 
  {
	  delete m_TcpIp.pBufPORT;
	  MessageBox("Hеправильный формат файла отбора - "+m_FileSel,NULL,MB_ICONERROR);
	  return FALSE;
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // ~~~~~~~~~~~~~~~~~~~~~Загружаем TCP-порты в  массив~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  m_TcpIp.pBufPORT->SetSize(65536);
  for(i=0;i<65536;i++)           // обнуляем массив 
  {
	  m_TcpIp.pBufPORT->SetAt(i,0);
  }

  while(m_FOtbor.ReadString(Str)) // считываем строки из файла
  {
    Str.TrimLeft();    
	Str.TrimRight();              // удаляем пробелы в начале и конце строки
  
    NewElem=(UINT)atoi(Str);
    m_TcpIp.pBufPORT->SetAt(NewElem,(unsigned short) NewElem);      
	if(Str=="//адрес") break;
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Конец загрузки~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //////////////////////////////////////////////////////////////////////////////////////////

  
  m_FOtbor.SeekToBegin();         // на  начало файла

  while(m_FOtbor.ReadString(Str))
  {
	  if((FindFlag=Str.Find("адрес"))!=-1) break;  //находим строку "//адрес"
  }

  if(FindFlag==-1) 
  {
	  delete m_TcpIp.pBufIP_2;
	  delete m_TcpIp.pBufIP_3;
	  delete m_TcpIp.pBufIP_4;
	  MessageBox("Hеправильный формат файла отбора - "+m_FileSel,NULL,MB_ICONERROR);
	  return FALSE;
  }

  //////////////////////////////////////////////////////////////////////////////////////
  // ~~~~~~~~~~~~~~~~~~~~~Загружаем IP-адреса в соответствующие массивы~~~~~~~~~~~~~~~~~

  m_TcpIp.pBufIP_2->SetSize(65536);
  for(i=0;i<65536;i++)           // обнуляем массив для 2-х байтных адресов
  {
	  m_TcpIp.pBufIP_2->SetAt(i,0);
  }

  while(m_FOtbor.ReadString(Str)) // считываем строки из файла
  {
    Str.TrimLeft();    
	Str.TrimRight();              // удаляем пробелы в начале и конце строки

	// если длина строки соответствует 2-х байтному адресу
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if(Str.GetLength()==7) 
	{
      NewElem=0;
      if(Str.Find('.')!=3) return FALSE;
	  for(i=0;i<2;i++)
	  {
		  NewElem=(NewElem<<8)|((UINT)atoi(Str.Mid(4*i,3)));
	  }
      m_TcpIp.pBufIP_2->SetAt(NewElem,(unsigned short) NewElem);      
	}
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	// если длина строки соответствует 3-х байтному адресу
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    else
	 if(Str.GetLength()==11) 
	 {
      NewElem=0; 
      if(Str.Find('.')!=3) return FALSE;
	  for(i=0;i<3;i++)
	  {
		  NewElem=(NewElem<<8)|((UINT)atoi(Str.Mid(4*i,3)));
	  }
      m_TcpIp.pBufIP_3->Add(NewElem);      
	 }
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

     // если длина строки соответствует 4-х байтному адресу
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 else
	  if(Str.GetLength()==15) 
	  {
       NewElem=0; 
       if(Str.Find('.')!=3) return FALSE;
	   for(i=0;i<4;i++)
	   {
		  NewElem=(NewElem<<8)|((UINT)atoi(Str.Mid(4*i,3)));
	   }
       m_TcpIp.pBufIP_4->Add(NewElem);      
	  }
     //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  }

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Конец загрузки~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //////////////////////////////////////////////////////////////////////////////////////////

  
  // После того как массивы сформированы, необходимо их рассортировать в порядке возрастания
  //~~~~~~~~~~~~~~~~~~~~~ (кроме pBufIP_2, так как он уже отсортирован) ~~~~~~~~~~~~~~~~~~~~
  //               Это существенно облегчит поиск IP-адреса в массивах отбора 

  int nSizeArrayIP_3,    // переменные для определения размерности массивов pBufIP_3 и pBufIP_4
	   nSizeArrayIP_4;

  nSizeArrayIP_3=m_TcpIp.pBufIP_3->GetSize();
  nSizeArrayIP_4=m_TcpIp.pBufIP_4->GetSize();    // определяем размеры массивов

  //~~~~~~~~~~~~~~~~~~~~~~~сортируем массив pBufIP_3~~~~~~~~~~~~~~~~~~~~~~
  if(nSizeArrayIP_3!=0) QuickSort(m_TcpIp.pBufIP_3,0,nSizeArrayIP_3-1);
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  //~~~~~~~~~~~~~~~~~~~~~~~сортируем массив pBufIP_4~~~~~~~~~~~~~~~~~~~~~~
  if(nSizeArrayIP_4!=0) QuickSort(m_TcpIp.pBufIP_4,0,nSizeArrayIP_4-1);
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
  m_FOtbor.Close();

return TRUE;
}

void CProtocolDlg::OnFileSel() 
{
	// TODO: Add your command handler code here
	CFileDialog dlgFile(TRUE,NULL,NULL,OFN_HIDEREADONLY,
		                "Файл отбора(*.slc)|*.slc|Все файлы(*.*)|*.*||",NULL) ;
	if(dlgFile.DoModal()==IDOK)
	{
      m_FileSel=dlgFile.GetPathName();
	  ZagrOtbor();                // загружаем признаки
	  UpdateData(FALSE);
	}
	else
	{
		m_FileSel="";
		UpdateData(FALSE);
	}
	
}

   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   // Особенностью использования данной функции является применение рекурсии

void CProtocolDlg::QuickSort(CArray<UINT,UINT>*A,int iLo,int iHi)
{
    int Lo,
		Hi;

	UINT
		 Mid,
		 T;

	div_t divResult;

    Lo = iLo;
    Hi = iHi;
	divResult=div(Lo + Hi,2);
    Mid = A->GetAt(divResult.quot); // элемент в середине массива

   do
	{
      while ((A->GetAt(Lo)) < Mid) Lo++;
      while ((A->GetAt(Hi)) > Mid) Hi--;
      if(Lo <= Hi)
      {
      
        T = A->GetAt(Lo);
		A->SetAt(Lo,A->GetAt(Hi));
		A->SetAt(Hi,T);
        Lo++;
        Hi--;
	  }   
	}
   while(Lo <= Hi);

    if(Hi > iLo) QuickSort(A, iLo, Hi);
    if(Lo < iHi) QuickSort(A, Lo, iHi);

return;  
}



void CProtocolDlg::OnNonSelDir() 
{
	// TODO: Add your command handler code here
	CDirOpenDialog m_DirDlg;
	if(m_DirDlg.DoModal())
	{
		m_TcpIp.strNonSelDir=m_DirDlg.GetPath();
		SetDlgItemText(IDC_STATIC_NONSEL,m_TcpIp.strNonSelDir);

	}
	else
	{
      m_TcpIp.strNonSelDir="C:\\";
	  SetDlgItemText(IDC_STATIC_NONSEL,m_TcpIp.strNonSelDir);
	}
	
}

void CProtocolDlg::OnSelDir() 
{
	// TODO: Add your command handler code here
	CDirOpenDialog m_DirDlg;
	if(m_DirDlg.DoModal())
	{
		m_TcpIp.strSelDir=m_DirDlg.GetPath();
		SetDlgItemText(IDC_STATIC_SEL,m_TcpIp.strSelDir);

	}
	else
	{
      m_TcpIp.strSelDir="C:\\";
	  SetDlgItemText(IDC_STATIC_SEL,m_TcpIp.strSelDir);
	}
}


void CProtocolDlg::OnHdrFile() // Функция считывает формат заголовка для приемных файлов
{
	// TODO: Add your command handler code here
	CFileDialog dlgFile(TRUE,NULL,NULL,OFN_HIDEREADONLY,
		                "Файл заголовка(*.hdr)|*.hdr|Все файлы(*.*)|*.*||",NULL) ;


	if(dlgFile.DoModal()==IDOK)
	{
      m_FileHDR=dlgFile.GetPathName();
	  ZagrHDR();
	  UpdateData(FALSE);
	}
	else
	{
			  m_TcpIp.strHDR.Empty();
			  m_FileHDR="";
			  UpdateData(FALSE);
	}
	return;
}

void CProtocolDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	::TerminateThread(pThread,0);
      CloseThread();
      delete m_TcpIp.pBufPORT;
      delete m_TcpIp.pBufIP_2;
      delete m_TcpIp.pBufIP_3;
      delete m_TcpIp.pBufIP_4;
 CDialog::OnCancel();
}

void CProtocolDlg::OnSaveCfg() 
{
	// TODO: Add your command handler code here
	CFileDialog dlgFile(FALSE,"cnf",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		                "Файл конфигурации (*.cnf)|*.cnf|Все файлы(*.*)|*.*||",NULL) ;
	if(dlgFile.DoModal()==IDOK)
	{
     SaveCfg(dlgFile.GetPathName());	  
	}
return;	
}

void CProtocolDlg::OnZagrCfg() 
{
	// TODO: Add your command handler code here
	CFileDialog dlgFile(TRUE,NULL,NULL,OFN_HIDEREADONLY,
		                "Файл конфигурации (*.cnf)|*.cnf|Все файлы(*.*)|*.*||",NULL) ;

	CStdioFile f;

	if(dlgFile.DoModal()==IDOK)
	{
		ZagrCfg(dlgFile.GetPathName());
	}
}

void CProtocolDlg::ZagrCfg(CString FileName)
{

	CStdioFile f;
	CString Str,sTemp;
	char CurDir[200];
	int Index;

	GetCurrentDirectory(200,CurDir);

		if(!f.Open(FileName,CFile::modeRead))
		{
			MessageBox("Не могу открыть файл конфигурации",0,MB_ICONERROR);
			return;
		}

		while(f.ReadString(Str))
		{
          if((Index=Str.Find(':'))==-1) {
				MessageBox("Неправильный формат файла конфигурации",0,MB_ICONERROR);
				return;
			}
            sTemp=Str.Mid(0,Str.Find(':'));
			sTemp.TrimLeft();
			sTemp.TrimRight();

			if(sTemp=="InpDirName")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
              m_InDir=sTemp;
			  SetDlgItemText(IDC_STATIC_IN,m_InDir);
			  if(!SetCurrentDirectory(m_InDir))
			  {
				 MessageBox("Не могу найти входную директорию - "+m_InDir,0,MB_ICONERROR);
			  }
			}
			else 
			if(sTemp=="TempDirName")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
              m_TcpIp.strTempDir=sTemp;
			  SetDlgItemText(IDC_STATIC_TEMP,m_TcpIp.strTempDir);
			  if(!SetCurrentDirectory(m_TcpIp.strTempDir))
			  {
				 MessageBox("Не могу найти рабочий каталог - "+m_TcpIp.strTempDir,0,MB_ICONERROR);
			  }
			}
			else
            if(sTemp=="SelectDirName")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
              m_TcpIp.strSelDir=sTemp;
			  SetDlgItemText(IDC_STATIC_SEL,m_TcpIp.strSelDir);
			  if(!SetCurrentDirectory(m_TcpIp.strSelDir))
			  {
				 MessageBox("Не могу найти каталог отбора - "+m_TcpIp.strSelDir,0,MB_ICONERROR);
			  }
			}
            else
            if(sTemp=="UnselDirName")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
              m_TcpIp.strNonSelDir=sTemp;
			  SetDlgItemText(IDC_STATIC_NONSEL,m_TcpIp.strNonSelDir);
			  if(!SetCurrentDirectory(m_TcpIp.strNonSelDir))
			  {
				 MessageBox("Не могу найти каталог неотбора - "+m_TcpIp.strNonSelDir,0,MB_ICONERROR);
			  }
			}
			else
            if(sTemp=="Select")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
              m_OtbDlg.m_RADIO=atoi(sTemp);
			}
			else
            if(sTemp=="HeaderFile")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
              m_FileHDR=sTemp;
			  ZagrHDR();
			}
			else
            if(sTemp=="SelectFile")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
              m_FileSel=sTemp;
			  ZagrOtbor();
			}
			else
            if(sTemp=="MinLen")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
			  if(atoi(sTemp)!=0)
			  {
               m_CheckDelMin=TRUE;
			   m_SliderK.SetPos(atoi(sTemp)); 
			   m_KData.Format("%d Byte",m_SliderK.GetPos());
               SetDlgItemText(IDC_STATIC_KD,m_KData);	
			   GetDlgItem(IDC_SLIDER_K)->EnableWindow(TRUE);
			  }
			}
			else
            if(sTemp=="MaxLen")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
              if(atoi(sTemp)!=0)
			  {
			   m_CheckDelMax=TRUE;
               m_SliderD.SetPos(atoi(sTemp)) ;
	           m_DData.Format("%d K",m_SliderD.GetPos());
               SetDlgItemText(IDC_STATIC_DD,m_DData);	
			   GetDlgItem(IDC_SLIDER_D)->EnableWindow(TRUE);
			  }
			}
			if(sTemp=="Flag_SaveNonSel")
			{
			  sTemp=Str.Mid(Index+1,Str.GetLength()-Str.Find(':'));
			  sTemp.TrimLeft();
			  sTemp.TrimRight();
              m_OtbDlg.m_NonSave=atoi(sTemp);
			}

		}

  UpdateData(FALSE);
  SetCurrentDirectory(CurDir);
  f.Close();
 return;
}

BOOL CProtocolDlg::ZagrHDR()
{
		CString Str,sTemp;
		UINT nCount=0,Index;
		int nPos;
		CStdioFile f;

		m_TcpIp.strHDR.Empty();

		if(!f.Open(m_FileHDR,CFile::modeRead))
		{
          sTemp="Не могу открыть файл заголовка - "+m_FileHDR;
          MessageBox(sTemp,0,MB_ICONERROR);
		  m_FileHDR.Empty();
          return FALSE;
		}

		while(f.ReadString(Str))
		{
			if((Index=Str.Find('-'))==-1) {
				MessageBox("Неправильный формат файла заголовка",0,MB_ICONERROR);
				OnRabota();
				return FALSE;
			}
            sTemp=Str.Mid(Index+1,Str.Find(':')-Index);
			sTemp.TrimLeft();
			sTemp.TrimRight();
		 
		if(sTemp=="DPR:") 
			m_TcpIp.nIndexHDR[0]=nCount;
		else
        if(sTemp=="TPR:")
			m_TcpIp.nIndexHDR[1]=nCount;
		else
		if(sTemp=="FAD:")
			m_TcpIp.nIndexHDR[2]=nCount;
		else
        if(sTemp=="FPT:")
			m_TcpIp.nIndexHDR[3]=nCount;
		else
		if(sTemp=="TAD:")
			m_TcpIp.nIndexHDR[4]=nCount;
		else
		if(sTemp=="TPT:")
			m_TcpIp.nIndexHDR[5]=nCount;

		    nPos=atoi(Str);
            nCount+=nPos;
			Index=Str.Find(':');
			
            sTemp=Str.Mid(Index+1);
		    sTemp=Str.Mid(Index+1,sTemp.Find(' '));
		    if(nPos>sTemp.GetLength())
		     while(atoi(Str)>sTemp.GetLength()) sTemp+=" ";
			  m_TcpIp.strHDR+=sTemp;
		}
f.Close();
return TRUE;
}

void CProtocolDlg::SaveCfg(CString FileName)
{

 CFile f;
 CString sTemp,d;

 f.Open(FileName,CFile::modeCreate|CFile::modeWrite);

  sTemp="InpDirName:"+m_InDir+"\r\n";
  f.Write(sTemp,sTemp.GetLength());

  sTemp="TempDirName:"+m_TcpIp.strTempDir+"\r\n";
  f.Write(sTemp,sTemp.GetLength());

  sTemp="SelectDirName:"+m_TcpIp.strSelDir+"\r\n";  
  f.Write(sTemp,sTemp.GetLength());

  sTemp="UnselDirName:"+m_TcpIp.strNonSelDir+"\r\n";  
  f.Write(sTemp,sTemp.GetLength());

  sTemp="HeaderFile:"+m_FileHDR+"\r\n";  
  f.Write(sTemp,sTemp.GetLength());

  sTemp="SelectFile:"+m_FileSel+"\r\n";  
  f.Write(sTemp,sTemp.GetLength());

  d.Format("%d",m_OtbDlg.m_RADIO);
  sTemp="Select:"+d+"\r\n";  
  f.Write(sTemp,sTemp.GetLength());

  d.Empty();
  if(m_CheckDelMin==TRUE)  d.Format("%d",m_SliderK.GetPos());
  sTemp="MinLen:"+d+"\r\n";  
  f.Write(sTemp,sTemp.GetLength());

  d.Empty();
  if(m_CheckDelMax==TRUE) d.Format("%d",m_SliderD.GetPos());
  sTemp="MaxLen:"+d+"\r\n";  
  f.Write(sTemp,sTemp.GetLength());

  d.Format("%d",m_OtbDlg.m_NonSave);
  sTemp="Flag_SaveNonSel:"+d+"\r\n";  
  f.Write(sTemp,sTemp.GetLength()); 
  f.Close();
}

void CProtocolDlg::CloseThread()
{
 CTempDirDlg *m_TempDlg;
  
 m_TempDlg=new CTempDirDlg;
 m_TempDlg->Create(IDD_TmpDir);

 m_TempDlg->m_Progress.SetRange(0,m_TcpIp.nCountData/50);
 
 for(int i=0;i<m_TcpIp.nCountData;i++) 
 {
   CloseHandle(m_TcpIp.nData.GetAt(i).h_File);
   DeleteFile(m_TcpIp.nData.GetAt(i).dFile);
   if(i%50==0) m_TempDlg->m_Progress.SetPos(i/50);
 }
 m_TempDlg->EndDialog(0);
 m_TempDlg->DestroyWindow();
 delete[] m_TempDlg;
return;
}

