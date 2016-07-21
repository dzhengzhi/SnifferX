
#include "sn_socket.h"

namespace snifferx {

	int SnSocket::Init(const wchar_t * ip_addr) {
		if (current_status_ != SnSocketStatus::kNotInit) {
			return SnErrorCode::kSnifferXIsInitialized;
		}
		if (ip_addr == NULL) {
			return SnErrorCode::kInvalidArgument;
		}

		int error;
		WSADATA wsa_data;
		//初始化
		if (WSAStartup(MAKEWORD(2, 2), &wsa_data) != 0) {
			return WSAGetLastError();
		}
		current_status_ = SnSocketStatus::kInitializing;

		//确认系统支持2.2版本
		if (LOBYTE(wsa_data.wVersion) != 2 || HIBYTE(wsa_data.wVersion) != 2) {
			error = WSAGetLastError();
			Cleanup();
			return error;
		}

		sock_ = WSASocket(AF_INET, SOCK_RAW, IPPROTO_IP, 0, NULL, WSA_FLAG_OVERLAPPED);
		if (sock_ == INVALID_SOCKET) {
			error = WSAGetLastError();
			Cleanup();
			return error;
		}

		unsigned long addr_buffer;
		SOCKADDR_IN localhost_addr;

		InetPton(AF_INET, ip_addr, &addr_buffer);
		localhost_addr.sin_addr.S_un.S_addr = addr_buffer;
		localhost_addr.sin_family = AF_INET;
		//绑定本地网卡
		if (bind(sock_, reinterpret_cast<PSOCKADDR>(&localhost_addr), sizeof(localhost_addr))) {
			error = WSAGetLastError();
			Cleanup();
			return error;
		}

		//自己处理IP头
		int ip_hdrincl_value = true;
		if (setsockopt(sock_, IPPROTO_IP, IP_HDRINCL, reinterpret_cast<char*>(&ip_hdrincl_value), sizeof(ip_hdrincl_value)) == SOCKET_ERROR) {
			error = WSAGetLastError();
			Cleanup();
			return error;
		}

		DWORD sio_rcvall_value = RCVALL_IPLEVEL;//1;
		//把socket设置成接收所有数据
		if (ioctlsocket(sock_, SIO_RCVALL, &sio_rcvall_value) != 0) {
			error = WSAGetLastError();
			Cleanup();
			return error;
		}

		//设置非阻塞模式
		unsigned long fionbio_mode = 0;
		if (ioctlsocket(sock_, FIONBIO, &fionbio_mode) != 0) {
			error = WSAGetLastError();
			Cleanup();
			return error;
		}

		current_status_ = SnSocketStatus::kReady;

		return 0;
	}

	int SnSocket::Cleanup() {
		if (current_status_ == SnSocketStatus::kReady || current_status_ == SnSocketStatus::kInitializing) {
			if (sock_ != NULL && sock_ != INVALID_SOCKET) {
				if (closesocket(sock_) == SOCKET_ERROR) {
					return WSAGetLastError();
				}
			}
			if (receiving_struct.overlapped_event() != NULL) {
				WSACloseEvent(receiving_struct.overlapped().hEvent);
				receiving_struct.overlapped_event() = NULL;
			}
			if (WSACleanup() != 0) {
				return WSAGetLastError();
			}
			current_status_ = SnSocketStatus::kNotInit;
			return SnErrorCode::kSuccess;
		}
		else if (current_status_ == SnSocketStatus::kNotInit) {
			return SnErrorCode::kSuccess;
		}
		else if (current_status_ == SnSocketStatus::kReceiving) {
			return SnErrorCode::kSnifferXIsReceiving;
		}
		return SnErrorCode::kUnknown;
	}

	int SnSocket::RecvAsync(void * buffer, int buffer_len) {
		if (current_status_ != SnSocketStatus::kReady) {
			return SnErrorCode::kSnifferXIsNotReady;
		}
		if (buffer == NULL || buffer_len <= 0) {
			return SnErrorCode::kInvalidArgument;
		}

		WSABUF wsabuf;
		unsigned long recv_flags = 0, error = 0;

		wsabuf.buf = static_cast<char*>(buffer);
		wsabuf.len = buffer_len;

		if (receiving_struct.overlapped_event() == NULL) {
			receiving_struct.overlapped_event() = WSACreateEvent();
		}
		else if (WSAResetEvent(receiving_struct.overlapped_event()) == false) {
			return WSAGetLastError();
		}

		//开始异步读取
		int result = WSARecv(sock_, &wsabuf, 1, NULL, &recv_flags, &receiving_struct.overlapped(), NULL);
		if (result == SOCKET_ERROR && (error = WSAGetLastError()) != WSA_IO_PENDING) {
			return error;
		}

		current_status_ = SnSocketStatus::kReceiving;

		return SnErrorCode::kSuccess;
	}

	int SnSocket::WaitRecvResult(unsigned long & recv_bytes_length, const int timeout) {
		recv_bytes_length = 0;
		if (current_status_ != SnSocketStatus::kReceiving) {
			return SnErrorCode::kSnifferXIsNotReceiving;
		}
		int error = 0;
		//等待异步读执行结束
		if ((error = WaitForSingleObject(receiving_struct.overlapped_event(), timeout)) == WSA_WAIT_FAILED) {
			return GetLastError();
		}
		if (error == WAIT_TIMEOUT) {
			return SnErrorCode::kSuccess;
		}

		unsigned long recv_flags = 0;
		//判断读取是否成功
		if (WSAGetOverlappedResult(sock_, &receiving_struct.overlapped(), &recv_bytes_length, false, &recv_flags) == false) {
			return WSAGetLastError();
		}

		current_status_ = SnSocketStatus::kReady;

		return SnErrorCode::kSuccess;
	}


	SnSocket::SnSocket() {
	}


	SnSocket::~SnSocket() {
	}



}