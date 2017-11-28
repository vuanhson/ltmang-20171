#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <errno.h>
#include <time.h>

int main(int argc,char* argv[])
{
	time_t my_time;
	struct sockaddr_in server;
	int clisock;
	char sendbuf[512], recvbuf[512]; 
	char mode[8];
	strcpy(mode,argv[1]);
	printf("Mode da chon: %s\n", mode);
	//-----Khai bao dia chi server-------------
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[3]);
    server.sin_port = htons(atoi(argv[4]));
	//-----socket()-------
	clisock = socket (AF_INET,SOCK_STREAM,0);

	//-----connect()------
	connect(clisock , (struct sockaddr *)&server , sizeof(server));
	//------Gui nhan thong tin--------
		send(clisock, mode, sizeof(mode), 0); // de gui yeu cau encode hay decode

		//Gui File toi server
		char* fs_name = argv[2];
		printf("Gui file %s toi server... \n", fs_name);
		FILE *fs = fopen(fs_name, "r");
		if(fs == NULL)
		{
			printf("Loi: Khong tim thay file %s\n", fs_name);
			exit(1);
		}

		bzero(sendbuf, 512); 
		int fs_block_sz; 
		while((fs_block_sz = fread(sendbuf, sizeof(char), 512, fs)) > 0)
		{
		    if(send(clisock, sendbuf, fs_block_sz, 0) < 0)
		    {
		        fprintf(stderr, "Loi: Khong gui duoc file %s. (Ma loi = %d)\n", fs_name, errno);
		        break;
		    }
		    bzero(sendbuf, 512);
		}

		printf("File %s da duoc gui tu client den server\n", fs_name);

		//Nhan File tu server gui ve lai
		printf("-----------------------------------------\n");
		printf("Nhan file tu server va luu lai: \n");

		time(&my_time);
		struct tm* tm_info;
		char time_buffer[26];
		tm_info = localtime(&my_time);
		strftime(time_buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info); //format time trong filename

		char file_name[255] = "";
		snprintf( file_name, sizeof(file_name), "%s%s%s", "client-file/ketqua_",time_buffer, ".txt");
		printf("%s\n", file_name);

		char* fr_name = file_name;
		FILE *fr = fopen(fr_name, "a");
			if(fr == NULL)
			printf("File %s khong doc duoc\n", fr_name);
			else{
			bzero(recvbuf, 512); 
			int fr_block_sz = 0;
	   		while((fr_block_sz = recv(clisock, recvbuf, 512, 0)) > 0)
	   		{
				int write_sz = fwrite(recvbuf, sizeof(char), fr_block_sz, fr);
	        	if(write_sz < fr_block_sz)
				{
	            	error("Loi ghi tep\n");
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
				printf("recv() timed out.\n");
			}
			else
			{
				fprintf(stderr, "recv() loi, ma loi: %d\n", errno);
			}
		}
	    printf("Ok da nhan lai file tu phia server, file duoc luu tai: %s\n",fr_name);
	    fclose(fr);
	}

	close(clisock);
	return 0;
}