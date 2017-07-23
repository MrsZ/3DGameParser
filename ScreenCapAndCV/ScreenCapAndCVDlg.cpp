
// ScreenCapAndCVDlg.cpp : implementation file
//
#include "stdafx.h"
#include "ScreenCapAndCV.h"
#include "ScreenCapAndCVDlg.h"
#include "afxdialogex.h"

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


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
public:
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


// CScreenCapAndCVDlg dialog



CScreenCapAndCVDlg::CScreenCapAndCVDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCREENCAPANDCV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenCapAndCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenCapAndCVDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_CAPPICACTIVE, &CScreenCapAndCVDlg::OnCappicactive)
	ON_COMMAND(ID_CAPPICDESK, &CScreenCapAndCVDlg::OnCappicdesk)
	ON_COMMAND(ID_CAPVIDEO, &CScreenCapAndCVDlg::OnCapvideo)
	ON_COMMAND(ID_STOPVIDEO, &CScreenCapAndCVDlg::OnStopvideo)
	ON_COMMAND(ID_STARTVDEO, &CScreenCapAndCVDlg::OnStartvdeo)
END_MESSAGE_MAP()


// CScreenCapAndCVDlg message handlers

BOOL CScreenCapAndCVDlg::OnInitDialog()
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
	//���Menu
	m_Menu.LoadMenu(IDR_MENU1);  //  IDR_MENU1Ϊ�����Ĳ˵���ID����Resource��ͼ��Menu�ļ����¿����ҵ�
	SetMenu(&m_Menu);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScreenCapAndCVDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScreenCapAndCVDlg::OnPaint()
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
		//˫������Ʒ���˸
		CPaintDC dc(this); // device context for painting
		CDC MemDC;
		CBitmap   MemBitmap;//����һ��λͼ����
		MemDC.CreateCompatibleDC(NULL);
		if (m_image.IsNull())
			return;
		CRect rect;
		GetClientRect(rect);
		MemBitmap.CreateCompatibleBitmap(GetDC(), rect.Width(), rect.Height());
		CBitmap   *pOldBit = MemDC.SelectObject(&MemBitmap);
		MemDC.FillSolidRect(0, 0, rect.Width(), rect.Height(), RGB(255, 255, 255));

		MemDC.SetStretchBltMode(HALFTONE);
		m_image.StretchBlt(MemDC, rect);

		GetDC()->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
		MemBitmap.DeleteObject();
		MemDC.DeleteDC();
		//CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScreenCapAndCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CScreenCapAndCVDlg::OnCappicactive()
{
	// TODO: Add your command handler code here
	//ShowWindow(SW_HIDE);
	Sleep(500);
	ConfigureCapture(GetSafeHwnd(), &m_CapData);
	m_CapData.bCaptureFullScreen = false;
	CaptureScreen(&m_CapData);
	//ShowWindow(SW_SHOW);

	if (m_CapData.szCaptureFilename[0] != '\0') {
		// In a real application that had interest in the
		// actual image and not just a screen capture
		// we would want to pass the Bitmap/CImage back
		// and forth directly, but for screen capture
		// sample purposes, this works fine.
		CString strPathName(m_CapData.szCapturePath);
		if (strPathName.Right(1) != "\\")
			strPathName += '\\';
		strPathName += m_CapData.szCaptureFilename;
		SetImage(strPathName);
	}
}


//��ȡ����
void CScreenCapAndCVDlg::OnCappicdesk()
{
	// TODO: Add your command handler code here
	ShowWindow(SW_HIDE);
	Sleep(500);
	ConfigureCapture(GetSafeHwnd(), &m_CapData);
	CaptureScreen(&m_CapData);
	ShowWindow(SW_SHOW);

	if (m_CapData.szCaptureFilename[0] != '\0') {
		// In a real application that had interest in the
		// actual image and not just a screen capture
		// we would want to pass the Bitmap/CImage back
		// and forth directly, but for screen capture
		// sample purposes, this works fine.
		CString strPathName(m_CapData.szCapturePath);
		if (strPathName.Right(1) != "\\")
			strPathName += '\\';
		strPathName += m_CapData.szCaptureFilename;
		SetImage(strPathName);
	}
}

//¼����Ļ
void CScreenCapAndCVDlg::OnCapvideo()
{
	// TODO: Add your command handler code here

}

//ֹͣ¼����Ļ���ϳ���Ƶ������
void CScreenCapAndCVDlg::OnStopvideo()
{
	// TODO: Add your command handler code here

}


//������Ƶ
void CScreenCapAndCVDlg::OnStartvdeo()
{
	// TODO: Add your command handler code here
	Mat img = imread("E:\\OpenCV3\\opencv\\sources\\samples\\data\\fruits.jpg");
	imshow("����ͼƬ", img);
	waitKey(5000);
}

//����ͼƬ
void CScreenCapAndCVDlg::SetImage(const CString &strPath)
{
	if (!m_image.IsNull())
		m_image.Destroy();

	HRESULT hr = m_image.Load(strPath);
	if (FAILED(hr)) {
		TRACE("Image Load Failed: %x\n", hr);
	}
	Invalidate();
}