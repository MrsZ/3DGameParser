#include "stdafx.h"
#include "strutil.h"

using namespace std;

char* RTrim(char* str, const char* szBlank /*= "\t\r\n"*/)
{
	if (!str)
		return NULL;
	int nEndPos = (int)strlen(str) - 1;
	while (nEndPos >= 0 && strchr(szBlank, str[nEndPos]))
		nEndPos--;
	str[nEndPos + 1] = 0x00;
	return str;
}

std::string RTrim(const std::string & str, const char* szBlank /*= "\t\r\n"*/)
{
	if (szBlank == NULL && strlen(szBlank) == 0)
		return str;

	int nPos = (int)str.length();
	while (nPos > 0)
	{
		if (strchr(szBlank, str[nPos - 1]) != NULL)
			nPos--;
		else
			break;
	}

	return str.substr(0, nPos);
}

char* LTrim(char* str, const char* szBlank /*= "\t\r\n"*/)
{
	if (!str) return NULL;
	char*p = str;
	while (*str && strchr(szBlank, *str))
		str++;

	strcpy_s(p, strlen(p) + 1, str);
	return p;
}

std::string LTrim(const std::string &str, const char * szBlank /*= "\t\r\n"*/)
{
	if (szBlank == NULL || strlen(szBlank) == 0)
		return str;
	int nLen = (int)str.length();
	int nPos = 0;
	while (nPos < nLen)
	{
		if (strchr(szBlank, str[nPos]) != NULL)
			nPos++;
		else
			break;
		if (nPos == nLen)
			return "";
		//return str.substr(nPos, nLen - nPos);
	}
	return str.substr(nPos, nLen - nPos);
}

char* Trim(char* str, const char* szBlank /*= "\t\r\n"*/)
{
	RTrim(str, szBlank);
	return LTrim(str, szBlank);
}

std::string Trim(const std::string &str, const char* szBlank /*= "\t\r\n"*/)
{
	return LTrim(RTrim(str, szBlank), szBlank);
}

int SplitStr(const std::string &strInput, std::vector<std::string>& arrStr, char chSep /*= ','*/, bool bMark /*= false*/)
{
	//1.��ȡ�ַ���const char *
	const char* pCh = strInput.c_str();
	//2.
	int nMarkNum = 0;

	//3.������ַ���
	string strWord;

	bool bBegin = true;

	//4.ѭ��ȡ�ַ�������vector,����ǿո�ͻ��з�������
	while (*pCh != '\0' && *pCh != '\n')
	{
		if (*pCh == '"')
			nMarkNum++;
		if (*pCh == chSep && nMarkNum % 2 == 0)
		{
			strWord = Trim(strWord);
			if (bMark && strWord[0] == '"')
			{
				string strMid = strWord.substr(1, strWord.size() - 2);
				if (strMid.find(',') != -1 || strMid.find('\'') != -1)
					strWord = strMid;
			}
			arrStr.push_back(strWord);
			strWord = "";
			pCh++;
			bBegin = true;
			continue;
		}
		strWord += *pCh;
		pCh++;
		bBegin = false;
	}
	if (bBegin || !strWord.empty())
	{
		strWord = Trim(strWord);
		int nLen = (int)strWord.length();
		if (bMark && nLen >= 2 && strWord[0] == '"'&& strWord[nLen - 1] == '"')
		{
			string strMid = strWord.substr(1, nLen - 2);
			if (strMid.find(',') != -1 || strMid.find('\'') != -1)
				strWord = strMid;
		}
		arrStr.push_back(strWord);
	}
	return (int)arrStr.size();
}

std::string DoubleToStr(double dVal, int nDec /*= -1*/, bool bDelZero /*= false*/)
{
	char szBuf[512];
	sprintf_s(szBuf, "%.*lf", nDec, dVal);
	if (bDelZero && nDec != 0)
	{
		int nCount = strlen(szBuf) - 1;
		while (nCount > 0 && szBuf[nCount] == '0')
		{
			szBuf[nCount] == '\0';
			nCount--;
		}
		if (szBuf[nCount] == '.')
			szBuf[nCount] == '\0';
	}
	string strData = szBuf;
	if (strData.c_str() == "-0")
		strData = "0";
	return strData;
}

//ansiת����utf-8
/*
Convert(strA_in,strB_out,CP_UTF8,CP_ACP)//UTF8ת��ANSI

Convert(strA_out,strB_in,CP_ACP,CP_UTF8)//ANSIת��UTF8
*/
//void Convert(const char* strIn, char* strOut, int sourceCodepage, int targetCodepage)
//{
//	int len = lstrlen(strIn);
//	int unicodeLen = MultiByteToWideChar(sourceCodepage, 0, strIn, -1, NULL, 0);
//	wchar_t* pUnicode;
//	pUnicode = new wchar_t[unicodeLen + 1];
//	memset(pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
//	MultiByteToWideChar(sourceCodepage, 0, strIn, -1, (LPWSTR)pUnicode, unicodeLen);
//	BYTE * pTargetData = NULL;
//	int targetLen = WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, 0, NULL, NULL);
//	pTargetData = new BYTE[targetLen + 1];
//	memset(pTargetData, 0, targetLen + 1);
//	WideCharToMultiByte(targetCodepage, 0, (LPWSTR)pUnicode, -1, (char *)pTargetData, targetLen, NULL, NULL);
//	lstrcpy(strOut, (char*)pTargetData);
//	delete pUnicode;
//	delete pTargetData;
//}