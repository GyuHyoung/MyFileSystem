#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct my_file_system{
	unsigned boot_block : 16;
	struct super_block *s;
	struct inode_list *i[512];
	union data_block *d[1024];
};

struct super_block{
	unsigned int i_info[16];
	unsigned int d_info[32];
};

struct inode_list{
	unsigned type : 1;
	unsigned int size;
	struct tm *ti;
	struct data_block_list *dl;
};

struct data_block_list{
	union data_block *db;
	union data_block *sib;
	union data_block *dib;
};

union data_block{
	struct file_info *fi;
	struct directory_info *di;
	union data_block *ib[16];
};

struct file_info{
	char data[120];
	union data_block *next;
};

struct directory_info{
	char name[10][4];
	struct inode_list *il[10];
	union data_block *next;
};

typedef struct my_file_system MY_FILE_SYSTEM;
typedef MY_FILE_SYSTEM *MYFS;

typedef struct super_block SUPER_BLOCK;
typedef SUPER_BLOCK *SB;

typedef struct inode_list INODE_LIST;
typedef INODE_LIST *IL;

typedef struct data_block_list DATA_BLOCK_LIST;
typedef DATA_BLOCK_LIST *DBL;

typedef union data_block DATA_BLOCK;
typedef DATA_BLOCK *DB;

typedef struct file_info FILE_INFO;
typedef FILE_INFO *FI;

typedef struct directory_info DIRECTORY_INFO;
typedef DIRECTORY_INFO DI;

//함수 모음
void usage_plus(unsigned int [], int, int);
void usage_minus(unsigned int [], int, int);

int main(){
	char command[100] = {0}, cmd[5][20] = {0}, pwd[10][4] = {0};
	int i;
	time_t now;
	FILE *load, *save;
	MYFS myfs = NULL;

	system("clear");

	while(1){
		printf("$");
		scanf("%[^\n]", command);
		getchar();

		if(!strcmp(command, "myfs_shell")){
			if(myfs == NULL){
				printf("error : no myfs\n");
			}
			else{
				printf("\n");
				break;
			}
		}
		else if(!strcmp(command, "mkmyfs")){
			if((load = fopen("abcde", "r")) == NULL){
				fclose(load);	
				myfs = malloc(sizeof(MY_FILE_SYSTEM));
				for(i=0; i<512; i++){
					myfs -> i[i] = NULL;
				}
				for(i=0; i<1024; i++){
					myfs -> d[i] = NULL;
				}
				myfs -> s = malloc(sizeof(SUPER_BLOCK));
				usage_plus(myfs -> s -> i_info, 16, 1);
				usage_plus(myfs -> s -> d_info, 32, 1);

				myfs -> i[0] = malloc(sizeof(INODE_LIST));
				myfs -> i[0] -> type = 1;
				myfs -> i[0] -> size = 0;
				now = time(NULL);	
				myfs -> i[0] -> ti = localtime(&now);

				myfs -> d[0] = malloc(sizeof(DATA_BLOCK));
				myfs -> i[0] -> dl = malloc(sizeof(DATA_BLOCK_LIST));
				myfs -> i[0] -> dl -> db = &(myfs -> d[0]);
				strcpy(pwd[0], "/");
			}
			else{
				printf("error : file exists\n");
			}
		}
		else if(!strcmp(command, "byebye")){
			return 0;
		}
		else{
			printf("error : wrong command\n");
		}
		printf("\n");
	}

	while(1){
		printf("[");
		for(i=0; i<10; i++){
			if(!printf("%s",pwd[i])){
				break;
			}
			else if(i != 0){
				printf("/");
			}
		}
		printf(" ]$");
		for(i=0; i<5; i++){
			strcpy(cmd[i], "");
		}
		scanf("%[^\n]", command);
		getchar();
		sscanf(command, "%s %s %s %s %s", cmd[0], cmd[1], cmd[2], cmd[3], cmd[4]);

		for(i=0; i<5; i++){
			printf("%d : %s\n", i + 1, cmd[i]);
		}
	}

	return 0;
}

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











