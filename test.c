/*
re
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYER_ITEMS 6
#define MAX_FRIENDS 5
#define MAX_DESCRIPTION_LENGTH 100

// 플레이어 구조체 정의
typedef struct {
    int id;
    char name[20];
    char gender;
    int age;
    int hp;
    int mp;
    int coin;
    int items[MAX_PLAYER_ITEMS];
    struct {
        int id;
        char name[20];
        char gender;
        int age;
    } friends[MAX_FRIENDS];
    char description[MAX_DESCRIPTION_LENGTH + 1];
} Player;

// 플레이어 초기화 함수
void initializePlayer(Player* player) {
    player->id = 1;
    strcpy(player->name, "John");
    player->gender = 'M';
    player->age = 25;
    player->hp = 100;
    player->mp = 50;
    player->coin = 1000;

    for (int i = 0; i < MAX_PLAYER_ITEMS; i++) {
        player->items[i] = i + 1;
    }

    for (int i = 0; i < MAX_FRIENDS; i++) {
        player->friends[i].id = i + 1;
        strcpy(player->friends[i].name, "Friend");
        player->friends[i].gender = 'M';
        player->friends[i].age = 20 + i;
    }

    strcpy(player->description, "Hello, I am John!");
}

// 압축 알고리즘 함수 (Run-Length Encoding)
void compress(const char* data, char* compressed) {
    int length = strlen(data);
    int count = 1;
    int index = 0;
    char current = data[0];

    for (int i = 1; i <= length; i++) {
        if (data[i] == current) {
            count++;
        }
        else {
            compressed[index++] = current;
            compressed[index++] = count + '0';
            count = 1;
            current = data[i];
        }
    }

    compressed[index] = '\0';
}

// 압축 해제 함수
void decompress(const char* compressed, char* decompressed) {
    int length = strlen(compressed);
    int index = 0;

    for (int i = 0; i < length; i += 2) {
        char current = compressed[i];
        int count = compressed[i + 1] - '0';

        for (int j = 0; j < count; j++) {
            decompressed[index++] = current;
        }
    }

    decompressed[index] = '\0';
}

// 플레이어 정보 인코딩 함수
void encodePlayerInfo(FILE* file, const Player* player) {
    // ID
    fwrite(&player->id, sizeof(int), 1, file);

    // NAME
    fwrite(player->name, sizeof(char), sizeof(player->name), file);

    // GENDER
    fwrite(&player->gender, sizeof(char), 1, file);

    // AGE
    fwrite(&player->age, sizeof(int), 1, file);

    // HP
    fwrite(&player->hp, sizeof(int), 1, file);

    // MP
    fwrite(&player->mp, sizeof(int), 1, file);

    // COIN
    fwrite(&player->coin, sizeof(int), 1, file);

    // ITEMS (압축)
    char compressedItems[MAX_PLAYER_ITEMS * 2 + 1];
    char itemsData[MAX_PLAYER_ITEMS];
    for (int i = 0; i < MAX_PLAYER_ITEMS; i++) {
        itemsData[i] = player->items[i] + '0';
    }
    compress(itemsData, compressedItems);
    fwrite(compressedItems, sizeof(char), sizeof(compressedItems), file);

    // FRIENDS (압축)
    char compressedFriends[MAX_FRIENDS * (sizeof(int) + sizeof(char[20]) + sizeof(char) + sizeof(int)) * 2 + 1];
    char friendsData[MAX_FRIENDS * (sizeof(int) + sizeof(char[20]) + sizeof(char) + sizeof(int))];
    int friendsDataIndex = 0;
    for (int i = 0; i < MAX_FRIENDS; i++) {
        memcpy(&friendsData[friendsDataIndex], &player->friends[i], sizeof(int) + sizeof(char[20]) + sizeof(char) + sizeof(int));
        friendsDataIndex += sizeof(int) + sizeof(char[20]) + sizeof(char) + sizeof(int);
    }
    compress(friendsData, compressedFriends);
    fwrite(compressedFriends, sizeof(char), sizeof(compressedFriends), file);

    // DESCRIPTION (압축)
    char compressedDescription[(2 * MAX_DESCRIPTION_LENGTH + 1)];
    char descriptionData[(2 * MAX_DESCRIPTION_LENGTH + 1)];
    strcpy(descriptionData, player->description);
    compress(descriptionData, compressedDescription);
    fwrite(compressedDescription, sizeof(char), sizeof(compressedDescription), file);
}

// 플레이어 정보 디코딩 함수
void decodePlayerInfo(FILE* file, Player* player) {
    // ID
    fread(&player->id, sizeof(int), 1, file);

    // NAME
    fread(player->name, sizeof(char), sizeof(player->name), file);

    // GENDER
    fread(&player->gender, sizeof(char), 1, file);

    // AGE
    fread(&player->age, sizeof(int), 1, file);

    // HP
    fread(&player->hp, sizeof(int), 1, file);

    // MP
    fread(&player->mp, sizeof(int), 1, file);

    // COIN
    fread(&player->coin, sizeof(int), 1, file);

    // ITEMS (압축 해제)
    char compressedItems[MAX_PLAYER_ITEMS * 2 + 1];
    fread(compressedItems, sizeof(char), sizeof(compressedItems), file);
    decompress(compressedItems, (char*)player->items);

    // FRIENDS (압축 해제)
    char compressedFriends[MAX_FRIENDS * (sizeof(int) + sizeof(char[20]) + sizeof(char) + sizeof(int)) * 2 + 1];
    fread(compressedFriends, sizeof(char), sizeof(compressedFriends), file);

    char friendsData[MAX_FRIENDS * (sizeof(int) + sizeof(char[20]) + sizeof(char) + sizeof(int))];
    decompress(compressedFriends, friendsData);

    int friendsDataIndex = 0;
    for (int i = 0; i < MAX_FRIENDS; i++) {
        memcpy(&(player->friends[i].id), &friendsData[friendsDataIndex], sizeof(int));
        friendsDataIndex += sizeof(int);
        memcpy(&(player->friends[i].name), &friendsData[friendsDataIndex], sizeof(char[20]));
        friendsDataIndex += sizeof(char[20]);
        memcpy(&(player->friends[i].gender), &friendsData[friendsDataIndex], sizeof(char));
        friendsDataIndex += sizeof(char);
        memcpy(&(player->friends[i].age), &friendsData[friendsDataIndex], sizeof(int));
        friendsDataIndex += sizeof(int);
    }

    // DESCRIPTION (압축 해제)
    char compressedDescription[(2 * MAX_DESCRIPTION_LENGTH + 1)];
    fread(compressedDescription, sizeof(char), sizeof(compressedDescription), file);
    char decompressedDescription[(2 * MAX_DESCRIPTION_LENGTH + 1)];
    decompress(compressedDescription, decompressedDescription);
    strncpy(player->description, decompressedDescription, MAX_DESCRIPTION_LENGTH);
}

// 인코딩 메인 함수
int encodeMain(const char* filename, const char* outputFilename) {
    FILE* file = fopen(filename, "wb");
    if (!file) {
        printf("Failed to open file: %s\n", filename);
        return 1;
    }

    // 플레이어 초기화
    Player player;
    initializePlayer(&player);

    // 플레이어 정보 인코딩
    encodePlayerInfo(file, &player);

    fclose(file);
    printf("Encoding completed. Encoded data is written to %s\n", outputFilename);
    return 0;
}

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

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: program_name <encode/decode> <filename>\n");
        return 1;
    }

    const char* mode = argv[1];
    const char* filename = argv[2];

    if (strcmp(mode, "encode") == 0) {
        return encodeMain(filename, "encoded_data");
    }
    else if (strcmp(mode, "decode") == 0) {
        return decodeMain(filename, "result.txt");
    }
    else {
        printf("Invalid mode. Use 'encode' or 'decode'.\n");
        return 1;
    }
}*/
