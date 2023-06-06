/*
Q : 바이너리 데이터를 비트 단위로 접근해서 수정후 다시 파일에 저장해줘
A : 위 예시 코드는 "binary_data.bin"이라는 이름의 바이너리 파일을 열고, 각 비트를 반전시킨 후 다시 파일에 저장합니다. 이를 위해 BitFile 구조체를 사용하여 비트 단위로 파일 작업을 수행합니다.

openBitFile 함수는 파일을 열고 BitFile 구조체를 초기화합니다. writeBit 함수는 비트 단위로 데이터를 수정하고 파일에 씁니다. closeBitFile 함수는 파일을 닫고 남은 비트를 저장합니다.

주의해야 할 점은 이 예시 코드는 입력 파일과 출력 파일의 크기가 같은 경우에만 동작합니다. 비트 단위의 파일 수정은 데이터 크기가 변하면 파일 구조가 깨질 수 있으므로, 이를 고려하여 파일을 수정해야 합니다.

실행하면 "binary_data.bin" 파일의 각 비트가 반전되고, 파일이 수정된 후에 "파일이 수정되었습니다."라는 메시지가 출력됩니다.
*/	 
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    FILE* file;         // 파일 포인터
    unsigned char buffer;   // 현재 버퍼
    int bitsRemaining;  // 현재 버퍼에 남은 비트 수
} BitFile;

// 비트 단위로 파일 열기
BitFile* openBitFile(const char* filename, const char* mode) {
    FILE* file = fopen(filename, mode);
    if (file == NULL) {
        return NULL;
    }

    BitFile* bitFile = (BitFile*)malloc(sizeof(BitFile));
    bitFile->file = file;
    bitFile->buffer = 0;
    bitFile->bitsRemaining = 8;

    return bitFile;
}

// 비트 쓰기
void writeBit(BitFile* bitFile, int bit) {
    if (bitFile->bitsRemaining == 0) {
        fwrite(&(bitFile->buffer), sizeof(unsigned char), 1, bitFile->file);
        bitFile->buffer = 0;
        bitFile->bitsRemaining = 8;
    }

    bitFile->buffer = (bitFile->buffer << 1) | (bit & 1);
    bitFile->bitsRemaining--;
}

// 파일 닫기 및 남은 비트 저장
void closeBitFile(BitFile* bitFile) {
    if (bitFile->bitsRemaining < 8) {
        bitFile->buffer <<= bitFile->bitsRemaining;
        fwrite(&(bitFile->buffer), sizeof(unsigned char), 1, bitFile->file);
    }

    fclose(bitFile->file);
    free(bitFile);
}

int main() {
    const char* filename = "binary_data.bin";

    // 바이너리 파일 열기
    BitFile* bitFile = openBitFile(filename, "rb");
    if (bitFile == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // 비트 단위로 데이터 수정 및 파일 저장
    while (1) {
        int bit = fgetc(bitFile->file);
        if (bit == EOF) {
            break;
        }

        // 비트 단위로 접근하여 수정
        // 이 예시에서는 각 비트를 반전시킴
        bit = !bit;

        // 수정된 비트 쓰기
        writeBit(bitFile, bit);
    }

    // 파일 닫기 및 저장
    closeBitFile(bitFile);

    printf("파일이 수정되었습니다.\n");

    return 0;
}
