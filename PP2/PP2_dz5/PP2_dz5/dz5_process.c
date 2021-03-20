#include "dz5.h"
#include <stdlib.h>
#include <string.h.>

void sortList(Node* head) {
	for (Node* p = head; p; p = p->next) {
		for (Node* q = p->next; q; q = q->next) {
			if (strcmp(p->c->pe, q->c->pe) > 0) {
				Contact* tmp = p->c;
				p->c = q->c;
				q->c = tmp;
			}
		}
	}
}

void freeList(Node* head) {
	while (head) {
		Node* old = head;
		head = head->next;
		freeNode(old);
	}
}

void freeNode(Node* n) {
	free(n->c->fn);
	free(n->c->ln);
	free(n->c->dn);
	free(n->c->nn);
	free(n->c->pe);
	free(n->c->se);
	free(n->c->sn);
	free(n->c->wp);
	free(n->c->hp);
	free(n->c->fax);
	free(n->c->pnum);
	free(n->c->mnum);
	free(n->c->ha1);
	free(n->c->ha2);
	free(n->c->hcity);
	free(n->c->hs);
	free(n->c->hzip);
	free(n->c->hcnt);
	free(n->c->wa1);
	free(n->c->wa2);
	free(n->c->wcity);
	free(n->c->ws);
	free(n->c->wzip);
	free(n->c->wcnt);
	free(n->c->jt);
	free(n->c->dep);
	free(n->c->org);
	free(n->c->web1);
	free(n->c->web2);
	free(n->c->by);
	free(n->c->bm);
	free(n->c->bd);
	free(n->c->c1);
	free(n->c->c2);
	free(n->c->c3);
	free(n->c->c4);
	free(n->c->notes);
	free(n->c);
	free(n);
}