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
	int count[9]; //�ܾ� �ߺ� ����. �ε��� 0 �� ���� 1�� ����Ŵ
	int position[9][100]; //�ִ� 0~ 8���� �������� 100���� ������ �ܾ� ��ġ ������ �� ����
}word_info;

typedef struct node {
	char word[100];
	word_info info;
	node_pointer link; //��ũ
}node;

int doc_index = 0; //���� ���� 1. ���߿� ������ ����

int db_word_number[9] = { 0 }; //�����ͺ��̽��� ���� �����ϰ� �ִ� �� �ܾ� ���� ����

int comparison[9] = {0};

char database[9][1000][100]; //������ ������ ������ 3���� �迭. database[document][number][size]

node Hash_Table[TABLE_SIZE]; //�ؽ� ���̺�

int transform(char *word); //folding�� �����ϴ� �Լ�. folding�� ���� �����Ѵ�.

void hash_insert(char *word, int position); //�ؽ� ���̺� �����ϴ� �Լ�

int hash(char *word); //�ؽ� �Լ�
 
void build_hash_table(char *fileName); //�ؽ� ���̺��� �����ϴ� �Լ�

int search_table(char *word); //�ܾ� �˻� �Լ�. ��Ƚ���� �����Ѵ�.

void show(int document, int number, int position, char *word);// �ܾ ����Ѵ�.


/*
���� ��� ����
*/
