
// ScreenCaptureDlg.h : header file
//

#pragma once
#include "ScreenUtil.h"
#include <dshow.h>
#pragma comment (lib,"Strmiids")
#pragma comment (lib,"quartz")
#include <uuids.h>
#include <strmif.h>


// CScreenCaptureDlg dialog
class CScreenCaptureDlg : public CDialogEx
{
// Construction
public:
	CScreenCaptureDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREENCAPTURE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CMenu m_Menu;
	CaptureData m_CapData;

private:
	CImage	m_image;
public:
	void SetImage(const CString &strPath);


	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCap();
	afx_msg void OnFull();
	afx_msg void OnCapvideo();

// 	void AVItoBmp(CString strAVIFileName, CString   strBmpDir);
// 	void BMPtoAVI(CString szAVIName, CString strBmpDir);

public://��ͼƬѹ����AVI
	LRESULT OnGraphNotify(WPARAM wParam, LPARAM lParam);

	IMediaControl     *pMediaControl;         //ý�����
	IGraphBuilder     *pGraph;                  //����ͼ��
	IBaseFilter       *pSrc, *pPreview, *pCompress, *pMux;         //������
	IMoniker          *pMoniker;                 //������

	IMediaEventEx     *pEvent;
	IMediaSeeking     *pSeek;

	BOOL              m_Completed;             //ѹ���Ƿ����
	BOOL              m_IsCompressing;         //ѹ���Ƿ����ڽ���
	REFERENCE_TIME    m_TotalTime;             //ѹ����ʱ��

	CString decodeName;							//�����������

												//��ȡ�������б�
	void GetDecodeList();

	//ָ����Ƶ���������Ѻ����֣�Ϊ������һ��Filter
	static IBaseFilter * CreateDecodeDevice(GUID inCategory, const char * inFriendlyName);

	//�����豸���Ѻ����֣�����һ��������豸��Filter
	static IBaseFilter * CreateHardwareFilter(GUID inCategory, const char * inFriendlyName);



	//����Pin
	IPin* FindPin(IBaseFilter *pFilter, PIN_DIRECTION dir);

	CStatic	m_Progress;
	CEdit	m_SourceFile;
	CEdit	m_DesFile;
	CComboBox	m_combodecode;

	afx_msg void OnSelchangeCombo();
	afx_msg void OnSourcebrown();
	afx_msg void OnDesbrown();
	afx_msg void OnStartcompress();

	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCancle();

	int CompressVideo();
};
