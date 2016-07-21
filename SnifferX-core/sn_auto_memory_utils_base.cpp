#include "sn_auto_memory_utils_base.h"

snifferx::SnAutoMemoryUtilsBase::~SnAutoMemoryUtilsBase()
{
	for (auto i = ptrs_.begin();i != ptrs_.end();i++) {
		auto value = *i;
		switch (value.type) {
		case AllocType::normal:
			delete value.ptr_;
			break;
		case AllocType::win32_global:
			GlobalFree(value.ptr_);
			break;
		}
	}
}

void snifferx::SnAutoMemoryUtilsBase::PutRecord(void * ptr, AllocType type)
{
	Record record_;
	record_.ptr_ = ptr;
	record_.type = type;
	ptrs_.push_back(record_);
}
