// PassDialog.cpp : implementation file
//

#include "stdafx.h"
#include "talk.h"
#include "PassDialog.h"
#include "rijndael.h"
#include "mainfrm.h"
#include "logdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPassDialog dialog


CPassDialog::CPassDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPassDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPassDialog)
	m_old = _T("");
	m_new = _T("");
	m_confirm = _T("");
	//}}AFX_DATA_INIT
}


void CPassDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPassDialog)
	DDX_Text(pDX, IDC_EDIT1, m_old);
	DDV_MaxChars(pDX, m_old, 16);
	DDX_Text(pDX, IDC_EDIT2, m_new);
	DDV_MaxChars(pDX, m_new, 16);
	DDX_Text(pDX, IDC_EDIT3, m_confirm);
	DDV_MaxChars(pDX, m_confirm, 16);
	//}}AFX_DATA_MAP
	CMainFrame * pMainWnd=(CMainFrame*)AfxGetMainWnd();
	if(pMainWnd->m_wndClient.m_Config.m_Password.IsEmpty())
		(CEdit *)GetDlgItem(IDC_EDIT1)->EnableWindow(false);
}

	
BEGIN_MESSAGE_MAP(CPassDialog, CDialog)
	//{{AFX_MSG_MAP(CPassDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPassDialog message handlers

void CPassDialog::OnOK() 
{
	CDialog::OnOK();

	if(m_new!=m_confirm){
		AfxMessageBox("New password and confirmed mismatched!");
		return;
	}

	CMainFrame * pMainWnd=(CMainFrame*)AfxGetMainWnd();
	CRijndael	AES_engine;
	char	old_pass[64],pass[64],result[64];

	memset(old_pass,0,64);
	memset(pass,0,64);
	memset(result,0,64);

	CString temp=pMainWnd->m_wndClient.m_Config.m_Password;
	HexStr2CharStr(temp,(unsigned char *)old_pass,16);
	
	if(m_old.IsEmpty()){
		if(!temp.IsEmpty()){
			AfxMessageBox("Password mismatched!");
			return;
		}
	}else{
		if(temp.IsEmpty()){
			AfxMessageBox("Password mismatched!");
			return;
		}
		strcpy(pass,m_old);
		AES_engine.MakeKey(pass,CRijndael::sm_chain0,16,16);

		AES_engine.DecryptBlock(old_pass,result);
		if(strcmp(pass,result)){
			AfxMessageBox("Password mismatched!");
			return;
		}
	}
	memset(pass,0,64);
	strcpy(pass,m_new);

	if(m_new!=m_old){
		CFile logf;
		CLog  Log;
		if(!logf.Open(pMainWnd->m_wndClient.m_sPath+LOGFILE,CFile::modeCreate|CFile::modeNoTruncate|CFile::modeReadWrite)){
			AfxMessageBox("Failed to open logfile!");
		}else{
			if(logf.GetLength()){
				CArchive logarr(&logf,CArchive::load);
				Log<<logarr;
				logarr.Close();
				
				if(!m_old.IsEmpty()){
					AES_engine.MakeKey(result,CRijndael::sm_chain0,16,16);
					Log.Decrypt(&AES_engine);
					Log.SetEncrypt(false);
				}
				
				if(m_new.IsEmpty()){
					pMainWnd->m_wndClient.m_AES_engine.DisableKey();
				}else{
					pMainWnd->m_wndClient.m_AES_engine.MakeKey(pass,CRijndael::sm_chain0,16,16);
					Log.Encrypt(&pMainWnd->m_wndClient.m_AES_engine);
				}
				CArchive logarw(&logf,CArchive::store);
				logarw.GetFile()->SeekToBegin();
				Log>>logarw;
				logarw.Close();
			}
		}
	}
	if(!m_new.IsEmpty()){
		pMainWnd->m_wndClient.m_AES_engine.MakeKey(pass,CRijndael::sm_chain0,16,16);
		pMainWnd->m_wndClient.m_AES_engine.EncryptBlock(pass,result);
		CharStr2HexStr((unsigned char *)result,pMainWnd->m_wndClient.m_Config.m_Password.GetBuffer(33),16);
		pMainWnd->m_wndClient.m_Config.m_Password.ReleaseBuffer();
	}else
		pMainWnd->m_wndClient.m_Config.m_Password="";
}
