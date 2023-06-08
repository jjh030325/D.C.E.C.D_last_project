#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getFile(const char* inputFile, char** data, int* dataSize) {
    FILE* file = fopen(inputFile, "rb");
    if (file == NULL) {
        printf("Failed to open the input file.\n");
        return;
    }

    // Determine the file size
    fseek(file, 0, SEEK_END);
    *dataSize = ftell(file);
    rewind(file);

    // Allocate memory for the data
    *data = (char*)malloc((*dataSize + 1) * sizeof(char));

    // Read the data from the file
    fread(*data, sizeof(char), *dataSize, file);

    // Null-terminate the data
    (*data)[*dataSize] = '\0';

    fclose(file);
}

void setTable(const char* data, int dataSize, char*** table, int* tableSize) {
    int i;
    int count = 0;
    for (i = 0; i < dataSize; i++) {
        if (data[i] == '\n') {
            count++;
        }
    }

    *tableSize = count;
    *table = (char**)malloc(count * sizeof(char*));

    char* line = strtok((char*)data, "\n");
    i = 0;
    while (line != NULL) {
        (*table)[i] = (char*)malloc((strlen(line) + 1) * sizeof(char));
        strcpy((*table)[i], line);
        line = strtok(NULL, "\n");
        i++;
    }
}

void getTable(const char* line, char** table, int tableSize, char*** result, int* resultSize) {
    int i;
    *resultSize = 0;
    for (i = 0; i < tableSize; i++) {
        if (strstr(line, table[i]) != NULL) {
            (*resultSize)++;
        }
    }

    *result = (char**)malloc((*resultSize) * sizeof(char*));
    int index = 0;
    for (i = 0; i < tableSize; i++) {
        if (strstr(line, table[i]) != NULL) {
            (*result)[index] = (char*)malloc((strlen(table[i]) + 1) * sizeof(char));
            strcpy((*result)[index], table[i]);
            index++;
        }
    }
}

void checkData(const char* data, int dataSize, char** table, int tableSize, char*** decodedData, int* decodedDataSize) {
    char* mutableData = (char*)malloc((dataSize + 1) * sizeof(char));
    strcpy(mutableData, data);

    int i;
    for (i = 0; i < dataSize; i++) {
        char* line = strtok(mutableData, "\n");
        while (line != NULL) {
            if (strlen(line) > 0) {
                char** result;
                int resultSize;
                getTable(line, table, tableSize, &result, &resultSize);

                if (resultSize == 0) {
                    (*decodedData)[*decodedDataSize] = (char*)malloc((strlen(line) + 1) * sizeof(char));
                    strcpy((*decodedData)[*decodedDataSize], line);
                    (*decodedDataSize)++;
                } else {
                    int j;
                    for (j = 0; j < resultSize; j++) {
                        char* temp = (char*)malloc((strlen(line) + 1) * sizeof(char));
                        strcpy(temp, line);
                        char* found = strstr(temp, result[j]);
                        while (found != NULL) {
                            int pos = found - temp;
                            memcpy(&temp[pos], "          ", strlen(result[j]));
                            found = strstr(temp, result[j]);
                        }
                        (*decodedData)[*decodedDataSize] = (char*)malloc((strlen(temp) + 1) * sizeof(char));
                        strcpy((*decodedData)[*decodedDataSize], temp);
                        (*decodedDataSize)++;
                        free(temp);
                    }
                }

                for (int j = 0; j < resultSize; j++) {
                    free(result[j]);
                }
                free(result);
            }
            line = strtok(NULL, "\n");
        }
    }

    free(mutableData);
}


void saveDecodedData(const char* outputFile, char** decodedData, int decodedDataSize) {
    FILE* file = fopen(outputFile, "w");
    if (file == NULL) {
        printf("Failed to open the output file.\n");
        return;
    }

    int i;
    for (i = 0; i < decodedDataSize; i++) {
        fprintf(file, "%s\n", decodedData[i]);
    }

    fclose(file);
}

void freeTable(char** table, int tableSize) {
    int i;
    for (i = 0; i < tableSize; i++) {
        free(table[i]);
    }
    free(table);
}

void freeDecodedData(char** decodedData, int decodedDataSize) {
    int i;
    for (i = 0; i < decodedDataSize; i++) {
        free(decodedData[i]);
    }
    free(decodedData);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    const char* inputFile = argv[1];
    const char* outputFile = argv[2];

    char* data = NULL;
    int dataSize = 0;

    getFile(inputFile, &data, &dataSize);

    char** table = NULL;
    int tableSize = 0;

    setTable(data, dataSize, &table, &tableSize);

    char** decodedData = NULL;
    int decodedDataSize = 0;

    checkData(data, dataSize, table, tableSize, &decodedData, &decodedDataSize);

    saveDecodedData(outputFile, decodedData, decodedDataSize);

    freeTable(table, tableSize);
    freeDecodedData(decodedData, decodedDataSize);
    free(data);

    printf("Decoded data saved to '%s'.\n", outputFile);

    return 0;
}

