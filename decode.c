#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** ASC_row;
int** ASC_column;
int ASC_height[10][10] = { 0 };

int** compare_ASC_row;
int** compare_ASC_column;
int compare_ASC_height[10][10] = { 0 };

// 아스키 배열들을 추출하기 위한 함수
// !@#$%^ 순으로 마지막에 적힌 문자열을 고려해서
// 알고리즘 구현
void getTable(const char* inputFile) {
	FILE* output = fopen(inputFile, "rb");
	if (output == NULL) {
		fprintf(stderr, "열 수 없습니다.\n");
		exit(0);
	}


	// 2차원 배열 할당 받기 + 마지막 줄 찾기
	int size = 0; // 압축된 문자열 길이
	int symbol = 0; // 특수기호 발견 시 카운트
	char ch;
	while (1) { // 파일 전체를 읽기 위한 루프문
		if (fread(&ch, 1, 1, output) != 1) break; // 끝까지 가면 탈출
		size++;
		if (ch == '!') {
			symbol++;
			for (int i = 0; i < 5; i++) { // 다음 글자를 읽는다 5글자
				fread(&ch, 1, 1, output);
				size++;
				if (ch == '@') symbol++;
				else if (ch == '#') symbol++;
				else if (ch == '$') symbol++;
				else if (ch == '%') symbol++;
				else if (ch == '^') symbol++;
			}
			if (symbol >= 2) {
				printf("! 조건문 GOOD\n");
				printf("symbol : %d\n", symbol);
				break;
			}
			symbol = 0;
		}  // 파일 전체 사이즈 + 아스키 코드값 시작
		else if (ch == '@') {
			symbol++;
			for (int i = 0; i < 4; i++) {
				fread(&ch, 1, 1, output);
				size++;
				if (ch == '#') symbol++;
				else if (ch == '$') symbol++;
				else if (ch == '%') symbol++;
				else if (ch == '^') symbol++;
			}
			if (symbol >= 2) {
				printf("GOOD\n");
				break;
			}
			symbol = 0;
		}  // 파일 전체 사이즈 + 아스키 코드값 시작
		else if (ch == '#') {
			symbol++;
			for (int i = 0; i < 3; i++) {
				fread(&ch, 1, 1, output);
				size++;
				if (ch == '$') symbol++;
				else if (ch == '%') symbol++;
				else if (ch == '^') symbol++;
			}
			if (symbol >= 2) {
				printf("GOOD\n");
				break;
			}
			symbol = 0;
		}
		else if (ch == '$') {
			symbol++;
			for (int i = 0; i < 2; i++) {
				fread(&ch, 1, 1, output);
				size++;
				if (ch == '%') symbol++;
				else if (ch == '^') symbol++;
			}
			if (symbol >= 2) {
				printf("GOOD\n");
				break;
			}
			symbol = 0;
		}
	}
	size -= 6;
	size = size / 2;
	fseek(output, 4, SEEK_CUR);
	printf("현재 파일 위치 : %ld\n", ftell(output));
	printf("FIEL SIZE : %d\n", size);
	int height = size / 100;
	size -= 100 * height; // 백자리 제외


	// 첫 번째 배열 할당
	ASC_column = (int**)malloc((height + 1) * sizeof(int*));
	ASC_row = (int**)malloc((height + 1) * sizeof(int*));
	for (int i = 0; i < height + 1; i++) {
		ASC_column[i] = (int*)calloc(10, sizeof(int));
		ASC_row[i] = (int*)calloc(10, sizeof(int));
	}

	// 두 번째 배열 할당
	compare_ASC_column = (int**)malloc((height + 1) * sizeof(int*));
	compare_ASC_row = (int**)malloc((height + 1) * sizeof(int*));
	for (int i = 0; i < height + 1; i++) {
		compare_ASC_column[i] = (int*)calloc(10, sizeof(int));
		compare_ASC_row[i] = (int*)calloc(10, sizeof(int));
	}

	// 첫 번째 배열 값 삽입
	for (int k = 0; k < height + 1; k++) {
		fread(ASC_column[k], sizeof(int), 10, output);
		fread(ASC_row[k], sizeof(int), 10, output);
	}
	for (int k = 0; k < 10; k++) {
		fread(ASC_height[k], sizeof(int), 10, output);
	}


	// 두 번째 배열 값 삽입
	for (int k = 0; k < height + 1; k++) {
		fread(compare_ASC_column[k], sizeof(int), 10, output);
		fread(compare_ASC_row[k], sizeof(int), 10, output);
	}
	for (int k = 0; k < 10; k++) {
		fread(compare_ASC_height[k], sizeof(int), 10, output);
	}




	// 값 확인
	for (int i = 0; i < height + 1; i++) {
		for (int j = 0; j < 10; j++) {
			printf("ASC_column[%d][%d] : %d\n", i, j, ASC_column[i][j]);
		}
		printf("\n");
	}
	for (int i = 0; i < height + 1; i++) {
		for (int j = 0; j < 10; j++) {
			printf("compare_ASC_column[%d][%d] : %d\n", i, j, compare_ASC_column[i][j]);
		}
		printf("\n");
	}


	// 할당 해제
	for (int i = 0; i < height + 1; i++) {
		free(ASC_column[i]);
		free(ASC_row[i]);
	}
	free(ASC_column);
	free(ASC_row);

	for (int i = 0; i < height + 1; i++) {
		free(compare_ASC_column[i]);
		free(compare_ASC_row[i]);
	}
	free(compare_ASC_column);
	free(compare_ASC_row);
	fclose(output);
}
void checkData() {
	// 변조 체크를 하는 함수
}

