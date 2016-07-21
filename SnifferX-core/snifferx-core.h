
#pragma once

#include <atomic>
#include <memory>
#include <thread>

#include "common.h"
#include "sn_errorcode.h"
#include "sn_socket.h"
#include "sn_package.h"
#include "sn_info_block.h"
#include "sn_blocking_queue.h"

namespace snifferx {
	using namespace utils;



	class SNIFFERXCORE_API SnifferX {
	public:
		SnifferX();
		~SnifferX();
		//��ʼ��
		int Init(const wchar_t * ip_addr);
		//��ʼ�ػ�����
		int Start();
		//ֹͣ�ػ�����
		int Stop();
		//ִ�������ͷ���Դ
		int Cleanup();
		//��ȡ��ǰ�Ƿ�������״̬
		bool IsRunning();
		//��ȡ���
		SnPackage * GetResult();
	private:
		static void WorkerFunction(shared_ptr<SnInfoBlock> &);
		SnSocket sock_;
		atomic<SnStatus> * current_status_;
		thread * worker_thread_;
		SnBlockingQueue<SnPackage*> * packet_queue_;
	};

}

