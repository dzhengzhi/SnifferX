#pragma once

#include <string>

#include "common.h"

using namespace std;

namespace snifferx {

	//分析器分析后返回的结果
	class SNIFFERXCORE_API SnPackage {
	public:
		//获取网络层数据的接口
		virtual string & getNetworkLayerData() = 0;
		//获取运输层数据的接口
		virtual string & getTransportLayerData() = 0;
		//获取应用层数据的接口
		virtual string & getApplicationLayerData() = 0;
		virtual ~SnPackage() { };
	};
}