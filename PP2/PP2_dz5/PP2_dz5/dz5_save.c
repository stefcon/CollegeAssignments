#include <stdio.h>
#include <string.h>
#include "dz5.h"

void VCardHelp(Node* curr, FILE* out) {
	//org
	if (strlen(curr->c->org)) {
		fprintf(out, "org:%s", curr->c->org);
		if (strlen(curr->c->dep)) {
			fprintf(out, ";%s\n", curr->c->dep);
		}
		else {
			fputc('\n', out);
		}
	}
	//adr
	if (strlen(curr->c->wa1)) {
		fprintf(out, "adr:;;%s", curr->c->wa1);
		if (strlen(curr->c->wcnt)) {
			fprintf(out, ";%s;%s;%s;%s\n", curr->c->wcity, curr->c->ws, curr->c->wzip, curr->c->wcnt);
		}
		else if (strlen(curr->c->wzip)) {
			fprintf(out, ";%s;%s;%s\n", curr->c->wcity, curr->c->ws, curr->c->wzip);
		}
		else if (strlen(curr->c->ws)) {
			fprintf(out, ";%s;%s\n", curr->c->wcity, curr->c->ws);
		}
		else if (strlen(curr->c->wcity)) {
			fprintf(out, ";%s\n", curr->c->wcity);
		}
		else {
			fputc('\n', out);
		}
	}
	//email
	if (strlen(curr->c->pe)) {
		fprintf(out, "email;internet:%s\n", curr->c->pe);
	}
	//title
	if (strlen(curr->c->jt)) {
		fprintf(out, "title:%s\n", curr->c->jt);
	}
	//tel: work, fax, pager, home, cell
	if (strlen(curr->c->wp)) {
		fprintf(out, "tel;work:%s\n", curr->c->wp);
	}
	if (strlen(curr->c->fax)) {
		fprintf(out, "tel;fax:%s\n", curr->c->fax);
	}
	if (strlen(curr->c->pnum)) {
		fprintf(out, "tel;pager:%s\n", curr->c->pnum);
	}
	if (strlen(curr->c->hp)) {
		fprintf(out, "tel;home:%s\n", curr->c->hp);
	}
	if (strlen(curr->c->mnum)) {
		fprintf(out, "tel;cell:%s\n", curr->c->mnum);
	}
	//note
	if (strlen(curr->c->notes)) {
		fprintf(out, "note:%s\n", curr->c->notes);
	}
	//url
	if (strlen(curr->c->web1)) {
		fprintf(out, "url:%s\n", curr->c->web1);
	}
}

void makeVCard(Node* head, FILE* out) {
	Node* current = head;
	while (current != NULL) {
		if (current == head) {
			fprintf(out, "begin:vcard\n");
		}
		else {
			fprintf(out, "\nbegin:vcard\n");
		}
		fprintf(out, "fn:%s\n", current->c->dn);
		fprintf(out, "n:%s;%s\n", current->c->ln, current->c->fn);
		VCardHelp(current, out);
		fprintf(out, "version:2.1\n");
		fprintf(out, "end:vcard\n");
		current = current->next;
	}
}