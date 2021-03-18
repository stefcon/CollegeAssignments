#ifndef _plane_h_
#define _plane_h_

#include "pilot.h"
#include <iostream>
#include <string>

using namespace std;

class Plane {
	string name;
	Pilot* captain = nullptr, * copilot = nullptr;
	int capacity;
public:
	Plane(string name, int capacity) : name(name), capacity(capacity) {}
	Plane(const Plane&) = delete;
	~Plane() {
		if (captain) {
			captain->change_status(false);
		}
		if (copilot) {
			copilot->change_status(false);
		}
	}

	string get_name() const { return name; }
	Pilot* get_captain() const { return captain; }
	Pilot* get_copilot() const { return copilot; }
	int get_capacity() const { return capacity; }

	void set_captain(Pilot* cap) {
		if (cap->get_hours() >= 100) {
			captain = cap;
			captain->change_status(true);
		}
		else {
			cout << "This pilot doesn't have enough hours" << endl;
		}
	}

	void set_copilot(Pilot* cop) { 
		copilot = cop; 
		copilot->change_status(true);
	}

	void print() {
		cout << "AVION:" + name + "-" << capacity << endl;
	}


};


#endif // !_plane_h_

