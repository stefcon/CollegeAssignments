#include "Tim.h"

void Tim::pisi(ostream& os) const {
	cout << naziv << "[";
	for (int i = 0; i < kapacitet; ++i) {
		if (postava[i]) {
			cout << *postava[i];
		}
		else {
			cout << "/";
		}
		if (i != kapacitet - 1) cout << ",";
	}
	cout << "]";
}

void Tim::kopiraj(const Tim& t) {
	postava = new Igrac * [kapacitet = t.kapacitet]{ nullptr };
	naziv = t.naziv;

	for (int i = 0; i < kapacitet; ++i) {
		if (t.postava[i]) {
			postava[i] = new Igrac(*t.postava[i]);
			broj++;
		}

		if (broj == t.broj) break;
	}
}

void Tim::premesti(Tim& t) {
	postava = t.postava;
	t.postava = nullptr;
	naziv = t.naziv;
	broj = t.broj;
	kapacitet = t.kapacitet;
}

void Tim::obrisi() {
	for (int i = 0; i < kapacitet; i++) {
		if (postava[i]) {
			delete postava[i];
			broj--;
			if (!broj) break;
		}
	}

	delete[] postava;
	postava = nullptr;
}

Tim& Tim::operator=(const Tim& t) {
	if (this != &t) {
		obrisi();
		kopiraj(t);
	}

	return *this;
}

Tim& Tim::operator=(Tim&& t) {
	if (this != &t) {
		obrisi();
		premesti(t);
	}

	return *this;
}

Tim& Tim::staviNaPoz(Igrac& igr, int rb) {
	if (!postava[rb]) {
		broj++;
	}
	postava[rb] = new Igrac(igr);

	return *this;
}

double Tim::srednjaVr() const {
	double ar = 0;
	int cnt = 0;
	for (int i = 0; i < kapacitet; ++i) {
		if (postava[i]) {
			ar += postava[i]->dohvVrednost();
			if (++cnt == broj) break;
		}
	}

	return ar / broj;
}

bool operator==(const Tim& tim1, const Tim& tim2)
{
	if (tim1.naziv == tim2.naziv && tim1.kapacitet == tim2.kapacitet && tim1.broj == tim2.broj) {
		for (int i = 0; i < tim1.kapacitet; ++i) {
			if (tim1.postava[i] && tim2.postava[i] && *tim1.postava[i] == *tim2.postava[i]) {
				continue;
			}
			else {
				return false;
			}
		}

		return true;
	}
	else {
		return false;
	}
}

ostream& operator<<(ostream& os, const Tim& tim) {
	tim.pisi(os);
	return os;
}

