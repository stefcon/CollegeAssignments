#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SAFE_REALLOC(p, n, tmp) \
tmp = realloc(p, (n) * sizeof(*p));\
if (!tmp) { \
	printf("MEM_GRESKA\n"); \
	exit(0); \
} \
p = tmp; 

char* readLine();
char** readLines(int*);
char* format(char*, char**, int);

int main() {
	char** zamene, * sablon, * formatirano;
	int n;
	sablon = readLine();
	zamene = readLines(&n);
	if (!n) {
		printf("GRESKA\n");
	}
	else {
		formatirano = format(sablon, zamene, n);
		printf("%s\n", formatirano);
		free(sablon);
		free(formatirano);
		for (int i = 0; i < n; i++) {
			free(zamene[i]);
		}
		free(zamene);
	}
	return 0;
}

char* readLine() {
	char* line = NULL, * tmp, c;
	int size = 0;
	while (1) {
		c = getchar();
		SAFE_REALLOC(line, size + 1, tmp);
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
char** readLines(int* n) {
	char** lines = NULL, ** tmp, * line;
	int cnt = 0;
	while (1) {
		line = readLine();
		if (*line != '\0') {
			SAFE_REALLOC(lines, cnt + 1, tmp);
			lines[cnt++] = line;
		}
		else {
			free(line);
			break;
		}
	}
	*n = cnt;
	return lines;
}
char* format(char* format, char** values , int n) {
	char* p = format, * formatted = NULL, * tmp;
	int ind = 0, size = 0;
	while (*p) {
		if (*p == '%') {
			if (ind == n) {
				ind = 0;
			}
			SAFE_REALLOC(formatted, size + strlen(values[ind]) + 1, tmp);
			strcpy(formatted + size, values[ind]);
			size += strlen(values[ind++]);
		}
		else {
			SAFE_REALLOC(formatted, size + 1, tmp);
			formatted[size++] = *p;
		}
		p++;
	}
	SAFE_REALLOC(formatted, size + 1, tmp);
	formatted[size] = '\0';
	return formatted;
}