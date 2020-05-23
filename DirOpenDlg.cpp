// DirOpenDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Protocol.h"
#include "DirOpenDlg.h"
#include <io.h>
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirOpenDialog dialog


CDirOpenDialog::CDirOpenDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CDirOpenDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDirOpenDialog)
	//}}AFX_DATA_INIT
}


void CDirOpenDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirOpenDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDirOpenDialog, CDialog)
	//{{AFX_MSG_MAP(CDirOpenDialog)
	ON_NOTIFY(TVN_ITEMEXPANDING, IDC_TreeDir, OnItemexpandingTreeDir)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TreeDir, OnSelchangedTreeDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirOpenDialog message handlers

BOOL CDirOpenDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	long lFindHandle; //для findfirst
	char s[256];
	int DirPresentFlag=0;
	HTREEITEM hTreeItem;
//~~~~~~~~~~~~~~~~  Инициализация Tree ~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//~~~~~~~~~~~~~~~ Инициализация списка изображений ~~~~~
	HICON hIcon[8];
	m_ImageList.Create(16,16,0,0,10);
	hIcon[0]=AfxGetApp()->LoadIcon(IDI_IconFloppy);
	hIcon[1]=AfxGetApp()->LoadIcon(IDI_IconHardDrive);
	hIcon[2]=AfxGetApp()->LoadIcon(IDI_IconCDDrive);
	hIcon[3]=AfxGetApp()->LoadIcon(IDI_IconRemoteDisk);
	hIcon[4]=AfxGetApp()->LoadIcon(IDI_IconRamDisk);
	hIcon[5]=AfxGetApp()->LoadIcon(IDI_IconBadDisk);
	hIcon[6]=AfxGetApp()->LoadIcon(IDI_IconClosFolder);
	hIcon[7]=AfxGetApp()->LoadIcon(IDI_IconExpFolder);
	for (int i=0;i<8;i++) m_ImageList.Add(hIcon[i]);
		//~~~~~~~~~~~~~~~ Системная информация о доступных томах
	DWORD dwSizeOfDrvStr;
	HANDLE hHeap;
	LPTSTR pszAllDrives,pszDrive;
 	dwSizeOfDrvStr=GetLogicalDriveStrings(0,NULL)*sizeof(TCHAR);
	hHeap=GetProcessHeap();
	pszAllDrives=(LPTSTR)HeapAlloc(hHeap,HEAP_ZERO_MEMORY,dwSizeOfDrvStr);
	GetLogicalDriveStrings(dwSizeOfDrvStr/sizeof(TCHAR),pszAllDrives);
	pszDrive=pszAllDrives;        
	    //~~~~~~~~~~~~~~~ Заполним дерево ~~~~~~~~~~~~~~~~~~~~
	pFolderTree=(CTreeCtrl*)GetDlgItem(IDC_TreeDir);
	pFolderTree->SetImageList(&m_ImageList,TVSIL_NORMAL);
	struct _finddata_t FindStructure; FindStructure.attrib=_A_SUBDIR; 

	tvinsert.hInsertAfter=TVI_LAST;// Общие инициализации
	tvinsert.item.mask=TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT;
	tvinsert.item.hItem=NULL;
	tvinsert.item.state=0;
	tvinsert.item.stateMask=0;
	tvinsert.item.cchTextMax=6;
	tvinsert.item.cChildren=0;
	tvinsert.item.lParam=0;
	while(pszDrive[0]!=0){// Вложенные циклы для ветвей дерева
		tvinsert.item.pszText=pszDrive;
		tvinsert.hParent=NULL;
		switch (GetDriveType(pszDrive)){
		case DRIVE_REMOVABLE  : tvinsert.item.iImage=0;	
								tvinsert.item.iSelectedImage=0;	break;
		case DRIVE_FIXED      : tvinsert.item.iImage=1;
			                    tvinsert.item.iSelectedImage=1;	break;
		case DRIVE_CDROM      : tvinsert.item.iImage=2;
								tvinsert.item.iSelectedImage=2;	break;
		case DRIVE_REMOTE     : tvinsert.item.iImage=3;
								tvinsert.item.iSelectedImage=3;	break;
		case DRIVE_RAMDISK    : tvinsert.item.iImage=4;
								tvinsert.item.iSelectedImage=4;	break;
		case DRIVE_UNKNOWN    : tvinsert.item.iImage=5;
								tvinsert.item.iSelectedImage=5;	break;
		case DRIVE_NO_ROOT_DIR: tvinsert.item.iImage=5;
								tvinsert.item.iSelectedImage=5;	break;
		}
		hTreeItem=pFolderTree->InsertItem(&tvinsert);
		sprintf(s,"%s\\*",pszDrive);
		lFindHandle=_findfirst(s,&FindStructure);
		if (lFindHandle!=-1){
			do{if ((FindStructure.attrib&0x10) &&
				   (strcmp(FindStructure.name,"."))&&
				   (strcmp(FindStructure.name,".."))){DirPresentFlag=1;break;}// Если директория
			}while(_findnext(lFindHandle,&FindStructure) == 0);
			if (DirPresentFlag){
				tvinsert.hParent=hTreeItem;
				tvinsert.item.iImage=6;	
				tvinsert.item.iSelectedImage=6;
				tvinsert.item.pszText=FindStructure.name;
				pFolderTree->InsertItem(&tvinsert);
				DirPresentFlag=0;
			}
		}
		_findclose(lFindHandle);
		pszDrive=_tcschr(pszDrive,0)+1;
	}
	HeapFree(hHeap,0,pszAllDrives);
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDirOpenDialog::OnItemexpandingTreeDir(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	CString m_FullPath,m_TmpStr,m_TmpStr1;
 	m_FullPath.Empty();
	HTREEITEM hItem;
	long lFindHandle,lFindHandle1;
	int ImageIndex,DirPresentFlag=0;
	struct _finddata_t FindStructure; FindStructure.attrib=_A_SUBDIR; 
	struct _finddata_t FindStructure1; FindStructure1.attrib=_A_SUBDIR; 
   if (pNMTreeView->action==TVE_EXPAND){
	   //~~~~~~~~~ Перегрузим иконку на раскрытую директорию ~~~~~~~~~~~~~~~~
		pFolderTree->GetItemImage(pNMTreeView->itemNew.hItem,ImageIndex,ImageIndex);
		if (ImageIndex==6)  pFolderTree->SetItemImage(pNMTreeView->itemNew.hItem,7,7);
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~`
		tvinsert.hParent=pNMTreeView->itemNew.hItem;
		tvinsert.item.iImage=6;	
		tvinsert.item.iSelectedImage=6;
		pFolderTree->DeleteItem(pFolderTree->GetChildItem(pNMTreeView->itemNew.hItem));
		hItem=pNMTreeView->itemNew.hItem;
		do { // ~~~~~~~~~~~~~~~~~~~~~ Вернули путь ~~~~~~~~~~~~~~~~~
			m_TmpStr=(pFolderTree->GetItemText(hItem)+"\\");
			m_TmpStr.MakeReverse();
			m_FullPath+=m_TmpStr;
			hItem=pFolderTree->GetParentItem(hItem);
		}while(hItem!=NULL);
		m_FullPath.MakeReverse();
		m_TmpStr=m_FullPath;
		m_FullPath+="*";//~~~~~~~~~~~ Заполнить ветвь ~~~~~~~~~~~~~~~~~~~~~~~
		lFindHandle=_findfirst((m_FullPath),&FindStructure);
		if (lFindHandle!=-1)// Если не вынули дискету из накопителя
		do{
			if (FindStructure.attrib&0x10)// Если директория
			if ((strcmp(FindStructure.name,"."))&&(strcmp(FindStructure.name,".."))){
				tvinsert.item.pszText=FindStructure.name;
				// Вставим или нет узел с плюсиком
				tvinsert.hParent=pFolderTree->InsertItem(&tvinsert);

				m_TmpStr1=m_TmpStr+FindStructure.name+"\\*";
				lFindHandle1=_findfirst(m_TmpStr1,&FindStructure1);
				if (lFindHandle1!=-1){
					do{if ((FindStructure1.attrib&0x10)&&
						   (strcmp(FindStructure1.name,"."))&&
						   (strcmp(FindStructure1.name,".."))){DirPresentFlag=1;break;}// Если директория
					}while(_findnext(lFindHandle1,&FindStructure1) == 0);
					if (DirPresentFlag){
						tvinsert.item.iImage=6;	
						tvinsert.item.iSelectedImage=6;
						tvinsert.item.pszText=FindStructure1.name;
						pFolderTree->InsertItem(&tvinsert);
						DirPresentFlag=0;
					}
				}
				_findclose(lFindHandle1);
				tvinsert.hParent=pNMTreeView->itemNew.hItem;
			}
		}while(_findnext(lFindHandle,&FindStructure) == 0);
		_findclose(lFindHandle);//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
   if (pNMTreeView->action==TVE_COLLAPSE){
	   //~~~~~~~~~ Перегрузим иконку на закрытую директорию ~~~~~~~~~~~~~~~~
		pFolderTree->GetItemImage(pNMTreeView->itemNew.hItem,ImageIndex,ImageIndex);
		if (ImageIndex==7) 	pFolderTree->SetItemImage(pNMTreeView->itemNew.hItem,6,6);
		//~~~~~~~~~~~~~~~~~ Удалим все элементы ветви кроме одного ~~~~~~~~~~~~~
		while((hItem=pFolderTree->GetChildItem(pNMTreeView->itemNew.hItem))!=NULL){
			pFolderTree->DeleteItem(hItem);
		}
		tvinsert.hParent=pNMTreeView->itemNew.hItem;
		pFolderTree->InsertItem(&tvinsert);
   }   //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	*pResult = 0;
}

void CDirOpenDialog::OnSelchangedTreeDir(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM hItem;
	CString m_TmpStr,m_FullPath;
	hItem=pNMTreeView->itemNew.hItem;
	do { // ~~~~~~~~~~~~~~~~~~~~~ Вернули путь ~~~~~~~~~~~~~~~~~
		if (pFolderTree->GetItemText(hItem).Find('\\')==-1)
			 m_TmpStr=(pFolderTree->GetItemText(hItem)+"\\");
		else m_TmpStr=pFolderTree->GetItemText(hItem);
		m_TmpStr.MakeReverse();
		m_FullPath+=m_TmpStr;
		hItem=pFolderTree->GetParentItem(hItem);
	}while(hItem!=NULL);
	m_FullPath.MakeReverse();//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (m_FullPath.GetLength()>3)m_FullPath=m_FullPath.Left(m_FullPath.ReverseFind('\\'));
	Path=m_FullPath;
	if(m_FullPath.GetLength()>32) m_FullPath=m_FullPath.Left(3)+"...."+m_FullPath.Right(25);
	SetDlgItemText(IDC_StaticFolderName,m_FullPath);
	*pResult = 0;
}

CString CDirOpenDialog::GetPath()
{
	return Path;
}
