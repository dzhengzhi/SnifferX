#pragma once

#include "sn_package.h"

namespace snifferx {

	//自定义分析器接口
	class SnCustomAnalyzer
	{
	public:
		SnCustomAnalyzer();
		virtual ~SnCustomAnalyzer();
		//分析数据接口
		virtual SnPackage * Analize(const void * buffer, int length) = 0;
		//自定义需要实现这个接口以便安全删除通过Analize接口返回的数据分析结果
		virtual void DeleteSnPackage(SnPackage * package);
	};
}

