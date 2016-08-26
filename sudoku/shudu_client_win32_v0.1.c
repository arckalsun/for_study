//#include "stdafx.h"
#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#pragma  comment(lib,"ws2_32.lib")

#define MAX_MES 81
#define BUFFERSIZE 512
#define MAX_ARR 81*512
int main(int argc, char ** argv)
{
	WSADATA              wsaData;
	SOCKET               s;
	SOCKADDR_IN          ServerAddr;
	int                  Port = 4096;
	char *				 host = argv[1];


	if (argc < 2)
	{
		printf("Usage: %s serverip", argv[0]);
		return 1;
	}
	//��ʼ��Windows Socket 2.2
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ����һ���µ�Socket�����ӷ�����
	s = socket(AF_INET, SOCK_STREAM, 0);

	// ��д�ͻ��˵�ַ��Ϣ
	ServerAddr.sin_family = AF_INET;
	//inet_pton(AF_INET, host, &ServerAddr.sin_addr);
	ServerAddr.sin_port = htons(Port);
	ServerAddr.sin_addr.s_addr = inet_addr(host);

	// �������������������
	if (connect(s, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr)) < 0)
	{
		printf("client connect error\n");
		exit(-1);
	}

	// �µ����ӽ����󣬾Ϳ��Ի���ͨ���ˣ�������򵥵������У�����ֱ�ӹر����ӣ�

	//char  sendData[MAX_MES] ;
	//for (int i = 0; i < MAX_MES; i++)
	//	scanf_s("%s", sendData);
	int sendData[MAX_MES] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9,
		2, 2, 3, 4, 5, 6, 7, 8, 9,
		3, 2, 3, 4, 5, 6, 7, 8, 9,
		4, 2, 3, 4, 5, 6, 7, 8, 9,
		5, 2, 3, 4, 5, 6, 7, 8, 9,
		6, 2, 3, 4, 5, 6, 7, 8, 9,
		7, 2, 3, 4, 5, 6, 7, 8, 9,
		8, 2, 3, 4, 5, 6, 7, 8, 9,
		9, 2, 3, 4, 5, 6, 7, 8, 9
	};
	int send_len = send(s, sendData, sizeof(sendData), 0);
	printf("sendData has %d Bytes.\n", send_len);

	//��������
	char recData[MAX_MES*4+1];
	memset(recData,0,sizeof(recData));
	int ret = recv(s, recData, MAX_MES*4, 0);
	if (ret > 0)
		recData[ret] = 0x00;
	else
	{
		printf("Receive Error.\n");
		return -1;
	}
		
	printf("\nReceived %d bytes data .\n",ret);
	//char[] to int[]
	//�ѽ��ܵ�char����recData ת��Ϊ int����
	
	int sudu[MAX_MES];
	union buf{
		int digit;
		char letter[4];
	};
	union buf data;
	
	for (int i = 0; i < MAX_MES; i++)
	{
		memset(&data,0,sizeof(data));
		for (int j = 0; j < 4; j++)
			data.letter[j] = recData[i * 4 + j];
		sudu[i] = data.digit;

		printf("%d ", sudu[i]);
		if ( (i+1) % 9 == 0 /*&& i != 0*/)
			printf("\n");
	}


	// ���رռ���Socket��Ȼ���˳�Ӧ�ó���
	closesocket(s);

	// �ͷ�Windows Socket DLL�������Դ
	WSACleanup();
	return 0;
}