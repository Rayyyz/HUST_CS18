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
	if (sendbase == nextseqnum)	//�������ͷ���ʱ��
		pns->startTimer(SENDER, Configuration::TIME_OUT, this->packetWaitingAck[nextseqnum].seqnum);
	nextseqnum = (nextseqnum + 1) % TCP_SEQ_NUM;
	if ((nextseqnum - sendbase + TCP_SEQ_NUM) % TCP_SEQ_NUM >= TCP_WINDOW_SIZE)
		this->waitingState = true;	//����ȴ�״̬	
	return true;
}

void TCPRdtSender::receive(const Packet& ackPkt) {

	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(ackPkt);

	//���У�����ȷ
	if (checkSum == ackPkt.checksum)
	{
		//�յ�ACK,����ACK�ֶ�ֵy
		y = ackPkt.acknum;
		// y>sendbase��ע�����ﲻ�ܵ��ڣ� �� y�ڴ����ڵ����
		if (((y - sendbase + TCP_SEQ_NUM) % TCP_SEQ_NUM < TCP_WINDOW_SIZE) && (y != sendbase))
		{	//���յ���ȷ�Ϻ��ڵ�ǰ�����ڵ�ʱ��
			this->waitingState = false;		// ��waitingState��Ϊfalse			
			int tmp = sendbase;	
			//����acknum֮ǰ�İ�һ����Receiver�յ�����֮ǰ��ack�����ж�ʧ������һ���������Ϊȷ�����acknum
			sendbase = y ;
			pUtils->printPacket("���ͷ���ȷ�յ�ȷ��", ackPkt);
			if (sendbase == nextseqnum)
				pns->stopTimer(SENDER, tmp);		//�رն�ʱ��,ע��رյ���֮ǰ�Ǹ�baseֵ�Ķ�ʱ��
			else {
				pns->stopTimer(SENDER, tmp);		//���ȹرն�ʱ��
				pns->startTimer(SENDER, Configuration::TIME_OUT, sendbase);		//�����������ͷ���ʱ��
			}
			this->extraack = 0;	//��y�յ�������ACK������
		}
		else
		{	//���Ѿ�ȷ�ϵı��Ķε�һ������ACK
			this->extraack++;	//��y�յ�������ACK����1
			cout << "���ͷ��յ���" << extraack << "������ACK��seqnum = " << ackPkt.acknum << endl;
			if (extraack == 3)	//����յ���������ACK����ִ�п����ش�
			{
				pUtils->printPacket("���ͷ��յ�����ͬ���ݵ���������ACK��ִ�п����ش���",this->packetWaitingAck[y]);
				//���·��;������y�ı��Ķ�
				pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[y]);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢�͵��Է�
				y = -1;
				this->extraack = 0;
			}
		}
	}
	//else:���ͷ��յ��˴���ı��ģ���һֱ�ȴ�ֱ����ʱ�����ط�����

}

void TCPRdtSender::timeoutHandler(int seqNum) {
	//��һ�ĳ�ʱ������
	pUtils->printPacket("���ͷ��ѳ�ʱ�����·������緢�͵ı��ĶΡ�", this->packetWaitingAck[sendbase]);
	pns->stopTimer(SENDER, seqNum);										//���ȹرն�ʱ��
	pns->startTimer(SENDER, Configuration::TIME_OUT, seqNum);			//�����������ͷ���ʱ��
	pns->sendToNetworkLayer(RECEIVER, this->packetWaitingAck[sendbase]);//���·������ݰ�
}
