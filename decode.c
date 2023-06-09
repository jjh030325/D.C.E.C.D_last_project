#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getFile(){

	// 메인함수에서 처음 파일을 읽어올때 쓰는 함수
}

void setTable(){
	// 읽은 파일에서 문자열을 3차원으로 setting하는 함수
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
