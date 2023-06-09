#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD

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
                fwrite(line, sizeof(char), strlen(line), output);
                break;
            }
            case 2:  // Friends List
            {
                if (strncmp(line, "FRIEND", 6) == 0)
                {
                    char* position = strchr(line, ' ');
                    if (position != NULL)
                    {
                        removeSubstring(position, "ID: ");
                        removeSubstring(position, "NAME: ");
                        removeSubstring(position, "GENDER: ");
                        removeSubstring(position, "AGE: ");
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

    return 0;
}

=======
void encodeASC(const char* outputFile) {
    FILE* output = fopen(outputFile, "rb");
    if (output == NULL)
    {
        printf("Failed to open output file.\n");
        return;
    }
    int size = 0;
    char ch;
    while (fread(&ch, 1, 1, output) == 1) size++; // 파일 전체 사이즈
    int height = size / 100;

    int **ASC_column = (int**)malloc((height + 1) * sizeof(int*));  // 전체 세로 길이 할당
    for (int i = 0; i < height + 1; i++) {
        ASC_column[i] = (int*)calloc(10, sizeof(int)); // 각 행마다 가로 길이 할당
    }

    int **ASC_row = (int**)malloc((height + 1) * sizeof(int*));
    for (int i = 0; i < height + 1; i++) {
        ASC_row[i] = (int*)calloc(10, sizeof(int));
    }

    int **ASC_height = (int**)malloc((height + 1) * sizeof(int*));
    for (int i = 0; i < height + 1; i++) {
        ASC_height[i] = (int*)calloc(10, sizeof(int));
    }

    for (int k = 0; k < height; k++) { // 최대 높이 만큼 반복
        for (int i = 0; i < 10; i++) { // 세로
            for (int j = 0; j < 10; j++) { // 가로
                fread(&ch, 1, 1, output); // 한바이트씩 읽어온다
                ASC_column[k][j] += ch; // 높이는 고정, 가로 j가 증가하면서
                ASC_row[k][i] += ch; // 높이 고정, 세로 i가 증가하면서 
                ASC_height[i][j] += ch;  // 
            }
        }
    }
    size -= 100 * height; // 남은 바이트
    for (int i = 0; i < size / 10; i++) {
        for (int j = 0; j < 10; j++) {
            fread(&ch, 1, 1, output); // 한바이트씩 읽어온다
            ASC_column[height][j] += ch; // 높이는 고정, 가로 j가 증가하면서
            ASC_row[height][i] += ch; // 높이 고정, 세로 i가 증가하면서 
            ASC_height[i][j] += ch;  // 
        }
        if ( i + 1 == size / 10 ) {
            size %= 10;
            for(int j = 0; j < size; j++){
                fread(&ch, 1, 1, output); // 한바이트씩 읽어온다
                ASC_column[height][j] += ch; // 높이는 고정, 가로 j가 증가하면서
                ASC_row[height][i] += ch; // 높이 고정, 세로 i가 증가하면서 
                ASC_height[i][j] += ch;  // 
            }
        }
    }
		fclose(output);
    output = NULL;
    FILE* input = fopen(outputFile, "ab");
    fwrite(ASC_column, sizeof(ASC_column), 1, input);
    fwrite(ASC_row, sizeof(ASC_row), 1, input);
    fwrite(ASC_height, sizeof(ASC_height), 1, input);
    fclose(input);
    input = NULL;

    for (int i = 0; i < height + 1; i++) free(ASC_column[i]);
    free(ASC_column);
    for (int i = 0; i < height + 1; i++) free(ASC_row[i]);
    free(ASC_row);
    for (int i = 0; i < height + 1; i++) free(ASC_height[i]);
    free(ASC_height);
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

>>>>>>> seungmin
