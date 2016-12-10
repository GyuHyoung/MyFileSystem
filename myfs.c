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
	char name[21];
	short number[21];
};

struct indirect_info{
	unsigned int number[32];
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


void mypwd(struct present_working_directory pwd);

int main(){
	int i, shell = 0;
	char mycmd[][12] = {"mymkfs", "myfs_shell", "myls", "mycat", "myshowfile", "mypwd", "mycd", "mycp", "mycpto", "mycpfrom", "mymkdir", "myrmdir", "myrm", "mymv", "mytouch", "myshowinode", "myshowblock", "mystate", "mytree", "byebye"};
	char command[100], cmd[5][20];
	FILE *save, *load;
	strcpy(pwd.name[0], "/");
	pwd.number[0] = 1;

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
				printf("case %d\n", i);
				break;
			//mycat
			case 2 :
				printf("case %d\n", i);
				break;
			//myshowfile
			case 3 :
				printf("case %d\n", i);
				break;
			//mypwd
			case 4 :
				mypwd(pwd);
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
				printf("case %d\n", i);
				break;
			//myshowblock
			case 15 :
				printf("case %d\n", i);
				break;
			//mystate
			case 16 :
				printf("case %d\n", i);
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
	}
	return 0;
}

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









