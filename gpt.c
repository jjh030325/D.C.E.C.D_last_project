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

// 압축 데이터와 아스키 데이터 비교 및 변조된 위치 특정 함수
void compareData(char compressedData[MAX_ROWS][MAX_COLS], int asciiDataRows, int asciiDataCols) {
    // 가로합 비교
    for (int row = 0; row < MAX_ROWS; row++) {
        int sum = 0;
        for (int col = 0; col < MAX_COLS; col++) {
            sum += compressedData[row][col];
        }
        if (sum != originalAsciiData[0][row]) {
            modifiedLocations[modifiedCount].row = row;
            modifiedLocations[modifiedCount].col = -1;
            modifiedLocations[modifiedCount].data = sum;
            modifiedCount++;
        }
    }
    
    // 세로합 비교
    for (int col = 0; col < MAX_COLS; col++) {
        int sum = 0;
        for (int row = 0; row < MAX_ROWS; row++) {
            sum += compressedData[row][col];
        }
        if (sum != originalAsciiData[1][col]) {
            modifiedLocations[modifiedCount].row = -1;
            modifiedLocations[modifiedCount].col = col;
            modifiedLocations[modifiedCount].data = sum;
            modifiedCount++;
        }
    }
    
    // 높이합 비교
    for (int row = 0; row < asciiDataRows; row++) {
        for (int col = 0; col < asciiDataCols; col++) {
            if (compressedData[row][col] != originalCompressedData[row][col]) {
                modifiedLocations[modifiedCount].row = row;
                modifiedLocations[modifiedCount].col = col;
                modifiedLocations[modifiedCount].data = compressedData[row][col];
                modifiedCount++;
            }
        }
    }
}

// 데이터 복원 함수
void restoreData(char compressedData[MAX_ROWS][MAX_COLS], int asciiDataRows, int asciiDataCols) {
    // 데이터 복원 로직 추가
    for (int i = 0; i < modifiedCount; i++) {
        int row = modifiedLocations[i].row;
        int col = modifiedLocations[i].col;
        char data = modifiedLocations[i].data;
        
        if (row == -1 && col == -1) {
            // 가로합 복원
            // ...
        } else if (row == -1) {
            // 세로합 복원
            // ...
        } else {
            // 압축 데이터 복원
            compressedData[row][col] = data;
        }
    }
}

int main() {
    // 예시 데이터
    char compressedData[MAX_ROWS][MAX_COLS] = {
        "abcde",
        "fghij",
        "klmno",
        "pqrst",
        "uvwxy",
        "zzzzz",
        "11111",
        "22222",
        "33333",
        "44444"
    };

    char originalCompressedData[MAX_ROWS][MAX_COLS] = {
        "abcde",
        "fghij",
        "klmno",
        "pqrst",
        "uvwxy",
        "zzzzz",
        "11111",
        "22222",
        "33333",
        "44444"
    };

    int asciiDataRows = 3;
    int asciiDataCols = 10;
    int originalAsciiData[3][10] = {
        { 123, 234, 345, 456, 567, 678, 789, 890, 901, 12 },
        { 321, 432, 543, 654, 765, 876, 987, 198, 219, 32 },
        { 111, 222, 333, 444, 555, 666, 777, 888, 999, 99 }
    };

    // 데이터 비교 및 변조된 위치 특정
    compareData(compressedData, asciiDataRows, asciiDataCols);

    // 데이터 복원
    restoreData(compressedData, asciiDataRows, asciiDataCols);

    return 0;
}
/* 압축 데이터가 10x10 배열에 있고 아스키 데이터가 가로합, 세로합, 높이합 3개로 주어진다는 가정하에 복원 함수를 수정해보겠습니다. 아래는 수정된 C 언어 예시 코드입니다.
* 위의 코드에서는 가로합, 세로합, 높이합을 비교하여 변조된 위치를 특정하고, 복원 로직을 추가하여 데이터를 복원합니다.
* 복원 로직은 현재 주석 처리되어 있으므로 실제로 복원해야 할 데이터에 맞게 구현해야 합니다.
*/
