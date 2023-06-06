#include <stdio.h>

// 해밍 코드를 생성하는 함수
void generateHammingCode(int data[], int dataSize, int hammingCode[]) {
    // 해밍 코드의 길이 계산
    int hammingCodeSize = dataSize + (int)(log2(dataSize)) + 1;
  
    // 데이터 비트를 해밍 코드에 복사
    int dataIndex = 0;
    int hammingCodeIndex = 1;
    for (; hammingCodeIndex <= hammingCodeSize; hammingCodeIndex++) {
        // 해밍 코드의 인덱스가 2의 제곱수라면 해당 비트는 패리티 비트이므로 0으로 초기화
        if (hammingCodeIndex == pow(2, dataIndex)) {
            hammingCode[hammingCodeIndex] = 0;
            dataIndex++;
        }
        else {
            hammingCode[hammingCodeIndex] = data[dataIndex++];
        }
    }
  
    // 패리티 비트 계산
    for (int i = 0; i < dataSize; i++) {
        if (data[i] == 1) {
            for (int j = 0; j < hammingCodeSize; j++) {
                if (((j + 1) & (i + 1)) != 0) {
                    hammingCode[j + 1] = (hammingCode[j + 1] + 1) % 2;
                }
            }
        }
    }
}

// 해밍 코드를 검사하는 함수
void checkHammingCode(int hammingCode[], int hammingCodeSize, int errorBitIndex) {
    int errorDetected = 0;
    int errorBit = 0;
  
    // 패리티 비트를 검사하여 오류 검출
    for (int i = 0; i < hammingCodeSize; i++) {
        if (((i + 1) & (errorBitIndex + 1)) != 0) {
            errorBit ^= hammingCode[i + 1];
        }
    }
  
    // 오류 검출 여부에 따라 결과 출력
    if (errorBit == hammingCode[errorBitIndex]) {
        errorDetected = 0;
    } else {
        errorDetected = 1;
    }
  
    if (errorDetected) {
        printf("오류가 발견되었습니다.\n");
        printf("오류 비트 위치: %d\n", errorBitIndex);
        printf("수정 후 데이터: ");
      
        // 오류 비트 수정
        hammingCode[errorBitIndex] = (hammingCode[errorBitIndex] + 1) % 2;
      
        // 수정된 데이터 출력
        for (int i = 1; i <= hammingCodeSize; i++) {
            printf("%d ", hammingCode[i]);
        }
        printf("\n");
    } else {
        printf("오류가 발견되지 않았습니다.\n");
        printf("데이터: ");
      
        // 데이터 출력
        for (int i = 1; i <= hammingCodeSize; i++) {
            printf("%d ", hammingCode[i]);
        }
        printf("\n");
    }
}

int main() {
    int dataSize;
  
    printf("데이터 비트의 개수를 입력하세요: ");
    scanf("%d", &dataSize);
  
    int data[dataSize];
    int hammingCodeSize = dataSize + (int)(log2(dataSize)) + 1;
    int hammingCode[hammingCodeSize];
  
    printf("데이터 비트를 입력하세요 (공백으로 구분): ");
    for (int i = 0; i < dataSize; i++) {
        scanf("%d", &data[i]);
    }
  
    generateHammingCode(data, dataSize, hammingCode);
  
    printf("생성된 해밍 코드: ");
    for (int i = 1; i <= hammingCodeSize; i++) {
        printf("%d ", hammingCode[i]);
    }
    printf("\n");
  
    int errorBitIndex;
    printf("오류 비트 위치를 입력하세요 (1부터 시작): ");
    scanf("%d", &errorBitIndex);
  
    checkHammingCode(hammingCode, hammingCodeSize, errorBitIndex);
  
    return 0;#include <stdio.h>

// 해밍 코드를 생성하는 함수
void generateHammingCode(int data[], int dataSize, int hammingCode[]) {
    // 해밍 코드의 길이 계산
    int hammingCodeSize = dataSize + (int)(log2(dataSize)) + 1;
  
    // 데이터 비트를 해밍 코드에 복사
    int dataIndex = 0;
    int hammingCodeIndex = 1;
    for (; hammingCodeIndex <= hammingCodeSize; hammingCodeIndex++) {
        // 해밍 코드의 인덱스가 2의 제곱수라면 해당 비트는 패리티 비트이므로 0으로 초기화
        if (hammingCodeIndex == pow(2, dataIndex)) {
            hammingCode[hammingCodeIndex] = 0;
            dataIndex++;
        }
        else {
            hammingCode[hammingCodeIndex] = data[dataIndex++];
        }
    }
  
    // 패리티 비트 계산
    for (int i = 0; i < dataSize; i++) {
        if (data[i] == 1) {
            for (int j = 0; j < hammingCodeSize; j++) {
                if (((j + 1) & (i + 1)) != 0) {
                    hammingCode[j + 1] = (hammingCode[j + 1] + 1) % 2;
                }
            }
        }
    }
}

// 해밍 코드를 검사하는 함수
void checkHammingCode(int hammingCode[], int hammingCodeSize, int errorBitIndex) {
    int errorDetected = 0;
    int errorBit = 0;
  
    // 패리티 비트를 검사하여 오류 검출
    for (int i = 0; i < hammingCodeSize; i++) {
        if (((i + 1) & (errorBitIndex + 1)) != 0) {
            errorBit ^= hammingCode[i + 1];
        }
    }
  
    // 오류 검출 여부에 따라 결과 출력
    if (errorBit == hammingCode[errorBitIndex]) {
        errorDetected = 0;
    } else {
        errorDetected = 1;
    }
  
    if (errorDetected) {
        printf("오류가 발견되었습니다.\n");
        printf("오류 비트 위치: %d\n", errorBitIndex);
        printf("수정 후 데이터: ");
      
        // 오류 비트 수정
        hammingCode[errorBitIndex] = (hammingCode[errorBitIndex] + 1) % 2;
      
        // 수정된 데이터 출력
        for (int i = 1; i <= hammingCodeSize; i++) {
            printf("%d ", hammingCode[i]);
        }
        printf("\n");
    } else {
        printf("오류가 발견되지 않았습니다.\n");
        printf("데이터: ");
      
        // 데이터 출력
        for (int i = 1; i <= hammingCodeSize; i++) {
            printf("%d ", hammingCode[i]);
        }
        printf("\n");
    }
}

int main() {
    int dataSize;
  
    printf("데이터 비트의 개수를 입력하세요: ");
    scanf("%d", &dataSize);
  
    int data[dataSize];
    int hammingCodeSize = dataSize + (int)(log2(dataSize)) + 1;
    int hammingCode[hammingCodeSize];
  
    printf("데이터 비트를 입력하세요 (공백으로 구분): ");
    for (int i = 0; i < dataSize; i++) {
        scanf("%d", &data[i]);
    }
  
    generateHammingCode(data, dataSize, hammingCode);
  
    printf("생성된 해밍 코드: ");
    for (int i = 1; i <= hammingCodeSize; i++) {
        printf("%d ", hammingCode[i]);
    }
    printf("\n");
  
    int errorBitIndex;
    printf("오류 비트 위치를 입력하세요 (1부터 시작): ");
    scanf("%d", &errorBitIndex);
  
    checkHammingCode(hammingCode, hammingCodeSize, errorBitIndex);
  
    return 0;
}