void dataRestore() {
	// 바이너리 파일 복원 함수
}

//파일 복원 함수
void restore(const char* inputFile, const char* outputFile) {
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
	int userStatusCount = 0; // *USER STATUS* 섹션 내의 데이터 개수를 저장하기 위한 변수
	int firstspace_check = 0; //FRIEND LIST 섹션 공백 개수 저장 변수
	int friend_check = 0; //FRIEND LIST 항목 체크용 변수 0 = ID, 1 = NAME...etc

	fprintf(textFile, "*USER STATUS*\nID: ");

	// 바이너리 파일에서 데이터 읽어와 텍스트 파일에 쓰기
	int ch;
	while ((ch = fgetc(binaryFile)) != EOF) {
		// '\n' 문자일 경우
		if (ch == '\n') {
			newlineCount++;
			firstspace_check = 0;
			if (newlineCount == 1 && userStatusCount <= 6) {
				// *USER STATUS* 섹션 내의 데이터를 출력
				switch (userStatusCount) {
				case 0:
					fprintf(textFile, "\nNAME: ");
					break;
				case 1:
					fprintf(textFile, "\nGENDER: ");
					break;
				case 2:
					fprintf(textFile, "\nAGE: ");
					break;
				case 3:
					fprintf(textFile, "\nHP: ");
					break;
				case 4:
					fprintf(textFile, "\nMP: ");
					break;
				case 5:
					fprintf(textFile, "\nCOIN: ");
					break;
				default:
					break;
				}
				userStatusCount++;
			}

			if (newlineCount == 2) {
				if (isFirstItem == 1)
				{
					// 첫 번째 '\n\n'일 경우 *ITEMS* 출력
					fprintf(textFile, "\n*ITEMS*");
					isFirstItem++;
				}
				else if (isFirstItem == 2)
				{
					// 두 번째 '\n\n'일 경우 *FRIENDS LIST* 출력
					fprintf(textFile, "\n*FRIENDS LIST*");
					isFirstItem++;
				}
			}
		}
		else {
			// 개행 문자가 아닐 경우 newlineCount 초기화
			newlineCount = 0;
		}

		if (isFirstItem == 3) {
			if (newlineCount == 0) {
				if (ch >= '1' && ch <= '9' && firstspace_check == 0)
				{
					fprintf(textFile, "FRIEND");
					firstspace_check++;
				}
			}
		}


		if (newlineCount == 0)
			fprintf(textFile, "%c", ch);
		else if (userStatusCount >= 7)
			fprintf(textFile, "%c", ch);
		if (userStatusCount == 7)
			userStatusCount++;
		// *ITEMS* 섹션 이후부터 *FRIENDS LIST* 이전까지만 첫 글자를 보고 텍스트를 추가
		if (isFirstItem == 2) {
			if (newlineCount == 0) {
				if (ch == 'A') {
					fseek(textFile, -1, SEEK_CUR);
					fprintf(textFile, "BOMB:");
				}
				else if (ch == 'P') {
					fseek(textFile, -1, SEEK_CUR);
					fprintf(textFile, "POTION:");
				}
				else if (ch == 'C') {
					fseek(textFile, -1, SEEK_CUR);
					fprintf(textFile, "CURE:");
				}
				else if (ch == 'B') {
					fseek(textFile, -1, SEEK_CUR);
					fprintf(textFile, "BOOK:");
				}
				else if (ch == 'S') {
					fseek(textFile, -1, SEEK_CUR);
					fprintf(textFile, "SHIELD:");
				}
				else if (ch == 'I') {
					fseek(textFile, -1, SEEK_CUR);
					fprintf(textFile, "CANNON:");
				}
			}
		}

		if (isFirstItem == 3) {
			if (newlineCount == 0) {
				if (ch == '/') {
					fseek(textFile, -1, SEEK_CUR);
					fprintf(textFile, "*DESCRIPTION*\n");
					isFirstItem++;
				}
				else if (ch == '&') {
					fseek(textFile, -1, SEEK_CUR);
					fprintf(textFile, " ");
					switch (friend_check)
					{
					case 0:
						fprintf(textFile, "ID: ");
						friend_check++;
						break;
					case 1:
						fprintf(textFile, "NAME: ");
						friend_check++;
						break;
					case 2:
						fprintf(textFile, "GENDER: ");
						friend_check++;
						break;
					case 3:
						fprintf(textFile, "AGE: ");
						friend_check = 0;
						break;
					}
				}
			}
		}

	}

	// 파일 닫기
	fclose(binaryFile);
	fclose(textFile);
	printf("텍스트 파일로 변환되었습니다.\n");
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("User: ./decoder.out <input_file> <output_file>\n");
		return 1;
	}

	const char* inputFile = argv[1];
	const char* outputFile = argv[2];
	//restore(inputFile, outputFile);
	getTable(inputFile);
	return 0;
}
