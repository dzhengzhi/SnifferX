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
		//初始化
		int Init(const  wchar_t * ip_addr);
		//执行清理，释放资源
		int Cleanup();
		//开始异步读取
		int RecvAsync(void * buffer, int buffer_len);
		//获取异步读取结果，如果读取未结束，则等待
		int WaitRecvResult(unsigned long & recv_bytes_length, const int timeout);
		SnSocket();
		~SnSocket();
	private:
		SnReceivingBlock receiving_struct;
		SnSocketStatus current_status_ = SnSocketStatus::kNotInit;
		SOCKET sock_ = NULL;

	};

}