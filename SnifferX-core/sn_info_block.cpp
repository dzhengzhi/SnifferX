#include "sn_info_block.h"

namespace snifferx {

	SnInfoBlock::SnInfoBlock
		(SnSocket & sock,
			utils::SnBlockingQueue<SnPackage*> & packet_queue,
			std::atomic<SnStatus> & current_status)
		:
		sock_(sock),
		packet_queue_(packet_queue),
		current_status_(current_status) {};

}