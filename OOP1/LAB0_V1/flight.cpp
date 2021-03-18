#include "flight.h"

int Flight::id_class = 0;

Flight::Flight(const Flight& f)
{
	start = f.start;
	dest = f.dest;
	id = ++id_class;
	plane = f.plane;
}

Flight::Flight(Flight&& f)
{
	start = f.start;
	dest = f.dest;
	id = ++id_class;
	plane = f.plane;
	f.plane = nullptr;
}

void Flight::print() const
{
	cout << "LET-" << start << ":" << dest << "-";
	plane->print();
}
