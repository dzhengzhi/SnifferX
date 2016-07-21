#pragma once



#include <atomic>

#include "common.h"
#include "sn_errorcode.h"
#include "sn_receiving_block.h"

#pragma comment(lib,"Ws2_32.lib")

namespace snifferx {



	class SNIFFERXCORE_API SnSocket
	{
	public:
		//��ʼ��
		int Init(const  wchar_t * ip_addr);
		//ִ�������ͷ���Դ
		int Cleanup();
		//��ʼ�첽��ȡ
		int RecvAsync(void * buffer, int buffer_len);
		//��ȡ�첽��ȡ����������ȡδ��������ȴ�
		int WaitRecvResult(unsigned long & recv_bytes_length, const int timeout);
		SnSocket();
		~SnSocket();
	private:
		SnReceivingBlock receiving_struct;
		SnSocketStatus current_status_ = SnSocketStatus::kNotInit;
		SOCKET sock_ = NULL;

	};

}