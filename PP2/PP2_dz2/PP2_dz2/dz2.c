#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SAFE_MALLOC(p, n) \
p = malloc((n) * sizeof(*p)); \
if(p == NULL){ \
    perror(NULL); \
    exit(-1); \
}
int main() {
	int** mat1, ** mat2;
	int* parnost;
	int m, n;
	scanf("%d%d", &m, &n);
	if (m > 0 && n > 0) {
		SAFE_MALLOC(mat1, m);
		for (int i = 0; i < m; i++) {
			SAFE_MALLOC(mat1[i], n);
			for (int j = 0; j < n; j++)
				scanf("%d", &mat1[i][j]);
		}
		//ispis mat1
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d%c", mat1[i][j], (j != n - 1) ? ' ' : '\n');
			}
		}
		//izracunavnje broja parnih i neparnih vrsta, ubacivanje u mat2 odmah onih koje su parne
		int cnt = 0;
		SAFE_MALLOC(mat2, m);
		SAFE_MALLOC(parnost, m);;
		for (int i = 0; i < m; i++) {
			int par = 0, nepar = 0;
			for (int j = 0; j < n; j++) {
				if (mat1[i][j] % 2)
					nepar++;
				else
					par++;
			}
			printf("%d %d\n", par, nepar);
			if (par >= nepar) {
				parnost[i] = 1;
				SAFE_MALLOC(mat2[cnt], n);
				memcpy(mat2[cnt++], mat1[i], n * sizeof(int));
			}
			else
				parnost[i] = 0; //oznaka za kasniji prolazak kroz niz parnosti
		}
		//prebacivanje neparnih u mat2 pomocu vektora parnosti
		for (int i = 0; i < m; i++) {
			if (!parnost[i]) {
				SAFE_MALLOC(mat2[cnt], n);
				memcpy(mat2[cnt++], mat1[i], n * sizeof(int));
			}
		}
		//ispis mat2, 'bivsi' moodle format...
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				printf("%d", mat2[i][j]);
				if (j != n - 1)
					putchar(' ');
				else if (i != m - 1) putchar('\n');
			}
		}
		//dealokacija memorije
		for (int i = 0; i < m; i++) {
			free(mat1[i]);
			free(mat2[i]);
		}
		free(mat1);
		free(mat2);
		free(parnost);
	}
	return 0;
}