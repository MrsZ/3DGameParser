#include "stdafx.h"
#include "CNetData.h"
#include <iostream>

CNetData::CNetData()
{

}

//���������׽��ֺ���
void CNetData::bind()
{
	WSADATA data;					//����ṹ�����
	CString name;					//�����������ַ���
	DWORD   ss = MAKEWORD(2, 0);	//ָ���׽��ְ汾
	::WSAStartup(ss, &data);		//��ʼ���׽��ֿ�
	SOCKET t_socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//�����׽���
	sockaddr_in addr;				//�����ַ�ṹ����
	::gethostname((char*)&name, (int)sizeof(name));		//��ȡ������
	hostent *p = ::gethostbyname((char*)&name);			//����������ȡ������ַ
	in_addr *a = (in_addr*)*p->h_addr_list;				//��ñ���IP��ַ
	//USES_CONVERSION;				//�ַ���ת������
	//CString str14 = A2W(::inet_ntoa(a[0]));		//ת���ַ���IP��ַ
	//CString str14;
	//str14.Format("%s", ::inet_ntoa(a[0]));
	std::string str14 = ::inet_ntoa(a[0]);
	addr.sin_family = AF_INET;			//����ַ�ṹ
	addr.sin_port = htons(80);			//ָ�������˿�80
	addr.sin_addr.S_un.S_addr = inet_addr(str14.c_str());//ָ������IP��ַ
	::bind(t_socket, (sockaddr*)&addr, sizeof(addr));	//��������Ϣ���׽���
	::listen(t_socket, 5);			//����
	WSAAsyncSelect(t_socket, this->m_hWnd, WM_SOCK, FD_ACCEPT | FD_READ);
}

void CNetData::sevsend(SOCKET&, char*, int, int)
{

}

void CNetData::sevrecv(SOCKET&, char*, int, int)
{

}

void CNetData::connect()
{

}

void CNetData::send(SOCKET&, char*, int, int)
{

}

void CNetData::recv(SOCKET&, char*, int, int)
{

}

