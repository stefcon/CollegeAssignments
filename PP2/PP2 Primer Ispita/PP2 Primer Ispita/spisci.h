#ifndef _STDLIB_H
#include <stdlib.h>
#endif
#ifndef _STDIO_H
#include <stdio.h>
#endif
#define SAFE_CALLOC(p, n) \
p = calloc((n), sizeof(*p)); \
if(p == NULL){ \
    perror(NULL); \
    exit(0); \
}
#define SAFE_REALLOC(p, n) \
p = realloc(p, (n) * sizeof(*p)); \
if (!p) { \
	printf("MEM_GRESKA"); \
	exit(0); \
}
#define SAFE_OPEN(name, dir, mode) \
	FILE* name = fopen(dir, mode); \
	if (!name) { \
		printf("DAT_GRESKA"); \
		exit(0); \
	}

typedef struct student {
	char* name[32], dep[3], year[5], index[3];
} Student;

typedef struct node {
	Student* info;
	int rb;
	struct node* prev, * next;
} Node;

void printList(Node* head);
Node* loadStudents(FILE* input);