#ifndef _datum_h
#define _datum_h

#include <iostream>
using namespace std;

class Datum {
	int dan, mes, god;
public:
	Datum(int d = 1, int m = 1, int g = 2021) : dan(d), mes(m), god(g) {}

	friend bool operator==(const Datum& d1, const Datum& d2) {
		if (d1.dan == d2.dan && d1.mes == d2.mes && d1.god == d2.god)
			return true;
		else
			return false;
	}

	friend bool operator!=(const Datum& d1, const Datum& d2) {
		return !(d1 == d2);
	}

	friend ostream& operator<<(ostream& os, const Datum& d) {
		return os << d.dan << '.' << d.mes << '.' << d.god << '.';
	}
};

#endif // !_datum_h

