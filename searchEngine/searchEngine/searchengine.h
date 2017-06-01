#pragma once
#include <malloc.h>
#define TABLE_SIZE 13
typedef struct node* node_pointer;

typedef struct node {
	char* word;
	int word_info[100][100]; //word_info[count][position]
	node_pointer link; //링크
};

char database[9][1000][100]; //워드의 정보를 저장할 3차원 배열. database[document][number][size]

int Hash_Table[9][TABLE_SIZE];

int transform(char* word);

int hash_insert(char* word);

int hash(char* word);

void build_hash_table(char *fileName);
