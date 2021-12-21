
#include "stdafx.h"
#include "OutlookBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutlookBar

COutlookBar::COutlookBar()
{
}

COutlookBar::~COutlookBar()
{
	// TODO: add destruction code here.
}

IMPLEMENT_DYNAMIC(COutlookBar, CListBox)

BEGIN_MESSAGE_MAP(COutlookBar, CListBox)
	//{{AFX_MSG_MAP(COutlookBar)
	ON_WM_ERASEBKGND()
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutlookBar message handlers

void COutlookBar::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    CDC*            pDC = CDC::FromHandle( lpDrawItemStruct->hDC );
    CRect           rcItem(lpDrawItemStruct->rcItem);
	CRect           rText(rcItem);
    CPoint          Pt(((rcItem.Width() - 32) /2 ), rcItem.top + 6);
    HICON           hIcon = m_ImageList.ExtractIcon(Image[lpDrawItemStruct->itemID]);
	
	
	
    CString str;
    rText.top +=40;
	rText.left+=2;
	rText.right -=2;
	rText.bottom -= 6;
	CRect ri;
	ri.left=Pt.x-1;
	ri.top=Pt.y-1;
	ri.bottom=ri.top+34;
	ri.right=ri.left+34;
	
	if(lpDrawItemStruct->itemAction&(ODA_SELECT|ODA_DRAWENTIRE)){
		pDC->SetTextColor( ::GetSysColor( COLOR_WINDOW ) );
		pDC->SetBkMode( TRANSPARENT );


		pDC->FillRect(rcItem,&CBrush(RGB(0,128,128)));
			
		if(lpDrawItemStruct->itemState&(ODS_SELECTED)){
		pDC->Draw3dRect(ri , ::GetSysColor( COLOR_3DDKSHADOW ),
			::GetSysColor( COLOR_BTNFACE ) );

		}
		pDC->DrawIcon( Pt, hIcon );
		GetText(lpDrawItemStruct->itemID,str);
		pDC->DrawText( str,rText,
			DT_CENTER | DT_END_ELLIPSIS|DT_WORDBREAK    );
	}
}

BOOL COutlookBar::OnEraseBkgnd(CDC* pDC) 
{

	CRect rcClient;
	GetClientRect( &rcClient );
	pDC->FillRect( rcClient, &CBrush(RGB(0,128,128)));
	return TRUE;
}

void COutlookBar::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	lpMeasureItemStruct->itemHeight = 60;
}

BOOL COutlookBar::PreCreateWindow(CREATESTRUCT& cs) 
{
	if(!CListBox::PreCreateWindow(cs))
		return false;
	cs.style|=LBS_HASSTRINGS|
		LBS_OWNERDRAWFIXED|
		LBS_NOINTEGRALHEIGHT|
		WS_VSCROLL|
		LBS_NOTIFY;
	cs.dwExStyle|=WS_EX_CLIENTEDGE;
	return true;
}

void COutlookBar::OnSize(UINT nType, int cx, int cy) 
{
	CListBox::OnSize(nType, cx, cy);
	Invalidate();		
}


int COutlookBar::InsertString(int nIndex, LPCTSTR lpszItem, int iImage)
{
	Image[nIndex]=iImage;
	return CListBox::InsertString(nIndex,lpszItem);
}

void COutlookBar::SetImage(int nIndex, int iImage)
{
	if(nIndex<0||nIndex>=30)
		return;
	Image[nIndex]=iImage;
	Invalidate();
}

int COutlookBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CFont ft;
	if(!ft.CreatePointFont (90, _T("ËÎÌו")))
		if(!ft.CreatePointFont (85, _T("Tahoma")))
			return -1;

	SetFont(&ft);
	ft.Detach();	
	return 0;
}

int COutlookBar::DeleteListString(int nIndex)
{
	int count=GetCount();
	for(int i=nIndex;i<count-1;i++)
		Image[i]=Image[i+1];
	return DeleteString(nIndex);
}

void COutlookBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture();		
	CListBox::OnLButtonDown(nFlags, point);
}

void COutlookBar::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CListBox::OnLButtonUp(nFlags, point);
	ReleaseCapture();
	if(GetParent())
		GetParent()->SetFocus();
}

void COutlookBar::SetString(int nIndex, CString str)
{
	DWORD dwTmp=GetItemData(nIndex);
	BOOL bTmp=false;;
	if(GetCurSel()==nIndex)
		bTmp=true;
	DeleteString(nIndex);
	CListBox::InsertString(nIndex,str);
	SetItemData(nIndex,dwTmp);
	if(bTmp)
		SetCurSel(nIndex);
}
