
// ChildView.h : interface of the CChildView class
//


#pragma once
#include <iostream>
#include <vector>
#include <map>


// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:
	void GetSavePath();
// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	struct ColorStruct
	{
		COLORREF myColor;
		std::vector<CPoint> arrPoint;
	};
	CPoint m_OldPoint;
	CPoint m_Point;
	BOOL m_bDraw;
	COLORREF m_Color;
	std::string m_strFilePath;
	std::vector<CPoint> m_arrPoint;		//�洢���Ƶ����߶�
	std::map<int, std::vector<CPoint>> m_mapArrPoint;		//����������������� ,�����������Ӵ���

	std::map<int, std::map<COLORREF, std::vector<CPoint>>> m_mapColorArrPoint;   //�������������ɫ��ͬ����
	std::map<int, ColorStruct> m_mapStruColorPoint;		//�������������ɫ��ͬ����

	int m_nNum; //���ߵĴ���
public:
	afx_msg void OnToolsColor();
	afx_msg void OnToolsSize();
	afx_msg void OnFileSaveWnd();
	afx_msg void OnFileSaveview();
};

