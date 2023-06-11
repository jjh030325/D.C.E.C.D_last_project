#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIM 3
#define MAX_ROWS 10
#define MAX_COLS 10

struct ModifiedCompressData {
    int row;
    int col;
    int height;
    int data;
};

// 변조된 위치 정보를 저장할 전역 변수
struct ModifiedCompressData modifiedLocations[4];
int modifiedCount = 0;

struct ModifiedAsciiData {
    int x;
    int y;
    const char* name;
    int data;
};

// 변조된 위치 정보를 저장할 전역 변수
struct ModifiedAsciiData asciiLocations[4];
int asciiCount = 0;

// 2개의 데이터를 비교하여 변조된 4곳을 특정하는 함수
void findModifiedLocations(int data1[MAX_DIM][MAX_ROWS][MAX_COLS], int data2[MAX_DIM][MAX_ROWS][MAX_COLS]) {
    for (int d = 0; d < MAX_DIM; d++) {
        for (int i = 0; i < MAX_ROWS; i++) {
            for (int j = 0; j < MAX_COLS; j++) {
                if (data1[d][i][j] != data2[d][i][j]) {
                    modifiedLocations[modifiedCount].row = i;
                    modifiedLocations[modifiedCount].col = j;
                    modifiedLocations[modifiedCount].height = d;
                    modifiedLocations[modifiedCount].data = 0;
                    modifiedCount++;
                }
            }
        }
    }
}

// 아스키 데이터 변조 확인 및 전역 변수에 저장하는 함수
void checkAndSaveModifiedAsciiData(int asciiData1[MAX_ROWS][MAX_COLS], int asciiData2[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (asciiData1[i][j] != asciiData2[i][j]) {
                asciiLocations[asciiCount].x = i;
                asciiLocations[asciiCount].y = j;
                asciiLocations[asciiCount].name = " ";
                asciiLocations[asciiCount].data = 0;
                asciiCount++;
            }
        }
    }
}

// 변조된 위치에 대한 데이터 복원 함수
void restoreModifiedData(int data[MAX_DIM][MAX_ROWS][MAX_COLS], struct ModifiedCompressData locations[], int count) {
    for (int i = 0; i < count; i++) {
        int row = locations[i].row;
        int col = locations[i].col;
        int height = locations[i].height;
        int restoredData = 0;  // 복원된 데이터 값
        // 복원 로직 구현
        // 예를 들어, 특정 규칙에 따라 데이터를 복원한다고 가정
        // 복원된 값을 restoredData 변수에 저장

        // 복원된 데이터를 해당 위치에 저장
        data[height][row][col] = restoredData;
    }
}

int main() {
    // 예시 데이터
    int binaryData1[MAX_DIM][MAX_ROWS][MAX_COLS];
    int binaryData2[MAX_DIM][MAX_ROWS][MAX_COLS];
    int asciiData1_1[MAX_ROWS][MAX_COLS];
    int asciiData1_2[MAX_ROWS][MAX_COLS];
    int asciiData1_3[MAX_ROWS][MAX_COLS];
    int asciiData2_1[MAX_ROWS][MAX_COLS];
    int asciiData2_2[MAX_ROWS][MAX_COLS];
    int asciiData2_3[MAX_ROWS][MAX_COLS];

    // 바이너리 파일에서 압축 데이터와 아스키 데이터를 추출하여 binaryData1, binaryData2, asciiData1, asciiData2에 저장하는 로직

    // 2개의 데이터 비교 및 변조된 위치 찾기
    findModifiedLocations(binaryData1, binaryData2);

    // 아스키 데이터 변조 확인 및 저장
    checkAndSaveModifiedAsciiData(asciiData1_1, asciiData2_1);
    checkAndSaveModifiedAsciiData(asciiData1_2, asciiData2_2);
    checkAndSaveModifiedAsciiData(asciiData1_3, asciiData2_3);

    // 변조된 위치 정보 출력
    for (int i = 0; i < modifiedCount; i++) {
        printf("Modified Location %d:\n", i + 1);
        printf("Row: %d, Col: %d, Height: %d\n", modifiedLocations[i].row, modifiedLocations[i].col, modifiedLocations[i].height);
    }

    // 변조된 위치에 대한 데이터 복원
    restoreModifiedData(binaryData1, modifiedLocations, modifiedCount);

    return 0;
}
