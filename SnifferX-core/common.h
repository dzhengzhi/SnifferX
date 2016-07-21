#pragma once

#include "stdafx.h"

#ifdef SNIFFERXCORE_EXPORTS
#define SNIFFERXCORE_API __declspec(dllexport)
#else
#define SNIFFERXCORE_API __declspec(dllimport)
#endif

namespace snifferx {

	//SnSocket当前状态
	enum class SNIFFERXCORE_API SnSocketStatus {
		//未初始化
		kNotInit,
		//正在初始化
		kInitializing,
		//就绪
		kReady,
		//正在接收数据
		kReceiving,
	};

	//SnifferX当前状态
	enum class SNIFFERXCORE_API SnStatus {
		//未初始化
		kNotInit,
		//正在初始化
		kInitializing,
		//就绪
		kReady,
		//正在运行
		kRunning,
		//正在退出
		kExiting,
	};

}