#ifndef RDT_RECEIVER_H
#define RDT_RECEIVER_H


#include "DataStructure.h"
//����RdtReceiver�����࣬�涨�˱���ʵ�ֵ�һ���ӿڷ���
//������������GBNRdtReceiver��GBNRdtReceiver���������һ�������ľ���ʵ��
//ֻ���ǵ����䣬�����շ�ֻ��������
struct  RdtReceiver
{
	//���ձ��ģ�����NetworkService����	
	virtual void receive(const Packet &packet) = 0;
	virtual ~RdtReceiver() = 0;
};

#endif