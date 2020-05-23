// TCP_IP.cpp: implementation of the CTCP_IP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Protocol.h"
#include "TCP_IP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
extern 	CProtocolApp theApp;


CTCP_IP::CTCP_IP()
{

 
}

CTCP_IP::~CTCP_IP()
{

}

UINT CTCP_IP::DePakets(BYTE *BufIN, UINT nCount)  // обработка протокола и выделение пакетов
{
	CString strTemp;
	int i;
	CDataProtocol m_DP;

	if(!InitData(BufIN,nCount)) return 0;

		//////////////////обработка...
		
		for(i=nCountData-1;i>=0;i--)
		{
			if(nData.GetAt(i).dIP_ot==nIP_ot
					&& nData.GetAt(i).dPort_ot==nPort_ot
					&& nData.GetAt(i).dPort_po==nPort_po
					&& nData.GetAt(i).dIP_po==nIP_po
					&& nData.GetAt(i).dIP_ot==nIP_ot)
			{
				if((nFlag&0x04)==0x04) 
				{
					  FormatData(i); // сброс соединения (RST) 
					  return 0;
				}

		      // Бывает, что SYN проходит несколько раз
			  // (наверное когда соединение не устанавливается сразу)
              // поэтому нужно каждый раз сбрасывать счетчик пакетов
			  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
				if((nFlag&0x02)==0x02) 
				{
				m_DP=nData.GetAt(i);
				m_DP.dNomData=nNomData+1;
				nData.SetAt(i,m_DP);
				}

			  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

				if(!Soed(BufIN, i)) return 0;
				if((nFlag&0x01)==0x01) FormatData(i);
				return 0;
			}
		}

       if(i==-1)
		 if((nFlag&0x02)==0x02)
	   {

				
				m_DP.dIP_ot=nIP_ot;
				m_DP.dIP_po=nIP_po;
				m_DP.dPort_po=nPort_po;
				m_DP.dPort_ot=nPort_ot;
				m_DP.dNomData=nNomData+1;

				strTemp.Format("%u",nCalcFiles++);
				m_DP.dFile=strTempDir+"\\"+strTemp;
			
				
	if((m_DP.h_File=CreateFile(m_DP.dFile,GENERIC_WRITE,
		               0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL))==INVALID_HANDLE_VALUE)
					   	MessageBox(NULL,"Создание",0,MB_ICONERROR);

	nData.Add(m_DP);
    
    if(!strHDR.IsEmpty()) Zagolovok();

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

                nCountData++;
				if((nFlag&0x04)==0x04)
				{
					  FormatData(nCountData-1); // сброс соединения (RST) 
					  return 0;
				}
                
				if(!Soed(BufIN,nCountData-1)) return 0;

				if((nFlag&0x01)==0x01) FormatData(nCountData-1);

	   }	
		
		///////////////////обновление BufIN/////////////////

		if(nCountData==1000) 
			          FormatData(0);	//переполнение nData
	return 0;
}

bool CTCP_IP::InitData(BYTE *BufIN,UINT nCount)			//фильтрация IP-пакетов
 {
	
 	nLengthIP=0;
 	nLengthPaket=0;
 	nLengthTCP=0;
 	nIP_ot=0;
 	nIP_po=0;
 	nNomData=0;
 	nPort_ot=0;
 	nPort_po=0;
	int i;
 	
 	nLengthIP=(*(BufIN+nBegin)<<4);		// длина IP заголовка
	nLengthIP=(nLengthIP>>4)*4;
 	
 
 	for(i=0;i<2;i++)
 	{
 		nLengthPaket<<=8;
 		nLengthPaket=nLengthPaket+*(BufIN+nBegin+2+i);		// длина всей дейтаграммы
 	}
 	
 	
 	for(i=0;i<4;i++)
 	{
 		nIP_ot<<=8;	nIP_po<<=8;	nNomData<<=8;
 		nIP_ot=nIP_ot+*(BufIN+nBegin+12+i);					//IP адрес отправителя
 		nIP_po=nIP_po+*(BufIN+nBegin+16+i);					//IP адрес получателя
 		nNomData=nNomData+*(BufIN+nBegin+nLengthIP+4+i);	//номер первого октета в поле данных
 	}
 	
 	for(i=0;i<2;i++)
 	{
 		nPort_ot<<=8;	nPort_po<<=8;
 		nPort_ot=nPort_ot+*(BufIN+nBegin+nLengthIP+i);		//порт отправителя
		nPort_po=nPort_po+*(BufIN+nBegin+nLengthIP+2+i);	//порт получателя
 	}
 	
 	nLengthTCP=(*(BufIN+nBegin+nLengthIP+12)>>4)*4;	//длина TCP заголовка
 
 	nFlag=(*(BufIN+nBegin+nLengthIP+13));	//управляющие биты


	if(*(BufIN+nBegin)!=0x45 || *(BufIN+nBegin+9)!=0x06
		|| (UINT)(nLengthIP+nLengthTCP)>nLengthPaket) return FALSE;
	return TRUE;
 }

