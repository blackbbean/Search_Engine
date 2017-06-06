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
	printf("*************검색엔진**************\n");
	printf("S: 단어 검색\n");
	printf("Q: 프로그램 종료\n");
	printf("**********************************\n");
	while (true) {
		printf("입력> ");
		c = getch();
		putch(c);
		c = toupper(c);
		switch (c) {
		case 'S':
			printf("\n");
			printf("찾으려는 단어를 입력하세요> ");
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

//해쉬 테이블 생성
void build_hash_table(char *fileName) {
	FILE *fp;
	fp = fopen(fileName, "r"); 
	while (!feof(fp)) { //파일 끝까지 읽어들인다
		fscanf(fp, "%s", database[doc_index][db_word_number[doc_index]]);//파일에서 문자하나를 읽어들인다.
		hash_insert(database[doc_index][db_word_number[doc_index]], db_word_number[doc_index]);
		db_word_number[doc_index]++;
	}
}

void hash_insert(char *word, int position) {
	node_pointer s = Hash_Table;
	char modified_word[100];
	strcpy(modified_word, word);
	int length = strlen(word);
	for (int i = 0; i < length; i++) {//모두 소문자로 바꿈
		if('A' <= modified_word[i] && modified_word[i] <= 'Z')
			modified_word[i] = tolower(modified_word[i]);
	}
	for (int i = 0; i < length; i++) {//알파벳만 남김
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
	if (!s->link->word) { //첫번째 자리가 NULL값이면 아무것도 저장되어있지 않다는 얘기가 되므로 그 자리에 값을 대입
		s->link = new_node;
		new_node->info.position[doc_index][++new_node->info.count[doc_index]] = position; //카운트값을 하나 증가시키고 그에 해당하는 인덱스에 포지션값을 넣는다.
	}
	else { //만약 NULL값이 아니면
		while (s->link){ //다음 노드가 NULL이 아니면
			if (strcmp(modified_word, s->link->word) == 0) { //삽입하려는 단어가 기존 단어에 있을 경우
				comparison[doc_index]++; //비교 횟수를 하나 올린다.
				s = s->link;
				s->info.position[doc_index][++s->info.count[doc_index]] = position;
				free(new_node);
				return;
			}
			else if (strcmp(modified_word, s->link->word) < 0) { //삽입 하려는 단어가 기존 단어보다 작으면 반복분 종료
				comparison[doc_index]++; //비교 횟수를 하나 올린다.
				new_node->link = s->link; 
				s->link = new_node;
				new_node->info.position[doc_index][++new_node->info.count[doc_index]] = position; //카운트값을 하나 증가시키고 그에 해당하는 인덱스에 포지션값을 넣는다.
				return;
			}
			else 
				s = s->link; //이동
		}
		//노드가 끝인 경우 그냥 붙인다.
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
	for (int i = 0; i < length; i++) {//모두 소문자로 바꿈
		if ('A' <= modified_word[i] && modified_word[i] <= 'Z')
			modified_word[i] = tolower(modified_word[i]);
	}
	for (int i = 0; i < length; i++) {//알파벳만 남김
		if ('a' <= modified_word[i] && modified_word[i] <= 'z') {
			modified_word[i] = modified_word[i];
		}
		else {
			modified_word[i] = NULL;
			break;
		}
	}
	int cmp = 0; //비교연산 카운터 함수
	int key = hash(modified_word); //단어를 키로 변환
	s = s + key; //s가 해당 인덱스를 가리키고 있음
	while (s->link) { //다음 노드가 존재하면
		if (strcmp(modified_word, s->link->word) == 0) {
			cmp++; //비교 (현재 일치하는 상태)
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
		cmp++; //(비교값과 다른 상태)
		s = s->link;
	}
	return false;
}

void show(int document, int number, int position, char *word) {
	int size = number;
	if (0 <= position && position <= 4) {} //파일의 시작부분이면 ...을 시작하지 않도록 함
	else {
		printf("... ");
	}
	for (int i = 4; i >= 0; i--) { //이전 4단어 출력
		if ((position - i) < 0) {
			continue;
		}
		else {
			printf("%s ", database[document][position - i]);
		}
	}
	for (int i = 1; i <= 4; i++) {//이후 4단어 출력
		if ((position + i) >= 1000) {
			break;
		}
		else {
			printf("%s ", database[document][position + i]);
		}
	}
	if (position >= db_word_number[doc_index] - 4 && position <= db_word_number[doc_index]) { printf("\n"); } // 파일의 끝일 경우 ...을 출력하지 않도록 함
	else {
		printf("... \n");
	}
}