// libraryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "producerAndConsumer.h"
#include "libraryDlg.h"
#include "afxdialogex.h"
#include <locale.h>

// libraryDlg �Ի���

IMPLEMENT_DYNAMIC(libraryDlg, CDialogEx)

libraryDlg::libraryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(libraryDlg::IDD, pParent)
{

}

libraryDlg::~libraryDlg()
{
}

void libraryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);
}


BEGIN_MESSAGE_MAP(libraryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &libraryDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// libraryDlg ��Ϣ�������


void libraryDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	setlocale(LC_CTYPE, "chs");
	m_Edit.GetDlgItem(IDC_EDIT1);

	CStdioFile file;
	CString str;
	CString str2;
	if (file.Open(_T("my.txt"), CFile::modeRead))
	{
		while (file.ReadString(str))
		{
			str2 += str + _T("\r\n");
		}
		m_Edit.SetWindowText(str2);

		str.ReleaseBuffer();
	}
	else
	{
		MessageBox(_T("��ʾ"), _T("�ļ���ȡʧ�ܣ�"), MB_OK);
	}
}
