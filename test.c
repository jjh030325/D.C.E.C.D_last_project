#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void){
	FILE* fp = fopen("ex.bin", "wb");
	int i[2] = {4, 5};
	int cnt;

	cnt = fwrite(i, sizeof(int), 2, fp);
	if(cnt == 1) printf("파일 입력 완료\n");
	fclose(fp);
	return 0;
}
