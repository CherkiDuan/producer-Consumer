
// producerAndConsumerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <list> 

typedef struct ParamInfo{
	int id;
	int speed;
	HWND m_hWnd;
}ParamInfo;


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
	void initEditToZero();
	//int BufferCapacity = 0;
	// ������־
	CListBox m_LogList;
	int BufferCapacity;//buffen����
	int ProdNum;//��������
	int ConsNum;//���Ѹ���
	int ProducerNum;//�����߸���
	int ConsumerNum;//�����߸���
	// ���������
	//void Situation3();
	afx_msg LRESULT OnResuReceData(WPARAM Wparam,LPARAM Lparam);
	afx_msg LRESULT showNumberOfP(WPARAM Wparam, LPARAM Lparam);
	afx_msg LRESULT showNumberOfC(WPARAM Wparam, LPARAM Lparam);
	afx_msg LRESULT showBuffer1Content(WPARAM Wparam, LPARAM Lparam);
	afx_msg LRESULT showBuffer2Content(WPARAM Wparam, LPARAM Lparam);
	afx_msg LRESULT showBuffer3Content(WPARAM Wparam, LPARAM Lparam);
	afx_msg void OnBnClickedBtnStart();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	// ��һ�����
	//void Situation1();
	// �ڶ������
	//void Situation2();
	// ���������
	void Situation();
	void initGlobalVariable();
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void showBufferContent();
	CListBox m_buff1List;
	CListBox m_buff2List;
	CListBox m_buff3List;
	afx_msg void OnBnClickedBtnPause();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