bool CTCP_IP::Soed(BYTE *BufIN,UINT cdata)
{
	BYTE a=0;
	BYTE*pBuf;
	UINT ppp;
	DWORD bReturned; 
	CDataProtocol m_DP;
	BOOL FlagMem=FALSE;

	if((nFlag&0x02)==0x02) 
		nNomData++; 

    if(nData.GetAt(cdata).dNomData==nNomData)
	{
			if(WriteFile(nData.GetAt(cdata).h_File,&BufIN[nBegin+nLengthIP+nLengthTCP],
				                nLengthPaket-nLengthIP-nLengthTCP,&bReturned,NULL)==NULL)
								MessageBox(NULL,"Запись",0,MB_ICONERROR);

            m_DP=nData.GetAt(cdata);
			m_DP.dNomData+=nLengthPaket-nLengthIP-nLengthTCP;
			nData.SetAt(cdata,m_DP);

 			return TRUE;
			

	}
	else
    if(nData.GetAt(cdata).dNomData<nNomData)
	 {

		ppp=nNomData-nData.GetAt(cdata).dNomData;
        if(ppp>10000000) return FALSE;
		pBuf=::new BYTE[ppp]; 
			
		memset(pBuf,'?',ppp);
		if(WriteFile(nData.GetAt(cdata).h_File,pBuf,ppp,&bReturned,NULL)==NULL)
				  MessageBox(NULL,"Запись",0,MB_ICONERROR);;

		if(WriteFile(nData.GetAt(cdata).h_File,&BufIN[nBegin+nLengthIP+nLengthTCP],
		          nLengthPaket-nLengthIP-nLengthTCP,&bReturned,NULL)==NULL)
				  MessageBox(NULL,"Запись",0,MB_ICONERROR);;

	    m_DP=nData.GetAt(cdata);
		m_DP.dNomData=nNomData+nLengthPaket-nLengthIP-nLengthTCP;
		nData.SetAt(cdata,m_DP);
		
		delete [] pBuf;
		return TRUE;
	 } 
    else 
	if(nData.GetAt(cdata).dNomData>nNomData)
	{
	 if(SetFilePointer(nData.GetAt(cdata).h_File,-(nData.GetAt(cdata).dNomData-nNomData),NULL,FILE_CURRENT)
		              ==0xFFFFFFFF) 
					  return FALSE;
	 
	 if(WriteFile(nData.GetAt(cdata).h_File,&BufIN[nBegin+nLengthIP+nLengthTCP],
				                nLengthPaket-nLengthIP-nLengthTCP,&bReturned,NULL)==NULL)
								MessageBox(NULL,"Запись",0,MB_ICONERROR);

		if(SetFilePointer(nData.GetAt(cdata).h_File,0,NULL,FILE_END)==0xFFFFFFFF)
		                 MessageBox(NULL,"Указатель 2",0,MB_ICONERROR);
		return TRUE;
	}

return FALSE;
}

void CTCP_IP::FormatData(UINT ii)
{
	if(!Granica(ii))
	{
		CloseHandle(nData.GetAt(ii).h_File);

		if(theApp.dlg->m_FileSel!="")
		{
		 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если ЕСТЬ отбор по TCP-портам~~~~~~~~~~~~~~~~~~~~~~~
			if(theApp.dlg->m_OtbDlg.m_RADIO==1)
			{
				if((nPort_po==(pBufPORT->GetAt(nPort_po)))||(nPort_ot==(pBufPORT->GetAt(nPort_ot))))
				{
					WriteSeans(nFilesInDirSEL,nDirInSel,strDirInSel,strSelDir,ii);
					nData.RemoveAt(ii,1);
					nCountData--;
					return;
				}
			}
            else
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если ЕСТЬ отбор по IP-адресам~~~~~~~~~~~~~~~~~~~~~~~
			if(theApp.dlg->m_OtbDlg.m_RADIO==0)
			{
				if(InArray(nIP_ot) || InArray(nIP_po))
				{
					WriteSeans(nFilesInDirSEL,nDirInSel,strDirInSel,strSelDir,ii);
					nData.RemoveAt(ii,1);
					nCountData--;
					return;
				}
			}
			else 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~если ЕСТЬ отбор по TCP-портам и IP-адресам~~~~~~~~~~
			if(theApp.dlg->m_OtbDlg.m_RADIO==2)
			{
				if(InArray(nIP_ot) || InArray(nIP_po)||(nPort_po==(pBufPORT->GetAt(nPort_po)))||(nPort_ot==(pBufPORT->GetAt(nPort_ot))))
				{
					WriteSeans(nFilesInDirSEL,nDirInSel,strDirInSel,strSelDir,ii);
					nData.RemoveAt(ii,1);
					nCountData--;
					return;
				}
			}
		}
    
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~во всех остальных случаях~~~~~~~~~~~~~~~~~~~~~~~
	if(!theApp.dlg->m_OtbDlg.m_NonSave)
		 WriteSeans(nFilesInDirNONSEL,nDirInNonSel,strDirInNonSel,strNonSelDir,ii);		   
	}

	nData.RemoveAt(ii,1);
	nCountData--;

	return;
}

