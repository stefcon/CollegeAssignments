#ifndef _dinarski_racun_h_
#define _dinarski_racun_h_

#include "Racun.h"

class Dinarski_racun : public Racun {
public:
	Dinarski_racun(Osoba& v, int br) : Racun(v, br) {}

	string dohvOznaku() const override {
		return "RSD";
	}
};


#endif // !_dinarski_racun_h_

