#include "Notice_list.h"

Notice_list::Notice_list() {
	head = nullptr;
	num = 0;
}

Notice_list::~Notice_list() {
	while (head) {
		ListNode* old = head;
		head = head->next;
		delete old;
	}
}

Notice_list& Notice_list::operator+=(Notice& n) {
	ListNode* tmp = new ListNode(&n, head);
	head = tmp;
	num++;
	return *this;
}

void Notice_list::operator()() {
	bool exist = false;

	for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
		if (!curr->notice->isRead()) {
			cout << curr->notice;
			exist = true;
		}
	}

	if (!exist) {
		cout << "Sva obavestenja iz liste su procitana!" << endl;
	}
}

int Notice_list::operator+() {
	int cnt = 0;

	for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
		if (!curr->notice->isRead()) {
			cnt++;
		}
	}

	return cnt;
}

void Notice_list::operator!() {
	for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
		curr->notice->Read();
	}
}

Notice* Notice_list::operator[](int id) {
	for (ListNode* curr = head; curr != nullptr; curr = curr->next) {
		if (curr->notice->getId() == id && curr->notice->isRead() == false)
			return curr->notice;
	}

	return nullptr;
}

ostream& operator<<(ostream& os, const Notice_list& n_l) {
	if (!n_l.head) {
		os << "Lista je prazna!" << endl;
	}

	for (Notice_list::ListNode* curr = n_l.head; curr != nullptr; curr = curr->next) {
		os << *curr->notice << endl;
	}
	return os;
}
