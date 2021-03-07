#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "type.h"

int main(int argc, const char** argv) {
	int option = -1, read_flag, graph_flag = 0, crit_flag = 0;
	int finaltime;
	int* EST = NULL, * LST = NULL;
	Graph* graph = NULL;
	int exists[26] = { 0 }, id[26] = { 0 };
	while (option) {

		printf("********************************************************************\n");
		printf("Unesite broj zeljene opcije: \n");
		printf("1. Unos programskog koda\n");
		printf("2. Unesite novu liniju koda(ukoliko postoji graf, samo se azurira)\n");
		printf("3. Ispis grafa zavisnosti(lista suseda) na standardnom izlazu\n");
		printf("4. Ispis grafa zavisnosti(lista suseda) u datoteci\n");
		printf("5. Izracunavanje najkraceg moguceg trajanja programskog segmenta\n");
		printf("6. Ispis operacija koje se nalaze na kriticnom putu\n");
		printf("7. Optimalni rasporedi za pojedinacne operacije\n");
		printf("8. Odredjivanje tranzitivnih zavisnosti izmedju operacija\n");
		printf("0. Izadji iz programa (ili prazna linija)\n");
		printf("********************************************************************\n");

		char* input = secureRead(&read_flag);
		if (!read_flag) {
			option = atoi(input);
			free(input);
		}
		else {
			printf("Greska pri unosu\n");
			free(input);
			continue;
		}
		switch (option)
		{
		case 1: 
			initializeArrays(exists, id);
			if (graph_flag) {
				freeGraph(graph);
				if (crit_flag) {
					free(EST);
					free(LST);
				}
			}
			if (graph = readGraph(exists, id))
				graph_flag = 1;
			break;
		case 2:
			if (!graph_flag) {
				graph_flag = 1;
				SAFE_CALLOC(graph, 1);
				initializeArrays(exists, id);
			}
			addVertex(graph, exists, id);
			if (!graph->vertex) {
				free(graph);
				graph_flag = 0;
			}
			break;
		case 3: 
			if (graph_flag)
				printDirectGraph(graph, stdout);
			else
				printf("Prvo unesite graf!\n");
			break;
		case 4:
			if (graph_flag) {
				printf("Unesite naziv izlazne datoteke:\n");
				char* input = readLine();
				SAFE_OPEN(out, input, "w");
				printDirectGraph(graph, out);
				free(input);
				fclose(out);
			}
			else {
				printf("Prvo unesite graf!\n");
			}
			break;
		case 5:
			if (graph_flag) {
				int size = graph->ElNum;
				if (!crit_flag) {
					SAFE_CALLOC(EST, size);
					SAFE_CALLOC(LST, size);
					finaltime = criticalPath(graph, EST, LST);
				}
				printf("Najkrace trajanje programskog segmenta iznosi %d taktova\n", finaltime);
			}
			else {
				printf("Prvo unesite graf!\n");
			}
			break;
		case 6: 
			if (graph_flag) {
				int size = graph->ElNum;
				if (!crit_flag) {
					SAFE_CALLOC(EST, size);
					SAFE_CALLOC(LST, size);
					finaltime = criticalPath(graph, EST, LST);
				}
				criticalVertices(graph);
			}
			else {
				printf("Prvo unesite graf!\n");
			}
			break;
		case 7:
			if (graph_flag) {
				int size = graph->ElNum;
				if (!crit_flag) {
					SAFE_CALLOC(EST, size);
					SAFE_CALLOC(LST, size);
					finaltime = criticalPath(graph, EST, LST);
				}
				optimalSchedule(graph, EST, LST, finaltime);
			}
			else {
				printf("Prvo unesite graf!\n");
			}
			break;
		case 8:
			if (graph_flag) {
				transitiveEdges(graph);
			}
			else {
				printf("Prvo unesite graf!\n");
			}
			break;
		case 0: 
			if (graph_flag) {
				freeGraph(graph);
				if (crit_flag) {
					free(EST);
					free(LST);
				}
			}
			break;
		default:
			printf("Nepostojeca opcija, pokusajte ponovo\n");
			option = -1;
			break;
		}
	}
	return 0;
}