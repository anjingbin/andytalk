// ABItem.h: interface for the CABItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ABITEM_H__9BDE6762_9D1E_11D3_8382_0080C86BAA81__INCLUDED_)
#define AFX_ABITEM_H__9BDE6762_9D1E_11D3_8382_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CABItem : public CObject  
{
public:
	CABItem();
	virtual ~CABItem();
public:
	CString Name;
	CString IP;
	CString WelMsg;
	CString LvWord;
	BOOL	bWelMsg;
	BOOL    bLvWord;


};

#endif // !defined(AFX_ABITEM_H__9BDE6762_9D1E_11D3_8382_0080C86BAA81__INCLUDED_)
