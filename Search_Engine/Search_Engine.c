#include "Search_Engine.h"

int main() {
	char c;
	char word[100];
	char fileName[9][100];
	int word_num_sum = 0;
	int comparison_sum = 0;
	strcpy(fileName[0], "document1.txt");
	strcpy(fileName[1], "document2.txt");
	strcpy(fileName[2], "document3.txt");
	strcpy(fileName[3], "document4.txt");
	strcpy(fileName[4], "document5.txt");
	strcpy(fileName[5], "document6.txt");
	strcpy(fileName[6], "document7.txt");
	strcpy(fileName[7], "document8.txt");
	strcpy(fileName[8], "document9.txt");

	for (int i = 0; i < 9; i++) {
		build_hash_table(fileName[i]);
		doc_index++;
	}
	for (int i = 0; i < 9; i++) {
		word_num_sum += db_word_number[i];
		comparison_sum += comparison[i];
	}
	printf("Total number of	documents: %d\n", doc_index);
	printf("Total number of indexed words: %d\n", word_num_sum);
	printf("Total number of comparison: %d\n", comparison_sum);
	printf("\n");
	printf("*************�˻�����**************\n");
	printf("S: �ܾ� �˻�\n");
	printf("Q: ���α׷� ����\n");
	printf("**********************************\n");
	while (true) {
		printf("�Է�> ");
		c = getch();
		putch(c);
		c = toupper(c);
		switch (c) {
		case 'S':
			printf("\n");
			printf("ã������ �ܾ �Է��ϼ���> ");
			scanf("%s", word);
			int comparison = search_table(word);
			printf("Total number of comparison: %d\n\n", comparison);
			break;
		case 'Q':
			printf("\n");
			exit(1);
			break;
		}
	}
}

//�ؽ� ���̺� ����
void build_hash_table(char *fileName) {
	FILE *fp;
	fp = fopen(fileName, "r"); 
	while (!feof(fp)) { //���� ������ �о���δ�
		fscanf(fp, "%s", database[doc_index][db_word_number[doc_index]]);//���Ͽ��� �����ϳ��� �о���δ�.
		hash_insert(database[doc_index][db_word_number[doc_index]], db_word_number[doc_index]);
		db_word_number[doc_index]++;
	}
}

void hash_insert(char *word, int position) {
	node_pointer s = Hash_Table;
	char modified_word[100];
	strcpy(modified_word, word);
	int length = strlen(word);
	for (int i = 0; i < length; i++) {//��� �ҹ��ڷ� �ٲ�
		if('A' <= modified_word[i] && modified_word[i] <= 'Z')
			modified_word[i] = tolower(modified_word[i]);
	}
	for (int i = 0; i < length; i++) {//���ĺ��� ����
		if ('a' <= modified_word[i] && modified_word[i] <= 'z') {
			modified_word[i] = modified_word[i];
		}
		else {
			modified_word[i] = NULL;
			break;
		}
	}
	int key = hash(modified_word);
	s = (s + key);
	node_pointer new_node = (node_pointer)malloc(sizeof(node)); 
	strcpy(new_node->word, modified_word);
	new_node->link = NULL;
	for (int i = 0; i < 9; i++) {
		new_node->info.count[i] = 0;
	}
	int compare;
	if (!s->link->word) { //ù��° �ڸ��� NULL���̸� �ƹ��͵� ����Ǿ����� �ʴٴ� ��Ⱑ �ǹǷ� �� �ڸ��� ���� ����
		s->link = new_node;
		new_node->info.position[doc_index][++new_node->info.count[doc_index]] = position; //ī��Ʈ���� �ϳ� ������Ű�� �׿� �ش��ϴ� �ε����� �����ǰ��� �ִ´�.
	}
	else { //���� NULL���� �ƴϸ�
		while (s->link){ //���� ��尡 NULL�� �ƴϸ�
			if (strcmp(modified_word, s->link->word) == 0) { //�����Ϸ��� �ܾ ���� �ܾ ���� ���
				comparison[doc_index]++; //�� Ƚ���� �ϳ� �ø���.
				s = s->link;
				s->info.position[doc_index][++s->info.count[doc_index]] = position;
				free(new_node);
				return;
			}
			else if (strcmp(modified_word, s->link->word) < 0) { //���� �Ϸ��� �ܾ ���� �ܾ�� ������ �ݺ��� ����
				comparison[doc_index]++; //�� Ƚ���� �ϳ� �ø���.
				new_node->link = s->link; 
				s->link = new_node;
				new_node->info.position[doc_index][++new_node->info.count[doc_index]] = position; //ī��Ʈ���� �ϳ� ������Ű�� �׿� �ش��ϴ� �ε����� �����ǰ��� �ִ´�.
				return;
			}
			else 
				s = s->link; //�̵�
		}
		//��尡 ���� ��� �׳� ���δ�.
		s->link = new_node;
		new_node->info.position[doc_index][++new_node->info.count[doc_index]] = position;
	}
}

int hash(char* word) {
	return transform(word) % TABLE_SIZE;
}

int transform(char* word) {
	int number = 0;
	while (*word) {
		number += *word++;
	}
	return number;
}

int search_table(char *word) {
	node_pointer s = Hash_Table;
	int word_number;
	int word_position;
	char modified_word[100];
	strcpy(modified_word, word);
	int length = strlen(word);
	for (int i = 0; i < length; i++) {//��� �ҹ��ڷ� �ٲ�
		if ('A' <= modified_word[i] && modified_word[i] <= 'Z')
			modified_word[i] = tolower(modified_word[i]);
	}
	for (int i = 0; i < length; i++) {//���ĺ��� ����
		if ('a' <= modified_word[i] && modified_word[i] <= 'z') {
			modified_word[i] = modified_word[i];
		}
		else {
			modified_word[i] = NULL;
			break;
		}
	}
	int cmp = 0; //�񱳿��� ī���� �Լ�
	int key = hash(modified_word); //�ܾ Ű�� ��ȯ
	s = s + key; //s�� �ش� �ε����� ����Ű�� ����
	while (s->link) { //���� ��尡 �����ϸ�
		if (strcmp(modified_word, s->link->word) == 0) {
			cmp++; //�� (���� ��ġ�ϴ� ����)
			for (int document = 0; document < 9; document++) {
				word_number = s->link->info.count[document];
				if (word_number == 0)
					continue;
				printf("\n<document%d.txt> %s: %d\n", document + 1, word, word_number);
				for (int n = 1; n <= word_number; n++) {
					word_position = s->link->info.position[document][n];
					show(document, word_number, word_position, word);
				}
				printf("\n");
			}
			return cmp;
		}
		cmp++; //(�񱳰��� �ٸ� ����)
		s = s->link;
	}
	return false;
}

void show(int document, int number, int position, char *word) {
	int size = number;
	if (0 <= position && position <= 4) {} //������ ���ۺκ��̸� ...�� �������� �ʵ��� ��
	else {
		printf("... ");
	}
	for (int i = 4; i >= 0; i--) { //���� 4�ܾ� ���
		if ((position - i) < 0) {
			continue;
		}
		else {
			printf("%s ", database[document][position - i]);
		}
	}
	for (int i = 1; i <= 4; i++) {//���� 4�ܾ� ���
		if ((position + i) >= 1000) {
			break;
		}
		else {
			printf("%s ", database[document][position + i]);
		}
	}
	if (position >= db_word_number[doc_index] - 4 && position <= db_word_number[doc_index]) { printf("\n"); } // ������ ���� ��� ...�� ������� �ʵ��� ��
	else {
		printf("... \n");
	}
}