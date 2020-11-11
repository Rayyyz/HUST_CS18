#ifndef TCP_RDT_SENDER_H
#define TCP_RDT_SENDER_H
#include "RdtSender.h"
#include "DataStructure.h"

//TCP_WINDOW_SIZE = 4
//TCP_SEQ_BIT = 3
class TCPRdtSender :public RdtSender
{
private:
	int sendbase;		//最早未被确认的字节的序号
	int nextseqnum;		//已传递的报文段的后一个序号
	int y;				//收到ACK，具有ACK字段值y
	int extraack;       //收到冗余ack的数量
	bool waitingState;	//是否处于等待Ack的状态
	Packet packetWaitingAck[GBN_SEQ_NUM];		//已发送并等待Ack的数据包

public:

	bool getWaitingState();
	bool send(const Message& message);		//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet& ackPkt);		//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);		//Timeout handler，将被NetworkServiceSimulator调用

public:
	TCPRdtSender();
	virtual ~TCPRdtSender();
};

#endif

