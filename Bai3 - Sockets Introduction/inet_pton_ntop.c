#include <stdio.h>
#include <math.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(){
	char *inputip[30];
	struct in_addr ap;
	char str[INET_ADDRSTRLEN];
	printf("Nhap vao dia chi IP: ");
	scanf("%s",inputip);
	printf("Ket qua tra ve inet_pton: %d\n",inet_pton(AF_INET,inputip,&ap));
	printf("\(Tra ve 1 neu la IP nam trong AF_INET, 0 neu bieu dien khong dung, -1 khi co loi\)\n");
	printf("Ket qua tra ve inet_ntop: %s\n",inet_ntop(AF_INET,&ap,str,INET_ADDRSTRLEN));
	printf("Gia tri trong sock_addr_in (32bit): %d\n",ap.s_addr);
	printf("Ket qua khi dung inet_addr (32bit): %d\n",inet_addr(inputip));
	return 0;
}