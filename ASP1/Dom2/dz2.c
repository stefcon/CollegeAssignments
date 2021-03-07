#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#define SAFE_MALLOC(p, n) \
p = malloc((n) * sizeof(*p)); \
if(p == NULL){ \
    perror(NULL); \
    exit(1); \
}

typedef struct cvor {
	char oznaka[4];
	int unary_flag;
	struct cvor* min_tree;
	struct cvor* levi, * desni;
} Cvor;
typedef struct stablo {
	Cvor* koren;
} Stablo;
typedef struct mapa {
	int flag[26];
	double vr[26];
} Mapa;
typedef struct stackNode {
	Cvor* info;
	int depth;
	double val;
	struct stackNode* next;
} Stack;

Cvor* get_tree_node();
Stack* get_stack_node();
Cvor* pop(Stack** s);
void push(Stack** s, Cvor* x);
Cvor* top(Stack* s);
int isEmptyStack(Stack*);
char* readLine();
void infix_transform(Stablo** stb, Mapa* map);
void restartMap(Mapa* map);
void printTree(Cvor*);
void printPrefix(Cvor*);
double calculate(double prvi, double drugi, Cvor* x, Mapa* map);
void push_calc(Stack** s, double x);
double pop_calc(Stack** s);
double calcExp(Cvor*, Mapa*);
Cvor* clone(Cvor* x);
Cvor* copyTree(Cvor* root);
Cvor* diff(Stablo* stb_1);
void diff_pom(Cvor*, Stack**, char);
int min_diff(Cvor*, Mapa*);
void setValues(Mapa* map);
void deallocate_tree(Cvor*);
int diff_tg_check(Cvor* root);
void set_min(Cvor*);

/* Program u svakom trenutku cuva najvise dva stabla, stablo izraza i stablo izvoda, koji se formiraju
odabirom odgovarajucih opcija. Prost i slozen izvod su implementirani na iterativan nacin i mogu se 
dobiti odabirom opcije 5 ili opcije 9. Kada se odabere opcija za vise izvode, staro stablo izvoda se brise,
a visi izvod postaje novo stablo izvoda, sto treba imati u vidu kada se pozivaju funkcije za ispis prefiksne
notacije, ispis stabla i izracunavanje izraza. Takodje, 'min' u izrazima izvoda ne predstavlja sustinski 
funkciju minimuma, vec operaciju koja vraca vrednost onog clana cija je vrednost originalnog izraza za date
brojeve manja, a ne vrednost manja od ta dva izvoda */

