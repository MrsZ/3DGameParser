#pragma once
#include <windows.h>


//��Ϸ��ʼ��
bool Game_Init(HWND hwnd);

//��Ϸ���г���
void Game_Run(HWND hwnd);

//��Ϸ����
void Game_End(HWND hwnd);

//��Ϣ��Ӧ����
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);




