#ifndef STOP_WAIT_RDT_RECEIVER_H
#define STOP_WAIT_RDT_RECEIVER_H
#include "RdtReceiver.h"
class StopWaitRdtReceiver :public RdtReceiver
{
private:
	int expectSequenceNumberRcvd;	// �ڴ��յ�����һ���������
	Packet lastAckPkt;				//�ϴη��͵�ȷ�ϱ���

public:
	StopWaitRdtReceiver();
	virtual ~StopWaitRdtReceiver();

public:
	
	void receive(const Packet &packet);	//���ձ��ģ�����NetworkService����
};

#endif

