#ifndef _lista_h_
#define _lista_h_

#include <exception>

class GNemaTekuceg : public std::exception {
public:
	GNemaTekuceg() : std::exception("*** Tekuci trenutno pokazuje na null vrednost! ***") {}
};


template <typename T>
class Lista {
	struct Elem {
		T info;
		Elem* sled;

		Elem(const T& i, Elem* s = nullptr) : info(i), sled(s) {}
	};

	Elem* prvi, * posl;
	mutable Elem* tek;

public:
	Lista() : prvi(nullptr), posl(nullptr), tek(nullptr) {}

	Lista(const Lista&) = delete;
	Lista& operator=(const Lista&) = delete;

	Lista& isprazni();

	~Lista() {
		isprazni();
	}

	Lista& dodaj(const T& t) {
		posl = (prvi ? posl->sled : prvi) = new Elem(t);
		return *this;
	}

	Lista& naPrvi() {
		tek = prvi;
		return *this;
	}

	const Lista& naPrvi() const {
		tek = prvi;
		return *this;
	}


	Lista& naSled() {
		if (tek)
			tek = tek->sled;
		return *this;
	}
	

	const Lista& naSled() const {
		if (tek)
			tek = tek->sled;
		return *this;
	}

	bool postojiTek() const {
		return tek != nullptr;
	}

	T& dohvTekInfo() {
		if (!tek) throw GNemaTekuceg();
		return tek ->info;
	}



};


#endif // !_lista_h_

template<typename T>
inline Lista<T>& Lista<T>::isprazni() {
	while (prvi) {
		Elem* brisanje = prvi;
		prvi = prvi->sled;
		delete brisanje;
	}

	posl = tek = nullptr;
	return *this;
}
