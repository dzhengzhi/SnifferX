#pragma once

#include "sn_package.h"
#include "sn_custom_analyzer.h"
#include <list>

namespace snifferx {

	class SnAnalyzer
	{
	public:
		//分析数据
		SnPackage * Analize(const void * buffer, int length);
		SnAnalyzer();
		~SnAnalyzer();
		//注册自定义分析器
		void RegisterCustomAnalyzer(SnCustomAnalyzer* customAnalyzer);
		//注销自定义分析器
		void UnregisterCustomAnalyzer(SnCustomAnalyzer* customAnalyzer);
	private:
		//分析器存储区
		std::list<SnCustomAnalyzer*> analyzer_list_;
	};

}