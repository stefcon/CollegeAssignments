#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include "type.h"

Edge* addEdge(Edge* head, int w, int id, char name) {
	Edge* tmp;
	SAFE_CALLOC(tmp, 1);
	tmp->id = id;
	tmp->name = name;
	tmp->w = w;
	tmp->next = NULL;
	if (head == NULL) {
		head = tmp;
	}
	else {
		Edge* current = head;
		while (current->next)
			current = current->next;
		current->next = tmp;
	}
	return head;
}

void removeEdge(Edge* out, Vertex head) {
	Edge* current = head.edge;
	while (current->next != out) current = current->next;
	current->next = out->next;
	free(out);
	head.ElNum--;
}

void removeVertex(Graph* graph, Vertex vertex, int exists[], int id[]) {
	freeEdges(vertex.edge);
	exists[vertex.name - 'a'] = 0;
	id[vertex.name - 'a'] = 0;
	vertex.name = '\0';

}

void initializeArrays(int exists[], int id[]) {
	for (int i = 0; i < 26; i++) {
		exists[i] = 0;
		id[i] = 0;
	}
}

void printDirectGraph(Graph* graph, FILE* output) {
	int n = graph->ElNum;
	fprintf(output, "Lista susednosti:\n");
	for (int i = 0; i < n; i++) {
		fprintf(output, "%c: ", graph->vertex[i].name);
		for (int j = 0; j < n; j++) {
			if (i != j) {
				Edge* current = graph->vertex[j].edge;
				while (current) {
					if (current->id == i + 1) {
						fprintf(output, "%c->", graph->vertex[j].name);
					}
					current = current->next;
				}
			}
		}
		fprintf(output, "NULL\n");
		
	}
}

void printGraph(Graph* graph) {
	int n = graph->ElNum;
	printf("Spisak operacija od kojih zavisi pocetak svake operacije:\n");
	for (int i = 0; i < n; i++) {
		int flag = 0;
		printf("%c: ", graph->vertex[i].name);
		Edge* current = graph->vertex[i].edge;
		while (current) {
			if (current == graph->vertex[i].edge) {
				flag = 1;
				printf("%c", current->name);
			}
			else {
				flag = 1;
				printf(" ,%c", current->name);
			}

			current = current->next;
		}
		if (!flag) printf("Ne zavisi ni od jedne operaije.");
		printf("\n");
		
	}
}

int isEmptyQueue(Queue* q) {
	if (q->front == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}

void insertQueue(Queue* q, int n) {
	QMem* p;
	SAFE_CALLOC(p, 1);
	p->data = n;
	p->next = NULL;
	if (q->rear == NULL) {
		q->front = p;
	}
	else {
		q->rear->next = p;
	}
	q->rear = p;
}

int deleteQueue(Queue* q) {
	int n;
	if (q->front == NULL) {
		printf("underflow\n");
		return -1;
	}
	else {
		QMem* old = q->front;
		q->front = old->next;
		n = old->data;
		if (q->front == NULL) {
			q->rear = NULL;
		}
		free(old);
		return n;
	}
}

void freeEdges(Edge* e) {
	Edge* current = e;
	while (current) {
		Edge* old = current;
		current = current->next;
		free(old);
	}
}

void freeGraph(Graph* graph) {
	int size = graph->ElNum;
	for (int i = 0; i < size; i++) {
		freeEdges(graph->vertex[i].edge);
	}
	free(graph->vertex);
	free(graph);
}

char* readLine() {
	char* line = NULL, * tmp, c;
	int size = 0;
	while (1) {
		c = getchar();
		tmp = realloc(line, (size + 1) * sizeof(char));
		if (tmp == NULL) {
			exit(0);
		}
		line = tmp;
		if (c != '\n') {
			line[size++] = c;
		}
		else {
			line[size] = '\0';
			break;
		}
	}
	return line;
}

char* secureRead(int* flag) {
	char* input = readLine();
	char* current = input;
	*flag = 0;
	while (*current) {
		if (!isdigit(*current))
			*flag = 1;
		current++;
	}

	return input;
}