void CTCP_IP::Zagolovok()  // вставляет заголовок в начало регистрируемого сеанса
{
	CString strZagFR="",strZagTO="",
		strZag, 
		strTemp;
	CString s,sT;
	BYTE zIP;
	DWORD bReturned;
	int j;
	
	s=strHDR;

	CTime t=CTime::GetCurrentTime();
	sT=t.Format("%d.%m.%y") ;          // текущие дата и время в заголовок
	s.Delete(nIndexHDR[0],8);
	s.Insert(nIndexHDR[0],sT);

	sT=t.Format("%H:%M:%S") ;
	s.Delete(nIndexHDR[1],8);
	s.Insert(nIndexHDR[1],sT);

	for(j=3;j>=0;j--)
	{
		zIP=(nData[nCountData].dIP_ot>>(8*j))&0xFF;
		strTemp=strZagFR;
		strZagFR.Format("%u",zIP);
		switch(strZagFR.GetLength())
		{
		 case 1: strZagFR="00"+strZagFR; break;
		 case 2: strZagFR="0"+strZagFR;  break;
		}
		strZagFR=strTemp+strZagFR;
		if(j>0) strZagFR+=".";
	}
		
   	strTemp.Format("%u",nData[nCountData].dPort_ot);
    switch(strTemp.GetLength())
	{ 
     case 1: strTemp="0000"+strTemp; break;
	 case 2: strTemp="000"+strTemp;  break;
	 case 3: strTemp="00"+strTemp;   break;
	 case 4: strTemp="0"+strTemp;    break;
	}


	s.Delete(nIndexHDR[2],strZagFR.GetLength()); // IP-адрес и порт отправ. в заголовок
	s.Insert(nIndexHDR[2],strZagFR);
	s.Delete(nIndexHDR[3],strTemp.GetLength());
	s.Insert(nIndexHDR[3],strTemp);

	strZagFR=" FROM "+strZagFR+" "+strTemp;

	for(j=3;j>=0;j--)
	{
		zIP=(nData[nCountData].dIP_po>>(8*j))&0xFF;
		strTemp=strZagTO;
		strZagTO.Format("%u",zIP);
		switch(strZagTO.GetLength())
		{
		 case 1: strZagTO="00"+strZagTO; break;
		 case 2: strZagTO="0"+strZagTO;  break;
		} 
		strZagTO=strTemp+strZagTO;
		if(j>0) strZagTO+=".";
	}
			
	strTemp.Format("%u",nData[nCountData].dPort_po);
    switch(strTemp.GetLength())
	{ 
     case 1: strTemp="0000"+strTemp; break;
	 case 2: strTemp="000"+strTemp;  break;
	 case 3: strTemp="00"+strTemp;   break;
	 case 4: strTemp="0"+strTemp;    break;
	}

	s.Delete(nIndexHDR[4],strZagTO.GetLength()); // IP-адрес и порт получ. в заголовок
	s.Insert(nIndexHDR[4],strZagTO);
	s.Delete(nIndexHDR[5],strTemp.GetLength());
	s.Insert(nIndexHDR[5],strTemp);

	strZagTO="  TO "+strZagTO+" "+strTemp;
	
	strZag=s+strZagFR+strZagTO+" \r\n";

	if(WriteFile(nData.GetAt(nCountData).h_File,strZag,strZag.GetLength(),&bReturned,NULL)==NULL)
		MessageBox(NULL,"Заголовок",0,MB_ICONERROR);
	return ;
}

BOOL CTCP_IP::Granica(UINT ii) // определяет размер регистрируемых сеансов
{

  DWORD bReturned;

  bReturned=GetFileSize(nData.GetAt(ii).h_File,NULL);
  if(bReturned==0xFFFFFFFF) 
	  MessageBox(NULL,"Размер невозможен",0,MB_ICONERROR);

  if(theApp.dlg->m_CheckDelMin==TRUE)
	  if(bReturned<=((DWORD)theApp.dlg->m_SliderK.GetPos()+strHDR.GetLength()))
	  {
		  CloseHandle(nData.GetAt(ii).h_File);
		  if(!DeleteFile(nData.GetAt(ii).dFile))
			  MessageBox(NULL,"Не могу удалить файл",0,MB_ICONERROR);
	//	  nFilesInDir--;
		  return TRUE;
	  }
  if(theApp.dlg->m_CheckDelMax==TRUE)
	  if(bReturned>=((DWORD)theApp.dlg->m_SliderD.GetPos())*1024)
	  {
		  CloseHandle(nData.GetAt(ii).h_File);
		   if(!DeleteFile(nData.GetAt(ii).dFile))
			   MessageBox(NULL,"Не могу удалить файл",0,MB_ICONERROR);
	//	  nFilesInDir--;
		  return TRUE;
	  }
return FALSE;
}

