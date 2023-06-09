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

<<<<<<< HEAD
// 디코딩 메인 함수
int decodeMain(const char* filename, const char* outputFilename) {
	FILE* file = fopen(filename, "rb");
	if (!file) {
		printf("Failed to open file: %s\n", filename);
		return 1;
	}

	// 플레이어 정보 디코딩
	Player decodedPlayer;
	decodePlayerInfo(file, &decodedPlayer);

	// 디코딩된 플레이어 정보 출력
	FILE* outputFile = fopen(outputFilename, "w");
	if (!outputFile) {
		printf("Failed to create output file: %s\n", outputFilename);
		return 1;
	}

	fprintf(outputFile, "ID: %d\n", decodedPlayer.id);
	fprintf(outputFile, "Name: %s\n", decodedPlayer.name);
	fprintf(outputFile, "Gender: %c\n", decodedPlayer.gender);
	fprintf(outputFile, "Age: %d\n", decodedPlayer.age);
	fprintf(outputFile, "HP: %d\n", decodedPlayer.hp);
	fprintf(outputFile, "MP: %d\n", decodedPlayer.mp);
	fprintf(outputFile, "Coin: %d\n", decodedPlayer.coin);
	fprintf(outputFile, "Items: ");
	for (int i = 0; i < MAX_PLAYER_ITEMS; i++) {
		fprintf(outputFile, "%d ", decodedPlayer.items[i]);
	}
	fprintf(outputFile, "\n");
	fprintf(outputFile, "Friends: \n");
	for (int i = 0; i < MAX_FRIENDS; i++) {
		fprintf(outputFile, "Friend %d:\n", i + 1);
		fprintf(outputFile, "  ID: %d\n", decodedPlayer.friends[i].id);
		fprintf(outputFile, "  Name: %s\n", decodedPlayer.friends[i].name);
		fprintf(outputFile, "  Gender: %c\n", decodedPlayer.friends[i].gender);
		fprintf(outputFile, "  Age: %d\n", decodedPlayer.friends[i].age);
	}
	fprintf(outputFile, "Description: %s\n", decodedPlayer.description);

	fclose(file);
	fclose(outputFile);
	printf("Decoding completed. Decoded data is written to %s\n", outputFilename);
	return 0;
}

int check_params(int argc, char* argv[]) {
	if (argc == 2) return 1;
	return 0;
}

int main(int argc, char* argv[]) {

	const char* filename = argv[0];

	if (check_params(argc, argv) == 0) {
		printf("Usage: %s param1\n", filename);
		exit(1);
	}

	const char* decoded_data = argv[1];

	decodeMain(filename, decoded_data);

	return 0;
}
=======
>>>>>>> 575e448baf14ad2773c62f42ed072a131d0774fe
