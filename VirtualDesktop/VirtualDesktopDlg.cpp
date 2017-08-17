
// VirtualDesktopDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VirtualDesktop.h"
#include "VirtualDesktopDlg.h"
#include "afxdialogex.h"
#include "gdiplus.h"

using namespace Gdiplus;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVirtualDesktopDlg dialog



CVirtualDesktopDlg::CVirtualDesktopDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VIRTUALDESKTOP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVirtualDesktopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVirtualDesktopDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_SHOWTASK, onShowTask)
	ON_MESSAGE(WM_HOTKEY, OnHotKey) //�����ȼ���Ϣ
	ON_BN_CLICKED(IDOK, &CVirtualDesktopDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CVirtualDesktopDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CVirtualDesktopDlg message handlers

BOOL CVirtualDesktopDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	//��̬�����Լ���ͼ��
	////GdiplusStartupInput gdiplusStartInput;
	////ULONG_PTR gdiplusTocken;
	////GdiplusStartup(&gdiplusTocken, &gdiplusStartInput, NULL);
	////const WCHAR* pStr = L"F:\\Ѹ������\\�����ĵ�\\yuzhu\\001.jpg";
	//////Gdiplus::Bitmap* pTmp = new Gdiplus::Bitmap(pStr);
	////Gdiplus::Bitmap* pTmp = Gdiplus::Bitmap::FromFile(pStr);
	////if (pTmp != NULL)
	////{
	////	HICON hIcon = NULL;
	////	pTmp->GetHICON(&hIcon);
	////	SetIcon(hIcon, FALSE);		// Set small icon
	////	CWnd* pMainWnd;
	////	pMainWnd = AfxGetMainWnd();
	////	pMainWnd->SetIcon(hIcon, TRUE);
	////}

	//GdiplusShutdown(gdiplusTocken);

	// TODO: Add extra initialization here
	ModifyStyleEx(WS_EX_APPWINDOW, WS_EX_TOOLWINDOW); //���ô�����ʽΪ������ʽ��������������û��ͼ����  

	IsOriginalDesktopActive = FALSE;
	IsInitialDesktop = TRUE;
	IsWindowShow = TRUE;
	::RegisterHotKey(this->GetSafeHwnd(), 521, MOD_CONTROL, 'X'); //������ʾ�����ȼ�Ϊ Win+X 

	ToTray();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVirtualDesktopDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CVirtualDesktopDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVirtualDesktopDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CVirtualDesktopDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1314) //��ϢΪ Alt+Z ʱ  
	{
		if (IsOriginalDesktopActive) //�Ƿ���ԭʼ����  
		{
// 			CWnd* hDeskWnd = GetDesktopWindow();
// 			hDeskWnd->ShowWindow(SW_HIDE);
// 			Sleep(5000);
// 			hDeskWnd->ShowWindow(SW_SHOW);
			hDesktop = CreateDesktopW(L"Virtual", NULL, NULL, 0, GENERIC_ALL, NULL); //�����������棨��CloseDesktop���Ӧ��  
			SetThreadDesktop(hDesktop);
			SwitchDesktop(hDesktop);
		}
		else
		{
			SetThreadDesktop(hOriginalThread);
			SwitchDesktop(hOriginalInput);
			CloseDesktop(hDesktop); //�ر���������  
			//Sleep(5000);
		}
		IsOriginalDesktopActive = !IsOriginalDesktopActive;
	}
	if (wParam == 521)
	{
		if (IsWindowShow)
		{
			AnimateWindow(521, AW_BLEND | AW_HIDE);//���ش���  
		}
		else
		{
			AnimateWindow(521, AW_BLEND);//��ʾ����
		}
		IsWindowShow = !IsWindowShow;
	}

	return TRUE;
}



