#pragma once

#include <windows.h>  

#include "sn_auto_memory_utils_base.h"

namespace snifferx {

	class SnErrorMessage : SnAutoMemoryUtilsBase
	{
	public:
		SnErrorMessage();
		//��ô�����Ϣ
		//����ɹ�������true�������ı�ͨ��buffer����
		//���򣬷���false
		bool GetErrorMessage(int error_code, wchar_t * & buffer);
		~SnErrorMessage();
	private:
		HMODULE module_handle_ = NULL;
	};

}