#include "Privilegovani.h"

void Privilegovani::pisi(ostream& os) const {
	Tim::pisi(os);
	os << "(" << min_vr << ")";
}

Privilegovani& Privilegovani::staviNaPoz(Igrac& igr, int rb) {
	if (igr.dohvVrednost() < min_vr) throw GMalaVrednost();
	if (!postava[rb]) {
		broj++;
	}
	postava[rb] = new Igrac(igr);

	return *this;
}
