
// producerAndConsumerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "producerAndConsumer.h"
#include "producerAndConsumerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define UM_RESURECEDATA WM_USER+10

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
	DDX_Control(pDX, IDC_COMBO1, cmbSituation);
	DDX_Control(pDX, IDC_LOG_LIST, m_LogList);
}

BEGIN_MESSAGE_MAP(CproducerAndConsumerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CproducerAndConsumerDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BTN_START, &CproducerAndConsumerDlg::OnBnClickedBtnStart)

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	cmbSituation.AddString(_T("Situation1"));
	cmbSituation.AddString(_T("Situation2"));
	cmbSituation.AddString(_T("Situation3"));
	cmbSituation.AddString(_T("Situation4"));
	cmbSituation.SetCurSel(0);

	GetDlgItem(IDC_PUTNUM_EDIT)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_GETNUM_EDIT)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_BUF_EDIT)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_PROD_EDIT)->SetWindowTextW(_T("0"));
	GetDlgItem(IDC_CONS_EDIT)->SetWindowTextW(_T("0"));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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



void CproducerAndConsumerDlg::OnCbnSelchangeCombo1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	switch (cmbSituation.GetCurSel())
	{
	case 2:
		GetDlgItem(IDC_PUTNUM_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PUTNUM_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PUTNUM_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_SPIN)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_BUF_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_STATIC)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_EDIT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_SPIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_SPIN)->ShowWindow(SW_HIDE);
		break;
	case 3:
		GetDlgItem(IDC_PUTNUM_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PUTNUM_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PUTNUM_SPIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GETNUM_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GETNUM_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_GETNUM_SPIN)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUF_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_STATIC)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONS_STATIC)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUF_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_EDIT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONS_EDIT)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_BUF_SPIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_PROD_SPIN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CONS_SPIN)->ShowWindow(SW_SHOW);
		break;
	default:
		GetDlgItem(IDC_PUTNUM_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PUTNUM_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PUTNUM_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_GETNUM_SPIN)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PROD_STATIC)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_STATIC)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PROD_EDIT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_EDIT)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_BUF_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_PROD_SPIN)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CONS_SPIN)->ShowWindow(SW_HIDE);
		break;
	}

}



const int limit = 30;  //��������
const int maxsize = 10; //��������С
const int kind = 7;  //ˮ��������
int bufIdx = 0;    //��ǰ�������±�

int rowCount = -1;
CString buf[maxsize];    //������ ���ַ�����
//α��Ĳ�Ʒ
CString product[] = { _T("AAAAA"), _T("BBBBB"), _T("CCCCC"), _T("DDDDD"), _T("EEEEE"), _T("FFFFF"), _T("GGGGG") };

HANDLE mutex, full, empty; //��������ռ���ź����������ź���
HANDLE disp;    //���ڿ�����Ļ��ӡ�Ļ�����

int rowNum = -1;


// �������ӹ���
DWORD WINAPI Producer(LPVOID param)
{
	CString strResu;
	int ct, idx;
	const int pwait = 100;
	srand(time(NULL)); //���������

	WaitForSingleObject(disp, INFINITE);

	//CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	strResu = _T("Producer Start!");
	CString* str = new CString(strResu);
	::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);

	//cout << "Producer Start!" << endl << endl;
	ReleaseMutex(disp);

	for (ct = 0; ct < limit; ct++)
	{
		idx = rand() % kind;

		WaitForSingleObject(disp, INFINITE);
		
		strResu.Format(_T("%s is ready!"), product[idx]);
		str = new CString(strResu);
		::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		//cout << product[idx] << " is ready!" << endl << endl;
		ReleaseMutex(disp);

		WaitForSingleObject(empty, INFINITE); //����һ���ջ�����������
		WaitForSingleObject(mutex, INFINITE); //���󻥳���������
		buf[bufIdx++] = product[idx];

		WaitForSingleObject(disp, INFINITE);

		strResu.Format(_T("%s added to slot No.%d"), product[idx], bufIdx);
		str = new CString(strResu);
		::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		//cout << product[idx] << " added to slot No. " << bufIdx << endl << endl;
		ReleaseMutex(disp);

		ReleaseMutex(mutex);    //�ͷŻ�����
		ReleaseSemaphore(full, 1, NULL);   //signal(full)
		Sleep(rand() % pwait + 100);  //��Ϣһ��
	}

	WaitForSingleObject(disp, INFINITE);
	strResu = _T("Producer Quit!");
	str = new CString(strResu);
	::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	//cout << "Producer Quit!" << endl << endl;
	ReleaseMutex(disp);
	return 0;
}


