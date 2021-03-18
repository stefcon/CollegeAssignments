#include "archive.h"

Archive::Archive(const Archive& a)
{
	num = a.num;
	Elem_A* curr = first;
	Elem_A* copy = nullptr, * last = nullptr;
	while (curr) {
		copy = new Elem_A(curr->flight);
		last = (!first ? first : last->next) = copy;
		curr = curr->next;
	}
}

Archive::Archive(Archive&& a)
{
	num = a.num;
	first = a.first;
	a.first = nullptr;
}

Archive::~Archive()
{
	Elem_A* curr = first, * old;
	while (curr) {
		old = curr;
		curr = curr->next;
		delete old;
	}
}

void Archive::add_flight(Flight* f)
{
	first = new Elem_A(f, first);
	num++;
}

Archive::Elem_A* Archive::dest_crit(string d)
{
	Elem_A* flights = nullptr;
	Elem_A* curr = first, * last = nullptr;
	while (curr) {
		if (d == curr->flight->get_dest()) {
			Elem_A* copy = new Elem_A(curr->flight);
			last = (!flights ? flights : last->next) = copy;
		}
		curr = curr->next;
	}

	return flights;
}

Archive::Elem_A* Archive::start_crit(string s)
{
	Elem_A* flights = nullptr;
	Elem_A* curr = first, * last = nullptr;
	while (curr) {
		if (s == curr->flight->get_start()) {
			Elem_A* copy = new Elem_A(curr->flight);
			last = (!flights ? flights : last->next) = copy;
		}
		curr = curr->next;
	}

	return flights;
}

Archive::Elem_A* Archive::start_dest_crit(string s, string d)
{
	Elem_A* flights = nullptr;
	Elem_A* curr = first, * last = nullptr;
	while (curr) {
		if (d == curr->flight->get_dest() && s == curr->flight->get_start()) {
			Elem_A* copy = new Elem_A(curr->flight);
			last = (!flights ? flights : last->next) = copy;
		}
		curr = curr->next;
	}

	return flights;
}

void Archive::print()
{
	Elem_A* curr = first;
	cout << "ARHIVA" << endl;
	while (curr) {
		curr->flight->print();
		curr = curr->next;
	}
}
