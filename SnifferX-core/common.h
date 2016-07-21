#pragma once

#include "stdafx.h"

#ifdef SNIFFERXCORE_EXPORTS
#define SNIFFERXCORE_API __declspec(dllexport)
#else
#define SNIFFERXCORE_API __declspec(dllimport)
#endif

namespace snifferx {

	//SnSocket��ǰ״̬
	enum class SNIFFERXCORE_API SnSocketStatus {
		//δ��ʼ��
		kNotInit,
		//���ڳ�ʼ��
		kInitializing,
		//����
		kReady,
		//���ڽ�������
		kReceiving,
	};

	//SnifferX��ǰ״̬
	enum class SNIFFERXCORE_API SnStatus {
		//δ��ʼ��
		kNotInit,
		//���ڳ�ʼ��
		kInitializing,
		//����
		kReady,
		//��������
		kRunning,
		//�����˳�
		kExiting,
	};

}