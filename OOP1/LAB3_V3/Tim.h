#ifndef _tim_h_
#define _tim_h_

#include "Igrac.h"

class Tim {
protected:
	string naziv;
	int kapacitet, broj = 0;
	Igrac** postava;

	virtual void pisi(ostream& os) const;

	void kopiraj(const Tim& t);
	void premesti(Tim& t);
	void obrisi();

public:
	Tim(string n, int kap) : naziv(n), kapacitet(kap) {
		postava = new Igrac*[kapacitet] {nullptr};
	}
	
	Tim(const Tim& t) {
		kopiraj(t);
	}

	Tim(Tim&& t) {
		premesti(t);
	}

	Tim& operator=(const Tim& t);

	Tim& operator=(Tim&& t);

	virtual ~Tim() {
		obrisi();
	}

	int dohvBroj() const { return broj; }

	virtual Tim& staviNaPoz(Igrac& igr, int rb);

	Igrac* operator[](int rb) {
		return postava[rb];
	}

	const Igrac* operator[](int rb) const {
		return postava[rb];
	}

	double srednjaVr() const;

	friend bool operator==(const Tim& tim1, const Tim& tim2);

	friend ostream& operator<<(ostream& os, const Tim& tim);

};

#endif // !_tim_h_

