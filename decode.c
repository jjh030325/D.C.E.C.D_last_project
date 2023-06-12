#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int** ASC_row;
int** ASC_column;
int ASC_height[10][10] = { 0 };

int** compare_ASC_row;
int** compare_ASC_column;
int compare_ASC_height[10][10] = { 0 };

char* compress_str;
char* compare_compress_str;

int size = 0;
int height = 0;

// (V_ASC_count, V_Char_count) = (4, 0), (3, 1), (2, 2), (1, 3), (0, 4)
// (4, 0) 인 경우 -> 바로 해독 실행 (3, 1), (2, 2), (1, 3), (0, 4)
// 가로 세로 높이 중 변조가 일어난 부분을 제외한 축을 이용해 변조 복구를 한다
// 한 개의 축을 이용해서 변조 복구가 가능하다
int V_ASC_count;
int V_Char_count;


// 인덱스 0부터 시작 되는 값을 그대로 받는다 배열에 그대로 가져다 쓰면 됨,
typedef struct {
	int row;
	int column;
	int height;
	char ch;
}Char_variable; // 변조된 압축문자에 대한 정보

typedef struct {
	int xpos;
	int ypos;
	char type; // r = ASC_row, c = ASC_column, h = ASC_height
}ASC_variable; // 변조된 아스키데이터에 대한 정보

Char_variable* Cvar;
ASC_variable* Avar;

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
	size -= 1;

	fseek(output, 4, SEEK_CUR);
	printf("현재 파일 위치 : %ld\n", ftell(output));
	printf("FIEL SIZE : %d\n", size);
	height = size / 100; // 0층부터 시작
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

	size += 100 * height;
	// 압축된 문자열 배열 할당 + 값삽입
	fseek(output, 0, SEEK_SET);
	compress_str = (char*)calloc(size, sizeof(int));
	compare_compress_str = (char*)calloc(size, sizeof(int));

	fread(compress_str, 1, size, output);
	fseek(output, 1, SEEK_CUR);
	fread(compare_compress_str, 1, size, output);
	compress_str[size] = '\n';
	compare_compress_str[size] = '\n';
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
	
	
	printf("compress_str : %s\n", compress_str);
	printf("compare_compress_str : %s\n", compare_compress_str);
	//printf("getTable 성공\n");
	fclose(output);
	output = NULL;
}
void checkData() {
	// 압축된 문자열에서 변조 확인 확인 
	Cvar = (Char_variable*)malloc(sizeof(Char_variable));
	Avar = (ASC_variable*)malloc(sizeof(ASC_variable));
	V_ASC_count = 0;
	V_Char_count = 0;

	for (int i = 0; i < size; i++) {
		if (compare_compress_str[i] != compress_str[i]) {
			if(V_Char_count != 0) Cvar = (Char_variable*)realloc(Cvar, sizeof(Char_variable) * (V_Char_count+1));
			(Cvar + V_Char_count)->ch = compress_str[i];
			(Cvar + V_Char_count)->height = i / 100;
			for (int j = 0; j < height + 1; j++) {
				if (i / 100 == j) {
					int num = i;
					num = num - 100 * j;
					(Cvar + V_Char_count)->row = num / 10;
					(Cvar + V_Char_count)->column = num % 10;
				}
			}
			V_Char_count++;
		}
	}


	//아스키 데이터에서 변조 확인
	for (int i = 0; i < height + 1; i++) {
		for (int j = 0; j < 10; j++) {
			if (compare_ASC_column[i][j] != ASC_column[i][j]) {
				if (V_ASC_count != 0) Avar = (ASC_variable*)realloc(Avar, sizeof(ASC_variable) * (V_ASC_count + 1));
				(Avar + V_ASC_count)->type = 'c';
				(Avar + V_ASC_count)->xpos = j;
				(Avar + V_ASC_count)->ypos = i;
				V_ASC_count++;
			}

			if (compare_ASC_row[i][j] != ASC_row[i][j]) {
				if (V_ASC_count != 0) Avar = (ASC_variable*)realloc(Avar, sizeof(ASC_variable) * (V_ASC_count + 1));
				(Avar + V_ASC_count)->type = 'r';
				(Avar + V_ASC_count)->xpos = j;
				(Avar + V_ASC_count)->ypos = i;
				V_ASC_count++;
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (compare_ASC_height[i][j] != ASC_height[i][j]) {
				if (V_Char_count != 0) Avar = (ASC_variable*)realloc(Avar, sizeof(ASC_variable) * (V_ASC_count + 1));
				(Avar + V_ASC_count)->type = 'h';
				(Avar + V_ASC_count)->xpos = j;
				(Avar + V_ASC_count)->ypos = i;
				V_ASC_count++;
			}
		}
	}



	for (int i = 0; i < V_Char_count; i++) {
		printf("--------------------------\n");
		printf("ch -> %c\n", Cvar[i].ch);
		printf("row -> %d\n", Cvar[i].row);
		printf("column - > %d\n", Cvar[i].column);
		printf("height - > %d\n", Cvar[i].height);
	}

	for (int i = 0; i < V_ASC_count; i++) {
		printf("--------------------------\n");
		printf("type -> %c\n", Avar[i].type);
		printf("xpos -> %d\n", Avar[i].xpos);
		printf("ypos - > %d\n", Avar[i].ypos);
	}
}

//압축된 문자 복원 함수
void dataRestore() {
	if()
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
	restore(inputFile, outputFile);
	getTable(inputFile);
	checkData();

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

	free(compress_str);
	free(compare_compress_str);

	free(Cvar);
	free(Avar);

	return 0;
}
