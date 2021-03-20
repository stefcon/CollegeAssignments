#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SAFE_CALLOC(p, size) \
	p = calloc(size, sizeof(*p)); \
	if (!p) { \
		printf("MEM_GRESKA"); \
		exit(0); \
	} 

//definicija studenta
typedef struct student {
	char name[32];
	int year;
	int index;
	int points;
	int task;
} Student;

//definicija clana liste
typedef struct node {
	Student s;
	struct node* next;
} Node;

//leksikografski sort
void sortList(Node* head) {
	for (Node* p = head; p; p = p->next) {
		for (Node* q = p->next; q; q = q->next) {
			if (strcmp(p->s.name, q->s.name) > 0) {
				Student tmp = p->s;
				p->s = q->s;
				q->s = tmp;
			}
		}
	}
}
//funkcija koja cita jedan red i od uzetih podataka pravi jedan clan liste 
Node* createNode() {
	char buffer[50];
	Student s = { 0 };
	Node* node = NULL;
	if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
		if (sscanf(buffer, "%d/%d, %31[^,], %d", &s.index, &s.year, s.name, &s.points) == 4) {
			SAFE_CALLOC(node, 1);
			node->s = s;
			node->next = NULL;
		}
	}
	return node;
}

//pravljenje liste, cvorovi se ubacuju na pocetak
Node* createList() {
	Node* head = NULL, * current;
	while ((current = createNode()) != NULL) {
		current->next = head;
		head = current;
	}
	return head;
}

//popunjavanje polja 'task' na osnovu ukupnog broja zadataka i formule
void taskDistribution(Node* head, int* x) {
	scanf("%d", x);
	Node* current = head;
	while (current != NULL) {
		int num = current->s.index + (current->s.year % 100); //izdvajanje prve dve cifre
		current->s.task = num % *x;
		current = current->next;
	}
}

//iz pocetne liste se izdvajaju elementi koji sadrze prosledjen broj zadatka i pravi se nova lista
Node* makeTaskList(Node* list, int n) {
	Node* current = list, * last = NULL, *head = NULL, *tmp;
	while (current != NULL) {
		if (current->s.task == n) {
			SAFE_CALLOC(tmp, 1);
			tmp->s = current->s;
			tmp->next = NULL;
			if (last == NULL) { //dodavanje na kraj radi ocuvanja poretka
				head = tmp;
			}
			else {
				last->next = tmp;
			}
			last = tmp;
		}
		current = current->next;
	}

	return head;
}

//pravi se lista pokazivaca za svaku grupu zadataka i popunjava se uz pomoc prethodne funkcije
Node** organizeTasks(Node* head, int x) {
	Node** tasks;
	SAFE_CALLOC(tasks, x);
	for (int i = 0; i < x; i++) {
		tasks[i] = makeTaskList(head, i);
	}

	return tasks;
}

//u zavisnosti parametra n stampa se format ucenika sa ili bez rednog broja zadatka
void printList(Node* head, int n) {
	while (head != NULL) {
		if (n) {
			printf("%d, %.4d/%d, %s, %d\n", head->s.task, head->s.index, 
				head->s.year, head->s.name, head->s.points);
		}
		else {
			printf("%.4d/%d, %s, %d\n", head->s.index,
				head->s.year, head->s.name, head->s.points);
		}
		head = head->next;
	}
}

void freeList(Node* head) {
	Node* old;
	while (head != NULL) {
		old = head; 
		head = head->next;
		free(old);
	}
}

//vraca aritmeticku sredinu poena svih ucenika
float calcAverage(Node* head) {
	float avg = 0;
	int cnt = 0;
	while (head != NULL) {
		cnt++;
		avg += head->s.points;
		head = head->next;
	}
	if (cnt) {
		return avg / cnt;
	}
	else
		return 0;

	
}

int main() {
	Node* head = NULL;
	head = createList();
	
	int x;
	taskDistribution(head, &x);
	Node** tasks = organizeTasks(head, x);

	for (int i = 0; i < x; i++) {
		sortList(tasks[i]);
	}

	printList(head, 0);
	for (int i = 0; i < x; i++) {
		printList(tasks[i], 1);
	}

	float average = calcAverage(head);
	printf("%.2f\n", average);

	freeList(head);
	for (int i = 0; i < x; i++) {
		freeList(tasks[i]);
	}
	free(tasks);

	return 0;
}