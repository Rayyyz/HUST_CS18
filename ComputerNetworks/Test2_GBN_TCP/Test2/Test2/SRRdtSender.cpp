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
	if (this->waitingState) { //���ͷ����ڵȴ�ȷ��״̬
		return false;
	}
	rcvpkt[nextseqnum] == false;	//����Ӧ������ŵ�rcvpkt����
	this->packetWaitingAck[nextseqnum].acknum = -1; //���Ը��ֶ�
	this->packetWaitingAck[nextseqnum].seqnum = this->nextseqnum;
	this->packetWaitingAck[nextseqnum].checksum = 0;
	memcpy(this->packetWaitingAck[nextseqnum].payload, message.data, sizeof(message.data));
	this->packetWaitingAck[nextseqnum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextseqnum]);
	pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck[nextseqnum]);
	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[nextseqnum]);
	//�������ͷ���ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[nextseqnum].seqnum);
	//nextseqnum++
	this->nextseqnum = (this->nextseqnum + 1) % SR_SEQ_NUM;
	if ((nextseqnum - send_base + SR_SEQ_NUM) % SR_SEQ_NUM >= SR_WINDOW_SIZE)
		this->waitingState = true;	//����ȴ�״̬					
	return true;
}

void SRRdtSender::receive(const Packet& ackPkt) {

	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ
	if (checkSum == ackPkt.checksum) {
		//ֻ�е��յ���ack�ڵ�ǰ������,��֮ǰδ�յ����Ž��д���, ����ֱ�Ӷ���
		if (rcvpkt[ackPkt.acknum] == false &&(ackPkt.acknum - send_base + SR_SEQ_NUM) % SR_SEQ_NUM < SR_WINDOW_SIZE)
		{
			rcvpkt[ackPkt.acknum] = true;		//����Ӧ������Ϊ�ѽ���
			pns->stopTimer(SENDER, ackPkt.acknum);		//�رշ��鶨ʱ��
			pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
			//����÷������ŵ���send_base���򴰿ڻ������ǰ�ƶ���������С��ŵ�δȷ�Ϸ��鴦
			int len = (nextseqnum - send_base + SR_SEQ_NUM) % SR_SEQ_NUM;
			if (send_base == ackPkt.acknum) {
				for (int i = 0, j = send_base; i < len; i++, j = (j + 1) % SR_SEQ_NUM) {
					if (rcvpkt[j] == true) {
						rcvpkt[j] = false;
						send_base = (send_base + 1) % SR_SEQ_NUM;
					}
					else break;
				}
				this->waitingState = false;		// ��waitingState��Ϊfalse	
			}
		}

	}
	//else:���ͷ��յ��˴���ı��ģ���һֱ�ȴ�ֱ����ʱ�����ط�����

}

void SRRdtSender::timeoutHandler(int seqNum) {

	cout << "���ͷ���ʱ��ʱ�䵽���ط�" << seqNum << "�ı���";
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	pUtils->printPacket("���·������ݰ�", packetWaitingAck[seqNum]);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[seqNum]);	//���·������ݰ�
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//�����������ͷ���ʱ��

}
