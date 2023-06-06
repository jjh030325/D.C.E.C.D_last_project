#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void decodeData(const char* inputFile, const char* outputFile)
{
    FILE* input = fopen(inputFile, "rb");
    if (input == NULL)
    {
        printf("Failed to open the input file.\n");
        return;
    }

    FILE* output = fopen(outputFile, "w");
    if (output == NULL)
    {
        printf("Failed to open the output file.\n");
        fclose(input);
        return;
    }

    size_t dataSize;
    while (fread(&dataSize, sizeof(size_t), 1, input) == 1)
    {
        char* line = (char*)malloc(dataSize);
        if (line == NULL)
        {
            printf("Failed to allocate memory.\n");
            fclose(input);
            fclose(output);
            return;
        }

        fread(line, sizeof(char), dataSize, input);

        fwrite(line, sizeof(char), dataSize, output);

        free(line);
    }

    fclose(input);
    fclose(output);
}

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        printf("Usage: ./decoder.out <input_file> <output_file>\n");
        return 1;
    }

    const char* inputFile = argv[1];
    const char* outputFile = argv[2];

    decodeData(inputFile, outputFile);

    printf("Decoded data saved to '%s'.\n", outputFile);

    return 0;
}