void CTCP_IP::WriteSeans(UINT& gFile, UINT& gDir, CString& gstrDir,CString strDir, UINT k)
{
	                     // gFile - nFilesInDir
	                     // gDir -  nDirInSel(nDirInNonSel)
	                     // gstrDir - strDirInSel(strDirInNonSel)
	                     // strDir  - strSelDir (strNonSelDir)
	                     // k - номер соединения
	
	CString sTemp,sNameFile,sDDD;

	if((nPort_po==80)||(nPort_ot==80)) sDDD=".htm";
	else
  	if((nPort_po==25)||(nPort_ot==25)) sDDD=".eml";
	else if((nPort_po==21)||(nPort_ot==21)||
		    (nPort_po==23)||(nPort_ot==23)||
            (nPort_po==110)||(nPort_ot==110)||
			(nPort_po==119)||(nPort_ot==119)||
			(nPort_po==4049)||(nPort_ot==4049)) sDDD=".psw";
	else sDDD=".rdy";
	
	sTemp.Format("%u",gFile);
	switch(8-sTemp.GetLength())
	{
	case 7: sTemp="0000000" + sTemp; break;
	case 6: sTemp="000000" + sTemp; break;
	case 5: sTemp="00000" + sTemp; break;
	case 4: sTemp="0000" + sTemp; break;
	case 3: sTemp="000" + sTemp; break;
	case 2: sTemp="00" + sTemp; break;
	case 1: sTemp="0" + sTemp; break;
	} 				

	if(gFile%300==0)
	{
		gstrDir.Format("%u",gDir);
        switch(8-gstrDir.GetLength())
		{
	      case 7: gstrDir="D000000" + gstrDir; break;
	      case 6: gstrDir="D00000" + gstrDir; break;
	      case 5: gstrDir="D0000" + gstrDir; break;
	      case 4: gstrDir="D000" + gstrDir; break;
	      case 3: gstrDir="D00" + gstrDir; break;
	      case 2: gstrDir="D0" + gstrDir; break;
	      case 1: gstrDir="D" + gstrDir; break;
		} 				
		gstrDir=strDir+"\\"+gstrDir;
		CreateDirectory(gstrDir,NULL);
		gDir++;
		gFile=0;
	}

	sNameFile=gstrDir+"\\"+sTemp+sDDD;

	if(!MoveFileEx(nData.GetAt(k).dFile,sNameFile,MOVEFILE_COPY_ALLOWED|MOVEFILE_REPLACE_EXISTING)) 
			MessageBox(NULL,"Не могу перенести файл",0,MB_ICONERROR);
	 gFile++;

	return;	 
}

bool CTCP_IP::InArray(UINT dData)
{
	int min=0,max;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Поиск 2-х байтного IP-адреса~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ 	

		if((dData>>16)==pBufIP_2->GetAt(dData>>16)) return TRUE;
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Поиск 3-х байтного IP-адреса~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	min=0;	
	max=pBufIP_3->GetSize()-1;
	
	if(max>=0)
	{
		if(pBufIP_3->GetAt(min)==dData>>8
			|| pBufIP_3->GetAt(max)==dData>>8) return TRUE;
	
		while(min+1<max)
		{
			if(pBufIP_3->GetAt(min+(max-min)/2)>dData>>8)
				max=min+(max-min)/2;
			else
				if(pBufIP_3->GetAt(min+(max-min)/2)<dData>>8)
					min=min+(max-min)/2;
				else
					if(pBufIP_3->GetAt(min+(max-min)/2)==dData>>8)
						return TRUE;
		}
	}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Поиск 4-х байтного IP-адреса~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	min=0;
	max=pBufIP_4->GetSize()-1;
	
	if(max>=0)
	{
		if(pBufIP_4->GetAt(min)==dData
			|| pBufIP_4->GetAt(max)==dData) return TRUE;
		
		while(min+1<max)
		{
			if(pBufIP_4->GetAt(min+(max-min)/2)>dData)
				max=min+(max-min)/2;
			else
				if(pBufIP_4->GetAt(min+(max-min)/2)<dData)
					min=min+(max-min)/2;
				else
					if(pBufIP_4->GetAt(min+(max-min)/2)==dData)
						return TRUE;
		}
	}
return FALSE;
}

void CTCP_IP::FullMem()
{
 
}
