#include "sn_error_message.h"
#include "sn_errorcode.h"

namespace snifferx {

	SnErrorMessage::SnErrorMessage()
	{
	}

	bool SnErrorMessage::GetErrorMessage(int error_code, wchar_t * & buffer)
	{
		if (error_code <= 0) {
			buffer = reinterpret_cast<wchar_t *>(GlobalAlloc(GMEM_FIXED, 256));
			if (buffer == NULL) {
				return false;
			}
			PutRecord(buffer, AllocType::win32_global);
			switch (error_code) {
			case SnErrorCode::kSuccess:wsprintf(buffer, TEXT("成功"));break;
			case SnErrorCode::kUnknown:wsprintf(buffer, TEXT("未知错误"));break;
			case SnErrorCode::kSnifferXIsReceiving:wsprintf(buffer, TEXT("SnifferX正在接收数据"));break;
			case SnErrorCode::kSnifferXIsInitialized:wsprintf(buffer, TEXT("SnifferX已经初始化"));break;
			case SnErrorCode::kSnifferXIsRunning:wsprintf(buffer, TEXT("SnifferX正在运行"));break;
			case SnErrorCode::kSnifferXIsNotReady:wsprintf(buffer, TEXT("SnifferX当前并未就绪"));break;
			case SnErrorCode::kSnifferXIsNotReceiving:wsprintf(buffer, TEXT("SnifferX当前不在接收数据"));break;
			case SnErrorCode::kSnifferXIsNotRunning:wsprintf(buffer, TEXT("SnifferX当前不在运行"));break;
			case SnErrorCode::kInvalidArgument:wsprintf(buffer, TEXT("内部错误:非法参数"));break;
			case SnErrorCode::kSnifferXCannotCreateThread:wsprintf(buffer, TEXT("内部错误:创建线程失败"));break;
			}
			return true;
		}

		DWORD buffer_length_;
		LPWSTR buffer_ptr_;

		DWORD flags_ = FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM;

		//加载系统网络模块
		if (module_handle_ == NULL) {
			module_handle_ = LoadLibraryEx(
				TEXT("netmsg.dll"),
				NULL,
				LOAD_LIBRARY_AS_DATAFILE
				);

			if (module_handle_ != NULL)
				flags_ |= FORMAT_MESSAGE_FROM_HMODULE;
		}

		//获得错误文本
		buffer_length_ = FormatMessage(
			flags_,
			module_handle_,
			error_code,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPWSTR)&buffer_ptr_,
			0,
			NULL
			);



		if (buffer_length_ >= 0) {
			buffer = buffer_ptr_;
			PutRecord(buffer_ptr_, AllocType::win32_global);
			return true;
		}
		else {
			return false;
		}
	}

	SnErrorMessage::~SnErrorMessage()
	{
		if (module_handle_ != NULL) {
			FreeLibrary(module_handle_);
		}
	}

}