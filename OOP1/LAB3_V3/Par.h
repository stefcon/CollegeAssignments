#ifndef _par_h_
#define _par_h_

#include <iostream>
using namespace std;

template<typename A, typename B>
class Par {
	A* prvi;
	B* drugi;

public:
	Par(A& p, B& d) {
		prvi = &p;
		drugi = &d;
	}

	A* dohvPrvi() { return prvi; }

	const A* dohvPrvi() const { return prvi; }

	B* dohvDrugi() { return drugi; }

	const B* dohvDrugi() const { return drugi; }

	void postaviPrvi(A* p) { prvi = p; }

	void postaviDrugi(B* d) { drugi = d; }

	friend bool operator==(const Par& p1, const Par& p2) {
		return p1.prvi == p2.prvi && p1.drugi == p2.drugi;
	}

	friend ostream& operator<<(ostream& os, const Par& p) {
		return os << "[" << *p.dohvPrvi() << "-" << *p.dohvDrugi() << "]";
	}
};


#endif // !_par_h_
