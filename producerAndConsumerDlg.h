
// producerAndConsumerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CproducerAndConsumerDlg �Ի���
class CproducerAndConsumerDlg : public CDialogEx
{
// ����
public:
	CproducerAndConsumerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PRODUCERANDCONSUMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ��Ӧ�������
	CComboBox cmbSituation;
	afx_msg void OnCbnSelchangeCombo1();
	//int BufferCapacity = 0;
	// ������־
	CListBox m_LogList;
	int BufferCapacity;//buffen����
	int ProdNum;//��������
	int ConsNum;//���Ѹ���
	int ProducerNum;//�����߸���
	int ConsumerNum;//�����߸���
	// ���������
	void Situation3();
	afx_msg LRESULT OnResuReceData(WPARAM Wparam,LPARAM Lparam);
	afx_msg void OnBnClickedBtnStart();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
