
// BubbleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Bubble.h"
#include <iostream>
#include "BubbleDlg.h"
#include "afxdialogex.h"

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


// CBubbleDlg dialog



CBubbleDlg::CBubbleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BUBBLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBubbleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

void CBubbleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	//MessageBox(_T("CHN"), _T("CHN"), MB_OK);
	CDialogEx::OnLButtonDown(nFlags, point);
}

void CBubbleDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nHitTest)
	{	// nHitTest==HTCAPTION �����ж�ֱ�ӵ���ȱʡ����
	case HTTOP:
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
		Invalidate(TRUE);
		//m_explorer.Invalidate(TRUE);
		break;
	case HTBOTTOM:
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
		Invalidate(TRUE);
		break;
	case HTLEFT:
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
		Invalidate(TRUE);
		break;
	case HTRIGHT:
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
		Invalidate(TRUE);
		break;
	case HTTOPLEFT:
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
		Invalidate(TRUE);
		break;
	case HTTOPRIGHT:
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
		Invalidate(TRUE);
		break;
	case HTBOTTOMLEFT:
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
		Invalidate(TRUE);
		break;
	case HTBOTTOMRIGHT:
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
		Invalidate(TRUE);
		break;
	}
}

//BOOL CBubbleDlg::PreTranslateMessage(MSG* pMsg)
//{
//	if (pMsg->message == WM_KEYDOWN)
//	{
//		switch (pMsg->wParam)
//		{
//		case VK_DOWN:
//			MessageBox(_T("CHN"), _T("��ʾ"), MB_OK);
//			break;
//		case WM_LBUTTONDOWN:
//			MessageBox(_T("CHN"), _T("��ʾ"), MB_OK);
//			break;
//			OnLButtonDown();
//		default:
//			break;
//		}
//	}
//	return TRUE;
//}

BEGIN_MESSAGE_MAP(CBubbleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_MESSAGE(WM_SHOWTASK, OnShowTask)
END_MESSAGE_MAP()

void CBubbleDlg::ToTray() {

	NOTIFYICONDATA nid;

	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);

	nid.hWnd = this->m_hWnd;

	nid.uID = IDR_MAINFRAME;

	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;

	nid.uCallbackMessage = WM_SHOWTASK;//�Զ������Ϣ����   

	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));

	//strcpy(nid.szTip, const_cast<char*>("��������"));    //��Ϣ��ʾ��  
	//nid.szTip = L"��������";
	std::string strTip = "��������";

	/*
	1�� wchar_t x[128] = L"������";
	2�� wchar_t x[128];
	lstrcpyW(x, L"������");
	3�� wchar_t x[128];
	MultiByteToWideChar(CP_ACP, 0, "������", -1, x, 128);
	*/
	//strcpy(nid.szTip, strTip.c_str());
	MultiByteToWideChar(CP_ACP, 0, "������", -1, nid.szTip, 128);
	Shell_NotifyIcon(NIM_ADD, &nid);    //�����������ͼ��   

	ShowWindow(SW_HIDE);    //����������

}

LRESULT CBubbleDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
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
		menu.AppendMenu(MF_STRING, WM_DESTROY, (LPCTSTR)"�ر�");
		menu.AppendMenu(MF_STRING, WM_DESTROY, (LPCTSTR)"����...");
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

		ShowWindow(SW_SHOWNORMAL);//�򵥵���ʾ���������¶�   SW_SHOW�����

								  // this->SetForegroundWindow(); // �ö���ʾ        
		DeleteTray();
	}
	break;
	default:
		break;
	}
	return 0;
}

void CBubbleDlg::DeleteTray()
{
	NOTIFYICONDATA nid;
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_SHOWTASK;//�Զ������Ϣ����
	nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	//strcpy(nid.szTip, "��������");    //��Ϣ��ʾ��Ϊ���ƻ��������ѡ� 
	/*��wchar�и�ֵ*/
	MultiByteToWideChar(CP_ACP, 0, "��������", -1, nid.szTip, 128);

	Shell_NotifyIcon(NIM_DELETE, &nid);    //��������ɾ��ͼ�� 
}

// CBubbleDlg message handlers

BOOL CBubbleDlg::OnInitDialog()
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
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	//CRgn rgn;
	//rgn.CreateEllipticRgn(0, 0, 196, 196);
	//SetWindowRgn(rgn, TRUE);

	//���ر߿�
	SetWindowLong(this->GetSafeHwnd(), GWL_STYLE, GetWindowLong(this->GetSafeHwnd(), GWL_STYLE) - WS_CAPTION);
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBubbleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		if (nID == SC_MINIMIZE)
			ToTray(); //��С�������̵ĺ���
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBubbleDlg::OnPaint()
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
		//ShowPicture();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBubbleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CBubbleDlg::OnNcHitTest(CPoint point)
{
	//LRESULT nHitTest = CDialog::OnNcHitTest(point);
	//if (nHitTest == HTCLIENT)
	//{
	//	nHitTest = HTCAPTION;
	//}
	//return nHitTest;
	
	// rect ָ����������ʲô�ط�ʱ�������ƶ�����
	// ��ʵ���ǰ��ⲿ�����򵱳��� ������
    CRect rect;
	GetClientRect(rect);
	rect.bottom = rect.top + rect.Height() / 4;
	// point ��ʾ�ĵ����ʾ����Ļ�ĵ�
	// Ҫת���ɴ��ڵĵ����ʹ��     
	::ScreenToClient(this->GetSafeHwnd(), &point);

	UINT nHitTest = CWnd::OnNcHitTest(point);
	return (rect.PtInRect(point)) ? HTCAPTION : nHitTest;
}

void CBubbleDlg::ShowPicture()
{
	CImage img;
	HRESULT result = img.Load(_T("imagemap.png"));

	for (int i = 0; i < img.GetWidth(); i++)
	{
		for (int j = 0; j < img.GetHeight(); j++)
		{
			unsigned char* pucColor = reinterpret_cast<unsigned char *>(img.GetPixelAddress(i, j));
			pucColor[0] = pucColor[0] * pucColor[3] / 255;
			pucColor[1] = pucColor[1] * pucColor[3] / 255;
			pucColor[2] = pucColor[2] * pucColor[3] / 255;
		}
	}

	CDC *pDC = GetWindowDC();
	int nX = img.GetWidth();
	int nY = img.GetHeight();

	img.Draw(pDC->m_hDC, -1800, -1800);
	ReleaseDC(pDC);
}