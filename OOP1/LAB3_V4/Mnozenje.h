#ifndef _mnozenje_h_
#define _mnozenje_h_

#include "BOperator.h"

class Mnozenje : public BOperator {
public:
	Mnozenje* kopija() const {
		return new Mnozenje(*this);
	}

	std::string dohvTekst() const override { return "*"; }

	int dohvPrioritet() const override { return 2; }
};

#endif // !_mnozenje_h_

