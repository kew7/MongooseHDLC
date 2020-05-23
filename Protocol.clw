; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProtocolDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Protocol.h"

ClassCount=5
Class1=CProtocolApp
Class2=CProtocolDlg
Class3=CAboutDlg

ResourceCount=7
Resource1=IDD_DIrOpenDialog
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_PROTOCOL_DIALOG
Resource5=IDD_TmpDir
Class4=COtborDlg
Resource6=IDD_OtborDlg
Class5=CTempDirDlg
Resource7=IDR_MENU1

[CLS:CProtocolApp]
Type=0
HeaderFile=Protocol.h
ImplementationFile=Protocol.cpp
Filter=N
LastObject=CProtocolApp

[CLS:CProtocolDlg]
Type=0
HeaderFile=ProtocolDlg.h
ImplementationFile=ProtocolDlg.cpp
Filter=D
LastObject=CProtocolDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ProtocolDlg.h
ImplementationFile=ProtocolDlg.cpp
Filter=D
LastObject=IDOK
BaseClass=CDialog
VirtualFilter=dWC

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROTOCOL_DIALOG]
Type=1
Class=CProtocolDlg
ControlCount=37
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RADIO1,button,1342308361
Control3=IDC_RADIO2,button,1342177289
Control4=IDC_STATIC,static,1342308354
Control5=IDC_STATIC,static,1342308354
Control6=IDC_RABOTA,button,1342246915
Control7=IDC_STATIC_C,static,1342312448
Control8=IDC_STATIC_O,static,1342312448
Control9=IDC_STATIC_INT,static,1342308354
Control10=IDC_STATIC_OUTT,static,1342308354
Control11=IDC_STATIC_IN,static,1342312448
Control12=IDC_STATIC_TEMP,static,1342312448
Control13=IDC_PROGRESS2,msctls_progress32,1350565889
Control14=IDC_SLIDER_K,msctls_trackbar32,1342242840
Control15=IDC_SLIDER_D,msctls_trackbar32,1342242840
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,button,1342177287
Control19=IDC_STATIC_KD,static,1342312448
Control20=IDC_STATIC_DD,static,1342312448
Control21=IDC_STATIC,static,1342308354
Control22=IDC_SOST,static,1342312961
Control23=IDC_CheckDelMin,button,1342242819
Control24=IDC_CheckDelMax,button,1342242819
Control25=IDC_STATIC,static,1342308354
Control26=IDC_STATIC_SEL,static,1342312448
Control27=IDC_STATIC_NONSEL,static,1342312448
Control28=IDC_STATIC,static,1342308354
Control29=IDC_STATIC,static,1342308354
Control30=IDC_STATIC_HDR,static,1342312448
Control31=IDC_STATIC_FileSel,static,1342312448
Control32=IDC_SPIN,msctls_updown32,1342177330
Control33=IDC_EditSpin,edit,1350631553
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342242818
Control36=IDC_STATIC,static,1342308354
Control37=IDC_EditFirstNumFile,edit,1350631552

[MNU:IDR_MENU1]
Type=1
Class=CProtocolDlg
Command1=ID_IN_FILE
Command2=ID_HDR_FILE
Command3=ID_IN_DIR
Command4=ID_OUT_DIR
Command5=ID_SelDir
Command6=ID_NonSelDir
Command7=ID_OTBOR
Command8=ID_FileOtbor
Command9=ID_SaveCfg
Command10=ID_ZagrCfg
CommandCount=10

[DLG:IDD_DIrOpenDialog]
Type=1
Class=?
ControlCount=5
Control1=IDC_FolderLabel,static,1342308364
Control2=IDC_TreeDir,SysTreeView32,1350631447
Control3=IDOK,button,1342242817
Control4=IDCANCEL,button,1342242816
Control5=IDC_StaticFolderName,static,1342308352

[DLG:IDD_OtborDlg]
Type=1
Class=COtborDlg
ControlCount=7
Control1=IDC_RADIO_IP,button,1342308361
Control2=IDC_RADIO_PORT,button,1342177289
Control3=IDC_RADIO_P_I,button,1342177289
Control4=IDC_RADIO_NO,button,1342177289
Control5=IDOK,button,1342242816
Control6=IDCANCEL,button,1342242816
Control7=IDC_SaveNonSel,button,1342242819

[CLS:COtborDlg]
Type=0
HeaderFile=OtborDlg.h
ImplementationFile=OtborDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_SaveNonSel
VirtualFilter=dWC

[DLG:IDD_TmpDir]
Type=1
Class=CTempDirDlg
ControlCount=4
Control1=IDC_STATIC,button,1342210055
Control2=IDC_TXT1,static,1342308353
Control3=IDC_STATIC,static,1342308353
Control4=IDC_PROGRESS,msctls_progress32,1350565888

[CLS:CTempDirDlg]
Type=0
HeaderFile=TempDirDlg.h
ImplementationFile=TempDirDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_PROGRESS
VirtualFilter=dWC

