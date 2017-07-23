
// ScreenCaptureDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScreenCapture.h"
#include "ScreenCaptureDlg.h"
#include "afxdialogex.h"
#include "resource.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CM_NOTIFY  WM_USER+1 //�û��Զ�����Ϣ

// #pragma comment(lib,"vfw32") 
// #pragma comment(lib,"winmm")


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


// CScreenCaptureDlg dialog



CScreenCaptureDlg::CScreenCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SCREENCAPTURE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScreenCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCEFILE, m_SourceFile);
	DDX_Control(pDX, IDC_DESFILE, m_DesFile);
	DDX_Control(pDX, IDC_COMBO1, m_combodecode);
}

BEGIN_MESSAGE_MAP(CScreenCaptureDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo)
	ON_BN_CLICKED(IDC_SOURCEBROWN, OnSourcebrown)
	ON_BN_CLICKED(IDC_DESBROWN2, OnDesbrown)
	ON_BN_CLICKED(IDC_STARTCOMPRESS, OnStartcompress)
	ON_BN_CLICKED(IDC_BUTTON5, OnCancle)
	ON_COMMAND(ID_CAP, &CScreenCaptureDlg::OnCap)
	ON_COMMAND(ID_FULL, &CScreenCaptureDlg::OnFull)
	ON_COMMAND(ID_CAPVIDEO, &CScreenCaptureDlg::OnCapvideo)
	ON_MESSAGE(CM_NOTIFY, &CScreenCaptureDlg::OnGraphNotify)
END_MESSAGE_MAP()


// CScreenCaptureDlg message handlers

void CScreenCaptureDlg::SetImage(const CString &strPath)
{
	if (!m_image.IsNull())
		m_image.Destroy();

	HRESULT hr = m_image.Load(strPath);
	if (FAILED(hr)) {
		TRACE("Image Load Failed: %x\n", hr);
	}
	Invalidate();
}

