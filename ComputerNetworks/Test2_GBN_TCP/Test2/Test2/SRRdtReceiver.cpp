#include "stdafx.h"
#include "Global.h"
#include "SRRdtReceiver.h"


SRRdtReceiver::SRRdtReceiver() :rcv_base(1)
{
	for (int i = 0; i < SR_SEQ_NUM; i++)
		rcvseq[i] = false;
	lastAckPkt.acknum = -1; //��ʼ״̬�£��ϴη��͵�ȷ�ϰ���ȷ�����Ϊ-1��ʹ�õ���һ�����ܵ����ݰ�����ʱ��ȷ�ϱ��ĵ�ȷ�Ϻ�Ϊ-1
	lastAckPkt.checksum = 0;
	lastAckPkt.seqnum = -1;	//���Ը��ֶ�
	for (int i = 0; i < Configuration::PAYLOAD_SIZE; i++) {
		lastAckPkt.payload[i] = '.';
	}
	lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
}


SRRdtReceiver::~SRRdtReceiver()
{
}

void SRRdtReceiver::receive(const Packet& packet) {
	//���У����Ƿ���ȷ
	int checkSum = pUtils->calculateCheckSum(packet);
	//���У�����ȷ��ͬʱ�յ����ĵ������rcv_base��rcv_base+SR_WINDOW_SIZE-1֮��
	if (checkSum == packet.checksum && (packet.seqnum - rcv_base + SR_SEQ_NUM)%SR_SEQ_NUM <= SR_WINDOW_SIZE - 1 ) {
		int delnum = 0;	//���ڼ�¼�ύ�ķ�����Ŀ
		if (rcvseq[packet.seqnum] == false) {
			//����÷���֮ǰû�յ������򻺴�÷���
			memcpy(rcvmsg[packet.seqnum].data, packet.payload, sizeof(packet.payload));
			rcvseq[packet.seqnum] = true;
			pUtils->printPacket("���շ���ȷ�յ����ͷ��ı���", packet);
		}
		if (packet.seqnum == this->rcv_base)
		{	//����÷�����ŵ��ڽ��մ��ڵĻ���ţ��򽫸÷����Լ�֮ǰ�ķ����Ͻ���Ӧ�ò�
			for (int i = 0, j = rcv_base; i < SR_SEQ_NUM; i++, j = (j + 1) % SR_SEQ_NUM) {
				if (rcvseq[j] == false) {
					//��¼һ���ύ�ķ�����Ŀ
					delnum = i;
					break;
				}
				//ȡ��Message�����ϵݽ���Ӧ�ò�
				pns->delivertoAppLayer(RECEIVER, rcvmsg[j]);
				//����rcvseq����
				rcvseq[j] = false;
			}
			cout << "�����շ��յ�����ŵķ��飬���ϵݽ�["<<rcv_base<<","<< (rcv_base + delnum - 1 + SR_SEQ_NUM) % SR_SEQ_NUM <<"]�ı��ġ�\n";
		}
		//������Ÿ����ύ�ķ����������д����л�
		rcv_base = (rcv_base + delnum ) % SR_SEQ_NUM;
		//����ACK
		lastAckPkt.acknum = packet.seqnum;			//ȷ����ŵ����յ��ı������
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�

	}
	//���У�����ȷ��ͬʱ�յ����ĵ������rcv_base - SR_WINDOW_SIZE��rcv_base-1֮��
	else if (checkSum == packet.checksum && (packet.seqnum - (rcv_base - SR_WINDOW_SIZE + SR_SEQ_NUM) % SR_SEQ_NUM + SR_SEQ_NUM) % SR_SEQ_NUM <= SR_WINDOW_SIZE - 1) {
		//����ACK
		lastAckPkt.acknum = packet.seqnum;			//ȷ����ŵ����յ��ı������
		lastAckPkt.checksum = pUtils->calculateCheckSum(lastAckPkt);
		pUtils->printPacket("���շ�����ȷ�ϱ���", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢��ȷ�ϱ��ĵ��Է�
	}
	else {
		if (checkSum != packet.checksum) {
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,����У�����", packet);
		}
		else {
			pUtils->printPacket("���շ�û����ȷ�յ����ͷ��ı���,������Ų���", packet);
		}
		pUtils->printPacket("���շ����·����ϴε�ȷ�ϱ���", lastAckPkt);
		pns->sendToNetworkLayer(SENDER, lastAckPkt);	//����ģ�����绷����sendToNetworkLayer��ͨ������㷢���ϴε�ȷ�ϱ���

	}
}