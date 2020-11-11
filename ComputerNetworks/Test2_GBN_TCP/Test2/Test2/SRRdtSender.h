#ifndef SR_RDT_SENDER_H
#define SR_RDT_SENDER_H
#include "RdtSender.h"
#include "DataStructure.h"

//SR_WINDOW_SIZE = 4
//SR_SEQ_BIT = 3
class SRRdtSender :public RdtSender
{
private:
	int send_base;	//发送方基序号
	int nextseqnum;	//下一个序号
	bool waitingState;			//是否处于等待Ack的状态
	bool rcvpkt[SR_SEQ_NUM];	//已收到窗口中某些分组的ACK
	Packet packetWaitingAck[SR_SEQ_NUM];	//已发送并等待Ack的数据包

public:

	bool getWaitingState();
	bool send(const Message& message);		//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet& ackPkt);		//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);		//Timeout handler，将被NetworkServiceSimulator调用

public:
	SRRdtSender();
	virtual ~SRRdtSender();
};

#endif

#pragma once
