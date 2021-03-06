//myshowinode 함수
void myshowinode(MYFS myfs, int n){
	int a, first = 1;
	struct tm *time = myfs -> i[n-1] -> ti;
	DB h = NULL;

	//아이노드가 할당되었는지 확인
	if((myfs -> i[n-1]) == NULL){
		printf("error : not allocated\n");
	}
	else{
		//아이노드 정보 출력
		printf("file type : %s\n", myfs -> i[n-1] -> type ? "regular file" : "directory");
		printf("file size : %d\n", myfs -> i[n-1] -> size);
		printf("modified time : %4d/%02d/%02d %02d:%02d:%02d\n", time -> tm_year + 1900 , time -> tm_mon + 1, time -> tm_mday, time -> tm_hour, time -> tm_min, time -> tm_sec);
		printf("data block list : ");
		h = myfs -> i[n-1] -> dl -> db;
		//데이터 블럭 리스트 출력
		while(1){
			if(h == NULL){
				break;
			}
			else{
				if(first){
					first = 0;
				}
				else{
					printf(", ");
				}
				for(a=0; a<1024; a++){
					if(h == myfs -> d[a]){
						printf("%d", a + 1);
						break;
					}
				}
			}
			//다음 데이터 블럭 지정
			if(check){
				h = h -> fi -> next;
			}
			else{
				h = h -> di -> next;
			}
		}
		printf("\n");
	}
}
