#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getFile(){
}

void setTable(){
}

void getTable(){
}

void checkData(){
}

void restore(){
}

int main(int argc, char* argv[]){
	if (argc != 3){
		printf("User: ./decoder.out <input_file> <output_file>\n");
		return 1;
	}

	const char * inputFile = argv[1];
	const char * outputFile = argv[2];

	return 0;
