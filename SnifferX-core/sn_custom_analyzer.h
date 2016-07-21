#pragma once

#include "sn_package.h"

namespace snifferx {

	//�Զ���������ӿ�
	class SnCustomAnalyzer
	{
	public:
		SnCustomAnalyzer();
		virtual ~SnCustomAnalyzer();
		//�������ݽӿ�
		virtual SnPackage * Analize(const void * buffer, int length) = 0;
		//�Զ�����Ҫʵ������ӿ��Ա㰲ȫɾ��ͨ��Analize�ӿڷ��ص����ݷ������
		virtual void DeleteSnPackage(SnPackage * package);
	};
}

