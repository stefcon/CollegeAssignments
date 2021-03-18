#include "Racun.h"

void Racun::pisi(ostream& os) const {
	os << "R:" << broj_racuna << ":=" << iznos << "-" << dohvOznaku();
}

bool Racun::prenesi(int vr, Racun& odrediste) {
	if (iznos - vr < 0) {
		return false;
	}
	else {
		*this += -vr;
		odrediste += vr;
		return true;
	}

}

Racun& Racun::operator+=(int iznos) {
	this->iznos += iznos;
	return *this;
}
