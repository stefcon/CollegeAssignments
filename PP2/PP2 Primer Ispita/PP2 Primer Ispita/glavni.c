#include <stdio.h>
#include <stdlib.h>
#include "spisci.h"

int main(int argc, const char** argv) {
	SAFE_OPEN(in, argv[1], "r");
	Node* head = loadStudents(in);
	fclose(in);
	printList(head);

	return 0;
}