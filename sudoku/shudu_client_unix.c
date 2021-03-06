#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MAX_MES 81
#define PORT 4096

int main(int argc, char **argv)
{
	int clifd;
	int num;
	int mes[MAX_MES]={	
		1, 2, 3, 4, 5, 6, 7, 8, 9,
		2, 2, 3, 4, 5, 6, 7, 8, 9,
		3, 2, 3, 4, 5, 6, 7, 8, 9,
		4, 2, 3, 4, 5, 6, 7, 8, 9,
		5, 2, 3, 4, 5, 6, 7, 8, 9,
		6, 2, 3, 4, 5, 6, 7, 8, 9,
		7, 2, 3, 4, 5, 6, 7, 8, 9,
		8, 2, 3, 4, 5, 6, 7, 8, 9,
		9, 2, 3, 4, 5, 6, 7, 8, 9};
	int i;
	int j;
	clifd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in seraddr;
	seraddr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr);
	seraddr.sin_port = htons(PORT);
	if(connect(clifd, (struct sockaddr*)&seraddr, sizeof(seraddr)) == -1)
	{
		printf("client connect error\n");
		exit(-1);
	}
	/*
	for(int i = 0; i < MAX_MES; ++i)
		scanf("%d", &mes[i]);
	*/
	
	

	if((num = write(clifd, mes, sizeof(int) * MAX_MES)) == -1)
	{
		printf("client write error\n");
		exit(-1);
	}
	if((num = read(clifd, mes, sizeof(int) * MAX_MES)) == -1)
	{
		printf("client read error\n");
		exit(-1);
	}

	for(i = 0; i < 9; ++i)
	{
		for(j = 0; j < 9; ++j)
		{
			printf("%2d", mes[i*9+j]);
		}
		printf("\n");
	}

	return 0;
}