void CVirtualDesktopDlg::OnBnClickedOk()
{
	if (IsInitialDesktop) //��һ������ʱ��ʼ�����򣬼����жϷ�ֹ��ɫ��ť����  
	{
		//��������Ϊ��Virtual������������  
		hDesktop = CreateDesktop("Virtual", NULL, NULL, 0, GENERIC_ALL, NULL);

		//��ʼ���������̱���Ľṹ��  
		ZeroMemory(&StartupInfo, sizeof(StartupInfo));
		ZeroMemory(&ProcessInfo, sizeof(ProcessInfo));
		StartupInfo.cb = sizeof(StartupInfo);
		StartupInfo.lpDesktop = "Virtual";

		//��¼ԭʼ����ľ��  
		hOriginalThread = GetThreadDesktop(GetCurrentThreadId());
		hOriginalInput = OpenInputDesktop(0, FALSE, DESKTOP_SWITCHDESKTOP);

		//����������ǽ���  
		CreateProcess(NULL, "explorer", NULL, NULL, FALSE, 0, NULL, NULL, &StartupInfo, &ProcessInfo);

		//��ɳ�ʼ�����Ժ󲻻��ٴα����ã���ֹ���������������Դ������  
		IsInitialDesktop = !IsInitialDesktop;

		SetThreadDesktop(hDesktop); //����������������������  
		SwitchDesktop(hDesktop); //�л�����������  

		GetDlgItem(IDOK)->EnableWindow(FALSE); //���ó�ʼ����ťʧЧ��ֻ�����ȼ�����  
		RegisterHotKey(m_hWnd, 1314, MOD_CONTROL, 'Z'); //�����ȼ�Ϊ Alt+Z  
	}

	return;
	CDialog::OnOK();
}


void CVirtualDesktopDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	//ע���ȼ�  
	UnregisterHotKey(m_hWnd, 1314);
	UnregisterHotKey(m_hWnd, 521);

	//�رմ�����explorer  
	if (!IsInitialDesktop)
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessInfo.dwProcessId); //��ȡ���������explorer���  
		if (hProcess)
		{
			TerminateProcess(hProcess, 1); //�������������explorer  
		}
		CloseHandle(hProcess);
	}
	exit(0);
	CDialog::OnClose();
}

//��ʼ�����̳���
void CVirtualDesktopDlg::ToTray(void)
{
	m_nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd = this->m_hWnd;
	m_nid.uID = IDR_MAINFRAME;
	m_nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	m_nid.uCallbackMessage = WM_SHOWTASK;
	//�Զ������Ϣ���� WM_SHOWTASK ͷ�����ж���ΪWM_USER+10
	m_nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	StrCpy(m_nid.szTip, "����ͼ��");//������������ʱ������ʾ������
	Shell_NotifyIcon(NIM_ADD, &m_nid);//�����������ͼ��
}

LRESULT CVirtualDesktopDlg::onShowTask(WPARAM wParam, LPARAM lParam) //wParam���յ���ͼ���ID��lParam���յ���������Ϊ
{
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
		case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա�
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);//�õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();//����һ������ʽ�˵�
									//���Ӳ˵���رա������������ϢWM_DESTROY�������ڣ���
									//���أ��������������
			menu.AppendMenu(MF_STRING, WM_DESTROY, "�˳�");
			//ȷ������ʽ�˵���λ��
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
			//��Դ����
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
		case WM_LBUTTONDBLCLK://˫������Ĵ���
		{
			this->ShowWindow(SW_SHOWNORMAL);//�򵥵���ʾ������
		}
		break;
		case WM_MOUSEMOVE:
		{
			LPPOINT lpoint = new tagPOINT;
			::GetCursorPos(lpoint);//�õ����λ��
			CMenu menu;
			menu.CreatePopupMenu();//����һ������ʽ�˵�
								   //���Ӳ˵���رա������������ϢWM_DESTROY�������ڣ���
								   //���أ��������������
			menu.AppendMenu(MF_STRING, WM_DESTROY, "�˳�");
			menu.AppendMenu(MF_STRING, WM_DESTROY, "��ʾ");
			menu.AppendMenu(MF_STRING, WM_DESTROY, "��ʾ2");
			//ȷ������ʽ�˵���λ��
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
			//��Դ����
			HMENU hmenu = menu.Detach();
			menu.DestroyMenu();
			delete lpoint;
		}
		break;
	}
	return 0;
}
