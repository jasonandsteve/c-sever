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
	//��socket�������׵�TCP�����
	/*����һ��socket
	bind�����ڽ��ܿͻ������ӵ�����˿�
	listen��������˿�
	accept�ȴ����ܿͻ�������
	send��ͻ��˷���һ������
	�ر��׽���closesocket
	���windows socket����

	*/
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);//host to net unsigned short 
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//���߰������ַҲ�У�INADDR_ANY
	if (SOCKET_ERROR ==bind(_sock, (sockaddr*)&_sin, sizeof(_sin))) {
		printf("ERROT,�����ڽ��ܿͻ������ӵ�����˿�ʧ��...\n");
	}
	else {
		printf("������˿ڳɹ�...\n");
	}
	if (SOCKET_ERROR == listen(_sock, 5)) {

		printf("ERROR,�������ڽ��ܿͻ������ӵ�����˿�ʧ��...\n");
	}
	else {
		printf("��������˿ڳɹ�...\n");
	}
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	
	_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (INVALID_SOCKET == _cSock) {
		printf("���󣬽��յ���Ч�ͻ���SOCKET...\n");
	}
	printf("�¿ͻ��˼��룺socket =%d , IP = %s \n", (int)_cSock,inet_ntoa(clientAddr.sin_addr));
	char _recvBuf[128] = {};
	while (true) 
	{
		//5���ܿͻ�������
		int	nlen = recv(_cSock, _recvBuf, 128, 0);
		if (nlen <= 0)
		{
			printf("�ͻ������˳����������");
			break;
		}
		printf("�յ�����:%s \n", _recvBuf);
		//6��������
		if (0 == strcmp(_recvBuf, "getInfo")) {

			//send��ͻ��˷���һ������
			DataPackage dp = {80,"�Ź���"}��
			send(_cSock, (const char*)&dp, sizeof(DataPackage) , 0);
		}
		else if (0 == strcmp(_recvBuf, "getAge")) {
			//send��ͻ��˷���һ������
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