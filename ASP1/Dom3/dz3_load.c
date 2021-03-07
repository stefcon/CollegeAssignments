#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "type.h"

Graph* readGraph(int exists[], int id[]) {
	Graph* graph = NULL;
	int option;
	int flag;
	printf("\nKako zelite da unesete vas graf?\n");
	printf("1.Standardni ulaz\n2.Tekstualna datoteka\n");
	char* line = secureRead(&flag);
	if (!flag) {
		option = atoi(line);
		if (option == 1) {
			putchar('\n');
			graph = createGraphStd(exists, id);
		}
		else if (option == 2) {
			putchar('\n');
			printf("Unesite put do datoteke:\n");
			char* file = readLine();
			SAFE_OPEN(input, file, "r");
			graph = createGraphDat(input, exists, id);
			fclose(input);
			free(file);
		}
		else {
			printf("\nNepostojece opcija\n");
		}
	}
	else {
		printf("\nGreska pri unosu\n");
	}
	
	free(line);
	return graph;
}

Vertex* readVertexDat(FILE* input, int exists[], int id[], int n, int* flag) {
	char buffer[120], * current, op[4], oprnd1[50] = { 0 }, oprnd2[50] = { 0 };
	Vertex* vertex = NULL;
	if (fgets(buffer, sizeof(buffer), input) != NULL) {
		SAFE_CALLOC(vertex, 1);
		vertex->edge = NULL;

		current = buffer;
		int whitespace = 0;
		while (*current != '\0') {
			whitespace += (isblank(*current) != 0);
			current++;
		}

		if (whitespace == 4) {
			if (sscanf(buffer, "%c = %s %s %s\n", &vertex->name, oprnd1, op, oprnd2) == 4) {
				if (!isdigit(*oprnd1))
					vertex->oprnd1 = *oprnd1;
				else
					vertex->oprnd1 = '\0';
				if (!isdigit(*oprnd2))
					vertex->oprnd2 = *oprnd2;
				else
					vertex->oprnd2 = '\0';
			}
			else {
				printf("Greska pri citanju programskog koda\n");
				*flag = 1;
				free(vertex);
				return NULL;
			}
		}
		else if (whitespace == 3) {
			if (sscanf(buffer, "%c = %s %s\n", &vertex->name, op, oprnd2) == 3) {
				vertex->oprnd1 = '\0';
				if (!isdigit(*oprnd2))
					vertex->oprnd2 = *oprnd2;
				else
					vertex->oprnd2 = '\0';
			}
			else {
				printf("Greska pri citanju programskog koda\n");
				*flag = 1;
				free(vertex);
				return NULL;
			}
		} 
		else {
			printf("Greska pri citanju programskog koda\n");
			*flag = 1;
			free(vertex);
			return NULL;
		}

		vertex->id = n + 1;
		exists[vertex->name - 'a'] = 1;
		id[vertex->name - 'a'] = vertex->id - 1;

		if (!strcmp(op, "and") || !strcmp(op, "or") || !strcmp(op, "not") || !strcmp(op, "xor"))
			vertex->w = 1;
		if (!strcmp(op, "+") || !strcmp(op, "-"))
			vertex->w = 3;
		if (!strcmp(op, "*"))
			vertex->w = 10;
		if (!strcmp(op, "/"))
			vertex->w = 23;
	}
	return vertex;
}

