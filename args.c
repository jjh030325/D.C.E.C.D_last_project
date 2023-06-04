#include <stdio.h>
#include <stdlib.h>

int check_params(int argc, char* argv[]) {
	if (argc == 2)
		return 1;
	return 0;
}

int main(int argc, char* argv[]) {
	if(check_params(argc, argv) == 0) {
		printf("Usage: %s param1\n", argv[0]);
		exit(1);	
	}

	printf("%s is good\n",argv[1]);
		
	return 0;
}
