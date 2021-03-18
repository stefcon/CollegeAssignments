#ifndef _desna_zagrada_h_
#define _desna_zagrada_h_

#include "Element.h"

class Desna_zagrada : public Element {
public:
	Desna_zagrada* kopija() const override {
		return new Desna_zagrada(*this);
	}

	char dohvOzn() const override { return ')'; }

	std::string dohvTekst() const override { return ")"; }
};

#endif // !_desna_zagrada_h_

