#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encodeASC(const char* outputFile)
{
    FILE* output = fopen(outputFile, "rb");
    if (output == NULL)
    {
        printf("Failed to open output file.\n");
        return;
    }
    int size = 0;
    char ch;
    while (fread(&ch, 1, 1, output) == 1) size++; // 파일 전체 사이즈
    size -= 5;
    printf("FIEL SIZE : %d\n", size);
    fseek(output, 0, SEEK_SET);
    int height = size / 100;

    size -= 100 * height; // 백자리 제외
    int** ASC_column = (int**)malloc((height + 1) * sizeof(int*));
    int** ASC_row = (int**)malloc((height + 1) * sizeof(int*));
    int ASC_height[10][10] = { 0 };
    for (int i = 0; i < height + 1; i++) {
        ASC_column[i] = (int*)calloc(10, sizeof(int));
        ASC_row[i] = (int*)calloc(10, sizeof(int));
    }
    printf("동적 할당 완료\n");

    for (int k = 0; k < height; k++) { // 최대 높이 만큼 반복
        for (int i = 0; i < 10; i++) { // 세로
            for (int j = 0; j < 10; j++) { // 가로
                if (fread(&ch, 1, 1, output) != 1) {
                    printf("Failed to read from output file.\n");
                    fclose(output);
                    return;
                }
                printf("%d%d%d 번째 아스키 코드값 : %d\n", k, i, j, ch);
                ASC_column[k][j] += ch; // 높이 고정, 가로 j가 증가하면서 해당 행에 대한 값을 더한다
                printf("ASC_column[%d][%d] : %d\n", k, j, ASC_column[k][j]);
                ASC_row[k][i] += ch; // 높이 고정, 세로 i가 증가하면서 해당 열에 대한 값을 더한다
                printf("ASC_row[%d][%d] : %d\n", k, i, ASC_row[k][i]);
                ASC_height[i][j] += ch;  // 
                printf("ASC_height[%d][%d] : %d\n\n", i, j, ASC_height[i][j]);
            }
        }
    }
    printf("100단위 값 저장 완료\n");


    for (int i = 0; i < size / 10 + 1; i++) { // 나머지 길이만큼 반복
        for (int j = 0; j < size % 10; j++) {
            if (fread(&ch, 1, 1, output) != 1) {
                printf(" Read to file end\n");
                break;
            }
            printf("%d%d%d 번째 아스키 코드값 : %d\n", height, i, j, ch);
            ASC_column[height][j] += ch; // 높이 고정, 가로 j가 증가하면서 해당 행에 대한 값을 더한다
            printf("ASC_column[%d][%d] : %d\n", height, j, ASC_column[height][j]);
            ASC_row[height][i] += ch; // 높이 고정, 세로 i가 증가하면서 해당 열에 대한 값을 더한다
            printf("ASC_row[%d][%d] : %d\n", height, i, ASC_row[height][i]);
            ASC_height[height][j] += ch;
            printf("ASC_height[%d][%d] : %d\n\n", height, j, ASC_height[height][j]);
        }
    }
    fclose(output);

    // 인코딩된 값을 파일에 쓰기
    FILE* encodedOutput = fopen(outputFile, "ab");
    if (encodedOutput == NULL) {
        printf("Failed to open encoded output file.\n");
        fclose(output);
        return;
    }
		printf("덧붙여 쓰기 시작 위치 : %ld\n", ftell(encodedOutput));
    for (int k = 0; k < height + 1; k++) {
        fwrite(ASC_column[k], sizeof(int), 10, encodedOutput);
        fwrite(ASC_row[k], sizeof(int), 10, encodedOutput);
    }
    for (int k = 0; k < 10; k++) {
        fwrite(ASC_height[k], sizeof(int), 10, encodedOutput);
    }
		
    for (int k = 0; k < height + 1; k++) {
        fwrite(ASC_column[k], sizeof(int), 10, encodedOutput);
        fwrite(ASC_row[k], sizeof(int), 10, encodedOutput);
    }
    for (int k = 0; k < 10; k++) {
        fwrite(ASC_height[k], sizeof(int), 10, encodedOutput);
    }
    fclose(encodedOutput);
    // 동적 할당된 메모리 해제
    for (int i = 0; i < height + 1; i++) {
        free(ASC_column[i]);
        free(ASC_row[i]);
    }
    free(ASC_column);
    free(ASC_row);
}

void removeSubstring(char* s, const char* toRemove)
{
    char* match = strstr(s, toRemove);
    if (match != NULL)
    {
        memmove(match, match + strlen(toRemove), strlen(match + strlen(toRemove)) + 1);
    }
}

