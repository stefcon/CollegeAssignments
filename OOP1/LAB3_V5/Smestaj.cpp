#include "Smestaj.h"

ostream& operator<<(ostream& os, const Smestaj& s) {
	string t[] = { "HOTEL", "APARTMAN" };
	os << t[(int)s.tip] << " " << s.naziv << " ";
	for (int i = 0; i < s.br_zvezdica; ++i) os << "*";
	return os;
}
