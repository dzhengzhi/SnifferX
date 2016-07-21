#include "sn_custom_analyzer.h"


namespace snifferx {

	SnCustomAnalyzer::SnCustomAnalyzer()
	{
	}


	SnCustomAnalyzer::~SnCustomAnalyzer()
	{
	}
	void SnCustomAnalyzer::DeleteSnPackage(SnPackage * package)
	{
		delete package;
	}
}