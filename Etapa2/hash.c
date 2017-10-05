/*
* André D. Carneiro e Victória Simonetti
*/
#include "hash.h"



void hashInit(){

    int i;

    for(i = 0; i < HASH_SIZE; i++){
        _hashTable[i] = 0;
    }
}

int hashAddress(char* text) {

    int address = 1;
	int i=0;

	for (i=0; i < strlen(text);i++){
		address = (address*text[i])%HASH_SIZE + 1;
	}
	return address - 1;
}

HASH_NODE* hashInsert(int type, char* text){

    HASH_NODE *newNode;
    int address;
    address = hashAddress(text);

    //Verify exist node
    HASH_NODE *exist_node;
    exist_node = hashFind(text);
    if(exist_node != NULL){
        return exist_node;
    }

    //Initializes new node
    newNode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
    newNode->type = type;
    newNode->text = (char*) calloc(strlen(text)+1, sizeof(char));
    strncpy(newNode->text, text, strlen(text));

    //Inserts new node
    newNode->next = _hashTable[address];
    _hashTable[address] = newNode;

    return newNode;
}

HASH_NODE* hashFind(char* text){

    HASH_NODE *node = NULL;
	int i;
	for(i=0; i<HASH_SIZE; i++){
		for(node=_hashTable[i]; node; node=node->next){
			if(strcmp(text, node->text) == 0){
				return node;
			}
		}
	}
    node = NULL;
	return node;
}

void hashPrint(){

    int i;
    HASH_NODE *iter;

    for(i = 0; i < HASH_SIZE; i++){
        for(iter = _hashTable[i]; iter; iter = iter->next){
            fprintf(stderr, "hashTable[%d] has type = %d and text = %s\n", i, iter->type, iter->text);
        }
    }
}
