#ifndef _privilegovani_h_
#define _privilegovani_h_


#include "Tim.h"
#include <exception>

class GMalaVrednost : public exception {
public:
	GMalaVrednost() : exception("*** Igrac koji se ubacuje u tim ne ispunjava kriterijum! ***") {}
};

class Privilegovani : public Tim {
	int min_vr;
protected:

	void pisi(ostream& os) const override;

public:
	Privilegovani(string n, int kap, int m) : Tim(n, kap), min_vr(m) {}

	Privilegovani& staviNaPoz(Igrac& igr, int rb) override;
};

#endif // !_privilegovani_h_