Vertex* readVertexStd(int exists[], int id[], int n, int* flag) {
	char buffer[120], * current, op[4], oprnd1[50] = { 0 }, oprnd2[50] = { 0 };
	Vertex* vertex = NULL;
	printf("%d: ", n + 1);
	gets_s(buffer, sizeof(buffer));
	if (*buffer != '\0') {
		SAFE_CALLOC(vertex, 1);
		vertex->edge = NULL;

		current = buffer;
		int whitespace = 0;
		while (*current != '\0') {
			whitespace += (isblank(*current) != 0);
			current++;
		}

		if (whitespace == 4) {
			if (sscanf(buffer, "%c = %s %s %s\n", &vertex->name, oprnd1, op, oprnd2) == 4) {
				if (!isdigit(*oprnd1))
					vertex->oprnd1 = *oprnd1;
				else
					vertex->oprnd1 = '\0';
				if (!isdigit(*oprnd2))
					vertex->oprnd2 = *oprnd2;
				else
					vertex->oprnd2 = '\0';
			}
			else {
				printf("Greska pri citanju programskog koda\n");
				*flag = 1;
				free(vertex);
				return NULL;
			}
		}
		else if (whitespace == 3) {
			if (sscanf(buffer, "%c = %s %s\n", &vertex->name, op, oprnd2) == 3) {
				vertex->oprnd1 = '\0';
				if (!isdigit(*oprnd2))
					vertex->oprnd2 = *oprnd2;
				else
					vertex->oprnd2 = '\0';
			}
			else {
				printf("Greska pri citanju programskog koda\n");
				*flag = 1;
				free(vertex);
				return NULL;
			}
		}
		else {
			printf("Greska pri citanju programskog koda\n");
			*flag = 1;
			free(vertex);
			return NULL;
		}

		vertex->id = n + 1;
		exists[vertex->name - 'a'] = 1;
		id[vertex->name - 'a'] = vertex->id - 1;

		if (!strcmp(op, "and") || !strcmp(op, "or") || !strcmp(op, "not") || !strcmp(op, "xor"))
			vertex->w = 1;
		if (!strcmp(op, "+") || !strcmp(op, "-"))
			vertex->w = 3;
		if (!strcmp(op, "*"))
			vertex->w = 10;
		if (!strcmp(op, "/"))
			vertex->w = 23;
	}
	return vertex;
}

Graph* createGraphDat(FILE* input, int exists[], int id[]) {
	Graph* graph;
	SAFE_CALLOC(graph, 1);
	int size = 0, flag = 0;
	Vertex* vertex;
	/*int exists[26] = { 0 }, id[26] = { 0 };*/
	while ((vertex = readVertexDat(input, exists, id, size, &flag)) != NULL) {
		Vertex* tmp = graph->vertex;
		SAFE_REALLOC(tmp, size + 1);
		graph->vertex = tmp;
		graph->vertex[size] = *vertex;
		free(vertex);
		updateGraph(graph, exists, id, size);
		size++;
	}
	graph->ElNum = size;
	if (flag) {
		freeGraph(graph);
		return NULL;
	}
	return graph;
}

Graph* createGraphStd(int exists[], int id[]) {
	Graph* graph;
	SAFE_CALLOC(graph, 1);
	int size = 0, flag = 0;
	Vertex* vertex;
	printf("U svakom redu unesite po jednu instrukciju (unesite prazan red za kraj unosa):\n");
	while ((vertex = readVertexStd(exists, id, size, &flag)) != NULL) {
		Vertex* tmp = graph->vertex;
		SAFE_REALLOC(tmp, size + 1);
		graph->vertex = tmp;
		graph->vertex[size] = *vertex;
		free(vertex);
		updateGraph(graph, exists, id, size);
		size++;
	}

	graph->ElNum = size;
	if (flag) {
		freeGraph(graph);
		return NULL;
	}
	return graph;
}

void addVertex(Graph* graph, int exists[], int id[]) {
	Vertex tmp;
	int size = graph->ElNum, flag;
	printf("Unesite novu instrukciju:\n");
	Vertex* vertex = readVertexStd(exists, id, size, &flag);

	if (vertex) {
		SAFE_REALLOC(graph->vertex, size + 1);
		graph->vertex[size] = *vertex;
		free(vertex);
		updateGraph(graph, exists, id, size);
		graph->ElNum++;
	}
}

void updateGraph(Graph* graph, int exists[], int id[], int size) {
	if (graph->vertex[size].oprnd1) {
		if (exists[graph->vertex[size].oprnd1 - 'a']) {
			int ind = id[graph->vertex[size].oprnd1 - 'a'];
			graph->vertex[size].edge = addEdge(graph->vertex[size].edge, graph->vertex[ind].w,
				graph->vertex[ind].id, graph->vertex[ind].name);
			graph->vertex[size].ElNum += 1;
		}
	}

	if (graph->vertex[size].oprnd2) {
		if (exists[graph->vertex[size].oprnd2 - 'a']) {
			int ind = id[graph->vertex[size].oprnd2 - 'a'];
			graph->vertex[size].edge = addEdge(graph->vertex[size].edge, graph->vertex[ind].w,
				graph->vertex[ind].id, graph->vertex[ind].name);
			graph->vertex[size].ElNum += 1;
		}
	}
}
