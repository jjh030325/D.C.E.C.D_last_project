#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    return 0;
}

