#pragma once
#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define true 1
#define false 0
#define TABLE_SIZE 13

typedef struct node *node_pointer;

typedef struct word_info {
	int count[9]; //단어 중복 개수. 인덱스 0 은 문서 1을 가리킴
	int position[9][100]; //최대 0~ 8개의 문서에서 100개의 동일한 단어 위치 저장할 수 있음
}word_info;

typedef struct node {
	char word[100];
	word_info info;
	node_pointer link; //링크
}node;

int doc_index = 0; //현재 문서 1. 나중에 변경할 예정

int db_word_number[9] = { 0 }; //데이터베이스가 현재 저장하고 있는 총 단어 수를 저장

int comparison[9] = {0};

char database[9][1000][100]; //워드의 정보를 저장할 3차원 배열. database[document][number][size]

node Hash_Table[TABLE_SIZE]; //해시 테이블

int transform(char *word); //folding을 진행하는 함수. folding한 값을 리턴한다.

void hash_insert(char *word, int position); //해시 테이블에 삽입하는 함수

int hash(char *word); //해시 함수
 
void build_hash_table(char *fileName); //해시 테이블을 생성하는 함수

int search_table(char *word); //단어 검색 함수. 비교횟수를 리턴한다.

void show(int document, int number, int position, char *word);// 단어를 출력한다.


/*
더미 노드 구현
*/
