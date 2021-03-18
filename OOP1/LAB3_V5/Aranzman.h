#ifndef _aranzman_h_
#define _aranzman_h_

#include "Datum.h"
#include "Smestaj.h"
#include "Prevoz.h"

class GSmestajLokacija : public exception {
public:
	GSmestajLokacija() : exception("*** Dodeljen smestaj nije vezan za destinaciju aranzmana! ***") {}
};

class GPrevozLokacija : public exception {
public:
	GPrevozLokacija() : exception("*** Dodeljena lokacija nije vezana za destinaciju aranzmana! ***") {}
};

class GDohvatanjeCene : public exception {
public:
	GDohvatanjeCene() : exception("*** Pokusaj dohvatanja cene aranzmanu kome nisu dodeljeni smestaj ili prevoz ***") {}
};

class Aranzman {
	Destinacija destinacija;
	Datum pocetak, kraj;
	Smestaj* smestaj = nullptr;
	Prevoz* prevoz = nullptr;

public:
	Aranzman(const Destinacija& d, const Datum& p, const Datum& k) : destinacija(d), pocetak(p), kraj(k) {}

	Aranzman& dodeliSmestaj(Smestaj& smestaj);

	Aranzman& dodeliPrevoz(Prevoz& prevoz);

	Datum dohvPocetak() const { return pocetak; }

	Datum dohvKraj() const { return kraj; }

	Destinacija dohvDestinaciju() const { return destinacija; }

	int dohvTrajanje() const { return kraj - pocetak; }

	double dohvCenu() const { 
		if (!smestaj || !prevoz) throw GDohvatanjeCene();
		return smestaj->dohvCenu() * (pocetak - kraj) + prevoz->dohvCenu(); 
	}

	friend ostream& operator<<(ostream& os, const Aranzman& aranzman) {
		return os << aranzman.destinacija << endl << *aranzman.smestaj << endl << aranzman.dohvCenu();
	}

};

#endif // !_aranzman_h_

