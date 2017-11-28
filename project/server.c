#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include "rsa.h"
void guifile(int clisock, char* filename){
	char sendbuf[500];
	printf("--------------------------------------------------------\n");
	//time_t now = time(0);
	//printf("%s\n", now);
		    char* fs_name = filename;
		    printf("Gui file %s toi client...\n", fs_name);
		    FILE *fs = fopen(fs_name, "r");
		    if(fs == NULL)
		    {
		        fprintf(stderr, "Loi: File %s khong ton tai, Ma loi = %d\n", fs_name, errno);
				exit(1);
		    }

		    bzero(sendbuf, 512); 
		    int fs_block_sz; 
		    while((fs_block_sz = fread(sendbuf, sizeof(char), 512, fs))>0)
		    {
		        if(send(clisock, sendbuf, fs_block_sz, 0) < 0)
		        {
		            fprintf(stderr, "Loi khong gui duoc file %s, ma loi: %d\n", fs_name, errno);
		            exit(1);
		        }
		        bzero(sendbuf, 512);
		    }
		    printf("Da gui lai file cho client!\n");
		    printf("--------------------------------------------------------\n");
			printf("<Doi ket noi tiep theo tu client>\n");
		    close(clisock);
			system("rm -f server-file/*");
			exit(0);
}
int main(int argc,char* argv[])
{
	int srvsock,clisock,bindret,sock_size,check_client_status,procid;
	struct sockaddr_in client, server;
	char sendbuf[500],recvbuf[500];
	pid_t pid;
	char mode[8];
	int tmp,x,y;
	rsa_params _rsa;
	//-----init RSA Key------
	init(&_rsa);
	//-----Khai bao thong so server--------
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
	
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
		
		recv(clisock, mode, 512, 0); // de nhan yeu cau encode hay decode
		
	if ((pid=fork())==0){
		close(srvsock);
		printf("#######################################################\n");
		procid = getpid();
		printf("Client co procid = %d da tham gia ket noi\n",procid);
		

		//nhan file tu client va luu lai file do
		char* fr_name = "server-file/server_rcv_tmp.txt";
		FILE *fr = fopen(fr_name, "a");
		if(fr == NULL)
			printf("Khong the mo file %s tren server\n", fr_name);
		else
		{
			bzero(recvbuf, 512); 
			int fr_block_sz = 0;
			while((fr_block_sz = recv(clisock, recvbuf, 512, 0)) > 0) 
			{
			    int write_sz = fwrite(recvbuf, sizeof(char), fr_block_sz, fr);
				if(write_sz < fr_block_sz)
			    {
			        error("Khong ghi duoc file tren server\n");
			    }
				bzero(recvbuf, 512);
				if (fr_block_sz == 0 || fr_block_sz != 512) 
				{
					break;
				}
			}

			if(fr_block_sz < 0)
		    {
		        if (errno == EAGAIN)
	        	{
	                printf("recv() timed out\n");
	            }
	            else
	            {
	                fprintf(stderr, "recv() loi, ma loi: %d\n", errno);
					exit(1);
	            }
        	}
			
			printf("Ok da nhan file tu client!\n");
			fclose(fr); 
		}
		
		printf("--------------------------------------------------------\n");
		//Chay ham ma hoa va giai ma
		printf("Thuc hien quy trinh %s:\n",mode);
		x=atoi("testx");
			printf("Khoa cong khai: (n=%d, e=%d)\n",_rsa.n,_rsa.e);			
			y=rsa_encode(x,_rsa);
			printf(" %d -->: %d -->: %d\n",x,y,rsa_decode(y,_rsa));
		if(strcmp(mode,"encode")==0){
		ma_hoa(_rsa,"server-file/server_rcv_tmp.txt");
		guifile(clisock,"encode");	
		}
		
		if(strcmp(mode,"decode")==0){ 
		giai_ma(_rsa,"server-file/server_rcv_tmp.txt");
		guifile(clisock,"decode");	
		}
			
		}

		close (clisock);
	}
	
	return 0;
}