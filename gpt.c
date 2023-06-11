#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIM 3
#define MAX_ROWS 10
#define MAX_COLS 10

struct ModifiedData {
    int row;
    int col;
    int height;
    int binaryData;
    int asciiData;
};

// 변조된 위치 정보를 저장할 전역 변수
struct ModifiedData modifiedLocations[4];
int modifiedCount = 0;

// 2개의 데이터를 비교하여 변조된 4곳을 특정하는 함수
void findModifiedLocations(int data1[MAX_DIM][MAX_ROWS][MAX_COLS], int data2[MAX_DIM][MAX_ROWS][MAX_COLS]) {
    for (int d = 0; d < MAX_DIM; d++) {
        for (int i = 0; i < MAX_ROWS; i++) {
            for (int j = 0; j < MAX_COLS; j++) {
                if (data1[d][i][j] != data2[d][i][j]) {
                    modifiedLocations[modifiedCount].row = i;
                    modifiedLocations[modifiedCount].col = j;
                    modifiedLocations[modifiedCount].height = d;
                    modifiedLocations[modifiedCount].binaryData = data2[d][i][j];
                    modifiedLocations[modifiedCount].asciiData = -1;  // 아스키 데이터 변조되지 않음
                    modifiedCount++;
                }
            }
        }
    }
}

// 아스키 데이터 변조 확인 및 전역 변수에 저장하는 함수
void checkAndSaveModifiedAsciiData(int asciiData[MAX_DIM][MAX_ROWS][MAX_COLS]) {
    for (int d = 0; d < MAX_DIM; d++) {
        for (int i = 0; i < MAX_ROWS; i++) {
            for (int j = 0; j < MAX_COLS; j++) {
                if (asciiData[d][i][j] != modifiedLocations[d].binaryData) {
                    modifiedLocations[modifiedCount].row = i;
                    modifiedLocations[modifiedCount].col = j;
                    modifiedLocations[modifiedCount].height = d;
                    modifiedLocations[modifiedCount].binaryData = -1;  // 압축 데이터 변조되지 않음
                    modifiedLocations[modifiedCount].asciiData = asciiData[d][i][j];
                    modifiedCount++;
                }
            }
        }
    }
}

int main() {
    // 예시 데이터
    int binaryData1[MAX_DIM][MAX_ROWS][MAX_COLS];
    int binaryData2[MAX_DIM][MAX_ROWS][MAX_COLS];
    int asciiData1[MAX_DIM][MAX_ROWS][MAX_COLS];
    int asciiData2[MAX_DIM][MAX_ROWS][MAX_COLS];

    // 바이너리 파일에서 압축 데이터와 아스키 데이터를 추출하여 binaryData1, binaryData2, asciiData1, asciiData2에 저장하는 로직

    // 2개의 데이터 비교 및 변조된 위치 찾기
    findModifiedLocations(binaryData1, binaryData2);

    // 아스키 데이터 변조 확인 및 저장
    checkAndSaveModifiedAsciiData(asciiData1);

    // 변조된 위치 정보 출력
    for (int i = 0; i < modifiedCount; i++) {
        printf("Modified Location %d:\n", i + 1);
        printf("Row: %d, Col: %d, Height: %d\n", modifiedLocations[i].row, modifiedLocations[i].col, modifiedLocations[i].height);
        printf("Binary Data: %d, Ascii Data: %d\n\n", modifiedLocations[i].binaryData, modifiedLocations[i].asciiData);
    }

    return 0;
}
