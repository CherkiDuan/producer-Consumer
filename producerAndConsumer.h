
// producerAndConsumer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CproducerAndConsumerApp: 
// �йش����ʵ�֣������ producerAndConsumer.cpp
//

class CproducerAndConsumerApp : public CWinApp
{
public:
	CproducerAndConsumerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CproducerAndConsumerApp theApp;