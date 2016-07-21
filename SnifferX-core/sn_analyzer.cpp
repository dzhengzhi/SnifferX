
#include "sn_analyzer.h"

namespace snifferx {

	SnPackage * SnAnalyzer::Analize(const void * buffer, int length)
	{
		SnPackage * package = NULL;
		if (buffer != NULL) {
			for each (auto var in analyzer_list_) {
				if ((package = var->Analize(buffer, length)) != NULL) {
					break;
				}
			}
		}
		return package;
	}

	SnAnalyzer::SnAnalyzer()
	{
	}


	SnAnalyzer::~SnAnalyzer()
	{
	}

	void SnAnalyzer::RegisterCustomAnalyzer(SnCustomAnalyzer *custom_analyzer)
	{
		if (custom_analyzer != NULL) {
			analyzer_list_.push_back(custom_analyzer);
		}
		
	}
	void SnAnalyzer::UnregisterCustomAnalyzer(SnCustomAnalyzer *custom_analyzer)
	{
		if (custom_analyzer != NULL) {
			analyzer_list_.remove(custom_analyzer);
		}
	}
}