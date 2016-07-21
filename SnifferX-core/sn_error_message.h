#pragma once

#include <windows.h>  

#include "sn_auto_memory_utils_base.h"

namespace snifferx {

	class SnErrorMessage : SnAutoMemoryUtilsBase
	{
	public:
		SnErrorMessage();
		//获得错误信息
		//如果成功，返回true，错误文本通过buffer返回
		//否则，返回false
		bool GetErrorMessage(int error_code, wchar_t * & buffer);
		~SnErrorMessage();
	private:
		HMODULE module_handle_ = NULL;
	};

}