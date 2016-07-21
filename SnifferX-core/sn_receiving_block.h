#pragma once

#include <winsock2.h>
#include <Ws2tcpip.h>
#include <Mstcpip.h>

#include "common.h"

namespace snifferx {

	struct SNIFFERXCORE_API SnReceivingBlock
	{
	private:
		WSAOVERLAPPED overlapped_;
	public:
		inline SnReceivingBlock();
		inline ~SnReceivingBlock();
		inline WSAEVENT & overlapped_event();
		inline WSAOVERLAPPED & overlapped();
	};

}