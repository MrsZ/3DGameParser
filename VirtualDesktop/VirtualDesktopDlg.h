
// VirtualDesktopDlg.h : header file
//

#pragma once

#define  WM_SHOWTASK  WM_USER+100		//������Ϣ


// CVirtualDesktopDlg dialog
class CVirtualDesktopDlg : public CDialogEx
{
// Construction
public:
	CVirtualDesktopDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIRTUALDESKTOP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	PROCESS_INFORMATION ProcessInfo;
	STARTUPINFO StartupInfo;
	HDESK hDesktop;
	HDESK hOriginalThread;
	HDESK hOriginalInput;
	//Desktop m_desk;
	BOOL IsOriginalDesktopActive; //�Ƿ���ԭʼ����rz  
	BOOL IsInitialDesktop; //�Ƿ��ʼ�����棬��ֹ��ɫ��ť������ɲ��ɹ��Ƶĺ��  
	BOOL IsWindowShow; //�����Ƿ�ɼ�  


protected:
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);//�Զ����ȼ���Ϣ  
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();

public:
	//���� ���̽ṹ��ı���
	NOTIFYICONDATA m_nid;
	//��ʼ�����������ĺ���
	void ToTray(void);
	//���̵���Ϣ������
	LRESULT onShowTask(WPARAM wParam, LPARAM lParam);
};
