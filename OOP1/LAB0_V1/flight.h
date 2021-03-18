#ifndef _flight_h_
#define _flight_h_

#include "fleet.h"
#include <iostream>

using namespace std;

class Flight {
	static int id_class;
	string start, dest;
	int id;
	Plane* plane;
public:
	Flight(string s, string d, Plane* p) : start(s), dest(d), plane(p) {
		id = ++id_class;
	}
	Flight(const Flight&);
	Flight(Flight&&);

	string get_start() const { return start; }
	string get_dest() const { return dest; }
	int get_id() const { return id; }
	Plane* get_plane() const { return plane; }
	void print() const;
};


#endif // !_flight_h_

