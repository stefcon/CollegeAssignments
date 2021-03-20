#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dz5.h"


int main(int argc, const char** argv) {
	if (argc < 3) {
		printf("ARG_GRESKA");
		return 0;
	}
	SAFE_OPEN(in, argv[1], "r");
	SAFE_OPEN(out, argv[2], "w");
	Node* head = formList(in);
	if (argc == 4 && !strcmp(argv[3], "-sort")) {
		sortList(head->next);
	}

	makeVCard(head->next, out);

	freeList(head);
	fclose(in);
	fclose(out);
	return 0;
}