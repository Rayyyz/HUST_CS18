#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"
class SRRdtReceiver :public RdtReceiver
{
private:

	int rcv_base;		//���շ��Ļ����
	bool rcvseq[SR_SEQ_NUM];	//���ܷ���Ľ���״̬
	Message rcvmsg[SR_SEQ_NUM];	//��ȷ�յ������ACK��Ϣ
	Packet lastAckPkt;	//�ϴη��͵�ȷ�ϱ���

public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();

public:
	void receive(const Packet& packet);	//���ձ��ģ�����NetworkService����
};

#endif#pragma once
