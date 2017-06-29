
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
	//����Ϣ����NCLButtondownʵ���϶�
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
}

//void CBubbleDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
//{
//	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//	switch (nHitTest)
//	{	// nHitTest==HTCAPTION �����ж�ֱ�ӵ���ȱʡ����
//	case HTTOP:
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
//		Invalidate(TRUE);
//		//m_explorer.Invalidate(TRUE);
//		break;
//	case HTBOTTOM:
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
//		Invalidate(TRUE);
//		break;
//	case HTLEFT:
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
//		Invalidate(TRUE);
//		break;
//	case HTRIGHT:
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
//		Invalidate(TRUE);
//		break;
//	case HTTOPLEFT:
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
//		Invalidate(TRUE);
//		break;
//	case HTTOPRIGHT:
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
//		Invalidate(TRUE);
//		break;
//	case HTBOTTOMLEFT:
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
//		Invalidate(TRUE);
//		break;
//	case HTBOTTOMRIGHT:
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, FALSE, NULL, 0);
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
//		SystemParametersInfo(SPI_SETDRAGFULLWINDOWS, TRUE, NULL, 0);
//		Invalidate(TRUE);
//		break;
//	}
//}

/*�Ƿ񿿽���Ļ���Ե*/
BOOL CBubbleDlg::NearLeftBorder()
{
	CRect rc;
	GetWindowRect(rc);
	if (rc.left < 20)
	{
		return TRUE;
	}
	return FALSE;
}

/*�Ƿ񿿽���Ļ�ϱ�Ե*/
BOOL CBubbleDlg::NearUpBorder()
{
	CRect rc;
	GetWindowRect(rc);
	if (rc.top < 20)
	{
		return TRUE;
	}
	return FALSE;
}

/*�Ƿ񿿽���Ļ�ұ�Ե*/
BOOL CBubbleDlg::NearRightBorder()
{
	CRect rc;
	GetWindowRect(rc);
	//Ҫ��ȡ��Ļ��С
	int sysWidth = GetSystemMetrics(SM_CXSCREEN);
	if (rc.right > sysWidth - 20)
	{ 
		return TRUE;
	}
	return FALSE;
}

/*����Ƿ��ڴ�����*/
BOOL CBubbleDlg::MouseInWnd()
{
	CRect rc;
	GetWindowRect(rc);
	POINT pt;
	GetCursorPos(&pt);
	if (PtInRect(&rc, pt))
	{
		return TRUE;
	}
	return FALSE;
}

//�����ƶ�
void CBubbleDlg::MoveUp()
{
	CRect rc;
	GetWindowRect(rc);
	//�����������ƣ���ʾ����  
	if (MouseInWnd())
	{
		int height = rc.Height();
		if (rc.top >= 0)
		{
			rc.top = 0;
		}
		else
		{
				rc.top += 20;
		}
		rc.bottom = rc.top + height;
		MoveWindow(rc);
	}
	//����ڱ𴦣����ھ������Ƴ���Ļ  
	else
	{
		int height = rc.Height();
		//���������ƶ�һ���أ����������(¶20)�Ͳ�����  
		if (rc.top <= 20 - height)
		{
			rc.top = 20 - height;
			//ShowWindow(SW_HIDE);
			//m_upDlg->m_Test360Dlg = this;
			//m_upDlg->DoModal();
		}
		else
		{
			if(rc.top > -148)
				rc.top -= 10;
		}
		if(rc.top > -158)
			rc.bottom = rc.top + height;
		MoveWindow(rc);
	}
}

//�����ƶ�
void CBubbleDlg::MoveLeft()
{
	CRect rc;
	GetWindowRect(rc);
	//�����������ƣ���ʾ����  
	if (MouseInWnd())
	{
		int width = rc.Width();
		if (rc.left >= 0)
		{
			rc.left = 0;
		}
		else
		{
			rc.left += 20;
		}
		rc.right = rc.left + width;
		MoveWindow(rc);
	}
	//����ڱ𴦣����ھ������Ƴ���Ļ  
	else
	{
		int width = rc.Width();
		//���������ƶ�һ���أ����������(¶20)�Ͳ�����  
		if (rc.left <= 20 - width)
		{
			rc.left = 20 - width;
		}
		else
		{
			if (rc.left > -188)
				rc.left -= 10;
		}
		if (rc.left > -198)
			rc.right = rc.left + width;
		MoveWindow(rc);
	}
}

