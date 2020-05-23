// TCP_IP.h: interface for the CTCP_IP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCP_IP_H__8C3C09E2_BEE9_11D5_9EDD_00A0C9C67EC7__INCLUDED_)
#define AFX_TCP_IP_H__8C3C09E2_BEE9_11D5_9EDD_00A0C9C67EC7__INCLUDED_

#include "DataProtocol.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h>
#include <malloc.h>
#include <STDDEF.H>


class CTCP_IP  
{
public:
	int nBegin ;	// № байта индикатора протокола
	CString strHDR;
	bool InArray(UINT dData);
	void WriteSeans(UINT& gFile, UINT& gDir, CString& gstrDir,CString strDir,UINT ii);
	BOOL Granica(UINT ii);
	void Zagolovok();
	void FormatData(UINT ii);
	bool InitData(BYTE *BufIN,UINT);
	BYTE nFlag;
	bool Soed(BYTE*BufIN, UINT cdata);
	ULONG nCalcFiles;
	int nCountData;
	//CDataProtocol *nData;
	CArray<CDataProtocol,CDataProtocol> nData;
	BYTE nLengthTCP;
	UINT nPort_po;
	UINT nIndexHDR[6]; // массив, содержащий позиции:
	                //                    даты[0]
                    //				      времени приема[1]
	                //				      адреса  отпр[2] 
	                //				      порта   отпр[3] 
	                //				      адреса  получ[4] 
	                //				      порта   получ[5] 
	                // в строке заголовка приемного файла
	UINT nPort_ot;
	UINT nFilesInDirSEL,
		 nFilesInDirNONSEL;
	UINT nNomData;
	UINT nIP_po;
	UINT nIP_ot;
	UINT nLengthPaket;
	BYTE nLengthIP;
	UINT DePakets(BYTE*BufIN,UINT nCount);
    CString strTempDir,
		    strSelDir,
			strNonSelDir,
			strDirInSel,
			strDirInNonSel;
	UINT nDirInSel,
		 nDirInNonSel;
	CArray<unsigned short,unsigned short> *pBufIP_2,
		                                  *pBufPORT ;
	CArray<UINT,UINT> *pBufIP_3;
	CArray<UINT,UINT> *pBufIP_4;
	CTCP_IP();
	virtual ~CTCP_IP();

protected:
	void FullMem();
};

#endif // !defined(AFX_TCP_IP_H__8C3C09E2_BEE9_11D5_9EDD_00A0C9C67EC7__INCLUDED_)
