#include "stdafx.h"
#include "Global.h"
#include "GBNRdtSender.h"


GBNRdtSender::GBNRdtSender() :base(1), nextseqnum(1), waitingState(false)
{
}


GBNRdtSender::~GBNRdtSender()
{
}



bool GBNRdtSender::getWaitingState() {
	return waitingState;
}




bool GBNRdtSender::send(const Message& message) {
	if (this->waitingState) { //发送方处于等待确认状态
		return false;
	}
	this->packetWaitingAck[nextseqnum].acknum = -1; //忽略该字段
	this->packetWaitingAck[nextseqnum].seqnum = this->nextseqnum;
	this->packetWaitingAck[nextseqnum].checksum = 0;
	memcpy(this->packetWaitingAck[nextseqnum].payload, message.data, sizeof(message.data));
	this->packetWaitingAck[nextseqnum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextseqnum]);
	pUtils->printPacket("发送方发送报文", this->packetWaitingAck[nextseqnum]);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[nextseqnum]);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
	if (base == nextseqnum)	//启动发送方定时器
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[nextseqnum].seqnum);
	nextseqnum = (nextseqnum + 1) % GBN_SEQ_NUM;
	if ((nextseqnum - base + GBN_SEQ_NUM) % GBN_SEQ_NUM >= GBN_WINDOW_SIZE)
		this->waitingState = true;	//进入等待状态			
	return true;
}

void GBNRdtSender::receive(const Packet& ackPkt){

		//检查校验和是否正确
		int checkSum = pUtils->calculateCheckSum(ackPkt);
	
		//如果校验和正确
		if (checkSum == ackPkt.checksum ){
			//只有当收到的ack在当前窗口内的时候才进行处理, 否则直接丢弃
			if ((ackPkt.acknum - base + GBN_SEQ_NUM) % GBN_SEQ_NUM < GBN_WINDOW_SIZE)
			{
				this->waitingState = false;		// 将waitingState置为false			
				int tmp = base;
				//由于acknum之前的包一定被Receiver收到，但之前的ack可能有丢失，故下一个发送序号直接为acknum+1（而不是base+1）
				base = (ackPkt.acknum + 1) % GBN_SEQ_NUM;	
				pUtils->printPacket("发送方正确收到确认", ackPkt);
				if (base == nextseqnum)
					pns->stopTimer(SENDER, tmp);		//关闭定时器,注意关闭的是之前那个base值的定时器
				else {
					pns->stopTimer(SENDER, tmp);		//首先关闭定时器
					pns->startTimer(SENDER, Configuration::TIME_OUT, base);		//重新启动发送方定时器
				}				
			}

		}
		//else:发送方收到了错误的报文，则一直等待直到超时进行重发处理

}

void GBNRdtSender::timeoutHandler(int seqNum) {

	cout << "发送方定时器时间到，重发[" << base << "," << nextseqnum - 1 << "]的报文";
	pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//重新启动发送方定时器
	int len = (nextseqnum - base + GBN_SEQ_NUM) % GBN_SEQ_NUM;
	for (int i = 0, j = base; i < len; i++,j = (j + 1) % GBN_SEQ_NUM)
	{
		pUtils->printPacket("重新发送数据包", packetWaitingAck[j]);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[j]);		//重新发送数据包
	}

}