BOOL CScreenCaptureDlg::OnInitDialog()
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

	//SetWindowLong(this->GetSafeHwnd(), GWL_STYLE, GetWindowLong(this->GetSafeHwnd(), GWL_STYLE) - WS_CAPTION);
	SetWindowPos(&this->wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

	GetDecodeList();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CScreenCaptureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScreenCaptureDlg::OnPaint()
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

		//����ͼ��

		// TODO: Add your message handler code here
		/*
			�ƶ�������ͼƬ��˸
			CDC   MemDC;   //���ȶ���һ����ʾ�豸����
			CBitmap   MemBitmap;//����һ��λͼ����
			//���������Ļ��ʾ���ݵ��ڴ���ʾ�豸
			MemDC.CreateCompatibleDC(NULL);
			//��ʱ�����ܻ�ͼ����Ϊû�еط���   ^_^
			//���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С
			MemBitmap.CreateCompatibleBitmap(pDC,nWidth,nHeight);

			//��λͼѡ�뵽�ڴ���ʾ�豸��
			//ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��
			CBitmap   *pOldBit=MemDC.SelectObject(&MemBitmap);
			//���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����
			//��Ҳ�������Լ�Ӧ���õ���ɫ
			MemDC.FillSolidRect(0,0,nWidth,nHeight,RGB(255,255,255));
			//��ͼ
			MemDC.MoveTo(����);
			MemDC.LineTo(����);

			//���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ
			pDC->BitBlt(0,0,nWidth,nHeight,&MemDC,0,0,SRCCOPY);
			//��ͼ��ɺ������
			MemBitmap.DeleteObject();
			MemDC.DeleteDC();
		*/
		// In a real app you would probably want to maintain aspect ratio.
	/*	if (m_image.IsNull())
			return;
		CRect rect;
		GetClientRect(rect);
		dc.SetStretchBltMode(HALFTONE);
		m_image.StretchBlt(dc, rect);*/
		//Invalidate(FALSE);//��˸
	//	CDialogEx::OnPaint();//����Ӱ
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CScreenCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CScreenCaptureDlg::OnCap()
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


void CScreenCaptureDlg::OnFull()
{
	// TODO: Add your command handler code here
}


/*
1�� ѡ��һ��ѹ��������
������ַ�������ѹ����Ƶ������Ƶ�����磺
a�� ����DirectShow������
b�� ��Ƶѹ�������������VCM��
c�� ��Ƶѹ�������������ACM��
d�� DirectXý�����DMOs��
*/

void CScreenCaptureDlg::OnCapvideo()
{
	// TODO: Add your command handler code here
	//¼������ʵ��
	ShowWindow(SW_HIDE);
	for (int i = 0; i < 200; i++)
	{
		Sleep(50);
		ConfigureCapture(GetSafeHwnd(), &m_CapData);
		CaptureScreen(&m_CapData);
	}
	ShowWindow(SW_SHOW);
}

//void CScreenCaptureDlg::AVItoBmp(CString strAVIFileName, CString   strBmpDir)
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������  
//	AVIFileInit();
//	PAVIFILE avi;
//	int res = AVIFileOpen(&avi, strAVIFileName, OF_READ, NULL);
//	int n = GetLastError();
//	if (res != AVIERR_OK)
//	{
//		//an error occures  
//		if (avi != NULL)
//			AVIFileRelease(avi);
//		return;
//	}
//	AVIFILEINFO avi_info;
//	AVIFileInfo(avi, &avi_info, sizeof(AVIFILEINFO));
//	PAVISTREAM pStream;
//	res = AVIFileGetStream(avi, &pStream, streamtypeVIDEO /*video stream*/,
//		0 /*first stream*/);
//	if (res != AVIERR_OK)
//	{
//		if (pStream != NULL)
//			AVIStreamRelease(pStream);
//		AVIFileExit();
//		return;
//	}
//
//	//do some task with the stream  
//	int iNumFrames;
//	int iFirstFrame;
//	iFirstFrame = AVIStreamStart(pStream);
//	if (iFirstFrame == -1)
//	{
//		//Error getteing the frame inside the stream  
//		if (pStream != NULL)
//			AVIStreamRelease(pStream);
//		AVIFileExit();
//		return;
//	}
//	iNumFrames = AVIStreamLength(pStream);
//	if (iNumFrames == -1)
//	{
//		//Error getteing the number of frames inside the stream  
//		if (pStream != NULL)
//			AVIStreamRelease(pStream);
//		AVIFileExit();
//		return;
//	}
//
//	//getting bitmap from frame  
//	BITMAPINFOHEADER bih;
//	ZeroMemory(&bih, sizeof(BITMAPINFOHEADER));
//
//	bih.biBitCount = 24;    //24 bit per pixel  
//	bih.biClrImportant = 0;
//	bih.biClrUsed = 0;
//	bih.biCompression = BI_RGB;
//	bih.biPlanes = 1;
//	bih.biSize = 40;
//	bih.biXPelsPerMeter = 0;
//	bih.biYPelsPerMeter = 0;
//	//calculate total size of RGBQUAD scanlines (DWORD aligned)  
//	bih.biSizeImage = (((bih.biWidth * 3) + 3) & 0xFFFC) * bih.biHeight;
//
//	PGETFRAME pFrame;
//	pFrame = AVIStreamGetFrameOpen(pStream, NULL);
//
//	AVISTREAMINFO streaminfo;
//	AVIStreamInfo(pStream, &streaminfo, sizeof(AVISTREAMINFO));
//
//	//Get the first frame  
//	BITMAPINFOHEADER bih2;
//	long lsize = sizeof(bih2);
//	int index = 0;
//	for (int i = iFirstFrame; i < iNumFrames; i++)
//	{
//		index = i - iFirstFrame;
//		BYTE* pDIB = (BYTE*)AVIStreamGetFrame(pFrame, index);                   //  
//		AVIStreamReadFormat(pStream, index, &bih2, &lsize);
//		BITMAPFILEHEADER stFileHdr;
//
//
//		BYTE* Bits = new BYTE[bih2.biSizeImage];
//		AVIStreamRead(pStream, index, 1, Bits, bih2.biSizeImage, NULL, NULL);
//		//RtlMoveMemory(Bits, pDIB + sizeof(BITMAPINFOHEADER), bih2.biSizeImage);  
//
//		bih2.biClrUsed = 0;
//		stFileHdr.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
//		stFileHdr.bfSize = sizeof(BITMAPFILEHEADER);
//		stFileHdr.bfType = 0x4d42;
//
//		CString FileName;
//		FileName.Format("Frame-%05d.bmp", index);
//		CString strtemp = strBmpDir;
//		strtemp += "\\";
//		strtemp += FileName;
//		FILE* fp = _tfopen(strtemp, _T("wb"));
//		fwrite(&stFileHdr, 1, sizeof(BITMAPFILEHEADER), fp);
//		fwrite(&bih2, 1, sizeof(BITMAPINFOHEADER), fp);
//		int ff = fwrite(Bits, 1, bih2.biSizeImage, fp);
//		int e = GetLastError();
//		fclose(fp);
//		/////  
//		delete Bits;
//		//CreateFromPackedDIBPointer(pDIB, index);  
//	}
//
//	AVIStreamGetFrameClose(pFrame);
//
//	//close the stream after finishing the task  
//	if (pStream != NULL)
//		AVIStreamRelease(pStream);
//
//	AVIFileExit();
//}
//
//void CScreenCaptureDlg::BMPtoAVI(CString szAVIName, CString strBmpDir)
//{
//	CFileFind finder;
//	strBmpDir += _T("\\*.*");
//	AVIFileInit();
//	AVISTREAMINFO strhdr;
//	PAVIFILE pfile;
//	PAVISTREAM ps;
//	int nFrames = 0;
//	HRESULT hr;
//
//	BOOL bFind = finder.FindFile(strBmpDir);
//	while (bFind)
//	{
//		bFind = finder.FindNextFile();
//		if (!finder.IsDots() && !finder.IsDirectory())
//		{
//			CString str = finder.GetFilePath();
//			FILE *fp = fopen(str, "rb");
//			BITMAPFILEHEADER bmpFileHdr;
//			BITMAPINFOHEADER bmpInfoHdr;
//			fseek(fp, 0, SEEK_SET);
//			fread(&bmpFileHdr, sizeof(BITMAPFILEHEADER), 1, fp);
//			fread(&bmpInfoHdr, sizeof(BITMAPINFOHEADER), 1, fp);
//
//			BYTE *tmp_buf = NULL;
//			if (nFrames == 0)
//			{
//				AVIFileOpen(&pfile, szAviName, OF_WRITE | OF_CREATE, NULL);
//				_fmemset(&strhdr, 0, sizeof(strhdr));
//				strhdr.fccType = streamtypeVIDEO;// stream type  
//				strhdr.fccHandler = 0;
//				strhdr.dwScale = 1;
//				strhdr.dwRate = 15;                 // 15 fps  
//				strhdr.dwSuggestedBufferSize = bmpInfoHdr.biSizeImage;
//				SetRect(&strhdr.rcFrame, 0, 0, bmpInfoHdr.biWidth, bmpInfoHdr.biHeight);
//
//				// And create the stream;  
//				hr = AVIFileCreateStream(pfile, &ps, &strhdr);
//				// hr = AVIStreamSetFormat(ps,nFrames,&bmpInfoHdr,sizeof(bmpInfoHdr));  
//			}
//			tmp_buf = new BYTE[bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 3];
//			fread(tmp_buf, 1, bmpInfoHdr.biWidth * bmpInfoHdr.biHeight * 3, fp);
//			hr = AVIStreamSetFormat(ps, nFrames, &bmpInfoHdr, sizeof(bmpInfoHdr));
//			hr = AVIStreamWrite(ps,       // stream pointer  
//				nFrames,                          // time of this frame  
//				1,                         // number to write  
//				(LPBYTE)tmp_buf,
//				bmpInfoHdr.biSizeImage, // size of this frame  
//				AVIIF_KEYFRAME,                    // flags....  
//				NULL,
//				NULL);
//
//			nFrames++;
//			fclose(fp);
//
//		}
//	}
//
//	AVIStreamClose(ps);
//
//	if (pfile != NULL)
//		AVIFileRelease(pfile);
//
//	AVIFileExit();
//}

//һ��jpg��bmp����ת��
///*********************************
//format:bmpתΪjpg�� formatΪimage/jpeg,jpgתΪbmp,formatΪimage/bmp
//strDstΪ����ת�������ͼƬ·��
//strSrcΪԭ��ͼƬ��·��
//**********************************/
//BOOL ConvertPic(const WCHAR *format, const CString &strDst, const CString &strSrc)
//{
//	BOOL bConvert = false;
//	CLSID clsid;
//	int nRet = 0;
//	nRet = GetEncoderClsid(format, &clsid);  //�õ�CLSID
//	USES_CONVERSION;
//	if (nRet >= 0)
//	{
//		Image image(A2W(strSrc));
//		image.Save(A2W(strDst), &clsid, NULL);
//		bConvert = true;
//	}
//	return bConvert;
//}
//����GetEncoderClsid�������£�
///*****************************************************
//����ֵΪ-1��ʾʧ�ܣ�����Ϊ�ɹ�
//******************************************************/
//int GetEncoderClsid(const WCHAR *format, CLSID *pClsid)
//{
//	int nRet = -1;
//	ImageCodecInfo * pCodecInfo = NULL;
//	UINT nNum = 0, nSize = 0;
//	GetImageEncodersSize(&nNum, &nSize);
//	if (nSize < 0)
//	{
//		return nRet;
//	}
//	pCodecInfo = new ImageCodecInfo[nSize];
//	if (pCodecInfo == NULL)
//	{
//		return nRet;
//	}
//	GetImageEncoders(nNum, nSize, pCodecInfo);
//	for (UINT i = 0; i < nNum; i++)
//	{
//		if (wcscmp(pCodecInfo[i].MimeType, format) == 0)
//		{
//			*pClsid = pCodecInfo[i].Clsid;
//			nRet = i;
//
//			delete[] pCodecInfo;
//			return nRet;
//		}
//		else
//		{
//			continue;
//		}
//	}
//	delete[] pCodecInfo;
//	return nRet;
//}
//bmpת��Ϊjpg
//ConvertPic(L"image/jpeg", "c:\\1.jpg", "c:\\1.bmp")
//jpgת��Ϊbmp
//ConvertPic(L"image/bmp", "c:\\1.bmp", "c:\\1.jpg")
//
//����bmpͼƬ�ϲ�
//BOOL CombinePic(const WCHAR *format, const CString &strDst, const CString &strPic1, \
//	const CString &strPic2)
//{
//	BOOL bCombine = false;
//	int nRet = 0;
//	CLSID clsid;
//	nRet = GetEncoderClsid(format, &clsid);
//	if (nRet >= 0)
//	{
//		USES_CONVERSION;
//		Bitmap bmp1(A2W(strPic1));
//		Bitmap bmp2(A2W(strPic2));
//
//		int nWidth = 0, nHeight = 0;
//		nWidth = bmp1.GetWidth();   //������ͼƬ��Сͬ
//		nHeight = bmp1.GetHeight();
//		Bitmap bmpCombine(2 * nWidth, nHeight);  //�߲��䣬��*2��ˮƽ�ϲ�
//		Graphics * pG = NULL;
//		pG = Graphics::FromImage(&bmpCombine);
//		if (pG != NULL)
//		{
//			pG->DrawImage(&bmp1, 0, 0);
//			pG->DrawImage(&bmp2, nWidth, 0);
//			bmpCombine.Save(A2W(strDst), &clsid, NULL);
//		}
//	}
//	return bCombine;
//}
//���ӣ�
//CombinePic(L"image/bmp", "12.bmp", "1.bmp", "2.bmp");

//
//����png�����һ��
//���Բ������κ��������豸
////����һ��λͼ,��������ϳɺ��ͼ��
//Gdiplus::Bitmap* pBitmap = new Bitmap(�ϳɺ���, �ϳɺ�߶�, PixelFormat32bppARGB);
//Gdiplus::Graphics g(pBitmap);
//
//Gdiplus::Bitmap tmp1(L"c:\\001.png");//������Ҫ�ϲ���PNG
//g.DrawImage(&tmp1, .....);
//
//Gdiplus::Bitmap tmp2(L"c:\\002.png");//������Ҫ�ϲ���PNG
//g.DrawImage(&tmp2, .....);
//
//pBitmap->Save(....);//����ϲ����ͼ��,�깤��

//��ȡ��Ƶ�ɼ��豸�б�
void CScreenCaptureDlg::GetDecodeList()
{
	// ��ʼ��COM  
	HRESULT hr = CoInitialize(NULL);
	ICreateDevEnum *pSysDevEnum = NULL;
	//ʹ��CoCreateInstance��������ϵͳö�����������,�����ICreateDevEnum�ӿ�;
	hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC_SERVER,
		IID_ICreateDevEnum, (void**)&pSysDevEnum);
	if (FAILED(hr))
	{
		return;
	}
	//ʹ�ýӿڷ���ICreateDevEnum::CreateClassEnumeratorΪָ����Filterע������Ŀ¼
	//����һ��ö����,�����IEnumMoniker�ӿ�;
	IEnumMoniker *pEnumCat = NULL;
	hr = pSysDevEnum->CreateClassEnumerator(CLSID_VideoCompressorCategory,
		&pEnumCat, 0);
	if (hr == S_OK)
	{
		//ö������
		IMoniker *pMoniker = NULL;
		ULONG cFetched;
		while (pEnumCat->Next(1, &pMoniker, &cFetched) == S_OK)
		{
			if (pMoniker)
			{
				WCHAR * wzDisplayName = NULL;
				IPropertyBag *pPropBag;
				IBaseFilter *pFilter = NULL;

				//��ȡ��ǰ�豸����ʾ����
				//hr = pMoniker->GetDisplayName(NULL,NULL,&wzDisplayName);
				//����IMoniker::BindToStorage֮��,���Է����豸��ʶ�����Լ�,
				//����õ�Display Name,Friendly Name��;
				hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
					(void **)&pPropBag);
				if (SUCCEEDED(hr))
				{
					//���Filter��FriendlyName
					VARIANT varName;
					VariantInit(&varName);
					hr = pPropBag->Read(L"FriendlyName", &varName, NULL);

					if (SUCCEEDED(hr))
					{
						//����IMoniker::BindToOject���Խ��豸��ʶ����һ��DirectShow Filter,
						//������IFilterGraph::AddFilter,����֮���뵽FilterGraph�оͿ��Բ��빤����
						//����һ��filter�󶨵��豸�ϡ�
						hr = pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pFilter);
					}
					if (SUCCEEDED(hr))
					{
						m_combodecode.AddString(CString(varName.bstrVal));
					}
					//�ͷ�ʹ�ù��Ľӿ�
					if (pFilter)
					{
						pFilter->Release();
						pFilter = NULL;
					}
				}
				pPropBag->Release();
			}
			pMoniker->Release();
		}
		pEnumCat->Release();
	}
	pSysDevEnum->Release();
}

