#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 10
#define MAX_COLS 10

struct ModifiedData {
    int row;
    int col;
    char data;
};

// 변조된 위치 정보를 저장할 전역 변수
struct ModifiedData modifiedLocations[4];
int modifiedCount = 0;

// 2개의 데이터를 비교하여 변조된 4곳을 특정하는 함수
void findModifiedLocations(char binaryData1[MAX_ROWS][MAX_COLS], char binaryData2[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (binaryData1[i][j] != binaryData2[i][j]) {
                modifiedLocations[modifiedCount].row = i;
                modifiedLocations[modifiedCount].col = j;
                modifiedLocations[modifiedCount].data = binaryData2[i][j];
                modifiedCount++;
            }
        }
    }
}

int main() {
    // 예시 데이터
    char binaryData1[MAX_ROWS][MAX_COLS];
    char binaryData2[MAX_ROWS][MAX_COLS];

    // 바이너리 파일에서 압축 데이터와 아스키 데이터를 추출하여 binaryData1, binaryData2에 저장하는 로직

    // 2개의 데이터 비교 및 변조된 위치 특정
    findModifiedLocations(binaryData1, binaryData2);

    // 변조된 위치 정보 출력
    for (int i = 0; i < modifiedCount; i++) {
        printf("Modified Location %d: Row %d, Column %d, Data %c\n",
            i + 1, modifiedLocations[i].row, modifiedLocations[i].col, modifiedLocations[i].data);
    }

    return 0;
}