void encodeData(const char* inputFile, const char* outputFile)
{
    FILE* input = fopen(inputFile, "r");
    if (input == NULL)
    {
        printf("Failed to open the input file.\n");
        return;
    }

    FILE* output = fopen(outputFile, "wb");
    if (output == NULL)
    {
        printf("Failed to open the output file.\n");
        fclose(input);
        return;
    }

    char line[256];
    int section = 0;  // Section identifier (0: User Status, 1: Items, 2: Friends List, 3: Description)

    while (fgets(line, sizeof(line), input) != NULL)
    {
        if (line[0] == '*')  // Check for section title
        {
            if (strcmp(line, "*USER STATUS*\n") == 0)
            {
                section = 0;
            }
            else if (strcmp(line, "*ITEMS*\n") == 0)
            {
                section = 1;
                fwrite("\n", sizeof(char), 1, output);
            }
            else if (strcmp(line, "*FRIENDS LIST*\n") == 0)
            {
                section = 2;
            }
            else if (strcmp(line, "*DESCRIPTION*\n") == 0)
            {
                section = 3;
                fwrite("/", sizeof(char), 1, output);
            }

            continue;
        }

        // Encode data based on section
        switch (section)
        {
        case 0:  // User Status
        {
            if (strncmp(line, "ID: ", 4) == 0)
                fwrite(line + 4, sizeof(char), strlen(line) - 4, output);
            else if (strncmp(line, "NAME: ", 6) == 0)
                fwrite(line + 6, sizeof(char), strlen(line) - 6, output);
            else if (strncmp(line, "GENDER: ", 8) == 0)
                fwrite(line + 8, sizeof(char), strlen(line) - 8, output);
            else if (strncmp(line, "AGE: ", 5) == 0)
                fwrite(line + 5, sizeof(char), strlen(line) - 5, output);
            else if (strncmp(line, "HP: ", 4) == 0)
                fwrite(line + 4, sizeof(char), strlen(line) - 4, output);
            else if (strncmp(line, "MP: ", 4) == 0)
                fwrite(line + 4, sizeof(char), strlen(line) - 4, output);
            else if (strncmp(line, "COIN: ", 6) == 0)
                fwrite(line + 6, sizeof(char), strlen(line) - 6, output);

            break;
        }
        case 1:  // Items
        {
            if (strncmp(line, "BOMB:", 5) == 0)
            {
                removeSubstring(line, "BOMB:");
                fwrite("A", sizeof(char), 1, output);
            }
            else if (strncmp(line, "POTION:", 7) == 0)
            {
                removeSubstring(line, "POTION:");
                fwrite("P", sizeof(char), 1, output);
            }
            else if (strncmp(line, "CURE:", 5) == 0)
            {
                removeSubstring(line, "CURE:");
                fwrite("C", sizeof(char), 1, output);
            }
            else if (strncmp(line, "BOOK:", 5) == 0)
            {
                removeSubstring(line, "BOOK:");
                fwrite("B", sizeof(char), 1, output);
            }
            else if (strncmp(line, "SHIELD:", 7) == 0)
            {
                removeSubstring(line, "SHIELD:");
                fwrite("S", sizeof(char), 1, output);
            }
            else if (strncmp(line, "CANNON:", 7) == 0)
            {
                removeSubstring(line, "CANNON:");
                fwrite("I", sizeof(char), 1, output);
            }
            fwrite(line, sizeof(char), strlen(line), output);
            break;
        }
        case 2:  // Friends List
        {
            if (strncmp(line, "FRIEND", 6) == 0)
            {
                removeSubstring(line, "FRIEND");
                char* position = strchr(line, ' ');
                if (position != NULL)
                {
                    removeSubstring(position, "ID: ");
                    removeSubstring(position, "NAME: ");
                    removeSubstring(position, "GENDER: ");
                    removeSubstring(position, "AGE: ");

                    // Replace the first space with "&"
                    *position = '&';
                }
            }
            fwrite(line, sizeof(char), strlen(line), output);
            break;
        }
        case 3:  // Description
        {
            fwrite(line, sizeof(char), strlen(line), output);
            break;
        }
        }
    }
    for (int i = 0; i < 5; i++) {
        char ch = '\n';
        fwrite(&ch, sizeof(char), 1, output);
    }
    fclose(input);
    fclose(output);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./encoder.out <input_file> <output_file>\n");
        return 1;
    }

    const char* inputFile = argv[1];
    const char* outputFile = argv[2];

    encodeData(inputFile, outputFile);
    printf("Encoded data saved to '%s'.\n", outputFile);
    encodeASC(outputFile);
    printf("Encoded ASC saved to '%s',\n", outputFile);
    return 0;
}
