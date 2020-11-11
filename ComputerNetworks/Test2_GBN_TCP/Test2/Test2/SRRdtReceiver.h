#ifndef SR_RDT_RECEIVER_H
#define SR_RDT_RECEIVER_H
#include "RdtReceiver.h"
class SRRdtReceiver :public RdtReceiver
{
private:

	int rcv_base;		//接收方的基序号
	bool rcvseq[SR_SEQ_NUM];	//接受分组的接收状态
	Message rcvmsg[SR_SEQ_NUM];	//正确收到分组的ACK信息
	Packet lastAckPkt;	//上次发送的确认报文

public:
	SRRdtReceiver();
	virtual ~SRRdtReceiver();

public:
	void receive(const Packet& packet);	//接收报文，将被NetworkService调用
};

#endif#pragma once
