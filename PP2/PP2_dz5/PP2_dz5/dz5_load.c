#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dz5.h"

void fillField(Contact* c, char* data, int cnt) {
	switch (cnt)
	{
	case 1: c->fn = data; break;
	case 2: c->ln = data; break;
	case 3: c->dn = data; break;
	case 4: c->nn = data; break;
	case 5: c->pe = data; break;
	case 6: c->se = data; break;
	case 7:	c->sn = data; break;
	case 8: c-> wp = data; break;
	case 9: c->hp = data; break;
	case 10: c->fax = data; break;
	case 11: c->pnum = data; break;
	case 12: c->mnum = data; break;
	case 13: c->ha1 = data; break;
	case 14: c->ha2 = data; break;
	case 15: c->hcity = data; break;
	case 16: c->hs = data; break;
	case 17: c->hzip = data; break; 
	case 18: c->hcnt = data; break;
	case 19: c->wa1 = data; break;
	case 20: c->wa2 = data; break;
	case 21: c->wcity = data; break;
	case 22: c->ws = data; break;
	case 23: c->wzip = data; break;
	case 24: c->wcnt = data; break;
	case 25: c->jt = data; break;
	case 26: c->dep = data; break;
	case 27: c->org = data; break;
	case 28: c->web1 = data; break;
	case 29: c->web2 = data; break;
	case 30: c->by = data; break; 
	case 31: c->bm = data; break;
	case 32: c->bd = data; break;
	case 33: c->c1 = data; break;
	case 34: c->c2 = data; break;
	case 35: c->c3 = data; break;
	case 36: c->c4 = data; break;
	case 37: c->notes = data; break;
	}
}

Node* formList(FILE* file) {
	Node* head = NULL, * tail = head, * tmp;
	Contact* contact;
	while ((contact = loadContact(file)) != NULL) {
		SAFE_CALLOC(tmp, 1);
		SAFE_CALLOC(tmp->c, 1);
		*tmp->c = *contact;
		free(contact);
		tmp->next = tmp->prev = NULL;
		if (head == NULL) {
			head = tmp;
		}
		else {
			tmp->prev = tail;
			tail->next = tmp;
		}
		tail = tmp;
	}
	return head;
}
char* specialChar(FILE* file) {
	char* data = NULL;
	int size = 0;
	char c1, c2;
	while (1) {
		c1 = fgetc(file);
		if (c1 == '"') {
			c2 = fgetc(file);
			if (c2 == '\t') {
				break;
			}
			else {
				SAFE_REALLOC(data, size + 2);
				data[size++] = c1;
				data[size++] = c2;
			}
		}
		else {
			SAFE_REALLOC(data, size + 1);
			data[size++] = c1;
		}
	}
	SAFE_REALLOC(data, size + 1);
	data[size] = '\0';

	return data;
}


Contact* loadContact(FILE* file) {
	Contact* contact;
	SAFE_CALLOC(contact, 1);
	int size, num = 1, flag = 0;
	char c, * data = NULL;
	c = fgetc(file);
	while (c  != '\n' && c != EOF) {
		flag = 1;
		if (c == '"') {
			data = specialChar(file);
			char* tmp;
			SAFE_CALLOC(tmp, strlen(data) + 1);
			strcpy(tmp, data);
			fillField(contact, tmp, num);
			num++;
		}
		else {
			size = 0;
			while (c != '\t') {
				SAFE_REALLOC(data, size + 1);
				data[size++] = c;
				c = fgetc(file);
			}
			SAFE_REALLOC(data, size + 1);
			data[size++] = '\0';
			char* tmp;
			SAFE_CALLOC(tmp, strlen(data) + 1);
			strcpy(tmp, data);
			fillField(contact, tmp, num);
			num++;
		}
		c = fgetc(file);
		free(data);
		data = NULL;
	}
	if (num == 1) {
		free(contact);
		return NULL;
	}
	else {
		return contact;
	}
}

