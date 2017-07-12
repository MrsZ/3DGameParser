#include "ScreenUtil.h"
#include <windows.h>
#include "stdafx.h"
#include <iostream>

void logs(std::string strMes)
{
	MessageBox(NULL, _T(strMes.c_str()), _T("��ʾ"), MB_OK);
}


//��Ļ��ͼ����ʵ��  
/*virtual */HBITMAP ScreenCapture(LPSTR filename, WORD bitCount, LPRECT lpRect)
{
	HBITMAP hBitmap;
	HDC hScreenDC = CreateDCA("DISPLAY", NULL, NULL, NULL);   //ͨ��ָ��DISPLAY����ȡһ����ʾ�豸�����Ļ���  
	HDC hmemDC = CreateCompatibleDC(hScreenDC);            //�ú�������һ����ָ���豸���ݵ��ڴ��豸�����Ļ�����DC��  
	int ScreenWidth = GetDeviceCaps(hScreenDC, HORZRES);    //��ȡָ���豸�����ܲ������˴���ȡ��Ļ��ȣ�  
	int ScreenHeight = GetDeviceCaps(hScreenDC, VERTRES);   //��ȡָ���豸�����ܲ������˴���ȡ��Ļ�߶ȣ�  
	HBITMAP hOldBM;
	PVOID lpData;   //�ڴ����ɹ����ص�ָ���������ڴ����׵�ַָ��  
	int startX;     //��ͼxλ��  
	int startY;     //��ͼyλ��  
	int width;      //��ͼ���  
	int height;     //��ͼ�߶�  
	long BitmapSize;
	DWORD BitsOffset;
	DWORD ImageSize;
	DWORD FileSize;
	BITMAPINFOHEADER bmInfo; //BITMAPINFOHEADER�ṹ�������ĳ�Ա������ͼ��ĳߴ硢ԭʼ�豸����ɫ��ʽ���Լ�����ѹ������  
	BITMAPFILEHEADER bmFileHeader;
	HANDLE bmFile, hpal, holdpal = NULL;;
	DWORD dwWritten;
	if (lpRect == NULL)
	{
		startX = startY = 0;
		width = ScreenWidth;
		height = ScreenHeight;
	}
	else
	{
		startX = lpRect->left;
		startY = lpRect->top;
		width = lpRect->right - lpRect->left;
		height = lpRect->bottom - lpRect->top;
	}
	//����һ�ų�width����height�Ļ��������ں������ͼ��  
	hBitmap = CreateCompatibleBitmap(hScreenDC, width, height);
	//�ú���ѡ��һ����ָ�����豸�����Ļ����У����¶����滻��ǰ����ͬ���͵Ķ���  
	hOldBM = (HBITMAP)SelectObject(hmemDC, hBitmap);
	//�ú�����ָ����Դ�豸���������е����ؽ���λ�飨bit_block��ת�����Դ��͵�Ŀ���豸������  
	BitBlt(hmemDC, 0, 0, width, height, hScreenDC, startX, startY, SRCCOPY);
	hBitmap = (HBITMAP)SelectObject(hmemDC, hOldBM);
	if (filename == NULL)
	{
		DeleteDC(hScreenDC);
		DeleteDC(hmemDC);
		return hBitmap;
	}
	BitmapSize = ((((width * 32) + 32) / 32) * 4)*height;
	//������ָ���Ķ��Ϸ����ڴ棬���ҷ������ڴ治���ƶ�(HEAP_NO_SERIALIZE ��ʹ��������ȡ)  
	lpData = HeapAlloc(GetProcessHeap(), HEAP_NO_SERIALIZE, BitmapSize);
	ZeroMemory(lpData, BitmapSize);
	ZeroMemory(&bmInfo, sizeof(BITMAPINFOHEADER));
	bmInfo.biSize = sizeof(BITMAPINFOHEADER); //λͼ��Ϣ�ṹ���� ,����Ϊ40  
	bmInfo.biWidth = width;                   //ͼ���� ��λ������  
	bmInfo.biHeight = height;                 //ͼ��߶� ��λ������  
	bmInfo.biPlanes = 1;                      //����Ϊ1  
	bmInfo.biBitCount = bitCount;             //����ͼ���λ��������8λ��16λ��32λλ��Խ�߷ֱ���Խ��  
	bmInfo.biCompression = BI_RGB;            //λͼ�Ƿ�ѹ�� BI_RGBΪ��ѹ��  
	ZeroMemory(&bmFileHeader, sizeof(BITMAPFILEHEADER));
	BitsOffset = sizeof(BITMAPFILEHEADER) + bmInfo.biSize;
	ImageSize = ((((bmInfo.biWidth*bmInfo.biBitCount) + 31) / 32) * 4)*bmInfo.biHeight;
	FileSize = BitsOffset + ImageSize;
	bmFileHeader.bfType = 0x4d42;//'B'+('M'<<8);  
	bmFileHeader.bfSize = FileSize;
	bmFileHeader.bfOffBits = BitsOffset;
	hpal = GetStockObject(DEFAULT_PALETTE);
	if (hpal)
	{
		holdpal = SelectPalette(hmemDC, (HPALETTE)hpal, false);
		RealizePalette(hmemDC);
	}
	GetDIBits(hmemDC, hBitmap, 0, bmInfo.biHeight, lpData, (BITMAPINFO *)&bmInfo, DIB_RGB_COLORS);
	if (holdpal)
	{
		SelectPalette(hmemDC, (HPALETTE)holdpal, true);
		RealizePalette(hmemDC);
	}
	bmFile = CreateFileA(filename, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (bmFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "Create File Error!", "��ʾ", MB_OK | MB_ICONWARNING);
	}
	WriteFile(bmFile, &bmFileHeader, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	WriteFile(bmFile, &bmInfo, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	WriteFile(bmFile, lpData, ImageSize, &dwWritten, NULL);
	CloseHandle(bmFile);
	HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, lpData);
	::ReleaseDC(0, hScreenDC);
	DeleteDC(hmemDC);
	//logs->WriteFormat("����ͼ����ɹ���");
	logs("����ͼ����ɹ���");
	//MessageBoxA(NULL,"������ã���ı�����Ϸս���Ѿ�ͨ����ͼ����������","��ʾ",MB_OK);  
	return hBitmap;
}

//�ѽ�ͼ���ļ����浽����  
/*virtual */BOOL CaptureLolToDesktop(HWND hWnd)
{
	Sleep(1 * 1000);
	LPRECT lprc = new RECT;
	GetWindowRect(hWnd, lprc);
	//std::string strTime;
	CString strTime;
	DWORD llocaltime = GetTickCount();
	char chDesktopPath[MAX_PATH] = { 0 };
	SHGetSpecialFolderPathA(NULL, chDesktopPath, CSIDL_DESKTOP, 0);//��ȡ��ǰ�û�����·��
	strTime.Format("%s\\��ͼ%ld.jpg", chDesktopPath, llocaltime);
	
	//CString - > string
	//char ch[2048] = "";
	//sprintf(ch, "%s", strFilePath.c_str());
	//int num = MultiByteToWideChar(0, 0, ch, -1, NULL, 0);
	//wchar_t *lpstr1 = new wchar_t[num];
	//MultiByteToWideChar(0, 0, ch, -1, lpstr1, num);
	char chStrTime[2048] = "";
	sprintf(chStrTime, "%s", strTime);
	std::string strTimeS = chStrTime;

	//logs->WriteFormat("��ͼ����·��Ϊ%s", strTime.c_str());
	CString strDirection;
	strDirection.Format("��ͼ����·��Ϊ%s", strTimeS.c_str());
	//char ch[2048] = "";
	//sprintf(ch, "%s", strFilePath.c_str());
	//int num = MultiByteToWideChar(0, 0, ch, -1, NULL, 0);
	//wchar_t *lpstr1 = new wchar_t[num];
	//MultiByteToWideChar(0, 0, ch, -1, lpstr1, num);

	//CString - > string
	char chStr[2048] = "";
	sprintf(chStr, "%s", strDirection);
	std::string strDir = chStr;
	logs(strDir);
	ScreenCapture(LPSTR(strTimeS.c_str()), 16, lprc);
	delete lprc;
	return TRUE;
}