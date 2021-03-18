#ifndef _fleet_h_
#define _fleet_h_

#include "pilot.h"
#include "plane.h"
#include <iostream>

using namespace std;

class Fleet {
public:
	struct Elem_F {
		Plane* plane;
		Elem_F* next;

		Elem_F(Plane* p, Elem_F* nxt = nullptr) : plane(p), next(nxt) {}
	};
	Fleet(string name) : name(name) {}
	Fleet(const Fleet& f) {
		name = f.name;
		size = f.size;
		Elem_F* curr = first;
		Elem_F* copy = nullptr, * last = nullptr;
		while (curr) {
			copy = new Elem_F(curr->plane);
			last = (!first ? first : last->next) = copy;
			curr = curr->next;
		}
	}

	Fleet(Fleet&& f) {
		name = f.name;
		size = f.size;
		first = f.first;
		f.first = nullptr;
	}

	~Fleet() {
		Elem_F* curr = first, * old;
		while (curr) {
			old = curr;
			curr = curr->next;
			delete old;
		}
	}

	void add_plane(Plane* p) {
		first = new Elem_F(p, first);
		size++;
	}

	int get_size() const { return size; }

	int get_capacity() const {
		Elem_F* curr = first;
		int cap = 0;
		while (curr) {
			cap += curr->plane->get_capacity();
		}
		return cap;
	}

	Plane* biggest_plane() const {
		int maximum = first->plane->get_capacity();
		Plane* biggest = first->plane;
		for (Elem_F* curr = first; curr; curr = curr->next) {
			if (curr->plane->get_capacity() > maximum) {
				biggest = curr->plane;
			}
		}

		return biggest;
	}

	void print() {
		cout << name + ":" << endl;
		for (Elem_F* curr = first; curr; curr = curr->next) {
			curr->plane->print();
		}
	}

	void remove_plane(string name);
	Elem_F* get_plane_range(int mini, int maxi);
private:
	string name;
	int size = 0;
	Elem_F* first = nullptr;
};

#endif // !_fleet_h_

