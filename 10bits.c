#include <stdio.h>

int main(){
	int test[32] = {0};
	int ten = 0;
	int cnt = 0;
	int mask = 3 << 30;
	unsigned int num = 0;
	unsigned int i = 0, temp;
	int a = 0;

	test[0] = 4206600;
	test[1] = 117506288;
	test[2] = 538903555;
	test[3] = 4034952976;
	test[4] = 267518463;

	while(1){
		while(1){
			if(ten == 10){
				ten = 0;
				break;
			}
			if(cnt == 32){
				i++;
				cnt = 0;
			}
			temp = test[i];
			if((cnt - ten) >= 0){
				temp = (temp << (cnt - ten));
			}
			else{
				temp = (temp >> (ten - cnt));
			}
			mask = (mask >> ten);
			temp = temp & mask;
			num = num | temp;
			mask = (mask << ten);
			ten += 2;
			cnt += 2;
		}
		num = (num >> 22);
		if(!num){
			printf("-----출력 마침-----\n");
			break;
		}
		printf("number : %u\n", num);
		num = 0;
	}

	printf("0~1023 숫자 입력 : ");
	scanf("%d", &a);
	printf("---입력 이후 결과---\n");

	if((cnt - 10) >= 0){
		a = (a << (32 - cnt));
		test[i] = (test[i] | a);
	}
	else{
		num = a;
		num = (num << (32 - cnt));
		test[i] = (test[i] | num);
		i--;
		num = a;
		num = (num >> cnt);
		test[i] = (test[i] | num);
	}

	cnt = 0;
	ten = 0;
	i = 0;

	while(1){
		while(1){
			if(ten == 10){
				ten = 0;
				break;
			}
			if(cnt == 32){
				i++;
				cnt = 0;
			}
			temp = test[i];
			if((cnt - ten) >= 0){
				temp = (temp << (cnt - ten));
			}
			else{
				temp = (temp >> (ten - cnt));
			}
			mask = (mask >> ten);
			temp = temp & mask;
			num = num | temp;
			mask = (mask << ten);
			ten += 2;
			cnt += 2;
		}
		num = (num >> 22);
		if(!num){
			printf("-----출력 마침-----\n");
			break;
		}
		printf("number : %u\n", num);
		num = 0;
	}
	return 0;
}
