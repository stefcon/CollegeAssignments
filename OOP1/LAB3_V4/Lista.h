#ifndef _lista_h_
#define _lista_h_

#include <iostream>
#include <exception>
using namespace std;

class GPrazna : public exception {
public:
	GPrazna() : exception("*** Lista je prazna! ***") {}
};

class GNemaTek : public exception {
public:
	GNemaTek() : exception("*** Tekuci pokazuje na null vrednost! ***") {}
};

template<typename T>
class Lista {

protected:
	struct Elem {
		T* pod;
		Elem* sled, * pret;
		Elem(T* po, Elem* pr = nullptr, Elem* sl = nullptr) : pod(po->kopija()), sled(sl), pret(pr) {}
	};

	Elem* prvi = nullptr, * posl = nullptr;
	int broj_pod = 0;

	void kopiraj(const Lista& l);

	void premesti(Lista& l) {
		prvi = l.prvi;
		posl = l.posl;
		broj_pod = l.broj_pod;
		l.prvi = nullptr;
		l.posl = nullptr;
	}

	void isprazni();

public:
	Lista() = default;
	Lista(const Lista& l) { kopiraj(l); }
	Lista(Lista&& l) { premesti(l); }

	Lista& operator=(const Lista& l) {
		if (this != &l) {
			isprazni();
			kopiraj(l);
		}

		return *this;
	}


	Lista& operator=(Lista&& l) {
		if (this != &l) {
			isprazni();
			premesti(l);
		}

		return *this;
	}

	virtual ~Lista() {
		isprazni();
	}

	//Lista& naPrvi() {
	//	tek = prvi;
	//	return *this;
	//}

	//Lista& naSled() {
	//	if (tek) tek = tek->sled;
	//	return *this;
	//}

	//Lista& naPret() {
	//	if (tek) tek = tek->pret;
	//	return *this;
	//}

	//bool imaTek() const {
	//	return tek != nullptr;
	//}

	//T& dohvTek() {
	//	if (!tek) throw GNemaTek();
	//	return tek->pod;
	//}

	Lista& operator+=(T* podatak) {
		if (!prvi) {
			prvi = new Elem(podatak);
			posl = prvi;
		}
		else {
			posl->sled = new Elem(podatak, posl);
			posl = posl->sled;
		}
		broj_pod++;

		return *this;
	}

	T* operator-() {
		if (!prvi) throw GPrazna();

		T* podatak = posl->pod;
		Elem* staro = posl;
		posl = posl->pret;
		delete staro;

		broj_pod--;
		if (broj_pod == 0) prvi = posl = nullptr;
		else posl->sled = nullptr;

		return podatak;
	}

	T* operator*() {
		if (!prvi) throw GPrazna();

		T* podatak = prvi->pod;
		Elem* staro = prvi;
		prvi = prvi->sled;
		delete staro;

		broj_pod--;
		if (broj_pod == 0) prvi = posl = nullptr;
		else prvi->pret = nullptr;

		return podatak;
	}

	T* vidiPrvi() {
		if (!prvi) return nullptr;
		return prvi->pod;
	}

	T* vidiPosl() {
		if (!posl) return nullptr;
		return posl->pod;
	}

	int dohvBrojPod() const { return broj_pod; }

	friend ostream& operator<<(ostream& os, const Lista& l) {
		Elem* curr = l.prvi;
		while (curr) {
			os << *curr->pod;
			if (curr != l.posl) os << " ";
			curr = curr->sled;
		}
		return os;
	}

};

#endif // !_lista_h_

template<typename T>
inline void Lista<T>::kopiraj(const Lista& l) {
	prvi = posl = nullptr;
	broj_pod = 0;
	for (Elem* pok = l.prvi; pok; pok = pok->sled) {
		Elem* novi = new Elem(pok->pod);
		if (!prvi) {
			prvi = posl = novi;
		}
		else {
			posl->sled = novi;
			novi->pret = posl;
			posl = posl->sled;
		}
		broj_pod++;
	}
}

template<typename T>
inline void Lista<T>::isprazni() {
	while (prvi) {
		Elem* staro = prvi;
		prvi = prvi->sled;
		delete staro->pod;
		delete staro;
	}

	broj_pod = 0;
	posl = nullptr;
}
