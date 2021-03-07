#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "type.h"

int* TopSort(Graph* graph) {
	int size = graph->ElNum;
	int* topsort = NULL;
	SAFE_CALLOC(topsort, size);
	Queue* q;
	SAFE_CALLOC(q, 1);
	int* in_degree, ind = 0;
	SAFE_CALLOC(in_degree, size);

	for (int i = 0; i < size; i++) {
		in_degree[i] = graph->vertex[i].ElNum;
		if (in_degree[i] == 0) {
			insertQueue(q, i + 1);
		}
	}

	for (int i = 0; i < size; i++) {
		int u = deleteQueue(q);
		topsort[ind++] = u;
		for (int j = 0; j < size; j++) {
			if (j != u - 1) {
				Edge* current = graph->vertex[j].edge;
				while (current) {
					if (current->id == u) {
						in_degree[j]--;
						if (in_degree[j] == 0) {
							insertQueue(q, j + 1);
						}
						break;
					}
					current = current->next;
				}
			}

		}
	}
	free(q);
	free(in_degree);
	return topsort;
}

int criticalPath(Graph* graph, int* EST, int* LST) {
	int size = graph->ElNum;
	int endtime = -1, endnode = 0;
	int* t = TopSort(graph);
	for (int u = 0; u < size; u++) {
		int i = t[u] - 1;
		EST[i] = 0;
		Edge* current = graph->vertex[i].edge;
		while (current) {
			if (EST[i] < EST[current->id - 1] + current->w) {
				EST[i] = EST[current->id - 1] + current->w;
			}
			current = current->next;
		}
		if (endtime < EST[i] + graph->vertex[i].w) {
			endtime = EST[i] + graph->vertex[i].w;
			endnode = i;
		}
	}
	int finaltime = endtime;// Vreme zavrsetka celog segmenta
	//Izracunavnje LST za sve cvorove ciji je izlazni stepen jednak 0
	int init[26] = { 0 };
	for (int i = 0; i < size; i++) {
		int flag = 0;
		for (int j = 0; j < size && !flag; j++) {
			if (j != i) {
				Edge* current = graph->vertex[j].edge;
				while (current) {
					if (current->id == i + 1) {
						flag = 1;
						break;
					}
					current = current->next;
				}
			}
		}
		if (!flag) {
			LST[i] = finaltime - graph->vertex[i].w;
			init[i] = 1;
		}
	}
	
	for (int u = size - 1; u >= 0; u--) {
		int i = t[u] - 1;
		if (!init[i]) {
			LST[i] = INT_MAX;
			for (int j = 0; j < size; j++) {
				if (j != i) {
					Edge* current = graph->vertex[j].edge;
					while (current) {
						if (current->id == i + 1) {
							if (LST[i] > LST[j] - current->w) {
								LST[i] = LST[j] - current->w;
							}
						}
						current = current->next;
					}
				}
			}
		}
	}

	for (int i = 0; i < size; i++) {
		int L = LST[i] - EST[i];
		if (L == 0) {
			graph->vertex[i].crit = 1;
		}
	}
	free(t);
	return finaltime;
}

void transitiveEdges(Graph* graph) {
	int id, size = graph->ElNum, read_flag;
	printf("Unesite identifikator (redni broj reda) operacije: ");
	char* input = secureRead(&read_flag);
	if (!read_flag) {
		id = atoi(input);
		free(input);
		if (id > size) {
			printf("Trazeni cvor ne postoji u grafu\n");
			return;
		}
	}
	else {
		printf("Greska pri unosu\n");
		free(input);
		return;
	}
	int* visited;
	SAFE_CALLOC(visited, size);
	Queue* q;
	SAFE_CALLOC(q, 1);
	visited[id] = 1;
	for (int i = 0; i < size; i++) {
		if (i != id - 1) {
			Edge* current = graph->vertex[i].edge;
			while (current) {
				if (current->id == id) {
					visited[i] = -1;
					insertQueue(q, i);
				}
				current = current->next;
			}
		}
	}
	printf("Tranzitivne grane za cvor %c su:\n", graph->vertex[id - 1].name);
	int flag = 0;
	while (!isEmptyQueue(q)) {
		int e = deleteQueue(q);
		for (int i = 0; i < size; i++) {
			if (i != e) {
				Edge* current = graph->vertex[i].edge;
				while (current) {
					if (current->id == e + 1) {
						if (!visited[i]) {
							visited[i] = 1;
							insertQueue(q, i);
						}
						else if (visited[i] == -1) {
						flag = 1;
						printf("%c->%c\n", graph->vertex[id - 1].name, graph->vertex[i].name);
						visited[i] = 1;
						}
					}
					current = current->next;
				}
			}
		}
	}
	if (!flag)
		printf("Ne postoje tranzitivne grane za dati cvor.\n");
	free(q);
	free(visited);
}

void optimalSchedule(Graph* graph, int* EST, int* LST, int finaltime) {
	int size = graph->ElNum;
	printf("Moguci trenuci za pocetak svake operacije:\n");
	for (int i = 0; i < size; i++) {
		printf("%c: ", graph->vertex[i].name);
		for (int j = 0; j < EST[i]; j++) printf("_");
		for (int j = EST[i]; j <= LST[i]; j++) printf("-");
		for (int j = LST[i] + 1; j <= finaltime; j++) printf("_");
		printf(" (w: %d, EST: %d, LST: %d, L: %d)", graph->vertex[i].w, EST[i], LST[i], LST[i] - EST[i]);
		putchar('\n');
	}
	printGraph(graph);
}

void criticalVertices(Graph* graph) {
	int size = graph->ElNum;
	printf("Cvorovi koji se nalaze na kriticno putu/putevima su: ");
	for (int i = 0; i < size; i++) {
		if (graph->vertex[i].crit)
			printf("%c ", graph->vertex[i].name);
	}
	putchar('\n');
}