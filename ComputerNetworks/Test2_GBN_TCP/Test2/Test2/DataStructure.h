#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#define GBN_WINDOW_SIZE 4
#define GBN_SEQ_BIT 3
#define GBN_SEQ_NUM 8 //2^3=8

#define TCP_WINDOW_SIZE 4
#define TCP_SEQ_BIT 3
#define TCP_SEQ_NUM 8 //2^3=8

#define SR_WINDOW_SIZE 4
#define SR_SEQ_BIT 3
#define SR_SEQ_NUM 8 //2^3=8

struct  Configuration{

	/**
	�������Э��Payload���ݵĴ�С���ֽ�Ϊ��λ��
	*/
	static const int PAYLOAD_SIZE = 21;

	/**
	��ʱ��ʱ��
	*/
	static const int TIME_OUT =20;

};



/**
	�����Ӧ�ò����Ϣ
*/
struct  Message {
	char data[Configuration::PAYLOAD_SIZE];		//payload

	Message();
	Message(const Message &msg);
	virtual Message & operator=(const Message &msg);
	virtual ~Message();

	virtual void print();
};

/**
	���Ĳ�����㱨�Ķ�
*/
struct  Packet {
	int seqnum;										//���
	int acknum;										//ȷ�Ϻ�
	int checksum;									//У���
	char payload[Configuration::PAYLOAD_SIZE];		//payload
	
	Packet();
	Packet(const Packet& pkt);
	virtual Packet & operator=(const Packet& pkt);
	virtual bool operator==(const Packet& pkt) const;
	virtual ~Packet();

	virtual void print();
};



#endif

