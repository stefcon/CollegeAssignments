#include <iostream>
#include "fleet.h"
#include "flight.h"
#include "archive.h"

int main() {
	Fleet flota("Bela Ladja");
	Plane a1("Sokol", 120), a2("Jastreb", 80), a3("Orao", 90);
	Pilot p1("Mica", 101), p2("Nebojsa", 90), p3("Simbad", 200), p4("Jakob", 300);

	a1.set_captain(&p1);
	a1.set_copilot(&p2);
	a2.set_captain(&p3);

	p1.print();

	flota.add_plane(&a1);
	flota.add_plane(&a2);
	
	flota.print();

	Flight let1("Beograd", "Pariz", &a1), let2("Budimpesta", "New York", &a3);
	Archive arc;
	arc.add_flight(&let1);
	arc.add_flight(&let2);
	arc.print();

	Fleet::Elem_F * lista = flota.get_plane_range(80, 110), * curr;
	curr = lista;
	cout << "Avioni koji pripadaju kriterijumu: " << endl;
	while (curr) {
		curr->plane->print();
		curr = curr->next;
	}

	Archive::Elem_A* lista2 = arc.dest_crit("Pariz");
	Archive::Elem_A* curr2 = lista2;
	cout << "Letovi sa dolaskom u Pariz: " << endl;
	while (curr2) {
		curr2->flight->print();
		curr2 = curr2->next;
	}


	return 0;
}