//ָ������������Ѻ����֣�Ϊ������һ��Filter
IBaseFilter * CScreenCaptureDlg::CreateDecodeDevice(GUID inCategory, const char * inFriendlyName)
{
	return CreateHardwareFilter(inCategory, inFriendlyName);
}

//�����豸���Ѻ����֣�����һ��������豸��Filter
IBaseFilter * CScreenCaptureDlg::CreateHardwareFilter(GUID inCategory, const char * inFriendlyName)
{
	//����һ��ϵͳö���������
	ICreateDevEnum * enumHardware = NULL;
	HRESULT hr = CoCreateInstance(CLSID_SystemDeviceEnum, NULL, CLSCTX_ALL,
		IID_ICreateDevEnum, (void**)&enumHardware);
	if (FAILED(hr))
	{
		return NULL;
	}

	IBaseFilter * hardwareFilter = NULL;
	IEnumMoniker * enumMoniker = NULL;
	//Ϊָ����Ŀ¼����ö����
	hr = enumHardware->CreateClassEnumerator(inCategory, &enumMoniker, 0);
	if (enumMoniker)
	{
		enumMoniker->Reset();

		ULONG	fetched = 0;
		IMoniker * moniker = NULL;
		char friendlyName[256];

		//ö�ٵõ���Ŀ¼�����е��豸�������������ƥ��
		while (!hardwareFilter && SUCCEEDED(enumMoniker->Next(1, &moniker,
			&fetched)) && fetched)
		{
			if (moniker)
			{
				IPropertyBag * propertyBag = NULL;
				VARIANT		name;
				friendlyName[0] = 0;
				//����IMoniker::BindToStorage֮��,���Է����豸��ʶ�����Լ�
				hr = moniker->BindToStorage(0, 0, IID_IPropertyBag, (void**)&propertyBag);
				//��ȡ�豸���Ѻ�����
				if (SUCCEEDED(hr))
				{
					name.vt = VT_BSTR;
					hr = propertyBag->Read(L"Friendlyname", &name, NULL);
				}
				if (SUCCEEDED(hr))
				{
					WideCharToMultiByte(CP_ACP, 0, name.bstrVal, -1,
						friendlyName, 256, NULL, NULL);
					//�����ǰ�豸���Ѻ��������û�ָ�����豸������ͬ��
					//�򽫵�ǰ�豸��ʶ��ΪFilter��ʽ
					if (strcmp(friendlyName, inFriendlyName) == 0)
					{
						moniker->BindToObject(0, 0, IID_IBaseFilter,
							(void**)&hardwareFilter);
					}
				}
				//�ͷ�ʹ�ù��Ľӿ�
				if (propertyBag)
				{
					propertyBag->Release();
					propertyBag = NULL;
				}
				moniker->Release();
			}
		}
		enumMoniker->Release();
	}
	enumHardware->Release();

	return hardwareFilter;
}


