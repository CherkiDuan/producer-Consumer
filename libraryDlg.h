#pragma once
#include "afxwin.h"


// libraryDlg �Ի���

class libraryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(libraryDlg)

public:
	libraryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~libraryDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CEdit m_Edit;
};