// �������ӹ���
DWORD WINAPI Consumer(LPVOID param)
{
	CString strResu;
	//CString* pstrResu;
	int ct;
	const int cwait = 300;
	CString stuff;
	srand(time(NULL));

	WaitForSingleObject(disp, INFINITE);
	CproducerAndConsumerDlg* pDlg = (CproducerAndConsumerDlg*)param;
	strResu = _T("Consumer Start!");
	CString* str = new CString(strResu);
	::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	//cout << "Consumer Start!" << endl << endl;
	ReleaseMutex(disp);

	for (ct = 0; ct < limit; ct++)
	{
		WaitForSingleObject(full, INFINITE); //����һ����������������
		WaitForSingleObject(mutex, INFINITE); //���󻥳���������
		stuff = buf[--bufIdx];

		WaitForSingleObject(disp, INFINITE);
		strResu.Format(_T("Consumer get %s from slot No. %d"), stuff, (bufIdx + 1));
		str = new CString(strResu);
		::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
		//cout << "Consumer get " << stuff << " from slot No. " << (bufIdx + 1) << endl << endl;
		ReleaseMutex(disp);

		ReleaseMutex(mutex);    //�ͷŻ�����
		ReleaseSemaphore(empty, 1, NULL);   //signal(empty)
		Sleep(rand() % cwait + 100);  //��Ϣһ��
	}

	WaitForSingleObject(disp, INFINITE);
	strResu = _T("Consumer Quit!");
	str = new CString(strResu);
	::PostMessageA((HWND)param, UM_RESURECEDATA, (WPARAM)str, (LPARAM)str);
	//cout << "Consumer Quit!" << endl << endl;
	ReleaseMutex(disp);
	return 0;
}


LRESULT CproducerAndConsumerDlg::OnResuReceData(WPARAM Wparam, LPARAM Lparam)
{
	//CString strResu = (LPCTSTR)Lparam;
	//m_LogList.InsertString(++rowCount, strResu);
	CString* str = (CString*)Lparam;
	m_LogList.InsertString(++rowCount, *str);
	 
	//GetDlgItem(IDC_LOG_LIST)->SetWindowTextW((LPCTSTR)Lparam);
	return TRUE;
}


// ���������
void CproducerAndConsumerDlg::Situation3()
{
	//�������߳����������̵߳��߳�ID
	DWORD ProducerID, ConsumerID;
	//�߳̾��
	HANDLE ProducerHandle, ConsumerHandle;

	//������Ļ��ӡ������
	disp = CreateMutex(NULL, FALSE, NULL);

	//�����������߳�
	ProducerHandle = CreateThread(NULL, 0, Producer, (LPVOID)m_hWnd, 0, &ProducerID);
	//�����������߳�
	ConsumerHandle = CreateThread(NULL, 0, Consumer, (LPVOID)m_hWnd, 0, &ConsumerID);
	
	MSG msg;
	while (::PeekMessageA(&msg, m_hWnd, WM_USER + 10, WM_USER + 10, PM_REMOVE))
	{
		if (msg.message == UM_RESURECEDATA)
		{
			WindowProc(msg.message,msg.wParam,msg.lParam);
			break;
		}
	}

	//����������
	mutex = CreateMutex(NULL, FALSE, NULL);
	//����������ռ���ź���
	full = CreateSemaphore(NULL, 0, maxsize, _T("full"));
	//���������������ź���
	empty = CreateSemaphore(NULL, maxsize, maxsize, _T("empty"));

	//�ȴ�ֱ���������߳�ִ�����
	if (ProducerHandle != NULL)
	{
		WaitForSingleObject(ProducerHandle, INFINITE);
		CloseHandle(ProducerHandle);
	}
	//�ȴ�ֱ���������߳�ִ�����
	if (ConsumerHandle != NULL)
	{
		WaitForSingleObject(ConsumerHandle, INFINITE);
		CloseHandle(ConsumerHandle);
	}
}


void CproducerAndConsumerDlg::OnBnClickedBtnStart()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


	switch (cmbSituation.GetCurSel())
	{
	case 0:
		
		break;
	case 1:
		break;
	case 2:
		Situation3();
		break;
	case 3:
		break;
	}
}


LRESULT CproducerAndConsumerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (message == UM_RESURECEDATA)
	{
		OnResuReceData(wParam,lParam);
	}
	else
		return CDialogEx::WindowProc(message, wParam, lParam);
}
