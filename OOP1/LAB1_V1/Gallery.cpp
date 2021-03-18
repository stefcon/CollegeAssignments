#include "Gallery.h"

Gallery::Gallery(const Gallery& g) {
	copy(g);
}

Gallery::Gallery(Gallery&& g) {
	move(g);
}

Gallery::~Gallery() {
	clear();
}

Gallery& Gallery::operator=(const Gallery& g) {
	if (this != &g) {
		clear();
		copy(g);
	}
	return *this;
}

Gallery& Gallery::operator=(Gallery&& g) {
	if (this != &g) {
		clear();
		move(g);
	}
	return *this;
}

int Gallery::getPictureSize() const {
	int total = 0;

	Elem* curr = head;
	while (curr) {
		total += curr->picture->getSize();
	}

	return total;
}

Gallery& Gallery::operator+=(const Picture& p) {
	((head)? tail->next : head) = new Elem(new Picture(p));
	if (tail == nullptr) tail = head;
	else tail = tail->next;
	num++;
	return *this;
}

Picture& Gallery::operator[](int ind) {
	if (ind > num - 1) exit(1);
	Elem* curr = head;
	while (ind) {
		ind--;
		curr = curr->next;
	}

	return *curr->picture;
}

void Gallery::copy(const Gallery& g) {
	Elem* curr = g.head;

	while (curr) {
		if (head == nullptr) {
			head = new Elem(new Picture(*curr->picture));
			tail = head;
		}
		else {
			tail->next = new Elem(new Picture(*curr->picture));
			tail = tail->next;
		}

		curr = curr->next;
	}

	num = g.num;
}

void Gallery::move(Gallery& g) {
	num = g.num;
	head = g.head;
	tail = g.tail;
	g.head = nullptr;
	g.tail = nullptr;
}

void Gallery::clear() {
	while (head) {
		Elem* old = head; 
		head = head->next;
		delete old;
	}
	tail = nullptr;
	num = 0;
}

std::ostream& operator<<(std::ostream& os, const Gallery& gal) {
	Gallery::Elem* curr = gal.head;
	while (curr) {
		os << *curr->picture << endl;
		curr = curr->next;
	}
	return os;
}
