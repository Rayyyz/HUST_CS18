// main.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "Global.h"
#include "RdtSender.h"
#include "RdtReceiver.h"
#include "StopWaitRdtSender.h"
#include "StopWaitRdtReceiver.h"

#define _STOPWAIT 0
#define _GBN 0
#define _SR 0
#define _TCP 1

int main(int argc, char* argv[])
{
#if _STOPWAIT
	RdtSender *ps = new StopWaitRdtSender();
	RdtReceiver * pr = new StopWaitRdtReceiver();
#elif _GBN
	RdtSender* ps = new GBNRdtSender();
	RdtReceiver* pr = new GBNRdtReceiver();
#elif _SR
	RdtSender* ps = new SRRdtSender();
	RdtReceiver* pr = new SRRdtReceiver();
#elif _TCP
	RdtSender* ps = new TCPRdtSender();
	RdtReceiver* pr = new TCPRdtReceiver();
#endif

 	pns->setRunMode(0);  //VERBOS模式
	pns->setRunMode(1);  //安静模式
	pns->init();
	pns->setRtdSender(ps);
	pns->setRtdReceiver(pr);
	pns->setInputFile("C:\\Users\\Ray\\Documents\\Codes\\HUST_CS18\\ComputerNetworks\\Test2_GBN_TCP\\Test2\\Debug\\input.txt");
	pns->setOutputFile("C:\\Users\\Ray\\Documents\\Codes\\HUST_CS18\\ComputerNetworks\\Test2_GBN_TCP\\Test2\\Debug\\output.txt");

	pns->start();

	delete ps;
	delete pr;
	delete pUtils;	//指向唯一的工具类实例，只在main函数结束前delete
	delete pns;		//指向唯一的模拟网络环境类实例，只在main函数结束前delete
	
	return 0;
}