int main() {
	int opcija = -1, izraz_flag = 0, izvod_flag = 0;
	double rez;
	Stablo* stb, * stb_izvod, * stb_pom;
	Mapa* map;
	SAFE_MALLOC(stb, 1);
	SAFE_MALLOC(stb_izvod, 1);
	SAFE_MALLOC(map, 1);
	stb->koren = NULL;
	stb_izvod->koren = NULL;
	restartMap(map);
	while (opcija) {
		printf("********************************************************************\n");
		printf("Unesite broj zeljene opcije: \n");
		printf("1. Unos infiksnog izraza\n");
		printf("2. Ispis formiranog stabla izraza\n");
		printf("3. Ispis izraza u prefiksnoj notaciji\n");
		printf("4. Racunanje vrednosti izraza\n");
		printf("5. Diferenciranje izraza(iterativno)\n");
		printf("6. Ispis formiranog stabla izvoda\n");
		printf("7. Ispis izvoda u prefiksnoj notaciji\n");
		printf("8. Izracunavanje izvoda u tacki(prethodno se mora izbrati 5.)\n");
		printf("9. Diferenciranje izvoda\n");
		printf("(brise se prethodni izvod, visi izvod postaje 'stablo izvoda')\n");
		printf("0. Izadji iz programa\n");
		printf("********************************************************************\n");
		scanf("%d", &opcija);
		getchar();

		switch (opcija) {
		case 1: 
			if (izraz_flag == 0) {
				izraz_flag = 1;
			}
			else {
				restartMap(map);
				deallocate_tree(stb->koren);
				deallocate_tree(stb_izvod->koren);
				stb_izvod->koren = NULL;
				izvod_flag = 0;
			}
			infix_transform(&stb, map);
			break;
		case 2: printTree(stb->koren); break;
		case 3: printPrefix(stb->koren); break;
		case 4: setValues(map); rez = calcExp(stb->koren, map); if (stb->koren != NULL) printf("Rezultat izraza iznosi %.4lf\n", rez); break;
		case 5: 
			if (izvod_flag == 0) {
				izvod_flag = 1;
			}
			else {
				deallocate_tree(stb_izvod->koren);
			}
			stb_izvod->koren = diff(stb); 
			break;
		case 6: printTree(stb_izvod->koren); break;
		case 7: printPrefix(stb_izvod->koren); break;
		case 8: 
			if (stb_izvod->koren != NULL) {
				setValues(map);
				rez = calcExp(stb_izvod->koren, map);
				printf("Vrednost izvoda iznosi %.4lf\n", rez);
			}
			else {
				printf("Stablo izvoda jos uvek nije formirano!\n");
			}
			break;
		case 9:
			if (stb_izvod->koren == NULL) {
				printf("Prvi izvod jos uvek nije izracunat!\n");
			}
			else {
				//nisu implementirane sve trigonometrijske funkcije da bi visi izvodi bili moguci
				if (diff_tg_check(stb->koren)) {
					printf("Nije moguce naci visi izvod usled ogranicenja programa.\n");
				}
				else {
					SAFE_MALLOC(stb_pom, 1);
					stb_pom->koren = stb_izvod->koren;
					stb_izvod->koren = diff(stb_pom);
					set_min(stb_izvod->koren);
					deallocate_tree(stb_pom->koren);
					free(stb_pom);
				}
			}
			break;
		case 0: deallocate_tree(stb->koren); deallocate_tree(stb_izvod->koren); free(stb); free(stb_izvod); free(map); continue; break;
		default: printf("Nepostojeca opcija.\n"); 
		}
	}

	return 0;
}


Cvor* get_tree_node() {
	Cvor* p = SAFE_MALLOC(p, 1);
	p->levi = NULL;
	p->unary_flag = 0;
	p->min_tree = NULL;
	p->desni = NULL;
	return p;
}
Stack* get_stack_node() {
	Stack* p = SAFE_MALLOC(p, 1);
	p->next = NULL;
	return p;
}

void deallocate_tree(Cvor* root) {
	Stack* s1 = NULL;
	Cvor* next = root;
	if (next) {
		do {
			while (next) {
				if (next->desni != NULL)
					push(&s1, next->desni);
				push(&s1, next);
				next = next->levi;
			}

			next = pop(&s1);

			if (next->desni && next->desni == top(s1)) {
				pop(&s1);
				push(&s1, next);
				next = next->desni;
			}
			else {
				free(next);
				next = NULL;
			}
		} while (!isEmptyStack(s1));
	}
}

