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
	if (this->waitingState) { //���ͷ����ڵȴ�ȷ��״̬
		return false;
	}
	this->packetWaitingAck[nextseqnum].acknum = -1; //���Ը��ֶ�
	this->packetWaitingAck[nextseqnum].seqnum = this->nextseqnum;
	this->packetWaitingAck[nextseqnum].checksum = 0;
	memcpy(this->packetWaitingAck[nextseqnum].payload, message.data, sizeof(message.data));
	this->packetWaitingAck[nextseqnum].checksum = pUtils->calculateCheckSum(this->packetWaitingAck[nextseqnum]);
	pUtils->printPacket("���ͷ����ͱ���", this->packetWaitingAck[nextseqnum]);
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[nextseqnum]);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
	if (base == nextseqnum)	//�������ͷ���ʱ��
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[nextseqnum].seqnum);
	nextseqnum = (nextseqnum + 1) % GBN_SEQ_NUM;
	if ((nextseqnum - base + GBN_SEQ_NUM) % GBN_SEQ_NUM >= GBN_WINDOW_SIZE)
		this->waitingState = true;	//����ȴ�״̬			
	return true;
}

void GBNRdtSender::receive(const Packet& ackPkt){

		//���У����Ƿ���ȷ
		int checkSum = pUtils->calculateCheckSum(ackPkt);
	
		//���У�����ȷ
		if (checkSum == ackPkt.checksum ){
			//ֻ�е��յ���ack�ڵ�ǰ�����ڵ�ʱ��Ž��д���, ����ֱ�Ӷ���
			if ((ackPkt.acknum - base + GBN_SEQ_NUM) % GBN_SEQ_NUM < GBN_WINDOW_SIZE)
			{
				this->waitingState = false;		// ��waitingState��Ϊfalse			
				int tmp = base;
				//����acknum֮ǰ�İ�һ����Receiver�յ�����֮ǰ��ack�����ж�ʧ������һ���������ֱ��Ϊacknum+1��������base+1��
				base = (ackPkt.acknum + 1) % GBN_SEQ_NUM;	
				pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
				if (base == nextseqnum)
					pns->stopTimer(SENDER, tmp);		//�رն�ʱ��,ע��رյ���֮ǰ�Ǹ�baseֵ�Ķ�ʱ��
				else {
					pns->stopTimer(SENDER, tmp);		//���ȹرն�ʱ��
					pns->startTimer(SENDER, Configuration::TIME_OUT, base);		//�����������ͷ���ʱ��
				}				
			}

		}
		//else:���ͷ��յ��˴���ı��ģ���һֱ�ȴ�ֱ����ʱ�����ط�����

}

void GBNRdtSender::timeoutHandler(int seqNum) {

	cout << "���ͷ���ʱ��ʱ�䵽���ط�[" << base << "," << nextseqnum - 1 << "]�ı���";
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//�����������ͷ���ʱ��
	int len = (nextseqnum - base + GBN_SEQ_NUM) % GBN_SEQ_NUM;
	for (int i = 0, j = base; i < len; i++,j = (j + 1) % GBN_SEQ_NUM)
	{
		pUtils->printPacket("���·������ݰ�", packetWaitingAck[j]);
		pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[j]);		//���·������ݰ�
	}

}
