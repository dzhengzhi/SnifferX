
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
		//初始化
		int Init(const wchar_t * ip_addr);
		//开始截获数据
		int Start();
		//停止截获数据
		int Stop();
		//执行清理，释放资源
		int Cleanup();
		//获取当前是否处于运行状态
		bool IsRunning();
		//获取结果
		SnPackage * GetResult();
	private:
		static void WorkerFunction(shared_ptr<SnInfoBlock> &);
		SnSocket sock_;
		atomic<SnStatus> * current_status_;
		thread * worker_thread_;
		SnBlockingQueue<SnPackage*> * packet_queue_;
	};

}

