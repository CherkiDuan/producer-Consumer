#pragma once


// LibDlg �Ի���

class LibDlg : public CDialogEx
{
	DECLARE_DYNAMIC(LibDlg)

public:
	LibDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LibDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
