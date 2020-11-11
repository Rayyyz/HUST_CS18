#pragma once
#include "winsock2.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#pragma comment(lib,"Mswsock.lib")
#pragma comment(lib,"ws2_32.lib")
#define DEFAULT_BUFFER 4096
/*http://10.11.54.243:8888/index.html*/


using namespace std;
const int port = 8877;	//监听端口号
//响应首部内容
const char* http_get_message_success = "HTTP/1.1 200 OK \r\n\Content-Length:%d\r\nConnection:close\r\nContent-Type:%s\r\n\r\n";
char* http_404_error = "HTTP/1.1 404 Not Found \r\n\Content-Length:%d\r\nConnection:close\r\nContent-Type:%s\r\n\r\n";

//定义文件类型对应的content-tyoe
struct doc_type {
	char* suffix;
	char* type;
};

//文件
struct doc_type file_type[] =
{
	{"html",  "text/html"},
	{"gif",   "imag/gif"},
	{"jpeg",  "imag/jpeg"},
	{NULL,    NULL}
};

//通过后缀，查找到对应的content-type
char* http_get_type_by_suffix(const char* suffix)
{
	struct doc_type* type;
	for (type = file_type; type->suffix; type++)
	{
		if (strcmp(type->suffix, suffix) == 0)
			return type->type;
	}
	return NULL;
}

//从报文请求中分离出文件名
void split_filename(char* revbuf, int buflen, char* file_name) {
	int flag = 0;
	memset(file_name, 1024, 0);
	int k = 0;
	for (int i = 0; i < buflen; i++) {
		if (revbuf[i] == ' ') {
			if (revbuf[i + 1] == '/') {
				flag = 1;
				i++;
				continue;
			}
			else {
				flag = 0;
				break;
			}
		}
		if (flag) {
			file_name[k++] = revbuf[i];
		}
	}
	file_name[k] = 0;
}


//解析客户端发来的请求，发送http文件
int http_send_response(SOCKET soc, char* buf, int buf_len, char* file_name)
{
	int read_len, file_len, hdr_len, send_len;
	char* type;
	char read_buf[1024];
	char http_header[1024];		//html文件头部内容
	char suffix[16];			//文件类型
	FILE* res_file;

	//获取suffix
	int k = 0;
	int len = strlen(file_name);
	for (int i = 0, flag = 0; i < strlen(file_name); i++) {
		if (file_name[i] == '.') {
			flag = 1;
			continue;
		}
		if (flag) {
			suffix[k++] = file_name[i];
		}
	}
	suffix[k] = 0;
	char file_read_name[1024];
	char http_condition[1024];
	strcpy(http_condition, http_get_message_success);
	strcpy(file_read_name, file_name);
	//获得文件content-type
	type = http_get_type_by_suffix(suffix);
	if (type == NULL)
	{
		if (suffix == "iso") {
			return 0;
		}
		if (!strlen(file_name)) {
			strcpy(file_read_name, "homepage.html");
		}
		else {
			printf("error:服务器没有相关的文件类型!\n");
			strcpy(file_read_name, "error.html");
			strcpy(http_condition, http_404_error);	//如果没有文件类型则返回404
		}
	}
	//打开文件
	res_file = fopen(file_read_name, "rb+");
	//如果文件不存在，返回404
	if (res_file == NULL)
	{
		printf("[Web]文件:%s 不存在!\n", file_name);
		res_file = fopen("error.html", "rb+");
		strcpy(http_condition, http_404_error);
	}
	//计算文件大小
	fseek(res_file, 0, SEEK_END);
	file_len = ftell(res_file);
	fseek(res_file, 0, SEEK_SET);

	//构造响应首部，加入文件长度，content-type信息
	hdr_len = sprintf(http_header, http_condition, file_len, type);
	send_len = send(soc, http_header, hdr_len, 0);
	printf("服务器发送的响应头部是:\n%s\n", http_header);
	if (send_len == SOCKET_ERROR)
	{
		fclose(res_file);
		printf("[Web]发送失败，错误:%d\n", WSAGetLastError());
		return 0;
	}
	//发送文件
	do
	{
		read_len = fread(read_buf, sizeof(char), 1024, res_file);
		if (read_len > 0)
		{
			send_len = send(soc, read_buf, read_len, 0);
			file_len -= read_len;
		}
	} while ((read_len > 0) && (file_len > 0));
	fclose(res_file);
	return 1;
}

void main() {
	//完成初始化工作
	WSADATA wsaData;
	int nRc = WSAStartup(0x0202, &wsaData);
	if (nRc) {
		cout << "Winsock  startup failed with error!" << endl;
	}
	if (wsaData.wVersion != 0x0202) {
		cout << "Winsock version is not correct!" << endl;
	}
	cout << "Winsock  startup Ok!" << endl;
	
	//创建套接字
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		cout << "Socket create ERROR!" << endl;
	}
	else {
		cout << "Socket create Ok!" << endl;
	}

	//绑定套接字
	sockaddr_in addr;
	/*设置IP和端口*/
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);	//本地地址转化成网络地址
	int rtn = bind(serverSocket, (LPSOCKADDR)&addr, sizeof(addr));
	if (rtn == SOCKET_ERROR) {
		cout << "Socket bind ERROR!" << endl;
	}
	else {
		cout << "Socket bind Ok!" << endl;
	}

	//开始监听
	rtn = listen(serverSocket, 5);	//表示队列中最多同时有5个连接请求
	if (rtn == SOCKET_ERROR) {
		cout << "Socket listen ERROR!" << endl;
	}
	cout << "Socket listen Ok! Listening PORT: " << port << endl;
	//将serverSock设为非阻塞模式以监听客户连接请求

	//创建连接
	SOCKET sessionSocket;	//创建会话套接字
	sockaddr_in clientAddr;	
	int addrLen = sizeof(clientAddr);
	char clientData[4096];	//用于存储从客户端请求的数据

	while (true) {
		//如果servervSock收到连接请求，接受客户连接请求
		//每当收到客户端连接请求，创建新的会话SOCKET，保存在sessionSocket中
		sessionSocket = accept(serverSocket, (LPSOCKADDR)&clientAddr, &addrLen);
		if (sessionSocket == INVALID_SOCKET) {
			//创建会话SOCKET出错处理
			cout << "Socket accept ERROR! "<< endl;
			break;
		}
		//创建会话SOCKET成功
		cout << "Socket accept Ok!Connection conse from IP:";
		cout << inet_ntoa(clientAddr.sin_addr) << "\tPort: " << ntohs(clientAddr.sin_port) << endl;

		//接受来自客户端的数据
		memset(clientData, '\0', DEFAULT_BUFFER);	//清空缓存区
		rtn = recv(sessionSocket, clientData, DEFAULT_BUFFER, 0);
		if (rtn == SOCKET_ERROR) {
			cout << "Receive data ERROR!";
			break;
		}
		cout << "----------------------------------------------" << endl;	//打印收到的数据
		cout << clientData << endl;
		cout << "----------------------------------------------" << endl;
		char file_name[1024];
		memset(file_name, 0, 1024);
		split_filename(clientData, rtn, file_name);	//获得文件名
		rtn = http_send_response(sessionSocket, clientData, 4096, file_name);
		if (rtn == SOCKET_ERROR) {
			cout << "Send data ERROR!";
			break;
		}
		closesocket(sessionSocket);
	}
	closesocket(serverSocket);
	WSACleanup();
			

}

