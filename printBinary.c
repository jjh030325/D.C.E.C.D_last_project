/*
chat_gpt 대답 : 
위 예시 코드에서는 "binary_data.bin"이라는 이름의 바이너리 파일을 읽고, printBinary 함수를 호출하여 각 바이트를 비트로 변환하여 출력합니다. 파일을 읽기 모드("rb")로 열고, fread 함수를 사용하여 바이트 단위로 데이터를 읽어옵니다. 읽어온 바이트는 printBinary 함수를 호출하여 비트로 변환하여 출력합니다. while 루프를 통해 파일의 끝까지 읽고 출력을 수행한 후, 파일을 닫습니다.

위 예시 코드를 실행하기 전에 "binary_data.bin" 파일이 존재해야 합니다. 이 파일은 바이너리 데이터를 포함하고 있어야 합니다. 파일이 존재하지 않을 경우에는 파일을 열 수 없다는 메시지가 출력됩니다.

실행하면 바이너리 파일에서 읽어온 데이터를 비트로 변환하여 출력하게 됩니다. 출력 결과는 각 바이트의 비트 표현이 공백으로 구분되어 나타납니다.

바이너리 파일에서 데이터를 읽어와 비트로 표현하는 경우, 파일의 크기와 읽어오는 데이터의 형식에 따라 적절한 크기의 변수를 사용하고, 데이터 읽기 오류에 대한 처리를 고려해야 합니다. 또한, 바이너리 파일의 내용과 구조에 따라 데이터의 해석과 표현 방식이 달라질 수 있으므로 해당 파일의 형식을 정확히 이해하고 처리해야 합니다.
*/
#include <stdio.h>

void printBinary(unsigned char byte) {
    for (int i = 7; i >= 0; i--) {
        unsigned char mask = 1 << i;
        unsigned char result = byte & mask;
        unsigned char bit = result >> i;
        printf("%u", bit);
    }
}

int main() {
    FILE* file = fopen("binary_data.bin", "rb");  // 바이너리 파일 열기

    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    unsigned char byte;

    while (fread(&byte, sizeof(byte), 1, file) == 1) {
        printBinary(byte);
        printf(" ");
    }

    fclose(file);  // 파일 닫기

    return 0;
}
