#include <stdlib.h>
#include <stdio.h>

#define HASH_SIZE 997

typedef struct HASH_NODE{

    int type;
    char *text;
    HASH_NODE *next;
};

void hashInit();
int hashAddress(char* text);
HASH_NODE* hashInsert(int type, char* text);
HASH_NODE hashFind(char* text);
void hashPrint();
