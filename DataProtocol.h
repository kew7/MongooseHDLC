// DataProtocol.h: interface for the CDataProtocol class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAPROTOCOL_H__05389CE2_C148_11D5_9EDD_00A0C9C67EC7__INCLUDED_)
#define AFX_DATAPROTOCOL_H__05389CE2_C148_11D5_9EDD_00A0C9C67EC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct CDataProtocol  
{
	HANDLE h_File;
	UINT dNomData;
	UINT dPort_po;
	UINT dPort_ot;
	UINT dIP_po;
	UINT dIP_ot;
	CString dFile;
	
};

#endif // !defined(AFX_DATAPROTOCOL_H__05389CE2_C148_11D5_9EDD_00A0C9C67EC7__INCLUDED_)
