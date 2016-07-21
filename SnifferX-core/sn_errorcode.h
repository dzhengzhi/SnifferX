#pragma once

namespace snifferx {

	//�������
	enum SnErrorCode : int {
		//�ɹ�
		kSuccess = 0,
		//δ֪����
		kUnknown = -1,
		//���ڽ�������
		kSnifferXIsReceiving = -2,
		//�Ѿ���ɳ�ʼ��
		kSnifferXIsInitialized = -3,
		//��������
		kSnifferXIsRunning = -4,
		//��δ����
		kSnifferXIsNotReady = -5,
		//��ǰ���ڽ�������
		kSnifferXIsNotReceiving = -6,
		//û������
		kSnifferXIsNotRunning = -7,
		//�Ƿ�����
		kInvalidArgument = -8,
		//�޷������߳�
		kSnifferXCannotCreateThread = -9,
	};

}