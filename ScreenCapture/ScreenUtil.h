#pragma once
#include <windef.h>
#include <ShlObj.h>
#include <iostream>
#include <afxstr.h>
#include <tchar.h>

/*
	����Ŀ��
	��ȡ��Ļ�ϣ�Ȼ����ʾ�ڶԻ����ϣ�����ǰ����ʾ�����Ϳ������޼ɵ��ĳ�������
*/

void logs(std::string strMes);

//ͼƬ���浽����
/*virtual */BOOL CaptureLolToDesktop(HWND hWnd);

//��Ļ��ͼ����ʵ��  
/*virtual */HBITMAP ScreenCapture(LPSTR filename, WORD bitCount, LPRECT lpRect);


