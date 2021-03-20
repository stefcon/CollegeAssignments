#ifndef _STDIO_H
#include <stdio.h>
#endif
#define SAFE_CALLOC(p, size) \
	p = calloc(size, sizeof(*p)); \
	if (!p) { \
		printf("MEM_GRESKA"); \
		exit(0); \
	} 
#define SAFE_REALLOC(p, n) \
p = realloc(p, (n) * sizeof(*p)); \
if (!p) { \
	printf("MEM_GRESKA"); \
	exit(1); \
}
#define SAFE_OPEN(name, dir, mode) \
	FILE* name = fopen(dir, mode); \
	if (!name) { \
		printf("DAT_GRESKA"); \
		exit(1); \
	}

typedef struct contact {
	char* fn, * ln, * dn, *nn, * pe, * se, * sn;
	char* wp, * hp, * fax, * pnum, * mnum, * ha1, * ha2;
	char* hcity, * hs, * hzip, * hcnt, * wa1, * wa2, * wcity;
	char* ws, * wzip, * wcnt, * jt, * dep, * org, * web1, * web2;
	char* by, * bm, * bd,* c1, * c2, * c3, *c4, * notes;
} Contact;

typedef struct node {
	Contact* c;
	struct node* prev, * next;
} Node;

Contact* loadContact(FILE* file);
void fillField(Contact* c, char* data, int cnt);
Node* formList(FILE* file);
Contact* loadContact(FILE* file);
char* specialChar(FILE* file);
void sortList(Node* head);
void makeVCard(Node* head, FILE* out);
void VCardHelp(Node* curr, FILE* out);
void freeNode(Node* n);
void freeList(Node* head);


/*First Name Last Name Display Name Nickname Primary Email Secondary Email
Screen Name Work Phone Home Phone Fax Number Pager Number Mobile
Number Home Address Home Address 2 Home City Home State Home ZipCode
Home Country Work Address Work Address 2 Work City Work State Work
ZipCode Work Country Job Title Department Organization Web Page 1 Web
Page 2 Birth Year Birth Month Birth Day Custom 1 Custom 2 Custom 3
Custom 4 Notes

	char* fn, * ln, * dn, *nn, * pe, * se, * sn;
	char* wp, * hp, * fax, * pnum, * mnum, * ha1, * ha2;
	char* hcity, * hs, * hzip, * hcnt, * wa1, * wa2, * wcity;
	char* ws, * wzip, * wcnt, * jt, * d, * o, * web1, * web2;
	char* by, * bm, * bd,* c1, * c2, * c3, *c4, * notes;*/