//�����ƶ�
void CBubbleDlg::MoveRight()
{
	CRect rc;
	GetWindowRect(rc);
	int sysWidth = GetSystemMetrics(SM_CXSCREEN);
	//����ڴ������򴰿����ƣ���ʾ����  
	if (MouseInWnd())
	{
		int width = rc.Width();
		if (rc.left <= sysWidth - width)
		{
			rc.left = sysWidth - width;
		}
		else
		{
			rc.left -= 20;
		}
		rc.right = rc.left + width;
		MoveWindow(rc);
	}
	//���û�ڴ����ϣ����ھ������Ƴ���Ļ  
	else
	{
		int width = rc.Width();
		//���������ƶ�һ���أ�����������ˣ�����20���أ��Ͳ�����  
		if (rc.left >= sysWidth - 20)
		{
			rc.left = sysWidth - 20;
		}
		else
		{
			rc.left += 10;
		}
		rc.right = rc.left + width;
		MoveWindow(rc);
	}
}
/*ʱ����Ӧ����*/
void CBubbleDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_MOVE)
	{
		//��갴�ŵģ�����ô�����ƶ�  
		if (GetKeyState(VK_LBUTTON)<0)
		{
			return;
		}
		//������Ļ�ϱ�Ե  
		if (NearUpBorder())
		{
			//������궯�����д��ڵ��ƶ������������������ƽ����ʾ������뿪������ƽ�����أ�  
			MoveUp();
			return;
		}
		//������Ļ���Ե  
		if (NearLeftBorder())
		{
			//������궯�����д��ڵ��ƶ������������������ƽ����ʾ������뿪������ƽ�����أ�  
			MoveLeft();
			return;
		}
		//������Ļ�ұ�Ե  
		if (NearRightBorder())
		{
			//������궯�����д��ڵ��ƶ������������������ƽ����ʾ������뿪������ƽ�����أ�  
			MoveRight();
			return;
		}

		if (MouseInWnd())
		{
			CRect rcBtn;
			rcBtn.MoveToXY(m_nLeft--, m_nTop);
			rcBtn.right = m_nLeft + m_rect.Width();
			rcBtn.bottom = m_nTop + m_rect.Height();
			m_BtnLar.MoveWindow(&rcBtn);
		}
		else
		{
			CRect rcBtn;
			rcBtn.MoveToXY(m_nLeft++, m_nTop);
			rcBtn.right = m_nLeft + m_rect.Width();
			rcBtn.bottom = m_nTop + m_rect.Height();
			m_BtnLar.MoveWindow(&rcBtn);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

BEGIN_MESSAGE_MAP(CBubbleDlg, CDialogEx)
	ON_WM_CREATE()
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
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

int CBubbleDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialogEx::OnCreate(lpCreateStruct) != 0)
		return -1;
	m_BtnLar.Create(_T("HAHA"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), this, IDD_BTN_CIRCLE);
	m_BtnLar.ShowWindow(SW_SHOW);
	m_BtnLar.SetFont(&(afxGlobalData.fontRegular));
	m_BtnLar.SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	//m_BtnLar.SetLayeredWindowAttributes()

	//CRect rect;
	//GetDesktopWindow()->GetWindowRect(rect);
	//SetWindowPos(0, 0, 0, rect.right, rect.bottom, 0);
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

	//��ʼʱ����  
	CenterWindow();

	//���ö�ʱ���������������������ƶ�  
	SetTimer(TIMER_MOVE, 10, NULL);

	GetDlgItem(IDOK)->GetWindowRect(&m_rect);
	ScreenToClient(m_rect);
	m_nLeft = m_rect.left;
	m_nTop = m_rect.top;
	m_BtnLar.MoveWindow(&m_rect);

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