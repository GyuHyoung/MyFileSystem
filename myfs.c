#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct super_block{
	unsigned int i_state[16];
	unsigned int d_state[32];
};

struct inode_list{
	unsigned type : 1;
	unsigned di : 10;
	unsigned sin : 10;
	unsigned din : 10;
	int size;
	struct tm *time;
};

struct file_info{
	char data[128];
};

struct directory_info{
	char name[18][5];
	short number[18];
};

struct indirect_info{
	short number[64];
};

union data_block{
	struct file_info file;
	struct directory_info directory;
	struct indirect_info indirect;
};

struct my_file_system{
	unsigned boot_block : 16;
	struct super_block super;
	struct inode_list inode[512];
	union data_block block[1024];
}myfs;

struct present_working_directory{
	char name[10][4];
	char number[10];
}pwd;

struct linked{
	int number;
	struct linked *next;
};

struct linked *list[1024];

void myshowfile(int, int, char []);
void print_byte(int, int, int);
void mypwd(struct present_working_directory);
void print_block_list(int);
void usage_plus(unsigned int [], int, int);
void usage_minus(unsigned int [], int, int);
int usage_check(unsigned int [], int, int);
int usage_count(unsigned int [], int n);
int where_i_am();

int main(){
	int i, n, m, shell = 0;
	char mycmd[][12] = {"mymkfs", "myfs_shell", "myls", "mycat", "myshowfile", "mypwd", "mycd", "mycp", "mycpto", "mycpfrom", "mymkdir", "myrmdir", "myrm", "mymv", "mytouch", "myshowinode", "myshowblock", "mystate", "mytree", "byebye"};
	char command[100], cmd[5][20];
	time_t now = time(NULL);
	FILE *save, *load;
	struct inode_list *inode = NULL;

	//초기화
	strcpy(pwd.name[0], "/");
	pwd.number[0] = 1;
	usage_plus(myfs.super.i_state, 16, 1);
	usage_plus(myfs.super.d_state, 32, 1);
	inode = &myfs.inode[0];
	inode->type = 0;
	inode->size = 0;
	inode->time = localtime(&now);
	inode->di = 1;

	for(i=0; i<1024; i++){
		list[i] = malloc(sizeof(struct linked));
		list[i] -> number = i;
		list[i] -> next = NULL;
	}
	usage_plus(myfs.super.i_state, 16, 2);
	usage_plus(myfs.super.d_state, 16, 2);
	strcpy(myfs.block[0].directory.name[0], "abcd");
	myfs.block[0].directory.number[0] = 2;
	myfs.inode[1].type = 1;
	myfs.inode[1].time = localtime(&now);
	myfs.inode[1].di = 2;
	char temp[128];
	strcpy(temp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ!");
	strcpy(myfs.block[1].file.data, temp);
	myfs.inode[1].size = sizeof(myfs.block[1].file.data);
	/*
	   inode->sin = 2;
	   inode->din = 67;
	   for(i=0; i<18; i++){
	   strcpy(myfs.block[0].directory.name[i], "abcd");
	   myfs.block[0].directory.number[i] = 99;
	   }
	   for(i=0; i<64; i++){
	   myfs.block[1].indirect.number[i] = i+3;
	   }
	   int j;
	   for(i=0; i<64; i++){
	   for(j=0; j<18; j++){
	   strcpy(myfs.block[i+2].directory.name[j], "efgh");
	   myfs.block[i+2].directory.number[j] = i+3;
	   }
	   }
	   strcpy(myfs.block[5].directory.name[0], "find");
	   myfs.block[5].directory.number[j] = 67;*/

	//명령어 받기
	while(1){
		if(shell){
			printf("[");
			mypwd(pwd);
			printf(" ]");
		}
		printf("$ ");
		for(i=0; i<5; i++){
			strcpy(cmd[i], "");
		}
		scanf("%[^\n]", command);
		getchar();
		sscanf(command, "%s %s %s %s %s", cmd[0], cmd[1], cmd[2], cmd[3], cmd[4]);
		for(i=0; i<20; i++){
			if(!strcmp(cmd[0], mycmd[i])){
				if(i==0 || i==1){
					i = 0;
					break;
				}
				i--;
				break;
			}
		}

		switch(i){
			//mkmyfs, myfs_shell
			case 0 :
				if(!strcmp(command, "myfs_shell")){
					if((load = fopen("myfs", "r")) == NULL){
						printf("error : no myfs\n");
					}
					else{
						shell = 1;
					}
				}
				else{
					if((load = fopen("myfs", "r")) == NULL){
						save = fopen("myfs", "w");
					}
					else{
						printf("error : myfs exists\n");
					}
				}
				break;
				//myls
			case 1 :
				break;
				//mycat
			case 2 :
				printf("case %d\n", i);
				break;
				//myshowfile
			case 3 :
				n = atoi(cmd[1]);
				m = atoi(cmd[2]);
				myshowfile(n, m, cmd[3]);
				break;
				//mypwd
			case 4 :
				mypwd(pwd);
				printf("\n");
				break;
				//mycd
			case 5 :
				printf("case %d\n", i);
				break;
				//mycp
			case 6 :
				printf("case %d\n", i);
				break;
				//mycpto
			case 7 :
				printf("case %d\n", i);
				break;
				//mycpfrom
			case 8 :
				printf("case %d\n", i);
				break;
				//mymkdir
			case 9 :
				printf("case %d\n", i);
				break;
				//myrmdir
			case 10 :
				printf("case %d\n", i);
				break;
				//myrm
			case 11 :
				printf("case %d\n", i);
				break;
				//mymv
			case 12 :
				printf("case %d\n", i);
				break;
				//mytouch
			case 13 :
				printf("case %d\n", i);
				break;
				//myshowinode
			case 14 :
				n = atoi(cmd[1]);
				if(usage_check(myfs.super.i_state, 16, n)){
					inode = &myfs.inode[n-1];
					printf("file type : %s\n", (inode->type == 0) ? "directory" : "regular file");
					printf("file size : %d byte\n", inode->size);
					printf("modified time : %d/%d/%d %02d:%02d:%02d\n", inode->time->tm_year + 1900, inode->time->tm_mon + 1, inode->time->tm_mday, inode->time->tm_hour, inode->time->tm_min, inode->time->tm_sec);
					printf("data block list : %d", inode->di);
					print_block_list(n);
					printf("\n");
				}
				else{
					printf("error : empty inode\n");
				}
				break;
				//myshowblock
			case 15 :
				n = atoi(cmd[1]);
				if(usage_check(myfs.super.d_state, 32, n)){
					printf("%s\n", myfs.block[n-1].file.data);
				}
				else{
					printf("error : empty data block\n");
				}
				break;
				//mystate
			case 16 :
				printf("free inode : %d\n", 512 - usage_count(myfs.super.i_state, 16));
				printf("free data block : %d\n", 1024 - usage_count(myfs.super.d_state, 32));
				break;
				//mytree
			case 17 :
				printf("case %d\n", i);
				break;
				//byebye
			case 18 :
				return 0;
			default :
				system(command);
		}
		printf("\n");
	}
	return 0;
}

//myshowfile 함수
void myshowfile(int num1, int num2, char file[]){
	int check, i, j, k, n, block, list;
	struct inode_list *inode;

	n = where_i_am();
	inode = &myfs.inode[n-1];


	list = inode -> di;
	//다이렉트 블럭에서
	for(i=0; i<18; i++){
		check = strcmp(myfs.block[list-1].directory.name[i], "");
		if(check==0){
			printf("error : no such file1\n");
			return;
		}
		check = strcmp(myfs.block[list-1].directory.name[i], file);
		if(check==0){
			n = myfs.block[list-1].directory.number[i];
			if(n==0){
				printf("error : no such file2\n");
				return;
			}
			print_byte(num1, num2, n);
			return;
		}
	}
	//싱글 인다이렉트 블럭에서
	block = inode -> sin;
	for(i=0; i<64; i++){
		list = myfs.block[block-1].indirect.number[i];
		for(j=0; j<18; j++){
			if(!strcmp(myfs.block[list-1].directory.name[i], "")){
				printf("error : no such file\n");
				return;
			}
			if(!strcmp(myfs.block[list-1].directory.name[i], file)){
				n = myfs.block[list-1].directory.number[i];
				if(n==0){
					printf("error : no such file\n");
					return;
				}
				print_byte(num1, num2, n);
				return;
			}
		}
	}
	//더블 인다이렉트 블럭에서
	for(i=0; i<64; i++){
		block = myfs.block[(inode -> din)-1].indirect.number[i];
		for(j=0; j<64; j++){
			list = myfs.block[block-1].indirect.number[i];
			for(k=0; k<18; k++){
				if(!strcmp(myfs.block[list-1].directory.name[i], "")){
					printf("error : no such file\n");
					return;
				}
				if(!strcmp(myfs.block[list-1].directory.name[i], file)){
					n = myfs.block[list-1].directory.number[i];
					if(n==0){
						printf("error : no such file\n");
						return;
					}
					print_byte(num1, num2, n);
					return;
				}
			}
		}
	}
}

//바이트단위 출력
void print_byte(int num1, int num2, int n){
	int i, start1, start2, count, num;
	union data_block *block;

	start1 = num1 / 128;
	start2 = num1 % 128;
	count = num2 - num1 + 1;
	num = list[(myfs.inode[n-1].di)-1]->number;
	block = &(myfs.block[num]);

	while(1){
		if(start1 == 0){
			i = start2 - 1;
			while(1){
				if(count==0){
					printf("\n");
					return;
				}
				if(i==128){
					num = list[num] -> next -> number;
					block = &(myfs.block[num]);
					i = 0;
				}
				printf("%c", block -> file.data[i]);
				i++;
				count--;
			}
		}
		else{
			num = list[num] -> next -> number;
			block = &(myfs.block[num]);
			start1--;
		}
	}
}

//현재 위치 출력
void mypwd(struct present_working_directory pwd){
	int i;
	for(i=0; i<10; i++){
		if(!printf("%s", pwd.name[i])){
			break;
		}
		else if(i != 0){
			printf("/");
		}
	}
}

//블럭 리스트 출력
void print_block_list(int n){
	int i, j, block;

	//싱글 인다이렉트 블럭에서
	block = myfs.inode[n-1].sin;

	if(block==0){
		return;
	}
	else{
		for(i=0; i<64; i++){
			if(myfs.block[block-1].indirect.number[i]!=0){
				printf(", %d", myfs.block[block-1].indirect.number[i]);
			}
			else{
				return;
			}
		}
	}

	//더블 인다이렉트 블럭에서
	for(j=0; j<64; j++){
		block = myfs.block[myfs.inode[n-1].din-1].indirect.number[j];
		if(block==0){
			return;
		}
		else{
			for(i=0; i<64; i++){
				if(myfs.block[block-1].indirect.number[i]){
					printf(", %d", myfs.block[block-1].indirect.number[i]);
				}
				else{
					return;
				}
			}
		}
	}
}

//슈퍼블럭에 비트열로 추가
void usage_plus(unsigned int c[], int n, int x){
	int i, j, l = sizeof(int) * 8;
	unsigned int mask = 1 << (l - 1);

	for(i=0; i<n; i++){
		for(j=0; j<l; j++){
			if(x == (i * l + j + 1)){
				mask >>= j;
				c[i] = c[i] | mask;
			}
		}
	}
}

//슈퍼블럭에 비트열로 제거
void usage_minus(unsigned int c[], int n, int x){
	int i, j, k ,l = sizeof(int) * 8;
	unsigned int mask = 1 << (l = 1), minus = 1;

	for(i=0; i<n; i++){
		for(j=0; j<l; j++){
			if(x == (i * l + j + 1)){
				mask >>= j;
				if((c[i] & mask) != 0){
					for(k=0; k<l-j-1; k++){
						minus *= 2;
					}
					c[i] -= minus;
				}
			}
		}
	}
}

//슈퍼블럭에서 가용 아이노드/데이터 블럭인지 확인
int usage_check(unsigned int c[], int n, int x){
	int i, j, k, l = sizeof(int) * 8;
	unsigned int mask = 1 << (l - 1);

	for(i=0; i<n; i++){
		for(j=0; j<l; j++){
			if( x == (i * l + j + 1)){
				mask >>= j;
				return ((c[i] & mask) != 0) ? 1 : 0;
			}
		}
	}

	return 0;
}

//몇개의 아이노드/데이터 블럭이 사용중인지 확인
int usage_count(unsigned int c[], int n){
	int a, i, j, count = 0, l = sizeof(int) * 8;
	unsigned int mask = 1 << (l - 1);

	for(i=0; i<n; i++){
		a = c[i];
		for(j=1; j<=l; j++){
			if((a & mask) != 0){
				count++;
			}
			a <<= 1;
		}
	}
	return count;
}

int where_i_am(){
	int i;
	for(i=0; i<10; i++){
		if(!strcmp(pwd.name[i], "")){
			i--;
			return pwd.number[i];
		}
	}
}











