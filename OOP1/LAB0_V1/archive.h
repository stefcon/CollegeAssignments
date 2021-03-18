#ifndef _archive_h_
#define _archive_h_

#include "fleet.h"
#include "flight.h"

using namespace std;

class Archive {
public:
	struct Elem_A {
		Flight* flight;
		Elem_A* next;

		Elem_A(Flight* f, Elem_A* n = nullptr) : flight(f), next(n) {}
	};
	Archive() : num(0), first(nullptr) {}
	Archive(const Archive&);
	Archive(Archive&&);
	~Archive();

	void add_flight(Flight* f);
	Elem_A* dest_crit(string d);
	Elem_A* start_crit(string s);
	Elem_A* start_dest_crit(string s, string d);
	void print();
private:
	int num = 0;
	Elem_A* first = nullptr;
};

#endif // !_archive_h_

