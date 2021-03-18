#ifndef _pilot_h_
#define _pilot_h_

#include <iostream>
#include <string>

using namespace std;


class Pilot {
	string name;
	int hours;
	bool flying;
public:
	Pilot(string name, int hours, bool flying = false) : name(name), hours(hours), flying(flying) {}
	Pilot(const Pilot&) = delete;
	string get_name() const { return name; }
	int get_hours() const { return hours; }
	bool isflying() const { return flying; }

	void add_hours(int x) { hours += x; }
	void change_status(bool x) { flying = x; }
	void print() const {
		cout << name << "(" << hours << ")-";
		if (flying) cout << "L" << endl;
		else cout << "N" << endl;
	}



};
#endif // !_pilot_h_



