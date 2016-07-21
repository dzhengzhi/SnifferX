#pragma once

#include "sn_package.h"
#include "sn_custom_analyzer.h"
#include <list>

namespace snifferx {

	class SnAnalyzer
	{
	public:
		//��������
		SnPackage * Analize(const void * buffer, int length);
		SnAnalyzer();
		~SnAnalyzer();
		//ע���Զ��������
		void RegisterCustomAnalyzer(SnCustomAnalyzer* customAnalyzer);
		//ע���Զ��������
		void UnregisterCustomAnalyzer(SnCustomAnalyzer* customAnalyzer);
	private:
		//�������洢��
		std::list<SnCustomAnalyzer*> analyzer_list_;
	};

}