#pragma once

#include <Windows.h>

#include <vector>

using namespace std;

namespace snifferx {

	//一个自动管理内存的类，在析构的时候自动释放自己管理内存
	class SnAutoMemoryUtilsBase
	{
	public:
		enum class AllocType
		{
			normal,
			win32_global,
		};

		struct Record
		{
			void * ptr_;
			AllocType type;
		};

		SnAutoMemoryUtilsBase() = default;
		~SnAutoMemoryUtilsBase();
		//登记内存
		//在这里登记的内存将在析构的时候自动释放
		void PutRecord(void * ptr, AllocType type);

	private:
		vector<Record> ptrs_;

	};

}