#pragma once

#include <string>

#include "common.h"

using namespace std;

namespace snifferx {

	//�����������󷵻صĽ��
	class SNIFFERXCORE_API SnPackage {
	public:
		//��ȡ��������ݵĽӿ�
		virtual string & getNetworkLayerData() = 0;
		//��ȡ��������ݵĽӿ�
		virtual string & getTransportLayerData() = 0;
		//��ȡӦ�ò����ݵĽӿ�
		virtual string & getApplicationLayerData() = 0;
		virtual ~SnPackage() { };
	};
}