// EmoteItem.h: interface for the CEmoteItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EMOTEITEM_H__E1275560_B6BA_11D3_81F2_0080C86BAA81__INCLUDED_)
#define AFX_EMOTEITEM_H__E1275560_B6BA_11D3_81F2_0080C86BAA81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEmoteItem : public CObject  
{
public:
	CString ToNone;
	CString ToMe;
	CString ToHe;
	CString Emote;
	CEmoteItem();
	virtual ~CEmoteItem();

};

#endif // !defined(AFX_EMOTEITEM_H__E1275560_B6BA_11D3_81F2_0080C86BAA81__INCLUDED_)
