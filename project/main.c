#include <stdio.h>
#include <stdlib.h>
#include "rsa.h"
int main(int argc,char* argv[]){	
	rsa_params _rsa;
	int x,y;	
	if(argc>=2){		
		init(&_rsa);
		if(argc>=3){
			x=atoi(argv[2]);
			printf("p=%d, q=%d, n=%d, m=%d, e=%d, d=%d, u=%d\n",_rsa.p,_rsa.q,_rsa.n,_rsa.m,_rsa.e,_rsa.d,_rsa.u);			
			y=rsa_encode(x,_rsa);
			printf(" %d -->: %d -->: %d\n",x,y,rsa_decode(y,_rsa));
		}				
		ma_hoa(_rsa,argv[1]);	
		giai_ma(_rsa,"encode");
	}else
		puts("No argument!");	
	return 0;
}