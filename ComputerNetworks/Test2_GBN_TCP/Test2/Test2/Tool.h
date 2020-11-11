#ifndef TOOL_H
#define TOOL_H
#include "DataStructure.h"

struct Tool{
	/* ��ӡPacket����Ϣ*/
	virtual void printPacket(const char * description, const Packet &packet) = 0;
	/*����һ��Packet��У���*/
	virtual int calculateCheckSum(const Packet &packet) = 0;
	/*����һ�����ȷֲ���[0-1]��������*/
	virtual double random() = 0;

	virtual ~Tool() = 0;
};

#endif