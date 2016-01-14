
// producerAndConsumerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "producerAndConsumer.h"
#include "producerAndConsumerDlg.h"
#include "afxdialogex.h"
#include "libraryDlg.h"
#include <locale.h>
#include <List>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define UM_RESURECEDATA WM_USER+10
#define UM_BUFFINFO1 WM_USER+11
#define UM_BUFFINFO2 WM_USER+12
#define UM_BUFFINFO3 WM_USER+13
#define UM_PUTEDNUM WM_USER+14
#define UM_GETEDNUM WM_USER+15

#define ID_TIMER 1

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CproducerAndConsumerDlg �Ի���



CproducerAndConsumerDlg::CproducerAndConsumerDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(CproducerAndConsumerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CproducerAndConsumerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO1, cmbSituation);
	DDX_Control(pDX, IDC_LOG_LIST, m_LogList);
}

BEGIN_MESSAGE_MAP(CproducerAndConsumerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_CBN_SELCHANGE(IDC_COMBO1, &CproducerAndConsumerDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTN_START, &CproducerAndConsumerDlg::OnBnClickedBtnStart)

	//	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CproducerAndConsumerDlg::OnBnClickedBtnPause)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_LIB, &CproducerAndConsumerDlg::OnBnClickedBtnLib)
	ON_BN_CLICKED(IDC_BTN_SAVE, &CproducerAndConsumerDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CproducerAndConsumerDlg ��Ϣ�������

BOOL CproducerAndConsumerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��


	initEditToZero();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CproducerAndConsumerDlg::initEditToZero()
{
	//�����е������������0
	GetDlgItem(IDC_PUTNUM_EDIT)->SetWindowTextW(_T("30"));
	GetDlgItem(IDC_GETNUM_EDIT)->SetWindowTextW(_T("30"));
	GetDlgItem(IDC_BUF1_EDIT)->SetWindowTextW(_T("10"));
	GetDlgItem(IDC_BUF2_EDIT)->SetWindowTextW(_T("10"));
	GetDlgItem(IDC_BUF3_EDIT)->SetWindowTextW(_T("10"));
	GetDlgItem(IDC_PROD_EDIT)->SetWindowTextW(_T("2"));
	GetDlgItem(IDC_CONS_EDIT)->SetWindowTextW(_T("2"));
	GetDlgItem(IDC_PUT_SPEED_EDIT)->SetWindowTextW(_T("500"));
	GetDlgItem(IDC_GET_SPEED_EDIT)->SetWindowTextW(_T("3000"));
	GetDlgItem(IDC_MOVE_SPEED_EDIT)->SetWindowTextW(_T("2000"));
}

void CproducerAndConsumerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CproducerAndConsumerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CproducerAndConsumerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int FinishedMoveNum = 0;//���ڼ�¼Move�߳���ɵĸ���
HANDLE FinishedMoveMutex;//Move�̵߳Ļ�����
int FinishedProduceNum = 0;//������ɸ���
HANDLE ProduceFinishedMutex;//������������ɸ���
int FinishedConsumerNum = 0;//��������ɸ���
HANDLE ConsumerFinishedMutex;//������������ɻ�����

int putNum = 0;//��������
int getNum = 0;//��������
int buffer1_capacity = 0;//Buffer1����
int buffer2_capacity = 0;//Buffer2����
int buffer3_capacity = 0; //Buffer3����
int producer_num = 0;//��������Ŀ
int consumer_num = 0;//��������Ŀ
int put_speed = 0;//�����ٶ�
int get_speed = 0;//�����ٶ�
int move_speed = 0;//�ƶ��ٶ�

int limit = 30;  //��������
//const int maxsize = 10; //��������С
int buf1Idx = 0;    //��ǰ������1�±�
int buf2Idx = 0;    //��ǰ������2�±�
int buf3Idx = 0;    //��ǰ������3�±�

int putedNum = 0;
int getedNum = 0;

int rowCount = -1;
char* buf1;//����1�� ���ַ�����
char* buf2;//����2�� ���ַ�����
char* buf3;//����3�� ���ַ�����

//�߳̾��
CWinThread* Move1Handle;
CWinThread* Move2Handle;
CList<CWinThread*> ProducerHandle;
CList<CWinThread*> ConsumerHandle;

HANDLE buf1Idx_Mutex; //Buffer1�±�Ļ�����
HANDLE buf2Idx_Mutex; //Buffer1�±�Ļ�����
HANDLE buf3Idx_Mutex; //Buffer1�±�Ļ�����

HANDLE buf1_Mutex, buf1_Full, buf1_Empty; //Buffer1�Ļ�������ռ���ź����������ź���
HANDLE buf2_Mutex, buf2_Full, buf2_Empty; //Buffer2�Ļ�������ռ���ź����������ź���
HANDLE buf3_Mutex, buf3_Full, buf3_Empty; //Buffer3�Ļ�������ռ���ź����������ź���
HANDLE disp;    //���ڿ�����Ļ��ӡ�Ļ�����

HANDLE puted_Mutex, geted_Mutex;//�Ѿ��������Ѿ��������������Ļ�����

//int rowNum = -1;

//�����漴�ַ�
char randomCharcter()
{
	char result;
	srand(GetTickCount());
	result = rand() % 93 + 33;
	return result;
}

// �������ӹ���
UINT Producer(LPVOID param)
{
	ParamInfo* paramInfo = (ParamInfo*)param;
	int speed = paramInfo->speed;
	int id = paramInfo->id;
	HWND hWnd = paramInfo->m_hWnd;
	CString strResu;
	//CList<char> list;
	int ct;
	const int pwait = 100;
	srand(GetTickCount()); //���������

	WaitForSingleObject(disp, INFINITE);

	CString currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu.Format(_T("%s  ������%d��ʼ����!"), currentTime, id);
	GetDlgItem(hWnd, IDC_LOG_LIST);

	CString* str = new CString(strResu);
	::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	int iputedNum;
	ReleaseMutex(disp);
	while (true)
	{
		WaitForSingleObject(puted_Mutex, INFINITE);
		putedNum++;
		iputedNum = putedNum;
		WaitForSingleObject(ConsumerFinishedMutex, INFINITE);
		if ((FinishedConsumerNum == consumer_num) || (putedNum > putNum))
		{
			ReleaseMutex(ConsumerFinishedMutex);
			ReleaseMutex(puted_Mutex);
			break;
		}
		ReleaseMutex(ConsumerFinishedMutex);
		ReleaseMutex(puted_Mutex);

		char result = randomCharcter();

		WaitForSingleObject(buf1_Empty, INFINITE); //����һ���ջ�����������
		WaitForSingleObject(buf1_Mutex, INFINITE); //���󻥳���������

		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		buf1[buf1Idx++] = result;
		ReleaseMutex(buf1Idx_Mutex);

		
		//������ʾ�Ѿ�������������Ϣ
		WaitForSingleObject(disp, INFINITE);
		strResu.Format(_T("%d"), iputedNum);
		str = new CString(strResu);
		::PostMessage(hWnd, UM_PUTEDNUM, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		//�����Ѿ����������в�Ʒ
		WaitForSingleObject(disp, INFINITE);
		strResu = buf1;
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		strResu.Left(buf1Idx);
		ReleaseMutex(buf1Idx_Mutex);
		str = new CString(strResu);
		::PostMessage(hWnd, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		WaitForSingleObject(disp, INFINITE);
		currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		strResu.Format(_T("%s  (P->B)������%d�� %s ���뵽Buffer1[%d]"), currentTime, id, CString(result), buf1Idx);
		ReleaseMutex(buf1Idx_Mutex);
		str = new CString(strResu);
		::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		ReleaseMutex(buf1_Mutex);    //�ͷŻ�����
		ReleaseSemaphore(buf1_Full, 1, NULL);   //signal(full)
		Sleep(rand() % speed+pwait );  //��Ϣһ��
	}
	WaitForSingleObject(ProduceFinishedMutex, INFINITE);
	FinishedProduceNum++;
	ReleaseMutex(ProduceFinishedMutex);

	WaitForSingleObject(disp, INFINITE);
	currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu.Format(_T("%s  ������%d��������!"), currentTime, id);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	//�����Ѿ����������в�Ʒ
	WaitForSingleObject(buf1_Mutex, INFINITE); //���󻥳���������
	WaitForSingleObject(disp, INFINITE);
	strResu = buf1;
	WaitForSingleObject(buf1Idx_Mutex, INFINITE);
	strResu.Left(buf1Idx);
	ReleaseMutex(buf1Idx_Mutex);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	ReleaseMutex(buf1_Mutex);    //�ͷŻ�����

	return 0;
}


// �������ӹ���
UINT Consumer(LPVOID param)
{
	ParamInfo* paramInfo = (ParamInfo*)param;
	int speed = paramInfo->speed;
	int id = paramInfo->id;
	HWND hWnd = paramInfo->m_hWnd;
	CString strResu;
	//CString* pstrResu;
	int ct;
	const int cwait = 100;
	CString stuff;
	srand(GetTickCount());

	WaitForSingleObject(disp, INFINITE);
	CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	CString currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu.Format(_T("%s  ������%d��ʼ����!"), currentTime, id);
	CString* str = new CString(strResu);
	::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	bool isReturn = false;
	int maxNum;
	if (getNum <= putNum)
	{
		maxNum = getNum;
	}
	else
	{
		maxNum = putNum;
	}	
	while (true)
	{
		WaitForSingleObject(geted_Mutex, INFINITE);
		if (getedNum < maxNum)
		{
			while (true)
			{
				if (WAIT_TIMEOUT == WaitForSingleObject(buf3_Full, 100))
				{
					if (WAIT_TIMEOUT == WaitForSingleObject(buf2_Full, 100))
					{
						continue;
					}
					else
					{
						WaitForSingleObject(buf2_Mutex, INFINITE); //���󻥳���������
						WaitForSingleObject(buf2Idx_Mutex, INFINITE);
						stuff = buf2[--buf2Idx];
						ReleaseMutex(buf2Idx_Mutex);
						getedNum++;

						WaitForSingleObject(disp, INFINITE);
						currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
						WaitForSingleObject(buf2Idx_Mutex, INFINITE);
						strResu.Format(_T("%s  (B2->C)������%d��Buffer2[%d]ȡ�� %s"), currentTime, id, (buf2Idx + 1), stuff);
						ReleaseMutex(buf2Idx_Mutex);
						str = new CString(strResu);
						::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
						ReleaseMutex(disp);

						WaitForSingleObject(disp, INFINITE);
						strResu.Format(_T("%d"), getedNum);
						str = new CString(strResu);
						::PostMessage(hWnd, UM_GETEDNUM, (WPARAM)str, (LPARAM)str);
						ReleaseMutex(disp);

						WaitForSingleObject(disp, INFINITE);
						strResu = buf2;
						WaitForSingleObject(buf2Idx_Mutex, INFINITE);
						strResu.Left(buf2Idx);
						ReleaseMutex(buf2Idx_Mutex);
						str = new CString(strResu);
						::PostMessage(hWnd, UM_BUFFINFO2, (WPARAM)str, (LPARAM)str);
						ReleaseMutex(disp);

						ReleaseMutex(buf2_Mutex);    //�ͷŻ�����
						ReleaseSemaphore(buf2_Empty, 1, NULL);   //signal(empty)
						Sleep(rand() % speed + cwait);  //��Ϣһ��

						break;
					}
				}
				else
				{
					WaitForSingleObject(buf3_Mutex, INFINITE); //���󻥳���������
					WaitForSingleObject(buf3Idx_Mutex, INFINITE);
					WaitForSingleObject(buf3Idx_Mutex, INFINITE);
					stuff = buf3[--buf3Idx];
					ReleaseMutex(buf3Idx_Mutex);
					ReleaseMutex(buf3Idx_Mutex);
					getedNum++;

					WaitForSingleObject(disp, INFINITE);
					currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
					WaitForSingleObject(buf3Idx_Mutex, INFINITE);
					strResu.Format(_T("%s  (B3->C)������%d��Buffer3[%d]ȡ�� %s"), currentTime, id, (buf3Idx + 1), stuff);
					ReleaseMutex(buf3Idx_Mutex);
					str = new CString(strResu);
					::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
					ReleaseMutex(disp);

					WaitForSingleObject(disp, INFINITE);
					strResu.Format(_T("%d"), getedNum);
					str = new CString(strResu);
					::PostMessage(hWnd, UM_GETEDNUM, (WPARAM)str, (LPARAM)str);
					ReleaseMutex(disp);

					WaitForSingleObject(disp, INFINITE);
					strResu = buf3;
					WaitForSingleObject(buf3Idx_Mutex, INFINITE);
					strResu.Left(buf3Idx);
					ReleaseMutex(buf3Idx_Mutex);
					str = new CString(strResu);
					::PostMessage(hWnd, UM_BUFFINFO3, (WPARAM)str, (LPARAM)str);
					ReleaseMutex(disp);

					ReleaseMutex(buf3_Mutex);    //�ͷŻ�����
					ReleaseSemaphore(buf3_Empty, 1, NULL);   //signal(empty)
					Sleep(rand() % speed + cwait);  //��Ϣһ��

					break;
				}
			}
		}
		else
		{
			break;
		}
		ReleaseMutex(geted_Mutex);
	}

	WaitForSingleObject(ConsumerFinishedMutex, INFINITE);
	FinishedConsumerNum++;
	ReleaseMutex(ConsumerFinishedMutex);

	WaitForSingleObject(disp, INFINITE);
	currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu.Format(_T("%s  ������%d���ѽ���!"), currentTime, id);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(buf2_Mutex, INFINITE); //���󻥳���������
	WaitForSingleObject(disp, INFINITE);
	strResu = buf2;
	WaitForSingleObject(buf2Idx_Mutex, INFINITE);
	strResu.Left(buf2Idx);
	ReleaseMutex(buf2Idx_Mutex);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_BUFFINFO3, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	ReleaseMutex(buf2_Mutex);    //�ͷŻ�����

	WaitForSingleObject(buf3_Mutex, INFINITE); //���󻥳���������WaitForSingleObject(disp, INFINITE);
	strResu = buf3;
	WaitForSingleObject(buf3Idx_Mutex, INFINITE);
	strResu.Left(buf3Idx);
	ReleaseMutex(buf3Idx_Mutex);
	str = new CString(strResu);
	::PostMessage(hWnd, UM_BUFFINFO2, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	ReleaseMutex(buf3_Mutex);    //�ͷŻ�����	

	WaitForSingleObject(ConsumerFinishedMutex,INFINITE);
	if (FinishedConsumerNum==producer_num)
	{
		TerminateThread(Move1Handle->m_hThread,NULL);
		TerminateThread(Move2Handle->m_hThread, NULL);
		HANDLE handle;
		WaitForSingleObject(FinishedMoveMutex, INFINITE);
		FinishedMoveNum = 2;
		ReleaseMutex(FinishedMoveMutex);
		WaitForSingleObject(ProduceFinishedMutex, INFINITE);
		FinishedProduceNum = ProducerHandle.GetCount();
		ReleaseMutex(ProduceFinishedMutex);
		for (int i = 0; i < ProducerHandle.GetCount(); i++)
		{
			handle = ProducerHandle.GetAt(ProducerHandle.FindIndex(i))->m_hThread;
			TerminateThread(handle, NULL);
		}
		WaitForSingleObject(disp, INFINITE);
		strResu = buf2;
		strResu.Left(buf2Idx);
		str = new CString(strResu);
		::PostMessage(hWnd, UM_BUFFINFO2, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		WaitForSingleObject(disp, INFINITE);
		strResu = buf1;
		strResu.Left(buf1Idx);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);


		WaitForSingleObject(disp, INFINITE);
		strResu = buf3;
		strResu.Left(buf3Idx);
		str = new CString(strResu);
		::PostMessage(hWnd, UM_BUFFINFO3, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

	}
	ReleaseMutex(ConsumerFinishedMutex);
	return 0;
}


UINT Move1(LPVOID param)
{
	CString strResu;
	int ct;
	const int cwait = 300;
	CString stuff;
	srand(GetTickCount());

	WaitForSingleObject(disp, INFINITE);
	CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	CString currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu = currentTime + _T("  Move1 Start!");
	CString* str = new CString(strResu);
	::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	char currentChar;
	int maxGet;
	int iFinishedProc = 0;
	if (putNum < getNum)
	{
		maxGet = putNum;
	}
	else
	{
		maxGet = getNum;
	}
	while (true)
	{
		WaitForSingleObject(ProduceFinishedMutex,INFINITE);
		WaitForSingleObject(ConsumerFinishedMutex, INFINITE);
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		if ((FinishedConsumerNum == consumer_num)||((FinishedProduceNum == producer_num) && (buf1Idx == 0)))
		{
			ReleaseMutex(buf1Idx_Mutex);
			ReleaseMutex(ConsumerFinishedMutex);
			ReleaseMutex(ProduceFinishedMutex);
			break;
		}	
		ReleaseMutex(buf1Idx_Mutex);
		ReleaseMutex(ConsumerFinishedMutex);
		ReleaseMutex(ProduceFinishedMutex);

		WaitForSingleObject(buf1_Full, INFINITE); //����һ����������������		
		WaitForSingleObject(buf1_Mutex, INFINITE); //���󻥳���������
		WaitForSingleObject(buf2_Empty, INFINITE);
		WaitForSingleObject(buf2_Mutex, INFINITE);
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		currentChar = buf1[--buf1Idx];
		WaitForSingleObject(buf2Idx_Mutex, INFINITE);
		buf2[buf2Idx++] = currentChar;
		ReleaseMutex(buf2Idx_Mutex);

		WaitForSingleObject(disp, INFINITE);
		currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		WaitForSingleObject(buf2Idx_Mutex, INFINITE);
		strResu.Format(_T("%s  (B1->B2)�ַ� %s ��Buffer1[%d]�ƶ���Buffer2[%d]"), currentTime, CString(currentChar), (buf1Idx + 1), (buf2Idx));
		ReleaseMutex(buf2Idx_Mutex);
		ReleaseMutex(buf1Idx_Mutex);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);
		ReleaseMutex(buf1Idx_Mutex);

		//�����Ѿ����������в�Ʒ
		WaitForSingleObject(disp, INFINITE);
		strResu = buf1;
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		strResu.Left(buf1Idx);
		ReleaseMutex(buf1Idx_Mutex);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		//
		WaitForSingleObject(disp, INFINITE);
		strResu = buf2;
		WaitForSingleObject(buf2Idx_Mutex, INFINITE);
		strResu.Left(buf2Idx);
		ReleaseMutex(buf2Idx_Mutex);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_BUFFINFO2, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		ReleaseMutex(buf2_Mutex);
		ReleaseSemaphore(buf2_Full, 1, NULL);

		ReleaseMutex(buf1_Mutex);    //�ͷŻ�����
		ReleaseSemaphore(buf1_Empty, 1, NULL);   //signal(empty)
		Sleep(rand() % move_speed + 100);  //��Ϣһ��
	}

	WaitForSingleObject(disp, INFINITE);
	currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu = currentTime + _T("  �ƶ�1����!");
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	//�����Ѿ����������в�Ʒ
	WaitForSingleObject(buf1_Mutex, INFINITE); //���󻥳���������
	WaitForSingleObject(disp, INFINITE);
	strResu = buf1;
	WaitForSingleObject(buf1Idx_Mutex, INFINITE);
	strResu.Left(buf1Idx);
	ReleaseMutex(buf1Idx_Mutex);
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	ReleaseMutex(buf1_Mutex);    //�ͷŻ�����

	WaitForSingleObject(buf2_Mutex, INFINITE); //���󻥳���������
	WaitForSingleObject(disp, INFINITE);
	strResu = buf2;
	WaitForSingleObject(buf2Idx_Mutex, INFINITE);
	strResu.Left(buf2Idx);
	ReleaseMutex(buf2Idx_Mutex);
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_BUFFINFO2, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	ReleaseMutex(buf2_Mutex);    //�ͷŻ�����
	

	WaitForSingleObject(FinishedMoveMutex, INFINITE);
	FinishedMoveNum++;
	ReleaseMutex(FinishedMoveMutex);

	return 0;
}

UINT Move2(LPVOID param)
{
	CString strResu;
	//CString* pstrResu;
	int ct;
	const int cwait = 300;
	CString stuff;
	srand(GetTickCount());

	WaitForSingleObject(disp, INFINITE);
	CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	CString currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu = currentTime + _T("  Move2 Start!");
	CString* str = new CString(strResu);
	::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);
	char currentChar;//��buffer1�л�ȡ���ַ�
	int maxGet;
	int iFinishedProc = 0;
	if (putNum < getNum)
	{
		maxGet = putNum;
	}
	else
	{
		maxGet = getNum;
	}
	while (true)
	{
		WaitForSingleObject(ProduceFinishedMutex, INFINITE);
		WaitForSingleObject(ConsumerFinishedMutex, INFINITE);
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		if ((FinishedConsumerNum == consumer_num) || ((FinishedProduceNum == producer_num) && (buf1Idx == 0)))
		{
			ReleaseMutex(buf1Idx_Mutex);
			ReleaseMutex(ConsumerFinishedMutex);
			ReleaseMutex(ProduceFinishedMutex);
			break;
		}
		ReleaseMutex(buf1Idx_Mutex);
		ReleaseMutex(ConsumerFinishedMutex);
		ReleaseMutex(ProduceFinishedMutex);

		WaitForSingleObject(buf1_Full, INFINITE); //����һ����������������		
		WaitForSingleObject(buf1_Mutex, INFINITE); //���󻥳���������

		WaitForSingleObject(buf3_Empty, INFINITE);
		WaitForSingleObject(buf3_Mutex, INFINITE);
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		currentChar = buf1[--buf1Idx];
		ReleaseMutex(buf1Idx_Mutex);
		WaitForSingleObject(buf3Idx_Mutex, INFINITE);
		buf3[buf3Idx++] = currentChar;
		ReleaseMutex(buf3Idx_Mutex);

		WaitForSingleObject(disp, INFINITE);
		currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
		WaitForSingleObject(buf3Idx_Mutex, INFINITE);
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		strResu.Format(_T("%s  (B1->B3)�ַ� %s ��Buffer1[%d]�ƶ���Buffer3[%d]"), currentTime, CString(currentChar), (buf1Idx + 1), (buf3Idx));
		ReleaseMutex(buf1Idx_Mutex);
		ReleaseMutex(buf3Idx_Mutex);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		//�����Ѿ����������в�Ʒ
		WaitForSingleObject(disp, INFINITE);
		strResu = buf1;
		WaitForSingleObject(buf1Idx_Mutex, INFINITE);
		strResu.Left(buf1Idx);
		ReleaseMutex(buf1Idx_Mutex);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		WaitForSingleObject(disp, INFINITE);
		strResu = buf3;
		WaitForSingleObject(buf3Idx_Mutex, INFINITE);
		strResu.Left(buf3Idx);
		ReleaseMutex(buf3Idx_Mutex);
		str = new CString(strResu);
		::PostMessage((HWND)param, UM_BUFFINFO3, (WPARAM)str, (LPARAM)str);
		ReleaseMutex(disp);

		ReleaseMutex(buf3_Mutex);
		ReleaseSemaphore(buf3_Full, 1, NULL);

		ReleaseMutex(buf1_Mutex);    //�ͷŻ�����
		ReleaseSemaphore(buf1_Empty, 1, NULL);   //signal(empty)
		Sleep(rand() % move_speed + 100);  //��Ϣһ��
	}

	WaitForSingleObject(disp, INFINITE);
	currentTime = CTime::GetCurrentTime().Format("%H:%M:%S");
	strResu = currentTime + _T("  �ƶ�2����!");
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	//�����Ѿ����������в�Ʒ
	WaitForSingleObject(disp, INFINITE);
	strResu = buf1;
	WaitForSingleObject(buf1Idx_Mutex, INFINITE);
	strResu.Left(buf1Idx);
	ReleaseMutex(buf1Idx_Mutex);
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_BUFFINFO1, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(disp, INFINITE);
	strResu = buf3;
	WaitForSingleObject(buf3Idx_Mutex, INFINITE);
	strResu.Left(buf3Idx);
	ReleaseMutex(buf3Idx_Mutex);
	str = new CString(strResu);
	::PostMessage((HWND)param, UM_BUFFINFO3, (WPARAM)str, (LPARAM)str);
	ReleaseMutex(disp);

	WaitForSingleObject(FinishedMoveMutex, INFINITE);
	FinishedMoveNum++;
	ReleaseMutex(FinishedMoveMutex);

	return 0;
}


// ��ʾ�Ѿ����������ѵĸ���

LRESULT CproducerAndConsumerDlg::showNumberOfP(WPARAM Wparam, LPARAM Lparam)
{
	CString *str = (CString*)Lparam;
	GetDlgItem(IDC_PUTED_NUM_STATIC)->SetWindowText(*str);
	return TRUE;
}

LRESULT CproducerAndConsumerDlg::showBuffer1Content(WPARAM Wparam, LPARAM Lparam)
{
	CString *str = (CString*)Lparam;
	CString strResu = CString(*str);
	GetDlgItem(IDC_BUF1_CONTENT_EDIT)->SetWindowText(strResu);
	return TRUE;
}

LRESULT CproducerAndConsumerDlg::showBuffer2Content(WPARAM Wparam, LPARAM Lparam)
{
	CString *str = (CString*)Lparam;
	CString strResu = CString(*str);
	GetDlgItem(IDC_BUF2_CONTENT_EDIT)->SetWindowText(strResu);
	return TRUE;
}

LRESULT CproducerAndConsumerDlg::showBuffer3Content(WPARAM Wparam, LPARAM Lparam)
{
	CString *str = (CString*)Lparam;
	CString strResu = CString(*str);
	GetDlgItem(IDC_BUF3_CONTENT_EDIT)->SetWindowText(strResu);
	return TRUE;
}

LRESULT CproducerAndConsumerDlg::showNumberOfC(WPARAM Wparam, LPARAM Lparam)
{
	CString *str = (CString*)Lparam;
	GetDlgItem(IDC_GETED_NUM_STATIC)->SetWindowText(*str);
	return TRUE;
}


LRESULT CproducerAndConsumerDlg::OnResuReceData(WPARAM Wparam, LPARAM Lparam)
{
	CString* str = (CString*)Lparam;
	m_LogList.InsertString(++rowCount, *str);
	m_LogList.SetCurSel(rowCount);
	return TRUE;
}



/*
��ʼ�����е�ȫ�ֱ���
*/
long timeStart;
void CproducerAndConsumerDlg::initGlobalVariable()
{
	
	CString str;
	GetDlgItem(IDC_PUTNUM_EDIT)->GetWindowText(str);
	putNum = _ttoi(str);
	GetDlgItem(IDC_GETNUM_EDIT)->GetWindowText(str);
	getNum = _ttoi(str);
	GetDlgItem(IDC_BUF1_EDIT)->GetWindowText(str);
	buffer1_capacity = _ttoi(str);
	GetDlgItem(IDC_BUF2_EDIT)->GetWindowText(str);
	buffer2_capacity = _ttoi(str);
	GetDlgItem(IDC_BUF3_EDIT)->GetWindowText(str);
	buffer3_capacity = _ttoi(str);
	GetDlgItem(IDC_PROD_EDIT)->GetWindowText(str);
	producer_num = _ttoi(str);
	GetDlgItem(IDC_CONS_EDIT)->GetWindowText(str);
	consumer_num = _ttoi(str);
	GetDlgItem(IDC_PUT_SPEED_EDIT)->GetWindowText(str);
	put_speed = _ttoi(str);
	GetDlgItem(IDC_GET_SPEED_EDIT)->GetWindowText(str);
	get_speed = _ttoi(str);
	GetDlgItem(IDC_MOVE_SPEED_EDIT)->GetWindowText(str);
	move_speed = _ttoi(str);
	putedNum = 0;
	getedNum = 0;
	rowCount = -1;
	buf1Idx = 0;    //��ǰ������1�±�
	buf2Idx = 0;    //��ǰ������2�±�
	buf3Idx = 0;
	timeStart = GetTickCount();
	FinishedMoveNum = 0;//���ڼ�¼Move�߳���ɵĸ���
	FinishedProduceNum = 0;//������ɸ���
	FinishedConsumerNum = 0;//��������ɸ���
	buf1 = new char[buffer1_capacity];
	buf2 = new char[buffer2_capacity];
	buf3 = new char[buffer3_capacity];
	memset(buf1, 0, sizeof(char)* buffer1_capacity);
	memset(buf2, 0, sizeof(char)* buffer2_capacity);
	memset(buf3, 0, sizeof(char)* buffer3_capacity);
}

int startThreadNum;
void CproducerAndConsumerDlg::OnBnClickedBtnStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_BTN_PAUSE)->SetWindowText(_T("||"));
	CButton* btn = (CButton*)GetDlgItem(IDC_BTN_PAUSE);
	btn->EnableWindow(1);
	m_LogList.ResetContent();
	initGlobalVariable();
	
	Situation();
	SetTimer(1, 1, 0);
	startThreadNum = 2;
	CString str;
	GetDlgItem(IDC_PROD_EDIT)->GetWindowText(str);
	startThreadNum += _ttoi(str);
	GetDlgItem(IDC_CONS_EDIT)->GetWindowText(str);
	startThreadNum += _ttoi(str);
	str.Format(_T("%d"), startThreadNum);
	SetDlgItemText(IDC_THREADNUM_STATIC, str);
}

LRESULT CproducerAndConsumerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (message == UM_RESURECEDATA)
	{
		OnResuReceData(wParam, lParam);
	}
	else if (message == UM_PUTEDNUM)
	{
		showNumberOfP(wParam, lParam);
	}
	else if (message == UM_GETEDNUM)
	{
		showNumberOfC(wParam, lParam);
	}
	else if (message == UM_BUFFINFO1)
	{
		showBuffer1Content(wParam, lParam);
	}
	else if (message == UM_BUFFINFO2)
	{
		showBuffer2Content(wParam, lParam);
	}
	else if (message == UM_BUFFINFO3)
	{
		showBuffer3Content(wParam, lParam);
	}

	else
		return CDialogEx::WindowProc(message, wParam, lParam);
}



// ���������
void CproducerAndConsumerDlg::Situation()
{
	Move1Handle = NULL;
	Move2Handle = NULL;
	ProducerHandle.RemoveAll();
	ConsumerHandle.RemoveAll();

	puted_Mutex = CreateMutex(NULL,FALSE,NULL);

	geted_Mutex = CreateMutex(NULL, FALSE, NULL);

	ProduceFinishedMutex = CreateMutex(NULL, FALSE, NULL);
	FinishedMoveMutex = CreateMutex(NULL, FALSE, NULL);
	ConsumerFinishedMutex = CreateMutex(NULL, FALSE, NULL);
	//������Ļ��ӡ������
	disp = CreateMutex(NULL, FALSE, NULL);
	buf1Idx_Mutex = CreateMutex(NULL, FALSE, NULL);
	buf2Idx_Mutex = CreateMutex(NULL, FALSE, NULL);
	buf3Idx_Mutex = CreateMutex(NULL, FALSE, NULL);
	//����������
	buf1_Mutex = CreateMutex(NULL, FALSE, NULL);
	//����������ռ���ź���
	buf1_Full = CreateSemaphore(NULL, 0, buffer1_capacity, _T("full1"));
	//���������������ź���
	buf1_Empty = CreateSemaphore(NULL, buffer1_capacity, buffer1_capacity, _T("empty1"));
	//
	buf2_Mutex = CreateMutex(NULL, FALSE, NULL);

	buf2_Full = CreateSemaphore(NULL, 0, buffer2_capacity, _T("full2"));

	buf2_Empty = CreateSemaphore(NULL, buffer2_capacity, buffer2_capacity, _T("empty2"));

	buf3_Mutex = CreateMutex(NULL, FALSE, NULL);

	buf3_Full = CreateSemaphore(NULL, 0, buffer3_capacity, _T("full3"));

	buf3_Empty = CreateSemaphore(NULL, buffer3_capacity, buffer3_capacity, _T("empty3"));

	for (int i = 1; i <= producer_num; i++)
	{
		ParamInfo *producerSpeed = new  ParamInfo;
		producerSpeed->id = i;
		producerSpeed->speed = put_speed;
		producerSpeed->m_hWnd = m_hWnd;
		//�����������߳�
		ProducerHandle.AddTail(AfxBeginThread(Producer, (LPVOID)producerSpeed, 0, 0, 0, NULL));
	}

	//move�߳�
	Move1Handle = AfxBeginThread(Move1, (LPVOID)m_hWnd, 0, 0, 0, NULL);
	Move2Handle = AfxBeginThread(Move2, (LPVOID)m_hWnd, 0, 0, 0, NULL);
	for (int i = 1; i <= consumer_num; i++)
	{
		ParamInfo *consumerSpeed = new  ParamInfo;
		consumerSpeed->id = i;
		consumerSpeed->speed = get_speed;
		consumerSpeed->m_hWnd = m_hWnd;
		//�����������߳�
		ProducerHandle.AddTail(AfxBeginThread(Consumer, (LPVOID)consumerSpeed, 0, 0, 0, NULL));
	}
	SetTimer(2, 10, NULL);

	MSG msg;
	while (::PeekMessageA(&msg, m_hWnd, WM_USER + 10, WM_USER + 10, PM_REMOVE))
	{
		if (msg.message == UM_RESURECEDATA)
		{
			WindowProc(msg.message, msg.wParam, msg.lParam);
			break;
		}
	}
}

bool pause = false;
void CproducerAndConsumerDlg::OnBnClickedBtnPause()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!pause)
	{
		try{
			if (Move1Handle)
			{
				Move1Handle->SuspendThread();
			}
			if (Move2Handle)
			{
				Move2Handle->SuspendThread();
			}
			if (!ProducerHandle.IsEmpty())
			{
				CWinThread* handle;
				for (int i = 0; i < ProducerHandle.GetCount(); i++)
				{
					handle = ProducerHandle.GetAt(ProducerHandle.FindIndex(i));
					handle->SuspendThread();
				}
			}
			if (!ConsumerHandle.IsEmpty())
			{
				CWinThread* handle;
				for (int i = 0; i < ConsumerHandle.GetCount(); i++)
				{
					handle = ConsumerHandle.GetAt(ConsumerHandle.FindIndex(i));
					handle->SuspendThread();
				}
			}
		}
		catch (CException* e){
				throw; // Do not delete e
		}		
		GetDlgItem(IDC_BTN_PAUSE)->SetWindowText(_T("|>"));
		pause = true;
	}
	else
	{
		try{
			if (Move1Handle)
			{
				Move1Handle->ResumeThread();
			}
			if (Move2Handle)
			{
				Move2Handle->ResumeThread();
			}
			if (!ProducerHandle.IsEmpty())
			{
				CWinThread* handle;
				for (int i = 0; i < ProducerHandle.GetCount(); i++)
				{
					handle = ProducerHandle.GetAt(ProducerHandle.FindIndex(i));
					handle->ResumeThread();
				}
			}
			if (!ConsumerHandle.IsEmpty())
			{
				CWinThread* handle;
				for (int i = 0; i < ConsumerHandle.GetCount(); i++)
				{
					handle = ConsumerHandle.GetAt(ConsumerHandle.FindIndex(i));
					handle->ResumeThread();
				}
			}
		}
		catch (CException* e){
			throw;
		}
		
		GetDlgItem(IDC_BTN_PAUSE)->SetWindowText(_T("||"));
		pause = false;
	}
}


void CproducerAndConsumerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString str;
	long timeEnd;
	long timeUse;
	int numberOfRunThread = 0;
	DWORD code;
	CWinThread* handle;
	GetDlgItem(IDC_RUN_NUM_STATIC)->GetWindowText(str);
	if (str=="0"||(FinishedMoveNum + FinishedProduceNum + FinishedConsumerNum) == startThreadNum)
	{
		CString str=_T("");
		for (int i = 0; i < buf1Idx; i++)
		{
			str += buf1[i];
		}
		GetDlgItem(IDC_BUF1_CONTENT_EDIT)->SetWindowText(str);
		for (int i = 0; i < buf2Idx; i++)
		{
			str += buf2[i];
		}
		GetDlgItem(IDC_BUF2_CONTENT_EDIT)->SetWindowText(str);
		for (int i = 0; i < buf3Idx; i++)
		{
			str += buf3[i];
		}
		GetDlgItem(IDC_BUF3_CONTENT_EDIT)->SetWindowText(str);
		KillTimer(1);
		KillTimer(2);
		CButton* btn = (CButton*)GetDlgItem(IDC_BTN_PAUSE);
		btn->EnableWindow(0);
	}
	switch (nIDEvent)
	{
	case 1:
		timeEnd = GetTickCount();
		timeUse = timeEnd - timeStart;
		str.Format(_T("%d"), timeUse);
		GetDlgItem(IDC_USE_TIME_STATIC)->SetWindowText(str);
		break;
	case 2:
		GetExitCodeThread(Move1Handle->m_hThread, &code);
		if (code == STILL_ACTIVE)
		{
			numberOfRunThread++;
		}
		GetExitCodeThread(Move2Handle->m_hThread, &code);
		if (code == STILL_ACTIVE)
		{
			numberOfRunThread++;
		}
		for (int i = 0; i < ProducerHandle.GetCount(); i++)
		{
			handle = ProducerHandle.GetAt(ProducerHandle.FindIndex(i));
			GetExitCodeThread(handle->m_hThread, &code);
			if (code == STILL_ACTIVE)
			{
				numberOfRunThread++;
			}
		}
		for (int i = 0; i < ConsumerHandle.GetCount(); i++)
		{
			handle = ConsumerHandle.GetAt(ConsumerHandle.FindIndex(i));
			GetExitCodeThread(handle->m_hThread, &code);
			if (code == STILL_ACTIVE)
			{
				numberOfRunThread++;
			}
		}
		str.Format(_T("%d"), numberOfRunThread);
		SetDlgItemText(IDC_RUN_NUM_STATIC, str);
		break;
	default:
		CDialogEx::OnTimer(nIDEvent);
		break;
	}
}

void CproducerAndConsumerDlg::OnBnClickedBtnLib()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	libraryDlg dlg;
	dlg.DoModal();
}


void CproducerAndConsumerDlg::OnBnClickedBtnSave()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	//�����ļ�
	setlocale(LC_CTYPE, "chs");
	m_LogList.GetDlgItem(IDC_LOG_LIST);
	CStdioFile file;
	if (file.Open(_T("my.txt"), CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite))
	{
		CString str, str2;
		int count = m_LogList.GetCount();
		file.SeekToEnd();
		for (int i = 0; i < count; i++)
		{
			m_LogList.GetText(i, str);
			str2 += str + _T("\n");

		}
		str2 += _T("\n");
		file.WriteString(str2);
		file.Close();
		str2.ReleaseBuffer();
	}
	else
	{
		MessageBox(_T("��ʾ"), _T("�ļ�д��ʧ�ܣ�"), MB_OK);
	}
}