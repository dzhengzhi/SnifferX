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
			case SnErrorCode::kSuccess:wsprintf(buffer, TEXT("�ɹ�"));break;
			case SnErrorCode::kUnknown:wsprintf(buffer, TEXT("δ֪����"));break;
			case SnErrorCode::kSnifferXIsReceiving:wsprintf(buffer, TEXT("SnifferX���ڽ�������"));break;
			case SnErrorCode::kSnifferXIsInitialized:wsprintf(buffer, TEXT("SnifferX�Ѿ���ʼ��"));break;
			case SnErrorCode::kSnifferXIsRunning:wsprintf(buffer, TEXT("SnifferX��������"));break;
			case SnErrorCode::kSnifferXIsNotReady:wsprintf(buffer, TEXT("SnifferX��ǰ��δ����"));break;
			case SnErrorCode::kSnifferXIsNotReceiving:wsprintf(buffer, TEXT("SnifferX��ǰ���ڽ�������"));break;
			case SnErrorCode::kSnifferXIsNotRunning:wsprintf(buffer, TEXT("SnifferX��ǰ��������"));break;
			case SnErrorCode::kInvalidArgument:wsprintf(buffer, TEXT("�ڲ�����:�Ƿ�����"));break;
			case SnErrorCode::kSnifferXCannotCreateThread:wsprintf(buffer, TEXT("�ڲ�����:�����߳�ʧ��"));break;
			}
			return true;
		}

		DWORD buffer_length_;
		LPWSTR buffer_ptr_;

		DWORD flags_ = FORMAT_MESSAGE_IGNORE_INSERTS |
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM;

		//����ϵͳ����ģ��
		if (module_handle_ == NULL) {
			module_handle_ = LoadLibraryEx(
				TEXT("netmsg.dll"),
				NULL,
				LOAD_LIBRARY_AS_DATAFILE
				);

			if (module_handle_ != NULL)
				flags_ |= FORMAT_MESSAGE_FROM_HMODULE;
		}

		//��ô����ı�
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