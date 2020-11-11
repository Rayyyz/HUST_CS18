#ifndef TCP_RDT_SENDER_H
#define TCP_RDT_SENDER_H
#include "RdtSender.h"
#include "DataStructure.h"

//TCP_WINDOW_SIZE = 4
//TCP_SEQ_BIT = 3
class TCPRdtSender :public RdtSender
{
private:
	int sendbase;		//����δ��ȷ�ϵ��ֽڵ����
	int nextseqnum;		//�Ѵ��ݵı��Ķεĺ�һ�����
	int y;				//�յ�ACK������ACK�ֶ�ֵy
	int extraack;       //�յ�����ack������
	bool waitingState;	//�Ƿ��ڵȴ�Ack��״̬
	Packet packetWaitingAck[GBN_SEQ_NUM];		//�ѷ��Ͳ��ȴ�Ack�����ݰ�

public:

	bool getWaitingState();
	bool send(const Message& message);		//����Ӧ�ò�������Message����NetworkServiceSimulator����,������ͷ��ɹ��ؽ�Message���͵�����㣬����true;�����Ϊ���ͷ����ڵȴ���ȷȷ��״̬���ܾ�����Message���򷵻�false
	void receive(const Packet& ackPkt);		//����ȷ��Ack������NetworkServiceSimulator����	
	void timeoutHandler(int seqNum);		//Timeout handler������NetworkServiceSimulator����

public:
	TCPRdtSender();
	virtual ~TCPRdtSender();
};

#endif

