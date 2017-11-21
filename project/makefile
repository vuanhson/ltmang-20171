all:
	rm -f *.o main encode decode
	gcc -o main main.c rsa.c	
	gcc -o client client.c -w
	gcc -o server server.c rsa.c -w
clean:
	rm -f *.o main encode decode client server client-file/ketqua.txt server-file/server_rcv_tmp.txt