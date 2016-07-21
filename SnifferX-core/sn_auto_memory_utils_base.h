#pragma once

#include <Windows.h>

#include <vector>

using namespace std;

namespace snifferx {

	//һ���Զ������ڴ���࣬��������ʱ���Զ��ͷ��Լ������ڴ�
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
		//�Ǽ��ڴ�
		//������Ǽǵ��ڴ潫��������ʱ���Զ��ͷ�
		void PutRecord(void * ptr, AllocType type);

	private:
		vector<Record> ptrs_;

	};

}