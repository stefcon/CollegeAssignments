#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spisci.h"

char* readLine() {
	char* line = NULL;
	int size = 0;
	while (1) {
		char c = getchar();
		SAFE_REALLOC(line, size + 1);
		if (c != '\n') {
			line[size++] = c;
		}
		else {
			line[size] = '\0';
		}
	}
	return line;
}

Node* loadStudents(FILE* input) {
	Node* head = NULL, * tail = NULL;
	int cnt = 0;
	char buffer[100];
	char year[3], index[5], name[32], dep[3];
	Node* element;
	Student* student;
	while ((fgets(buffer, sizeof(buffer), input)) != NULL) {
		if (sscanf(buffer, "%2s%4s %31[^\t] %s", year, index, name, dep) == 4) {
			SAFE_CALLOC(student, 1);
			SAFE_CALLOC(element, 1);
			strcpy(student->dep, dep);
			strcpy(student->index, index);
			strcpy(student->name, name);
			strcpy(student->year, year);
			element->info = student;
			cnt++;
			element->rb = cnt;
			if (!head) {
				head = element;
			}
			else {
				tail->next = element;
				element->prev = tail;
				element->next = NULL;
			}
			tail = element;
		}
	}
	return head;
}