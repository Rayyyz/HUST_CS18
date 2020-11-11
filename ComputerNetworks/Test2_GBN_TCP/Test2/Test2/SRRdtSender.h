#ifndef SR_RDT_SENDER_H
#define SR_RDT_SENDER_H
#include "RdtSender.h"
#include "DataStructure.h"

//SR_WINDOW_SIZE = 4
//SR_SEQ_BIT = 3
class SRRdtSender :public RdtSender
{
private:
	int send_base;	//���ͷ������
	int nextseqnum;	//��һ�����
	bool waitingState;			//�Ƿ��ڵȴ�Ack��״̬
	bool rcvpkt[SR_SEQ_NUM];	//���յ�������ĳЩ�����ACK
	Packet packetWaitingAck[SR_SEQ_NUM];	//�ѷ��Ͳ��ȴ�Ack�����ݰ�

public:

	bool getWaitingState();
	bool send(const Message& message);		//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet& ackPkt);		//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);		//Timeout handler������NetworkServiceSimulator����

public:
	SRRdtSender();
	virtual ~SRRdtSender();
};

#endif

#pragma once
