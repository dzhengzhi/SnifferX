#pragma once

#include <atomic>

#include "common.h"
#include "sn_socket.h"
#include "sn_blocking_queue.h"
#include "sn_package.h"

namespace snifferx {

	struct SnInfoBlock {
	public:
		SnSocket & sock_;
		utils::SnBlockingQueue<SnPackage*> & packet_queue_;
		std::atomic<SnStatus> & current_status_;
	private:
		SnInfoBlock
			(SnSocket & sock, utils::SnBlockingQueue<SnPackage*> & packet_queue,
				std::atomic<SnStatus> & current_status);
		friend class SnifferX;
	};

}