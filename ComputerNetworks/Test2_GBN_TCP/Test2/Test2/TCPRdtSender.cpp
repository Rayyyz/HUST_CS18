#include "stdafx.h"
#include "Global.h"
#include "TCPRdtSender.h"


TCPRdtSender::TCPRdtSender() :sendbase(1), nextseqnum(1),y(-1),extraack(0),waitingState(false)
{

}


TCPRdtSender::~TCPRdtSender()
{
}



bool TCPRdtSender::getWaitingState() {
	return waitingState;
}




bool TCPRdtSender::send(const Message& message) {
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
	if (sendbase == nextseqnum)	//启动发送方定时器
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[nextseqnum].seqnum);
	nextseqnum = (nextseqnum + 1) % TCP_SEQ_NUM;
	if ((nextseqnum - sendbase + TCP_SEQ_NUM) % TCP_SEQ_NUM >= TCP_WINDOW_SIZE)
		this->waitingState = true;	//进入等待状态	
	return true;
}

void TCPRdtSender::receive(const Packet& ackPkt) {

	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确
	if (checkSum == ackPkt.checksum)
	{
		//收到ACK,具有ACK字段值y
		y = ackPkt.acknum;
		// y>sendbase（注意这里不能等于） 且 y在窗口内的情况
		if (((y - sendbase + TCP_SEQ_NUM) % TCP_SEQ_NUM < TCP_WINDOW_SIZE) && (y != sendbase))
		{	//当收到的确认号在当前窗口内的时候
			this->waitingState = false;		// 将waitingState置为false			
			int tmp = sendbase;	
			//由于acknum之前的包一定被Receiver收到，但之前的ack可能有丢失，故下一个发送序号为确认序号acknum
			sendbase = y ;
			pUtils->printPacket("发送方正确收到确认", ackPkt);
			if (sendbase == nextseqnum)
				pns->stopTimer(SENDER, tmp);		//关闭定时器,注意关闭的是之前那个base值的定时器
			else {
				pns->stopTimer(SENDER, tmp);		//首先关闭定时器
				pns->startTimer(SENDER, Configuration::TIME_OUT, sendbase);		//重新启动发送方定时器
			}
			this->extraack = 0;	//对y收到的冗余ACK数置零
		}
		else
		{	//对已经确认的报文段的一个冗余ACK
			this->extraack++;	//对y收到的冗余ACK数加1
			cout << "发送方收到第" << extraack << "个冗余ACK，seqnum = " << ackPkt.acknum << endl;
			if (extraack == 3)	//如果收到三个冗余ACK，则执行快速重传
			{
				pUtils->printPacket("发送方收到对相同数据的三个冗余ACK，执行快速重传。",this->packetWaitingAck[y]);
				//重新发送具有序号y的报文段
				pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[y]);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
				y = -1;
				this->extraack = 0;
			}
		}
	}
	//else:发送方收到了错误的报文，则一直等待直到超时进行重发处理

}

void TCPRdtSender::timeoutHandler(int seqNum) {
	//单一的超时计算器
	pUtils->printPacket("发送方已超时，重新发送最早发送的报文段。", this->packetWaitingAck[sendbase]);
	pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//重新启动发送方定时器
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[sendbase]);//重新发送数据包
}
