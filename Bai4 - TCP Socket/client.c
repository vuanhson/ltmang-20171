#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
int main()
{
	struct sockaddr_in server;
	int clisock;
	char message[500],recv_msg[500];
	//-----Khai bao dia chi server-------------
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(2311);
	//-----socket()-------
	clisock = socket (AF_INET,SOCK_STREAM,0);

	//-----connect()------
	connect(clisock , (struct sockaddr *)&server , sizeof(server));
	//------Gui nhan thong tin--------
	while(1){
		memset (recv_msg,0,500);
		memset (message,0,500);
		printf("Nhap tin nhan: ");
		scanf("%s", message);
		if (strcmp (message,"END") == 0 ){
			close(clisock);
			return 0;
		} 
		send(clisock, message, strlen(message), 0);
		recv(clisock, recv_msg, 500, 0);
		printf("%s\n", recv_msg);

	}
	close(clisock);
	return 0;
}