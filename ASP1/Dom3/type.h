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


typedef struct edge {
	char name;
	int w, id;
	struct edge* next;
} Edge;

typedef struct vertex {
	int  ElNum, w, id, crit;
	char name, oprnd1, oprnd2;
	Edge* edge;
} Vertex;

typedef struct graph {
	int ElNum;
	Vertex* vertex;
} Graph;

typedef struct queuemem {
	int data;
	struct queuemem* next;
} QMem;

typedef struct queue {
	QMem* front, * rear;
} Queue;

//stvaranje grafa, dodavanje cvorova, dodavanje grana
//brisanje cvorova, brisanje brisanje grana, brisanje celog grafa

Vertex* readVertexDat(FILE* input, int exists[], int id[], int n, int* flag);
Vertex* readVertexStd(int exists[], int id[], int n, int* flag);
Graph* createGraphDat(FILE* input, int exists[], int id[]);
Graph* createGraphStd(int exists[], int id[]);
Graph* readGraph(int exists[], int id[]);
Edge* addEdge(Edge* head, int w, int id, char name); //dodvanje na kraj
void updateGraph(Graph* graph, int exists[], int id[], int size);
void printGraph(Graph* graph);
void printDirectGraph(Graph* graph, FILE* output);
void addVertex(Graph* graph, int exists[], int id[]);
void insertQueue(Queue* q, int n);
int deleteQueue(Queue* q);
int* TopSort(Graph* graph);
int criticalPath(Graph* graph, int* EST, int* LST);
void criticalVertices(Graph* graph);
void transitiveEdges(Graph* graph);
void optimalSchedule(Graph* graph, int* EST, int* LST, int finaltime);
int isEmptyQueue(Queue* q);
void freeEdges(Edge* e);
void freeGraph(Graph* graph);
char* readLine();
char* secureRead(int* flag);
void initializeArrays(int exists[], int id[]);