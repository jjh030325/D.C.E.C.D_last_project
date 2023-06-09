#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main(void){
	FILE* fp = fopen("ex.bin.modified", "rb");
	int i[2];

	fread(i, sizeof(i), 1, fp);
	printf("%d %d\n", *(i+0), *(i+1));
	fclose(fp);
	return 0;
}
