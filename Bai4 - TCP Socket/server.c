#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
int main()
{
	int srvsock,clisock,bindret,sock_size,check_client_status,procid;
	struct sockaddr_in client, server;
	char message[500],recv_msg[500];
	pid_t pid;

	//-----Khai bao thong so server--------
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(2311);
	//-----socket()-------
	srvsock = socket (AF_INET,SOCK_STREAM,0);
	if (srvsock == -1){
		printf("Khong tao duoc socket\n");
	} printf("Socket tao thanh cong\n");
	//-----bind()-------
	bindret = bind(srvsock, (struct sockaddr*)&server,sizeof(server));
	if (bindret <0){
		printf("Bind khong thanh cong\n");
		return 0;
	} printf("Bind thanh cong\n");
	//-----listen()-------
	listen(srvsock,4);
	printf("Dang listen...\n");
	//------Gui nhan thong tin--------
	sock_size = sizeof(struct sockaddr_in);
	for (;;){
		clisock = accept(srvsock, (struct sockaddr*)&client, (socklen_t*)&sock_size);
		if ((pid=fork())==0){
			close(srvsock);
			memset (recv_msg,0,500);
			memset (message,0,500);

			while (check_client_status = recv(clisock, recv_msg, 500, 0) > 0){
				for (int i = 0; i < strlen(recv_msg); ++i){
					message[i]=toupper(recv_msg[i]);
				}
				if (strcmp (recv_msg,"END") == 0 ){
					close(clisock);
					kill (pid,SIGTERM);
				} 
				send (clisock, message, strlen(message),0);
				memset (recv_msg,0,500);
				memset (message,0,500);

			}
			if (check_client_status ==0 ){
				procid = getpid();
				printf("Client co procid = %d da ngat ket noi\n",procid);
			}
			else if (check_client_status == -1){
				printf("Loi nhan tin tu client\n");
			}

			close(clisock);
			exit(0);
		}

		close (clisock);
	}
	
	return 0;
}