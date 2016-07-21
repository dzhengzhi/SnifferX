#include "sn_receiving_block.h"

namespace snifferx {

	SnReceivingBlock::SnReceivingBlock() {
		ZeroMemory(&overlapped_, sizeof(WSAOVERLAPPED));
	}

	SnReceivingBlock::~SnReceivingBlock() {

	}

	WSAEVENT & SnReceivingBlock::overlapped_event() {
		return overlapped_.hEvent;
	}

	WSAOVERLAPPED & SnReceivingBlock::overlapped() {
		return overlapped_;
	}

}