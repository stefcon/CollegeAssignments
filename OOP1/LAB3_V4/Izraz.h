#ifndef _izraz_h_
#define _izraz_h_

#include "Lista.h"
#include "Element.h"

class Izraz : public Lista<Element> {
public:
	Izraz() = default;
	Izraz(const Izraz& l) : Lista<Element>(l) {}
	Izraz(Izraz&& l) : Lista<Element>(std::move(l)) {}

	Izraz& operator=(const Izraz& l) {
		if (this != &l) {
			isprazni();
			kopiraj(l);
		}

		return *this;
	}


	Izraz& operator=(Izraz&& l) {
		if (this != &l) {
			isprazni();
			premesti(l);
		}

		return *this;
	}

	virtual Izraz* kopija() const {
		return new Izraz(*this);
	}
};

#endif // !_izraz_h_
