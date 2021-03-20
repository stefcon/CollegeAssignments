#include <stdio.h>
#include "spisci.h"

void printList(Node* head) {
	SAFE_OPEN(out, "studenti.txt", "w");
	while (head) {
		fprintf(out,"%d. %s/%s\t%s\n", head->rb, head->info->index, head->info->year, head->info->name);
		head = head->next;
	}
}