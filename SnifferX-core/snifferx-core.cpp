
#include "stdafx.h"

#include <process.h>
#include <thread>
#include <memory>

#include "sn_errorcode.h"
#include "snifferx-core.h"
#include "sn_socket.h"
#include "sn_analyzer.h"
#include "sn_swapper.h"

namespace snifferx {

	//缓冲区大小
	const int recv_buffer_size = 4 * 1024;
	//等待时间
	const int wait_for_recv_time_in_ms = 200;

	SnifferX::SnifferX():worker_thread_(NULL) {
		current_status_ = new atomic<SnStatus>(SnStatus::kNotInit);
		packet_queue_ = new SnBlockingQueue<SnPackage*>();
		return;
	}
	SnifferX::~SnifferX() {
		if (current_status_ != NULL) {
			delete current_status_;
		}
		if (packet_queue_ != NULL) {
			delete packet_queue_;
		}
		return;
	}

	int SnifferX::Init(const wchar_t * ip_addr) {
		if (ip_addr == NULL) {
			return SnErrorCode::kInvalidArgument;
		}

		auto expected_value = SnStatus::kNotInit;
		if (current_status_->compare_exchange_strong(expected_value, SnStatus::kInitializing, memory_order_seq_cst)) {
			int error = 0;
			//初始化SnSocket
			if ((error = sock_.Init(ip_addr)) != 0) {
				return error;
			}

			shared_ptr<SnInfoBlock> info_block_(new SnInfoBlock(sock_, *packet_queue_, *current_status_));

			//启动工作线程
			worker_thread_ = new thread(WorkerFunction, info_block_);

			current_status_->store(SnStatus::kReady);
			return SnErrorCode::kSuccess;
		}
		else {
			current_status_->store(SnStatus::kNotInit);
			return SnErrorCode::kSnifferXIsInitialized;
		}


	}

	int SnifferX::Start() {
		auto expected_value = SnStatus::kReady;
		if (current_status_->compare_exchange_strong(expected_value, SnStatus::kRunning, memory_order_seq_cst)) {
			return SnErrorCode::kSuccess;
		}
		else {
			return SnErrorCode::kSnifferXIsNotReady;
		}
	}

	int SnifferX::Stop() {
		auto expected_value = SnStatus::kRunning;
		if (current_status_->compare_exchange_strong(expected_value, SnStatus::kReady, memory_order_seq_cst)) {
			return SnErrorCode::kSuccess;
		}
		else {
			return SnErrorCode::kSnifferXIsNotRunning;
		}
	}

	int SnifferX::Cleanup() {
		auto expected_value = SnStatus::kReady;
		if (current_status_->compare_exchange_strong(expected_value, SnStatus::kExiting, memory_order_seq_cst)) {
			if (worker_thread_ != NULL) {
				worker_thread_->join();
				delete worker_thread_;
				worker_thread_ = NULL;
			}
			int error = SnErrorCode::kSuccess;
			current_status_->store(SnStatus::kNotInit);
			if ((error = sock_.Cleanup()) == SnErrorCode::kSuccess) {
				return SnErrorCode::kSuccess;
			}
			else {
				return error;
			}
		}
		else {
			switch (current_status_->load(memory_order_seq_cst)) {
			case SnStatus::kNotInit:
				return SnErrorCode::kSuccess;
			case SnStatus::kInitializing:
				return SnErrorCode::kSnifferXIsNotReady;
			default:
				return SnErrorCode::kUnknown;
			}
		}
	}

	bool SnifferX::IsRunning() {
		return current_status_->load() == SnStatus::kRunning;
	}

	SnPackage * SnifferX::GetResult()
	{
		return packet_queue_->Take();
	}

	void SnifferX::WorkerFunction(shared_ptr<SnInfoBlock> & args) {

		int error = 0, recv_index = 0, other_recv_index = 0;
		const int single_recv_buffer_size = recv_buffer_size / 2;
		unsigned long recv_length[2] = { 0,0 };
		//双缓冲区，交替读取和分析
		char recv_buffer[single_recv_buffer_size][2];

		shared_ptr<SnInfoBlock> & current_info_block_ = args;
		SnAnalyzer analyzer;

		while (current_info_block_->current_status_.load(memory_order_seq_cst) != SnStatus::kExiting)
		{
			//将网络IO读入recv_buffer[recv_index]的时候，分析recv_buffer[other_recv_index]
			error = current_info_block_->sock_.RecvAsync(static_cast<void*>(recv_buffer[recv_index]), single_recv_buffer_size);
			if (other_recv_index > 0) {
				//分析recv_buffer[other_recv_index]
				SnPackage * package = (analyzer.Analize(recv_buffer[other_recv_index], recv_length[other_recv_index]));
				current_info_block_->packet_queue_.Put(package);
			}
			error = current_info_block_->sock_.WaitRecvResult(recv_length[recv_index], wait_for_recv_time_in_ms);
			if (current_info_block_->current_status_.load(memory_order_seq_cst) == SnStatus::kExiting)
				break;

			other_recv_index = recv_index;
			recv_index = (recv_index + 1) % 2;
		}
	}
}
