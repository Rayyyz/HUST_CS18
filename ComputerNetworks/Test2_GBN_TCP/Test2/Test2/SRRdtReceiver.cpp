#include "stdafx.h"
#include "Global.h"
#include "SRRdtReceiver.h"


SRRdtReceiver::SRRdtReceiver() :rcv_base(1)
{
	for (int i = 0; i < SR_SEQ_NUM; i++)
		rcvseq[i] = false;
	lastAckPkt.acknum = -1; //初始状态下，上次发送的确认包的确认序号为-1，使得当第一个接受的数据包出错时该确认报文的确认号为-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//忽略该字段
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


SRRdtReceiver::~SRRdtReceiver()
{
}

void SRRdtReceiver::receive(const Packet& packet) {
	//检查校验和是否正确
	int checkSum = pUtils->calculateCheckSum(packet);
	//如果校验和正确，同时收到报文的序号在rcv_base和rcv_base+SR_WINDOW_SIZE-1之间
	if (checkSum == packet.checksum && (packet.seqnum - rcv_base + SR_SEQ_NUM)%SR_SEQ_NUM <= SR_WINDOW_SIZE - 1 ) {
		int delnum = 0;	//用于记录提交的分组数目
		if (rcvseq[packet.seqnum] == false) {
			//如果该分组之前没收到过，则缓存该分组
			memcpy(rcvmsg[packet.seqnum].data, packet.payload, sizeof(packet.payload));
			rcvseq[packet.seqnum] = true;
			pUtils->printPacket("接收方正确收到发送方的报文", packet);
		}
		if (packet.seqnum == this->rcv_base)
		{	//如果该分组序号等于接收窗口的基序号，则将该分组以及之前的分组上交给应用层
			for (int i = 0, j = rcv_base; i < SR_SEQ_NUM; i++, j = (j + 1) % SR_SEQ_NUM) {
				if (rcvseq[j] == false) {
					//记录一下提交的分组数目
					delnum = i;
					break;
				}
				//取出Message，向上递交给应用层
				pns->delivertoAppLayer(RECEIVER, rcvmsg[j]);
				//重置rcvseq数组
				rcvseq[j] = false;
			}
			cout << "↑接收方收到基序号的分组，向上递交["<<rcv_base<<","<< (rcv_base + delnum - 1 + SR_SEQ_NUM) % SR_SEQ_NUM <<"]的报文↑\n";
		}
		//接收序号根据提交的分组数量进行窗口切换
		rcv_base = (rcv_base + delnum ) % SR_SEQ_NUM;
		//发送ACK
		lastAckPkt.acknum = packet.seqnum;			//确认序号等于收到的报文序号
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("接收方发送确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方

	}
	//如果校验和正确，同时收到报文的序号在rcv_base - SR_WINDOW_SIZE和rcv_base-1之间
	else if (checkSum == packet.checksum && (packet.seqnum - (rcv_base - SR_WINDOW_SIZE + SR_SEQ_NUM) % SR_SEQ_NUM + SR_SEQ_NUM) % SR_SEQ_NUM <= SR_WINDOW_SIZE - 1) {
		//发送ACK
		lastAckPkt.acknum = packet.seqnum;			//确认序号等于收到的报文序号
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("接收方发送确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送确认报文到对方
	}
	else {
		if (checkSum != packet.checksum) {
			pUtils->printPacket("接收方没有正确收到发送方的报文,数据校验错误", packet);
		}
		else {
			pUtils->printPacket("接收方没有正确收到发送方的报文,报文序号不对", packet);
		}
		pUtils->printPacket("接收方重新发送上次的确认报文", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//调用模拟网络环境的sendToNetworkLayer，通过网络层发送上次的确认报文

	}
}