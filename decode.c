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

void restore(const char* inputFile, const char* outputFile){
	FILE* binaryFile;     
	FILE* textFile;
	// 바이너리 파일 열기
	binaryFile = fopen(inputFile, "rb");
	if (binaryFile == NULL) {
		printf("바이너리 파일을 열 수 없습니다.");
		return;
	}

	// 텍스트 파일 열기
	textFile = fopen(outputFile, "w");
	if (textFile == NULL) {
		printf("텍스트 파일을 생성할 수 없습니다.");
		fclose(binaryFile);
		return;
	}

	int newlineCount = 0; // 연속된 '\n' 개수를 저장하기 위한 변수
	int isFirstItem = 1; // 첫 번째 *ITEMS* 입력 여부를 확인하기 위한 변수

	fprintf(textFile, "*USER STATUS*\n");

	// 바이너리 파일에서 데이터 읽어와 텍스트 파일에 쓰기
	int ch;
	while ((ch = fgetc(binaryFile)) != EOF) {
    // '\n' 문자일 경우
    if (ch == '\n') {
        newlineCount++;
        if (newlineCount == 2) {
						if(isFirstItem == 1)
						{
           			// 첫 번째 '\n\n'일 경우 *ITEMS* 출력
            		fprintf(textFile, "\n*ITEMS*");
								isFirstItem++;
						}else if(isFirstItem == 2)
						{
								// 두 번째 '\n\n'일 경우 *FRIENDS LIST* 출력
								fprintf(textFile, "\n*FRIENDS LIST*");
								isFirstItem++;				
						}
        }
    } else {
        // 개행 문자가 아닐 경우 newlineCount 초기화
        newlineCount = 0;
    }
		fprintf(textFile, "%c", ch);
	}

	// 파일 닫기
	fclose(binaryFile);
	fclose(textFile);
	printf("텍스트 파일로 변환되었습니다.");
}

int main(int argc, char* argv[]){
	if (argc != 3){
		printf("User: ./decoder.out <input_file> <output_file>\n");
		return 1;
	}

	const char * inputFile = argv[1];
	const char * outputFile = argv[2];
	restore(inputFile, outputFile);

	return 0;
}

