// Log.h: interface for the CLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOG_H__B7BF7C5E_8102_4F3C_834C_30C6C65C7BE7__INCLUDED_)
#define AFX_LOG_H__B7BF7C5E_8102_4F3C_834C_30C6C65C7BE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rijndael.h"

class CLog : public CList<LOGITEM *, LOGITEM *>
{
public:
	BOOL ContainItem(LOGITEM *);
	void SetEncrypt(BOOL benc=true);
	CLog(CRijndael *paes=NULL);
	CLog(CArchive &, CRijndael *paes=NULL);
	CLog(CString &,BOOL bRW=false, CRijndael *paes=NULL);
	virtual ~CLog();
	BOOL IsLocked(void);
	BOOL UnLock(void);
	void SetAES_engine(CRijndael *paes);

	LOGITEM * operator [] (POSITION);
	LOGITEM * operator [] (UINT);
	void operator << (LOGITEM *);
	CArchive & operator << (CArchive &);
	CArchive & operator >> (CArchive &);
	CLog & operator << (CLog &);
	CLog & operator >> (CLog &);
	BOOL	IsReady(void);
	BOOL Decrypt(CRijndael *paes=NULL);
	BOOL Encrypt(CRijndael *paes=NULL);
private:
	CRijndael * pAES_engine;
	BOOL bLocked;
	BOOL	bEncrypted;
	BOOL	bReady;

};

#endif // !defined(AFX_LOG_H__B7BF7C5E_8102_4F3C_834C_30C6C65C7BE7__INCLUDED_)
