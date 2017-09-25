#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
int main(){
	char *inputip[30];
	struct in_addr ap;
	printf("Nhap vao dia chi IP: ");
	scanf("%s",inputip);
	printf("Ket qua tra ve aton (1 la dia chi IP, 0 khong la dia chi IP): %d\n",inet_aton(&inputip,&ap));
	printf("Ket qua tra ve ntoa (dia chi IP): %s\n",inet_ntoa(ap));
	printf("Gia tri trong sock_addr_in (32bit): %d\n",ap.s_addr);
	printf("Ket qua khi dung inet_addr (32bit): %d\n",inet_addr(inputip));
		
	return 0;
}