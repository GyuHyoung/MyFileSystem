#include <stdio.h>

#define N 16

int counting(unsigned int []);
void bit_print(unsigned int []);

int main(){
	int a, i, j, k, count;
	unsigned int c[N] = {0};
	unsigned int mask = 1 << (sizeof(int) * 8 - 1);
	unsigned int minus = 1;
	

	while(1){

		printf("사용할 inode : ");
		scanf("%d", &a);

		if(a == 999){
			break;
		}
		
		for(i=0;i<N;i++){
			for(j=0;j<32;j++){
				if(a == (i * 32 + j + 1)){
					mask >>= j;
					c[i] = c[i] | mask;
					mask <<= j;
				}
			}
		}
	}
	
	bit_print(c);
	count = counting(c);
	printf("\n사용한 inode 개수 : %d개\n", count);

	while(1){

		printf("제거할 inode : ");
		scanf("%d", &a);

		if(a == 999){
			break;
		}

		for(i=0;i<N;i++){
			for(j=0;j<32;j++){
				if(a == (i * 32 + j + 1)){
					mask >>= j;
					if((c[i] & mask) != 0){
						for(k=0;k<31-j;k++){
							minus *= 2;
						}
						c[i] -= minus;
						minus = 1;
					}
					mask <<= j;
				}
			}
		}
	}

	bit_print(c);
	count = counting(c);
	printf("\n사용한 inode 개수 : %d개\n", count);

	return 0;
}

void bit_print(unsigned int c[]){
	int a, i, j;
	int n = sizeof(int) * 8;
	int mask = 1 << (n - 1);

	for(i=0;i<N;i++){
		a = c[i];
		for(j=1;j<=n;j++){
			putchar(((a & mask) == 0) ? '0' : '1');
			a <<= 1;
			if((j % 8 == 0) && (i < n)){
				putchar(' ');
			}
		}
		printf("\n");
	}
}

int counting(unsigned int c[]){
	int a, i, j, count = 0;
	int n = sizeof(int) * 8;
	int mask = 1 << (n - 1);

	for(i=0;i<N;i++){
		a = c[i];
		for(j=1;j<=n;j++){
			if((a & mask) != 0){
				count++;
			}
			a <<= 1;
		}
	}
	return count;
}
