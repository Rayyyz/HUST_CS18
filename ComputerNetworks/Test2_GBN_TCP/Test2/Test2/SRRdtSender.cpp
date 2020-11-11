#include "stdafx.h"
#include "Global.h"
#include "SRRdtSender.h"


SRRdtSender::SRRdtSender() :send_base(1), nextseqnum(1), waitingState(false)
{
	for (int i = 0; i < SR_SEQ_NUM; i++){
		rcvpkt[i] = false;
	}
}

SRRdtSender::~SRRdtSender()
{
}

bool SRRdtSender::getWaitingState() {
	return waitingState;
}

bool SRRdtSender::send(const Message& message) {
	if (this->waitingState) { //发送方处于等待确认状态
		return false;
	}
	rcvpkt[nextseqnum] == false;	//将对应报文序号的rcvpkt置零
	this->packetWaitingAck[nextseqnum].acknum = -1; //忽略该字段
	this->packetWaitingAck[nextseqnum].seqnum = this->nextseqnum;
	this->packetWaitingAck[nextseqnum].checksum = 0;
	memcpy(this->packetWaitingAck[nextseqnum].payload, message.data, sizeof(message.data));
	this->packetWaitingAck[nextseqnum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextseqnum]);
	pUtils->printPacket("发送方发送报文", this->packetWaitingAck[nextseqnum]);
	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送到对方
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[nextseqnum]);
	//启动发送方定时器
	pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[nextseqnum].seqnum);
	//nextseqnum++
	this->nextseqnum = (this->nextseqnum + 1) % SR_SEQ_NUM;
	if ((nextseqnum - send_base + SR_SEQ_NUM) % SR_SEQ_NUM >= SR_WINDOW_SIZE)
		this->waitingState = true;	//进入等待状态					
	return true;
}

void SRRdtSender::receive(const Packet& ackPkt) {

	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//如果校验和正确
	if (checkSum == ackPkt.checksum) {
		//只有当收到的ack在当前窗口内,且之前未收到过才进行处理, 否则直接丢弃
		if (rcvpkt[ackPkt.acknum] == false &&(ackPkt.acknum - send_base + SR_SEQ_NUM) % SR_SEQ_NUM < SR_WINDOW_SIZE)
		{
			rcvpkt[ackPkt.acknum] = true;		//将对应分组标记为已接收
			pns->stopTimer(SENDER, ackPkt.acknum);		//关闭分组定时器
			pUtils->printPacket("发送方正确收到确认", ackPkt);
			//如果该分组的序号等于send_base，则窗口基序号向前移动到具有最小序号的未确认分组处
			int len = (nextseqnum - send_base + SR_SEQ_NUM) % SR_SEQ_NUM;
			if (send_base == ackPkt.acknum) {
				for (int i = 0, j = send_base; i < len; i++, j = (j + 1) % SR_SEQ_NUM) {
					if (rcvpkt[j] == true) {
						rcvpkt[j] = false;
						send_base = (send_base + 1) % SR_SEQ_NUM;
					}
					else break;
				}
				this->waitingState = false;		// 将waitingState置为false	
			}
		}

	}
	//else:发送方收到了错误的报文，则一直等待直到超时进行重发处理

}

void SRRdtSender::timeoutHandler(int seqNum) {

	cout << "发送方定时器时间到，重发" << seqNum << "的报文";
	pns->stopTimer(SENDER, seqNum);										//首先关闭定时器
	pUtils->printPacket("重新发送数据包", packetWaitingAck[seqNum]);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum]);	//重新发送数据包
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//重新启动发送方定时器

}
