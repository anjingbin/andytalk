// CPassDlg.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "CPassDlg.h"
#include "mainfrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassDlg dialog


CPassDlg::CPassDlg(CString pass,CRijndael *paes, CWnd* pParent /*=NULL*/)
	: CDialog(CPassDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPassDlg)
	m_Password = _T("");
	//}}AFX_DATA_INIT
	sOldPass=pass;
	pAES_engine=paes;
}


void CPassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassDlg)
	DDX_Text(pDX, IDC_EDIT1, m_Password);
	DDV_MaxChars(pDX, m_Password, 16);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPassDlg, CDialog)
	//{{AFX_MSG_MAP(CPassDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassDlg message handlers

void CPassDlg::OnOK() 
{
	UpdateData();

	CRijndael	aes;
	char	old_pass[64],new_pass[64],result[64];

	memset(old_pass,0,64);
	memset(new_pass,0,64);
	memset(result,0,64);
	if(sOldPass.IsEmpty() && m_Password.IsEmpty())
		return;
	HexStr2CharStr(sOldPass,(unsigned char *)old_pass,16);
	strcpy(new_pass,m_Password);
	aes.MakeKey(new_pass,CRijndael::sm_chain0,16,16);
	aes.DecryptBlock(old_pass,result);
	if(!strcmp(result,new_pass)){
		pAES_engine->MakeKey(new_pass,CRijndael::sm_chain0,16,16);
		EndDialog(IDOK);
	}
	else{
		AfxMessageBox("Password mismatched!");
		EndDialog(IDCANCEL);
	}
}