//��������
IPin* CScreenCaptureDlg::FindPin(IBaseFilter *pFilter, PIN_DIRECTION dir)
{
	IEnumPins* pEnumPins;
	IPin* pOutpin;
	PIN_DIRECTION pDir;
	pFilter->EnumPins(&pEnumPins);
	while (pEnumPins->Next(1, &pOutpin, NULL) == S_OK)
	{
		pOutpin->QueryDirection(&pDir);
		if (pDir == dir)
		{
			return pOutpin;
		}
	}
	return 0;
}

void CScreenCaptureDlg::OnSelchangeCombo()
{
	m_combodecode.GetLBText(m_combodecode.GetCurSel(), decodeName);
}

void CScreenCaptureDlg::OnSourcebrown()
{
	// TODO: Add your control notification handler code here
	CFileDialog fDlg(TRUE, "", "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "AVI�ļ�|*.avi|all|*.*||");
	if (fDlg.DoModal() == IDOK)
	{
		CString strFile = fDlg.GetPathName();
		m_SourceFile.SetWindowText(strFile);
	}
}

void CScreenCaptureDlg::OnDesbrown()
{
	// TODO: Add your control notification handler code here
	CFileDialog fDlg(FALSE, "avi", "one", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "AVI�ļ�|*.avi");
	CString strFile;

	if (fDlg.DoModal() == IDOK)
	{
		strFile = fDlg.GetPathName();
		DeleteFile(strFile);		//����ļ����ڣ�����ɾ���ļ�
		m_DesFile.SetWindowText(strFile);
	}
}

void CScreenCaptureDlg::OnStartcompress()
{
	// TODO: Add your control notification handler code here
	CString srcFile, dstFile;
	m_SourceFile.GetWindowText(srcFile);
	m_DesFile.GetWindowText(dstFile);

	if (srcFile.IsEmpty() || dstFile.IsEmpty())
	{
		MessageBox("Դ�ļ���Ŀ���ļ�����Ϊ��!", "��ʾ");
		return;
	}
	if (srcFile == dstFile)
	{
		MessageBox("Դ�ļ���Ŀ���ļ�������ͬ!", "��ʾ");
		return;
	}

	ICaptureGraphBuilder2 * pBuilder = NULL;
	pGraph = NULL;

	pMediaControl = NULL;
	pCompress = NULL;

	//��һ�������� ICaptureGraphBuilder2�ӿ�
	CoCreateInstance(CLSID_CaptureGraphBuilder2, 0, CLSCTX_INPROC_SERVER,
		IID_ICaptureGraphBuilder2, (void**)&pBuilder);
	//�ڶ���������IGraphBuilder�ӿ�
	CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER,
		IID_IGraphBuilder, (void **)&pGraph);

	//������������ICaptureBuilder��SetFilterGraph������FilterGraph���뵽Builder��
	pBuilder->SetFiltergraph(pGraph);
	//��ѯ�����ӿڣ��õ�ý����ƽӿڣ��ýӿڿ�������Graph״̬��
	pGraph->QueryInterface(IID_IMediaControl, (void**)&pMediaControl);

	//ʹ��Capture Graph Builder����������ͼ��
	//a�� ����������Ⱦ�Ĺ���ͼ�Σ�������AVI Mux ��������File Writer��������
	//����һ����������ʵ��������IMoniker::BindToObject�����������᷵��һ��IBaseFilter�ӿ�ָ��
	pBuilder->SetOutputFileName(&MEDIASUBTYPE_Avi,			//�ļ�����
		dstFile.AllocSysString(),	//�ļ���
		&pMux,						// �õ�һ��ָ��multiplexer��ָ��
		NULL);						// �õ�һ��ָ��File Write��ָ��
									//b�� ���Դ��������ѹ����������
									//����IgraphBuilder::AddSourceFilter����������첽�ļ�Դ������
	pGraph->AddSourceFilter(srcFile.AllocSysString(), L"Source Filter", &pSrc);

	if (decodeName.IsEmpty())
	{
		MessageBox("��ѡ��������!", "��ʾ");
		return;
	}

	pCompress = CreateDecodeDevice(CLSID_VideoCompressorCategory, decodeName);

	if (pCompress == NULL)
	{
		MessageBox("û�з��ָ�ѹ����!", "��ʾ", MB_ICONASTERISK);
		return;
	}

	//b�� ���Դ��������ѹ����������
	//����IfilterGraph::AddFilter�����������Ƶѹ��������
	pGraph->AddFilter(pCompress, L"Compressor");

	IPin* pCompressIn, *pCompressOut;
	// Ѱ��֧�� IAMVideoCompression������
	pCompressIn = FindPin(pCompress, PINDIR_INPUT);
	pCompressOut = FindPin(pCompress, PINDIR_OUTPUT);

	IAMVideoCompression * pAMCompress;
	pCompressOut->QueryInterface(IID_IAMVideoCompression, (void**)&pAMCompress);
	HRESULT hret;
	//����IAMVideoCompression::get_KeyFrameRate�������õ��ؼ�������ʣ�
	//����IAMVideoCompression::put_KeyFrameRate�����������ʡ�
	hret = pAMCompress->put_KeyFrameRate(8);

	//c�� ����Դ��������MUX ������
	//ʹ��IcaptureGraphBuilder2::RenderStream����������Դ��������������ŵ�ָ���Ĺ�������
	pBuilder->RenderStream(NULL, NULL, pSrc, pCompress, pMux);
	HRESULT hr = pMux->QueryInterface(IID_IMediaSeeking, (void**)&pSeek);

	pGraph->QueryInterface(IID_IMediaEventEx, (void **)&pEvent);
	hret = pEvent->SetNotifyWindow((OAHWND)m_hWnd, CM_NOTIFY, 0);

	pMediaControl->Run();
	m_IsCompressing = TRUE;
}

