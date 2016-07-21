#pragma once

namespace snifferx {

	//错误代码
	enum SnErrorCode : int {
		//成功
		kSuccess = 0,
		//未知错误
		kUnknown = -1,
		//正在接收数据
		kSnifferXIsReceiving = -2,
		//已经完成初始化
		kSnifferXIsInitialized = -3,
		//正在运行
		kSnifferXIsRunning = -4,
		//尚未就绪
		kSnifferXIsNotReady = -5,
		//当前不在接收数据
		kSnifferXIsNotReceiving = -6,
		//没有运行
		kSnifferXIsNotRunning = -7,
		//非法参数
		kInvalidArgument = -8,
		//无法创建线程
		kSnifferXCannotCreateThread = -9,
	};

}