void push(Stack** s, Cvor* x) {
	Stack* p = get_stack_node();
	p->info = x;
	p->next = *s;
	(*s) = p;
}
Cvor* pop(Stack** s) {
	if (*s == NULL) {
		printf("underflow\n");
		return NULL;
	}
	else {
		Stack* p = *s;
		*s = (*s)->next;
		Cvor* x = p->info;
		free(p);
		return x;
	}
}
Cvor* top(Stack* s) {
	if (s == NULL) {
		return NULL;
	}
	else {
		return s->info;
	}
}
int isEmptyStack(Stack* s) {
	if (s == NULL) {
		return 1;
	}
	else {
		return 0;
	}
}
char* readLine() {
	char* line = NULL, * tmp, c;
	int size = 0;
	while (1) {
		c = getchar();
		tmp = realloc(line, (size + 1) * sizeof(char));
		if (tmp == NULL) {
			exit(1);
		}
		line = tmp;
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
int find_priority(Cvor* x) {
	switch (x->oznaka[0]) {
	case '+': return 0;
	case '-': return (x->unary_flag == 0) ? 0 : 4;
	case '*': case '/': return 1; 
	case '^': return 2;
	case '(': return 5;
	case ')': case ',': return 6;
	default: return 3;
	}
}
void restartMap(Mapa* map) {
	for (int i = 0; i < 26; i++) {
		map->flag[i] = 0;
		map->vr[i] = 0;
	}
}
void push_depth(Stack** s, Cvor* x, int cnt) {
	Stack* p = get_stack_node();
	p->info = x;
	p->depth = cnt;
	p->next = *s;
	(*s) = p;
}
int top_depth(Stack* s) {
	if (s == NULL) {
		printf("underflow");
		return -1;
	}
	else {
		return s->depth;
	}
}
void push_calc(Stack** s, double x) {
	Stack* p = get_stack_node();
	p->val = x;
	p->next = *s;
	(*s) = p;
}
double pop_calc(Stack** s) {
	if (*s == NULL) {
		printf("underflow\n");
		return 0;
	}
	else {
		Stack* p = *s;
		*s = (*s)->next;
		double x = p->val;
		free(p);
		return x;
	}
}

int diff_tg_check(Cvor* root) {
	Stack* s = NULL;
	int tg_flag = 0;
	push(&s, root);
	while (!isEmptyStack(s)) {
		Cvor* next = pop(&s);
		while (next != NULL) {
			if (next->oznaka[0] == 't') {
				tg_flag = 1;
			}
			if (next->desni != NULL) {
				push(&s, next->desni);
			}
			next = next->levi;
		}
	}
	return tg_flag;
}
void set_min(Cvor* root) {
	Stack* s = NULL;
	push(&s, root);
	while (!isEmptyStack(s)) {
		Cvor* next = pop(&s);
		while (next != NULL) {
			if (next->oznaka[0] == 'm') {
				next->min_tree = next->min_tree->min_tree;
			}
			if (next->desni != NULL) {
				push(&s, next->desni);
			}
			next = next->levi;
		}
	}
}
void diff_pom(Cvor* x, Stack** s, char prom) {
	char oznaka = x->oznaka[0], cos[4] = "cos", ln[3] = "ln";
	Cvor* izvod1, * izvod2, * jedan, * dva, * tri, * cetiri, * pet, * sest;
	Cvor* oprnd1, * oprnd2, * oprnd2_2;
	if (isupper(oznaka) || isdigit(oznaka)) {
		Cvor* tmp = get_tree_node();
		if (oznaka == prom) {
			tmp->oznaka[0] = '1';
			tmp->oznaka[1] = '\0';
		}
		else {
			tmp->oznaka[0] = '0';
			tmp->oznaka[1] = '\0';
		}
		push(&*s, tmp);
	}
	else {
		switch (oznaka) {
		case '+':
			izvod2 = pop(&*s);
			izvod1 = pop(&*s);
			if (izvod2->oznaka[0] == '0' && izvod1->oznaka[0] == '0') {
				push(&*s, izvod1);
				free(izvod2);
			}
			else if (izvod2->oznaka[0] == '0') {
				push(&*s, izvod1);
				free(izvod2);
			}
			else if (izvod1->oznaka[0] == '0') {
				push(&*s, izvod2);
				free(izvod1);
			}
			else {
				jedan = get_tree_node();
				strcpy(jedan->oznaka, x->oznaka);
				jedan->desni = izvod2;
				jedan->levi = izvod1;
				push(&*s, jedan);
			}
			break;
		case '*': 
			izvod2 = pop(&*s);
			izvod1 = pop(&*s);
			if (izvod2->oznaka[0] == '0' && izvod1->oznaka[0] == '0') {
				push(&*s, izvod2);
				free(izvod1);
			}
			else if (izvod1->oznaka[0] == '0') {
				oprnd1 = copyTree(x->levi);
				if (izvod2->oznaka[0] == '1') {
					push(&*s, oprnd1);
				}
				else {
					jedan = get_tree_node();
					strcpy(jedan->oznaka, x->oznaka);
					jedan->levi = oprnd1;
					jedan->desni = izvod2;
					free(izvod1);
					push(&*s, jedan);

				}
			}
			else if (izvod2->oznaka[0] == '0') {
				oprnd2 = copyTree(x->desni);
				if (izvod1->oznaka[0] == '1') {
					push(&*s, oprnd2);
				}
				else {
					jedan = get_tree_node();
					strcpy(jedan->oznaka, x->oznaka);
					jedan->levi = izvod1;
					jedan->desni = oprnd2;
					free(izvod2);
					push(&*s, jedan);
				}
			}
			else {
				oprnd2 = copyTree(x->desni);
				oprnd1 = copyTree(x->levi);
				jedan = get_tree_node();
				jedan->oznaka[0] = '+';
				jedan->oznaka[1] = '\0';
				if (izvod1->oznaka[0] == '1') {
					jedan->levi = oprnd2;
				}
				else {
					dva = get_tree_node();
					strcpy(dva->oznaka, x->oznaka);
					jedan->levi = dva;
					dva->levi = izvod1;
					dva->desni = oprnd2;
				}
				if (izvod2->oznaka[0] == '1') {
					jedan->desni = oprnd1;
				}
				else {
					tri = get_tree_node();
					strcpy(tri->oznaka, x->oznaka);
					jedan->desni = tri;
					tri->levi = oprnd1;
					tri->desni = izvod2;
				}
				push(&*s, jedan);
			}
			break;
		case '-':
			jedan = get_tree_node();
			strcpy(jedan->oznaka, x->oznaka);
			if (x->unary_flag == 1) {
				izvod2 = NULL;
				izvod1 = pop(&*s);
				jedan->unary_flag = 1;
			}
			else {
				izvod2 = pop(&*s);
				izvod1 = pop(&*s);
			}
			if (jedan->unary_flag ==  1) {
				if (izvod1->oznaka[0] == '0') {
					free(jedan);
					push(&*s, izvod1);
				}
				else {
					jedan->levi = izvod1;
					push(&*s, jedan);
				}
			}
			else if (izvod2->oznaka[0] == '0' && izvod1->oznaka[0] == '0') {
				push(&*s, izvod2);
				free(izvod1);
				free(jedan);
			}
			else if (izvod2->oznaka[0] == '0') {
				free(jedan);
				free(izvod2);
				push(&*s, izvod1);
			}
			else if (izvod1->oznaka[0] == '0') {
				jedan->unary_flag = 1;
				jedan->levi = izvod2;
				free(izvod1);
				push(&*s, jedan);
			}
			else {
				jedan->desni = izvod2;
				jedan->levi = izvod1;
				push(&*s, jedan);
			}
			break;
		case '/':
			izvod2 = pop(&*s);
			izvod1 = pop(&*s);
			if (izvod2->oznaka[0] == '0' && izvod1->oznaka[0] == '0') {
				free(izvod1);
				push(&*s, izvod2);
			}
			else if (izvod2->oznaka[0] == '0') {
				jedan = get_tree_node();
				oprnd2 = copyTree(x->desni);
				strcpy(jedan->oznaka, x->oznaka);
				jedan->levi = izvod1;
				jedan->desni = oprnd2;
				free(izvod2);
				push(&*s, jedan);
			}
			else if (izvod1->oznaka[0] == '0') {
				jedan = get_tree_node();
				dva = get_tree_node();
				tri = get_tree_node();
				pet = get_tree_node();
				sest = get_tree_node();
				oprnd2 = copyTree(x->desni);
				oprnd1 = copyTree(x->levi);
				strcpy(jedan->oznaka, x->oznaka);
				dva->oznaka[0] = '-';
				dva->oznaka[1] = '\0';
				dva->unary_flag = 1;
				tri->oznaka[0] = '^';
				tri->oznaka[1] = '\0';
				sest->oznaka[0] = '2';
				sest->oznaka[1] = '\0';
				jedan->levi = dva;
				jedan->desni = tri;
				if (izvod2->oznaka[0] == '1') {
					dva->levi = oprnd1;
					free(pet);
					free(izvod2);
				}
				else {
					pet->oznaka[0] = '*';
					pet->oznaka[1] = '\0';
					dva->levi = pet;
					pet->levi = oprnd1;
					pet->desni = izvod2;
				}
				tri->levi = oprnd2;
				tri->desni = sest;
				free(izvod1);
				push(&*s, jedan);
			}
			else {
				oprnd2 = copyTree(x->desni);
				oprnd2_2 = copyTree(x->desni);
				oprnd1 = copyTree(x->levi);
				jedan = get_tree_node();
				dva = get_tree_node();
				tri = get_tree_node();
				sest = get_tree_node();
				strcpy(jedan->oznaka, x->oznaka);
				dva->oznaka[0] = '-';
				dva->oznaka[1] = '\0';
				tri->oznaka[0] = '^';
				tri->oznaka[1] = '\0';
				sest->oznaka[0] = '2';
				sest->oznaka[1] = '\0';
				jedan->levi = dva;
				jedan->desni = tri;
				tri->levi = oprnd2_2;
				tri->desni = sest;
				if (izvod1->oznaka[0] == '1') {
					dva->levi = oprnd2;
				}
				else {
					cetiri = get_tree_node();
					cetiri->oznaka[0] = '*';
					cetiri->oznaka[1] = '\0';
					cetiri->levi = izvod1;
					cetiri->desni = oprnd2;
					dva->levi = cetiri;
				}
				if (izvod2->oznaka[0] == '1') {
					dva->desni = oprnd1;
				}
				else {
					pet = get_tree_node();
					pet->oznaka[0] = '*';
					pet->oznaka[1] = '\0';
					pet->levi = oprnd1;
					pet->desni = izvod2;
					dva->desni = pet;
				}
				push(&*s, jedan);
			}
			break;
		case '^':
			izvod2 = pop(&*s);
			izvod1 = pop(&*s);
			if (izvod1->oznaka[0] == '0' && izvod2->oznaka[0] == '0') {
				push(&*s, izvod1);
				free(izvod2);
			}
			else if (izvod2->oznaka[0] == '0') {
				free(izvod2);
				oprnd2 = copyTree(x->desni);
				oprnd1 = copyTree(x->levi);
				oprnd2_2 = copyTree(x->desni);
				dva = get_tree_node();
				tri = get_tree_node();
				cetiri = get_tree_node();
				pet = get_tree_node();
				sest = get_tree_node();
				dva->oznaka[0] = '*';
				dva->oznaka[1] = '\0';
				strcpy(cetiri->oznaka, x->oznaka);
				pet->oznaka[0] = '-';
				pet->oznaka[1] = '\0';
				sest->oznaka[0] = '1';
				sest->oznaka[1] = '\0';
				dva->levi = oprnd2;
				dva->desni = cetiri;
				cetiri->levi = oprnd1;
				cetiri->desni = pet;
				pet->levi = oprnd2_2;
				pet->desni = sest;
				if (izvod1->oznaka[0] == '1') {
					push(&*s, dva);
					free(izvod1);
				}
				else {
					jedan = get_tree_node();
					jedan->oznaka[0] = '*';
					jedan->oznaka[1] = '\0';
					jedan->levi = dva;
					jedan->desni = izvod1;
					push(&*s, jedan);
				}
			}
			else {
				free(izvod1);
				oprnd1 = copyTree(x);
				oprnd2 = copyTree(x->levi);
				dva = get_tree_node();
				tri = get_tree_node();
				dva->oznaka[0] = '*';
				dva->oznaka[1] = '\0';
				strcpy(tri->oznaka, ln);
				tri->unary_flag = 1;
				dva->levi = oprnd1;
				dva->desni = tri;
				tri->levi = oprnd2;
				if (izvod2->oznaka[0] == '1') {
					free(izvod2);
					push(&*s, dva);
				}
				else {
					jedan = get_tree_node();
					jedan->oznaka[0] = '*';
					jedan->oznaka[1] = '\0';
					jedan->levi = dva;
					jedan->desni = izvod2;
					push(&*s, jedan);
				}
			}
			break;
		case 't':
			izvod1 = pop(&*s);
			if (izvod1->oznaka[0] == '0') {
				push(&*s, izvod1);
			}
			else {
				oprnd1 = copyTree(x->levi);
				dva = get_tree_node();
				tri = get_tree_node();
				cetiri = get_tree_node();
				pet = get_tree_node();
				sest = get_tree_node();
				dva->oznaka[0] = '/';
				dva->oznaka[1] = '\0';
				tri->oznaka[0] = '1';
				tri->oznaka[1] = '\0';
				strcpy(cetiri->oznaka, cos);
				pet->oznaka[0] = '^';
				pet->oznaka[1] = '\0';
				sest->oznaka[0] = '2';
				sest->oznaka[1] = '\0';
				dva->levi = tri;
				dva->desni = pet;
				cetiri->levi = oprnd1;
				pet->levi = cetiri;
				pet->desni = sest;
				cetiri->unary_flag = 1;
				if (izvod1->oznaka[0] == '1') {
					push(&*s, dva);
					free(izvod1);
				}
				else {
					jedan = get_tree_node();
					jedan->oznaka[0] = '*';
					jedan->oznaka[1] = '\0';
					jedan->levi = dva;
					jedan->desni = izvod1;
					push(&*s, jedan);
				}
			}
			break;
		case 'l':
			izvod1 = pop(&*s);
			if (izvod1->oznaka[0] == '0') {
				push(&*s, izvod1);
			}
			else {
				oprnd1 = copyTree(x->levi);
				jedan = get_tree_node();
				dva = get_tree_node();
				tri = get_tree_node();
				jedan->oznaka[0] = '*';
				jedan->oznaka[1] = '\0';
				dva->oznaka[0] = '/';
				dva->oznaka[1] = '\0';
				tri->oznaka[0] = '1';
				tri->oznaka[1] = '\0';
				jedan->levi = dva;
				jedan->desni = izvod1;
				dva->levi = tri;
				dva->desni = oprnd1;
				if (izvod1->oznaka[0] == '1') {
					push(&*s, dva);
					free(izvod1);
				}
				else {
					jedan = get_tree_node();
					jedan->oznaka[0] = '*';
					jedan->oznaka[1] = '\0';
					jedan->levi = dva;
					jedan->desni = izvod1;
					push(&*s, jedan);
				}
			}
			break;
		case 'm':
			izvod2 = pop(&*s);
			izvod1 = pop(&*s);
			if (izvod2->oznaka[0] == '0' && izvod1->oznaka[0] == '0' || izvod2->oznaka[0] == '1' && izvod1->oznaka[0] == '1') {
				free(izvod2);
				push(&*s, izvod1);
			}
			else {
				jedan = get_tree_node();
				jedan->levi = izvod1;
				jedan->desni = izvod2;
				jedan->min_tree = x;
				strcpy(jedan->oznaka, x->oznaka);
				push(&*s, jedan);
			}
			break;
		}
	}
}
Cvor* diff(Stablo* stb) {
	char prom;
	Cvor* next = stb->koren;
	Stack* s1 = NULL;
	Stack* s2 = NULL;
	double prvi_oprnd = 0, drugi_oprnd = 0, rez = 0;
	if (!next) {
		printf("Prvo unesite izraz!\n");
		return NULL;
	}
	else {
		printf("Unesite promenljivu po kojoj diferencirate: ");
		scanf("%c", &prom);
		do {
			while (next) {
				if (next->desni != NULL)
					push(&s1, next->desni);
				push(&s1, next);
				next = next->levi;
			}

			next = pop(&s1);

			if (next->desni && next->desni == top(s1)) {
				pop(&s1);
				push(&s1, next);
				next = next->desni;
			}
			else {
				diff_pom(next, &s2, prom);
				next = NULL;
			}
		} while (!isEmptyStack(s1));
		Cvor* izvod = pop(&s2);
		return izvod;
	}
}
int min_diff(Cvor* x, Mapa* map) {
	double left = calcExp(x->levi, map);
	double right = calcExp(x->desni, map);
	if (left <= right)
		return 1;
	else
		return 0;

}
void printTree(Cvor* root) {
	if (root == NULL) {
		printf("Prvo napravite stablo!\n");
	}
	else {
		Stack* s = NULL;
		Cvor* next = NULL;
		int cnt = 0;
		printf("Uputstvo:\n");
		printf("Otac\n\tlevi sin\n\tdesni sin\n");
		push_depth(&s, root, cnt);
		while (!isEmptyStack(s)) {
			cnt = top_depth(s);
			next = pop(&s);
			while (next != NULL) {
				for (int i = 0; i < cnt; i++) putchar('\t');
				printf("(%s)\n", next->oznaka);
				if (next->desni != NULL) {
					push_depth(&s, next->desni, cnt + 1);
				}
				cnt++;
				next = next->levi;
			}
		}
	}
}
Cvor* clone(Cvor* x) {
	Cvor* p = get_tree_node();
	strcpy(p->oznaka, x->oznaka);
	p->unary_flag = x->unary_flag;
	p->levi = x->levi;
	p->desni = x->desni;
	return p;
}
Cvor* copyTree(Cvor* root) {
	if (root == NULL) {
		return NULL;
	}
	Stack* s = NULL;
	Cvor* tmp, * cpy = clone(root);
	push(&s, cpy);
	while (!isEmptyStack(s)) {
		tmp = pop(&s);

		if (tmp->levi != NULL) {
			tmp->levi = clone(tmp->levi);
			push(&s, tmp->levi);
		}
		if (tmp->desni != NULL) {
			tmp->desni = clone(tmp->desni);
			push(&s, tmp->desni);
		}
	}
	return cpy;
}
void printPrefix(Cvor* root) {
	Stack* s = NULL;
	if (root == NULL) {
		printf("Prvo napravite stablo!\n");
	}
	else {
		int flag = 0;
		push(&s, root);
		while (!isEmptyStack(s)) {
			Cvor* next = pop(&s);
			while (next != NULL) {
				if (next->oznaka[0] == '-' && next->unary_flag == 1) {
					printf("~ ", next->oznaka);
					flag = 1;
				}
				else
					printf("%s ", next->oznaka);
				if (next->desni != NULL) {
					push(&s, next->desni);
				}
				next = next->levi;
			}
		}
		putchar('\n');
		if (flag) {
			printf("(~ = unarni minus)\n");
		}
	}
}
double calculate(double prvi, double drugi, Cvor* x, Mapa* map) {
	char c = x->oznaka[0];
	double rez = 0;
	switch (c) {
	case '+': rez = prvi + drugi; break;
	case '-': rez = prvi - drugi; break;
	case '*': rez = prvi * drugi; break;
	case '/': rez = prvi / drugi; break;
	case '^': rez = pow(prvi, drugi); break;
	case 'l': rez = log(drugi); break;
	case 't': rez = tan(drugi); break;
	case 'c': rez = cos(drugi); break;
	case 'm': 
		if (x->min_tree == NULL) {
			rez = min(prvi, drugi);
		}
		else {
			int ind = min_diff(x->min_tree, map);
			if (ind) {
				rez = prvi;
			}
			else {
				rez = drugi;
			}
		}
	}
	return rez;
}
//prebacivanje infix-a u stablo direktno pomocu dva steka
void infix_transform(Stablo** stb, Mapa* map) {
	int ipr[] = {2, 3, 5, 8, 7, 9, 1};
	int spr[] = {2, 3, 4, 8, 6, 0};
	printf("Unesite zeljeni infiksni izraz(bez razmaka):\n ");
	char* izraz = readLine();
	char* p = izraz;
	Cvor* znak, * x, * prvi_oprnd, * drugi_oprnd;
	Stack* s1 = NULL;
	Stack* s2 = NULL;
	while (*p) {
		if (isupper(*p)) {
			x = get_tree_node();
			map->flag[*p - 'A'] = 1;
			x->oznaka[0] = *p;
			x->oznaka[1] = '\0';
			push(&s1, x);
			p++;
		}
		else {
			znak = get_tree_node();
			switch (*p) {
			case 't': case 'l': strncpy(znak->oznaka, p, 2); znak->oznaka[2] = '\0'; znak->unary_flag = 1; p += 2;  break;
			case 'm': strncpy(znak->oznaka, p, 3); znak->oznaka[3] = '\0'; znak->unary_flag = 0; p += 3; break;
			default: 
				if (*p == '-') {
					if (*(p - 1) == '(') {
						znak->oznaka[0] = *p;
						znak->oznaka[1] = '\0';
						znak->unary_flag = 1;
						p++;
						break;
					}
				}
				
				znak->oznaka[0] = *p;
				znak->oznaka[1] = '\0';
				znak->unary_flag = 0;
				p++;
				
			}
			while (!isEmptyStack(s2) && ipr[find_priority(znak)] <= spr[find_priority(top(s2))]) {
				x = pop(&s2);
				if (!(x->unary_flag)) {
					drugi_oprnd = pop(&s1);
					prvi_oprnd = pop(&s1);
					x->levi = prvi_oprnd;
					x->desni = drugi_oprnd;
					push(&s1, x);
				}
				else {
					Cvor* prvi_oprnd = pop(&s1);
					x->levi = prvi_oprnd;
					push(&s1, x);
				}	
			}
			if (znak->oznaka[0] == ')') {
				x = pop(&s2);
				free(x);
			}
			if (znak->oznaka[0] == ',' || znak->oznaka[0] == ')')
				free(znak);
			else
				push(&s2, znak);
		}
	}
	while (!isEmptyStack(s2)) {
		x = pop(&s2);
		if (!(x->unary_flag)) {
			drugi_oprnd = pop(&s1);
			prvi_oprnd = pop(&s1);
			x->levi = prvi_oprnd;
			x->desni = drugi_oprnd;
			push(&s1, x);
		}
		else {
			prvi_oprnd = pop(&s1);
			x->levi = prvi_oprnd;
			push(&s1, x);
		}	
	}
	(*stb)->koren = pop(&s1);
	free(izraz);
}
void setValues(Mapa* map) {
	printf("Molim vas ucitajte vrednosti promenljivih:\n");
	for (int i = 0; i < 27; i++) {
		if (map->flag[i] == 1) {
			printf("%c?: ", i + 'A');
			scanf("%lf", &map->vr[i]);
		}
	}
}
double calcExp(Cvor* root, Mapa* map) {
	Cvor* next = root;
	Stack* s1 = NULL;
	Stack* s2 = NULL;
	double prvi_oprnd, drugi_oprnd, rez;
	if (!next) {
		printf("Prvo unesite izraz!\n");
		return -1;
	}
	else {
		do {
			while (next) {
				if (next->desni != NULL)
					push(&s1, next->desni);
				push(&s1, next);
				next = next->levi;
			}

			next = pop(&s1);

			if (next->desni && next->desni == top(s1)) {
				pop(&s1);
				push(&s1, next);
				next = next->desni;
			}
			else {
				if (isupper(next->oznaka[0])) {
					push_calc(&s2, map->vr[next->oznaka[0] - 'A']);
				}
				else if (isdigit(next->oznaka[0])) {
					push_calc(&s2, atof(next->oznaka));
				}
				else if (next->unary_flag == 0) {
					drugi_oprnd = pop_calc(&s2);
					prvi_oprnd = pop_calc(&s2);
					rez = calculate(prvi_oprnd, drugi_oprnd, next, map);
					push_calc(&s2, rez);
				}
				else {
					prvi_oprnd = pop_calc(&s2);
					rez = calculate(0, prvi_oprnd, next, map);
					push_calc(&s2, rez);
				}
				next = NULL;
			}
		} while (!isEmptyStack(s1));
		rez = pop_calc(&s2);
		return rez;
	}
}