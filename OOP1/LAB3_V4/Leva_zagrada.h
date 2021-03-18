#ifndef _leva_zagrada_h_
#define _leva_zagrada_h_

#include "Element.h"

class Leva_zagrada : public Element {
public:
	Leva_zagrada* kopija() const override {
		return new Leva_zagrada(*this);
	}

	char dohvOzn() const override { return '('; }

	std::string dohvTekst() const override { return "("; }
};

#endif // !_leva_zagrada_h_

