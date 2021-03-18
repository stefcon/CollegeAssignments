#ifndef _racun_h_
#define _racun_h_

#include "Osoba.h"

class Racun {
	Osoba& vlasnik;
	int iznos = 0, broj_racuna;
protected:

	virtual void pisi(ostream& os) const;

public:
	
	Racun(Osoba& v, int br) : vlasnik(v), broj_racuna(br) {}

	Racun(const Racun&) = delete;
	Racun& operator=(const Racun&) = delete;

	virtual ~Racun() {}

	Osoba& dohvVlasnika() { return vlasnik; }

	const Osoba& dohvVlasnika() const { return vlasnik; }

	int dohvIznos() const { return iznos; }

	int dohvBrRacuna() const { return broj_racuna; }

	virtual string dohvOznaku() const = 0;

	bool prenesi(int vr, Racun& odrediste);

	Racun& operator+=(int iznos);

	friend ostream& operator<<(ostream& os, const Racun& r) {
		r.pisi(os);
		return os;
	}

};

#endif // !_racun_h_