void CScreenCaptureDlg::OnCancle()
{
	// TODO: Add your control notification handler code here

}

int CScreenCaptureDlg::CompressVideo()
{
	IGraphBuilder *pGraph = NULL;          // ͼ��������ӿ�
	IMediaControl *pControl = NULL;        // ý��������ӿ�
	IMediaEvent *pEvent = NULL;           // ý���¼��ӿ�

		// ��ʼ��com��
	HRESULT hr = CoInitialize(NULL);
	if (FAILED(hr))
	{
		printf("��ʼ��com���ʧ��\n");
		return -1;
	}

	// �����˲������������
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&pGraph);
	if (FAILED(hr))
	{
		printf("��ʼ��com���ʧ��\n");
		return -1;
	}

	//��ѯý����ƺ�ý���¼��ӿ�
	hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
	hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

	//��������,�����û����Ը��Ĵ����ŵ��ļ�������
	hr = pGraph->RenderFile(L"E:\\DXSDK\\DXSDK 9.0B\\Samples\\Media\\ruby.avi", NULL);
	if (SUCCEEDED(hr))
	{
		//��������
		hr = pControl->Run();
		if (SUCCEEDED(hr))
		{
			//�ȴ��طŽ���
			long evCode;
			pEvent->WaitForCompletion(INFINITE, &evCode);
			// �мǣ���ʵ��Ӧ���У�����ʹ��INFINITE��ʶ����Ϊ���᲻ȷ������������
		}
	}

	// �ͷ�������Դ
	pControl->Release();
	pEvent->Release();
	pGraph->Release();
	CoUninitialize();
	printf("this is example\n");
	return 0;
}

LRESULT CScreenCaptureDlg::OnGraphNotify(WPARAM wParam, LPARAM lParam)
{
	if (pEvent)
	{
		LONG eventcode = 0, param1 = 0, param2 = 0;
		while (SUCCEEDED(pEvent->GetEvent(&eventcode, &param1, &param2, 0)))
		{
			pEvent->FreeEventParams(eventcode, param1, param2);
			switch (eventcode)
			{
			case EC_COMPLETE:
			{
				m_Completed = TRUE;
				m_IsCompressing = FALSE;
				pMediaControl->Stop();
				pMediaControl->Release();

				MessageBox("ѹ�����!", "��ʾ");
				break;
			}
			}
		}
		return S_OK;
	}
	return S_OK;
}

void CScreenCaptureDlg::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);
}