#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include<windows.h>
#include<WinSock2.h>
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")
struct DataPackage {
	long 
	int age;
	char name[32];

};




int main()
{
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//用socket建立简易的TCP服务端
	/*建立一个socket
	bind绑定用于接受客户端连接的网络端口
	listen监听网络端口
	accept等待接受客户端连接
	send向客户端发送一条数据
	关闭套接字closesocket
	清除windows socket环境

	*/
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);//host to net unsigned short 
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//或者绑定随机地址也行，INADDR_ANY
	if (SOCKET_ERROR ==bind(_sock, (sockaddr*)&_sin, sizeof(_sin))) {
		printf("ERROT,绑定用于接受客户端连接得网络端口失败...\n");
	}
	else {
		printf("绑定网络端口成功...\n");
	}
	if (SOCKET_ERROR == listen(_sock, 5)) {

		printf("ERROR,监听用于接受客户端连接得网络端口失败...\n");
	}
	else {
		printf("监听网络端口成功...\n");
	}
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	
	_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (INVALID_SOCKET == _cSock) {
		printf("错误，接收到无效客户端SOCKET...\n");
	}
	printf("新客户端加入：socket =%d , IP = %s \n", (int)_cSock,inet_ntoa(clientAddr.sin_addr));
	char _recvBuf[128] = {};
	while (true) 
	{
		//5接受客户端数据
		int	nlen = recv(_cSock, _recvBuf, 128, 0);
		if (nlen <= 0)
		{
			printf("客户端已退出，任务结束");
			break;
		}
		printf("收到命令:%s \n", _recvBuf);
		//6处理请求
		if (0 == strcmp(_recvBuf, "getInfo")) {

			//send向客户端发送一条数据
			DataPackage dp = {80,"张国荣"}；
			send(_cSock, (const char*)&dp, sizeof(DataPackage) , 0);
		}
		else if (0 == strcmp(_recvBuf, "getAge")) {
			//send向客户端发送一条数据
			char msgBuf[] = "80";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
		
		}
		else {
			char msgBuf[] = "?????";
			send(_cSock, msgBuf, strlen(msgBuf) + 1, 0);
		
		
		}

	}
	closesocket(_sock);

	//
	WSACleanup();

	return 0;

}